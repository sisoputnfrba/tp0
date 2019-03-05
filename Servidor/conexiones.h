/*
 * conexiones.h
 *
 *  Created on: 3 mar. 2019
 *      Author: utnso
 */

#ifndef CONEXIONES_H_
#define CONEXIONES_H_

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/log.h>
#include<commons/collections/list.h>
#include<string.h>

#define IP "127.0.0.1"
#define PUERTO "4444"

typedef enum
{
	MENSAJE,
	PAQUETE
}op_code;

static int g_socket_servidor;
static int g_socket_cliente;
t_log* logger;

static void* recibir_buffer(int*);

extern void iniciar_servidor(void);
extern void esperar_cliente(void);
t_list* recibir_paquete(void);
extern void recibir_mensaje(void);
extern int recibir_operacion(void);

#endif /* CONEXIONES_H_ */
