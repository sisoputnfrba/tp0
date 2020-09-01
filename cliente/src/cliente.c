/*
 * Resolucion 1 del TP0 [Dificultad Baja]
 *
 * Buenas! Esta es una resolucion similar hicimos en las charlas.
 * Tiene varios problemas de disenio y buen criterio de codigo, dado que nos tomamos
 * un par de licencias para que el workshop sea mas ameno y rapido.
 *
 * Les proponemos tomen esta resolucion como "una que funciona" y los invitamos
 * a que revisen las resoluciones 2 y 3, que van introduciones varios conceptos nuevos,
 * tanto desde el lado duro y tecnico, como de la mantenibilidad del codigo y buenas
 * practicas.
 *
 * Las otras dos resoluciones pueden encontrarlas en otras branches de este mismo repositorio.
 *
 * Espero que le saquen provecho a esta implementacion, comparandola no solo en funcionalidades
 * con las suyas, sino que tambien a nivel disenio y saquen sus propias conclusiones :).
 *
 * Saludos!
 *
 * Nota: Sacamos todos los caracteres especiales para que se vea simpre bien :P
 */
#include "cliente.h"

int main(void)
{
	int conexion;
	char* ip;
	char* puerto;

	//las variables de logger y config estan declaradas como globales en el encabezado de este tp0

	iniciar_logger();

	leer_config();

	leer_consola();

	//antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	//Una vez hecho eso, tenemos que conectarnos a él! Las conexiones se representan mediante enteros por cosas que hablaremos más adelante.
	//Esta parte la vamos a hacer aca en el main por simpleza.

	//Primero vas a tener que levantar los valores IP y PUERTO del archivo de configuracion con esas claves. Adivina a quien se los tenes que asignar :P
	ip = config_get_string_value(g_config, "IP");
	puerto = config_get_string_value(g_config, "PUERTO");
	//Hecho esto, vamos a conectarnos! usamos la funcion ya dada para hacerlo, y le asignamos el entero que devuelve a conexion
	conexion = crear_conexion(ip, puerto);

	char* valor;

	//ahora que tenemos la conexion, es hora de empezar a enviar cosas. Primero, el mensaje.
	//Levantá el valor que le corresponde a CLAVE del archivo de configuracion de nuevo.
	valor = config_get_string_value(g_config, "CLAVE");
	//Ahora le podés mandar el mensaje al servidor!
	enviar_mensaje(valor, conexion);

	paquete(conexion);

	terminar_programa(conexion);
}

void iniciar_logger(void)
{
	//creemos el log! Este se debe crear con el nombre "tp0.log", se debe mostrar por consola y debe estar en el nivel INFO
	g_logger = log_create("tp0.log", "TP0", 1, LOG_LEVEL_INFO);

	//logeemos el mensaje "Soy un log"
	log_info(g_logger, "Soy un log");
}

void leer_config(void)
{
	char* valor;

	//ahora, vamos a abrir el archivo de configuracion "tp0.config"
	g_config = config_create("cliente.config");

	//tenemos que levantar en valor asociado a la clave "CLAVE" del archivo y asignarselo a la variable valor
	valor = config_get_string_value(g_config, "CLAVE");

	//Por último, logeame ese valor :)
	log_info(g_logger, valor);
}

void leer_consola(void)
{
	char* leido;

	//El primero te lo dejo de yapa
	leido = readline(">");

	while(*leido != '\0') {
		log_info(g_logger, leido);
		free(leido);
		leido = readline(">");
	}

	free(leido);
}

void paquete(int conexion)
{
	//Ahora toca lo divertido!

	char* leido;
	t_paquete* paquete = crear_paquete();

	leido = readline(">");

	while(*leido != '\0') {
		agregar_a_paquete(paquete, leido, strlen(leido) + 1);
		free(leido);
		leido = readline(">");
	}

	free(leido);
	//Una vez hayamos terminado de ingresar valores, toca enviarlo
	enviar_paquete(paquete, conexion);

	//Y no nos olvidemos de borrar el paquete con eliminar_paquete
	eliminar_paquete(paquete);
}

void terminar_programa(int conexion)
{
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
	liberar_conexion(conexion);
	log_destroy(g_logger);
	config_destroy(g_config);
}
