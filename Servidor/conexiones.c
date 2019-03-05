/*
 * conexiones.c
 *
 *  Created on: 3 mar. 2019
 *      Author: utnso
 */

#include"conexiones.h"

extern void iniciar_servidor(void)
{
    struct addrinfo hints, *servinfo, *p;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(IP, PUERTO, &hints, &servinfo);

    for (p=servinfo; p != NULL; p = p->ai_next)
    {
        if ((g_socket_servidor = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
            continue;

        if (bind(g_socket_servidor, p->ai_addr, p->ai_addrlen) == -1) {
            close(g_socket_servidor);
            continue;
        }
        break;
    }

	listen(g_socket_servidor, SOMAXCONN);

    freeaddrinfo(servinfo);

    log_trace(logger, "Listo para escuchar a mi cliente");
}

extern void esperar_cliente(void)
{
	struct sockaddr_in dir_cliente;
	int tam_direccion = sizeof(struct sockaddr_in);

	g_socket_cliente = accept(g_socket_servidor, (void*) &dir_cliente, &tam_direccion);

	log_info(logger, "Se conecto un cliente!");
}

extern int recibir_operacion(void)
{
	int cod_op;
	if(recv(g_socket_cliente, &cod_op, sizeof(int), MSG_WAITALL) != 0)
		return cod_op;
	else
	{
		log_warning(logger, "el cliente se desconecto. Terminando servidor");
		close(g_socket_cliente);
		exit(0);
	}
}

static void* recibir_buffer(int* size)
{
	void * buffer;

	recv(g_socket_cliente, size, sizeof(int), MSG_WAITALL);
	buffer = malloc(*size);
	recv(g_socket_cliente, buffer, *size, MSG_WAITALL);

	return buffer;
}

extern void recibir_mensaje(void)
{
	int size;
	char* buffer = recibir_buffer(&size);
	log_info(logger, "Me llego el mensaje %s", buffer);
	free(buffer);
}

//podemos usar la lista de valores para poder hablar del for y de como recorrer la lista
t_list* recibir_paquete(void)
{
	int size;
	int desplazamiento = 0;
	void * buffer;
	t_list* valores = list_create();
	int tamanio;

	buffer = recibir_buffer(&size);
	while(desplazamiento < size)
	{
		memcpy(&tamanio, buffer + desplazamiento, sizeof(int));
		desplazamiento+=sizeof(int);
		char* valor = malloc(tamanio);
		memcpy(valor, buffer+desplazamiento, tamanio);
		desplazamiento+=tamanio;
		list_add(valores, valor);
	}
	free(buffer);
	return valores;
	return NULL;
}
