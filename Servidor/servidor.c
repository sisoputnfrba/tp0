/*
 * servidor.c
 *
 *  Created on: 3 mar. 2019
 *      Author: utnso
 */

#include "servidor.h"

int main(void)
{
	void iterator(char* value)
	{
		printf("%s\n", value);
	}

	logger = log_create("log.log", "Servidor", 1, LOG_LEVEL_DEBUG);

	iniciar_servidor();
	esperar_cliente();

	t_list* lista;
	while(1)
	{
		int cod_op = recibir_operacion();
		switch(cod_op)
		{
		case MENSAJE:
			recibir_mensaje();
			break;
		case PAQUETE:
			lista = recibir_paquete();
			printf("Me llegaron los siguientes valores:\n");
			list_iterate(lista, (void*) iterator);
			break;
		}
	}
}
