/*
 * conexiones.h
 *
 *  Created on: 2 mar. 2019
 *      Author: utnso
 */

#ifndef CONEXIONES_H_
#define CONEXIONES_H_

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>

typedef enum
{
	MENSAJE,
	PAQUETE
}op_code;

typedef struct
{
	int size;
	void* stream;
} t_buffer;

typedef struct
{
	op_code codigo_operacion;
	t_buffer* buffer;
} t_paquete;

static int g_socket_cliente;

static void segfault_handler();
static void* serializar_paquete(t_paquete*, int);

extern void iniciar_cliente(void);
extern void conectar_cliente(char* ip, char* puerto);
extern void enviar_mensaje(char* mensaje);
extern t_paquete* crear_paquete(void);
extern void agregar_a_paquete(t_paquete* paquete, void* valor, int tamanio);
extern void enviar_paquete(t_paquete* paquete);
extern void terminar_cliente(void);

#endif /* CONEXIONES_H_ */
