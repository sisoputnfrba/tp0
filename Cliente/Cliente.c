/*
 * main.c
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#include"Cliente.h"

int main(int argc, char** argv)
{
	iniciar_cliente();

	//Para hablar de consola y los parametros del main!
	t_config* archivo_config = config_create(argv[1]);
	t_log* logger = log_create("logs.log", "Cliente", 1, LOG_LEVEL_DEBUG);

	char* nombre = config_get_string_value(archivo_config, "NOMBRE");
	log_info(logger, "abri el archivo %s exitosamente", nombre);

	char* ip = config_get_string_value(archivo_config, "IP");
	char* puerto = config_get_string_value(archivo_config, "PUERTO");


	conectar_cliente(ip, puerto);


	char *clave = NULL, *valor = NULL;

	clave = readline(">");

	//levantar claves con readline del archivo y que el servidor muestre los valores de a uno
	while(clave[0] != '0')
	{
		valor = config_get_string_value(archivo_config, clave);
		enviar_mensaje(valor);
		free(clave);
		clave = readline(">");
	}

	free(clave);


	//crear_paquete() hace un malloc de t_paquete. La idea es que el malloc no este, tire seg fault y ahi empezar a hablar del debugger y el malloc
	t_paquete* paquete = crear_paquete();


	//datos pa probar. Aca podria ir otro bucle que levante claves.
	agregar_a_paquete(paquete, "Mauro", 6);
	agregar_a_paquete(paquete, "Sofia", 6);
	agregar_a_paquete(paquete, "Hernan", 7);
	agregar_a_paquete(paquete, "Alf", 4);

	enviar_paquete(paquete);

	terminar_cliente();
	config_destroy(archivo_config);
	log_destroy(logger);
}
