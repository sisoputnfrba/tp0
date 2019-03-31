/*
 * Resolucion TP0
 *
 * Buenas! A diferencia de la resolucion que hicimos en las charlas,
 * esta resolucion les va a presentar una mejora en buenas practicas de programacion.
 * Dado que no queriamos abrumarlos durante el Workshops, nos tomamos un par de licencias
 * de hacer codigo "feo" y poco mantenible.
 *
 * Por lo tanto, esta resolucion plantea tambien otra forma de resolverlo, cambiando la
 * estructura del esqueleto que ustedes tienen.
 *
 * Espero que le saquen provecho a esta implementacion, comparandola no solo en funcionalidades
 * con las suyas, sino que tambien a nivel disenioo y saquen sus propias conclusiones :).
 *
 * Saludos!
 *
 * Nota: Sacamos todos los caracteres especiales para que se vea simpre bien :P
 */

#include "tp0.h"

int main(void) {
	// PARTE 2
	t_log* logger = iniciar_logger();
	log_info(logger, "Soy un log");

	t_config* config = leer_config();
	char* valor = config_get_string_value(config, "CLAVE");
	log_info(logger, valor);

	leer_consola(logger);

	// PARTE 3
	char* ip = config_get_string_value(config, "IP");
	char* puerto = config_get_string_value(config, "PUERTO");

	int conexion = crear_conexion(ip, puerto);

	enviar_mensaje(valor, conexion);

	t_paquete* paquete = armar_paquete();

	enviar_paquete(paquete, conexion);

	// Viejo terminar programa
	eliminar_paquete(paquete);
	log_destroy(logger);
	config_destroy(config);
	close(conexion);
}

t_log* iniciar_logger() {
	return log_create("tp0.log", "TP0", 1, LOG_LEVEL_INFO);
}

t_config* leer_config() {
	return config_create("tp0.config");
}

t_paquete* armar_paquete() {
	t_paquete* paquete = crear_paquete();

	void _agregar(char* leido) {
		agregar_a_paquete(paquete, leido, strlen(leido) + 1);
	}

	_leer_consola_haciendo((void*) _agregar);

	return paquete;
}

void leer_consola(t_log* logger) {
	void loggear(char* leido) {
		log_info(logger, leido);
	}

	_leer_consola_haciendo((void*) loggear);
}


void _leer_consola_haciendo(bool(*accion)(char*)) {
	char* leido;

	//El primero te lo dejo de yapa
	leido = readline(">");

	while(strncmp(leido, "", 1) != 0) {
		accion(leido);
		free(leido);
		leido = readline(">");
	}

	free(leido);
}
