/*
 * Resolucion 3 del TP0 [Dificultad Alto]
 *
 * Buenas! A diferencia de la resolucion que hicimos en las charlas (la version 1)
 * y su contraparte mas "pulida" (version 2), esta resolucion les va a presentar,
 * aparte de una mejora en buenas practicas de programacion (como evitar repetir codigo),
 * con el concepto de Funciones Anidadas (Nested Functions) y punteros a funciones.
 *
 * Esta resolucion es analoga a la version 2, cambiando la parte estructura del
 * esqueleto que ustedes tienen.
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

/*
 * Hasta esta funcion, es parecida a la resolucion numero 2. Pero esta
 * ultima tenia un problema grave: la logica de leer strings de consola
 * se encontraba duplicada.
 *
 * Para solucionar eso vamos a introducir los dos conceptos nuevos, que
 * si bien no forman parte del standard de ANSI C, si forman parte de la
 * implementacion de GNU C, que es la que se encuentra en el compilador que
 * usamos por la catedra: GCC. Estos son:
 *
 * Funciones anidadas (o Nested Functions):
 * ---------------------------------------
 * El compilador nos permite crear funciones locales al contexto de otra funcion.
 * De esta manera, pueden evitar crear muchas funciones auxiliares que se van a usar
 * en un unico lugar, y tener que pensar miles de nombres diferentes para cada una.
 * Algo importante a tener en cuenta, es que las funciones anidadas, mantienen el
 * contexto de la funcion exterior, es decir, que las variables definidas en la funcion
 * exterior son accesibles desde le interior (masomenos, como funcionan las variables globales).
 *
 *
 * Punteros a Funcion:
 * ------------------
 * Las funciones no escapan  del concepto de puntero, por como funciona el compilador.
 * Esto implica que llamar a una funcion por su nombre, ejemplo:
 * ```
 * void _soy_funcion() { };
 *
 * variable = _soy_funcion;
 * ```
 * Es como tener un puntero a "alguna cosa", y podemos definir la variable como:
 * ```
 * void* variable = (void*) _soy_funcion;
 * ```
 * El casteo a "void*" es necesario para que el compilador entienda que es un puntero
 * a "alguna cosa".
 *
 * Ahora, si podemos asignar a una variable, porque no: pasar una funcion por parametro.
 * Esto nos habilita el orden superior en nuestras funciones.
 */
void leer_consola(t_log* logger) {
	void loggear(char* leido) {
		log_info(logger, leido);
	}

	_leer_consola_haciendo((void*) loggear);
}

t_paquete* armar_paquete() {
	t_paquete* paquete = crear_paquete();

	void _agregar(char* leido) {
		// Estamos aprovechando que podemos acceder al paquete
		// de la funcion exterior y podemos agregarle lineas!
		agregar_a_paquete(paquete, leido, strlen(leido) + 1);
	}

	_leer_consola_haciendo((void*) _agregar);

	return paquete;
}

/*
 * Este comportamiento es el comun a ambas funciones,
 * cambiando solamente que por un lado vamos a loggear y
 * por el otro, queremos agregar las lineas a un paquete.
 *
 * Por lo tanto, necesita que se le pase una funcion que reciba
 * un string por parametro y no haga nada.
 *
 * Noten que la firma de la funcion pide void(*accion)(char*)
 * que implica:
 * - Un puntero a la funcion accion: (*accion)
 * - Devuelve un void
 * - Recibe un solo argumento (char*)
 */
void _leer_consola_haciendo(void(*accion)(char*)) {
	char* leido = readline(">");

	while(strncmp(leido, "", 1) != 0) {
		accion(leido);
		free(leido);
		leido = readline(">");
	}

	free(leido);
}
