/*
 * Resolucion 2 del TP0 [Dificultad Media]
 *
 * Buenas! A diferencia de la resolucion que hicimos en las charlas,
 * esta resolucion les va a presentar una mejora en buenas practicas de programacion.
 * Dado que no queriamos abrumarlos durante el Workshops, nos tomamos un par de licencias
 * de hacer codigo "feo" y poco mantenible.
 *
 * Por lo tanto, esta resolucion plantea tambien otra forma de resolverlo, cambiando la
 * estructura del esqueleto que ustedes tienen.
 * Cosas que se cambiaron:
 * - Se evitaron las variables globales que, como mencionamos en la charla, generan problemas
 * de mantenibilidad y estabilidad del código.
 * - Hay transparencia referencial.
 * - Evitamos comparar strings en funcion de sus caracteres: Usamos funciones de la biblioteca
 * standard para trabajar strings: strncmp.
 * - Organizacion del codigo y eliminacion de variables innecesarias.
 *
 * Espero que le saquen provecho a esta implementacion, comparandola no solo en funcionalidades
 * con las suyas, sino que tambien a nivel disenio y saquen sus propias conclusiones :).
 *
 * Saludos!
 *
 * Nota: Sacamos todos los caracteres especiales para que se vea simpre bien :P
 */

#include "cliente.h"

int main(void) {
	// PARTE 2
	t_log* logger = iniciar_logger();
	log_info(logger, "Soy un log");

	t_config* config = leer_config();
	char* valor = config_get_string_value(config, "CLAVE");
	log_info(logger, valor);

	leer_consola(logger);

	// PARTE 3
	int conexion = crear_conexion(
		config_get_string_value(config, "IP"),
		config_get_string_value(config, "PUERTO")
	);

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

void leer_consola(t_log* logger) {
	char* leido = readline(">");

	while(strncmp(leido, "", 1) != 0) {
		log_info(logger, leido);
		free(leido);
		leido = readline(">");
	}

	free(leido);
}

t_paquete* armar_paquete() {
	t_paquete* paquete = crear_paquete();

	char* leido = readline(">");

	while(strncmp(leido, "", 1) != 0) {
		agregar_a_paquete(paquete, leido, strlen(leido) + 1);
		free(leido);
		leido = readline(">");
	}

	free(leido);

	return paquete;
}
