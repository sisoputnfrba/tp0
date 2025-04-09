#include"utils.h"

t_log* logger;

int iniciar_servidor(void)
{
	int socket_servidor;

	struct addrinfo hints, *serv_info, *p;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, "4444", &hints, &serv_info);

	// Creamos el socket de escucha del servidor
	// O sea, creamos el file descriptor (fd)
	socket_servidor = socket( serv_info->ai_family, serv_info->ai_socktype, serv_info->ai_protocol);

	// Asociamos el socket a un puerto
	setsockopt(socket_servidor, SOL_SOCKET, SO_REUSEPORT, &(int){1}, sizeof(int));
	// Toma el socket y le pido al sistema operativo que lo asocie al puerto
	bind(socket_servidor, serv_info->ai_addr, serv_info->ai_addrlen);

	// Escuchamos las conexiones entrantes
	// Toma ese mismo socket y lo marca en el sistema como un socket cuya única responsabilidad es notificar cuando un nuevo cliente esté intentando conectarse
	listen(socket_servidor, SOMAXCONN);

	freeaddrinfo(serv_info);
	log_trace(logger, "Listo para escuchar a mi cliente");

	return socket_servidor;
}

int esperar_cliente(int socket_servidor)
{
	struct sockaddr_in dir_cliente;
	socklen_t tam_direccion = sizeof(struct sockaddr_in);

	int socket_cliente = accept(socket_servidor, (struct sockaddr*) &dir_cliente, &tam_direccion);

	if (socket_cliente == -1) {
		log_error(logger, "Error al aceptar cliente");
		return -1;
	}

	log_info(logger, "Se conectó un cliente!");

	return socket_cliente;
}


int recibir_operacion(int socket_cliente)
{
	int cod_op;
	if(recv(socket_cliente, &cod_op, sizeof(int), MSG_WAITALL) > 0)
		return cod_op;
	else
	{
		close(socket_cliente);
		return -1;
	}
}

void* recibir_buffer(int* size, int socket_cliente)
{
	void * buffer;

	recv(socket_cliente, size, sizeof(int), MSG_WAITALL);
	buffer = malloc(*size);
	recv(socket_cliente, buffer, *size, MSG_WAITALL);

	return buffer;
}

void recibir_mensaje(int socket_cliente)
{
	int size;
	char* buffer = recibir_buffer(&size, socket_cliente);
	log_info(logger, "Me llego el mensaje %s", buffer);
	printf("Me llego esto : %s",buffer);
	free(buffer);
}

t_list* recibir_paquete(int socket_cliente)
{
	int size;
	int desplazamiento = 0;
	void * buffer;
	t_list* valores = list_create();
	int tamanio;

	buffer = recibir_buffer(&size, socket_cliente);
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
}
