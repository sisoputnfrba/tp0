/*
 * main.c
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#include "tp0.h"

int main(void)
{
	t_log* logger;
	t_config* config;
	int conexion;

	iniciar_logger(logger);

	leer_config(config, logger);

	//antes de poder hacer esta parte, vas a tener que incluir en "tp0.h" readline (vease el enunciado), y agregar la biblioteca al proyecto de Eclipse
	//Lo vamos a estar explicando en la puesta en comun. Si te adelantaste, llamá a un ayudante!
	leer_consola(logger);

	//antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.
	//Una vez hecho eso, tenemos que conectarnos a él! Las conexiones se representan mediante enteros por cosas que hablaremos más adelante
	conexion = conectar_cliente(config);

	enviar_clave(config, conexion);

	paquete(conexion);

	terminar_programa(logger, config, conexion);
}

void iniciar_logger(t_log* logger)
{
	//creemos el log! Este se debe crear con el nombre "tp0.log", se debe mostrar por consola y debe estar en el nivel INFO
	//logger = log_create(/*nombre del archivo, nombre del programa, 1 para mostrar por consona 0 caso contrario, nivel de log deseado */);

	//logeemos el mensaje "Soy un log"
	//log_info(/*logger, mensaje*/);
}

void leer_config(t_config* config, t_log* logger)
{
	char* valor;

	//ahora, vamos a abrir el archivo de configuracion "tp0.config"
	//config = config_create(/*path*/);

	//tenemos que levantar en valor asociado a la clave "CLAVE" del archivo y asignarselo a la variable valor
	//config_get_string_value(/*config, clave*/);

	//Por último, logeame ese valor :)
}

void leer_consola(t_log* logger)
{
	char* leido;

	//aca vas a tener que asignarle lo que devuelve readline a 'leido' y loggearlo hasta que eso sea nulo. Te doy uno pista: No es con un for ;)
	//readline(">");

	//Loggeamelo

	//Y no te olvides de liberar la memoria antes de volver al readline!
	//free(/*puntero a liberar*/);
}

int conectar_cliente(t_config* config)
{
	int conexion;
	char* ip;
	char* puerto;

	//Primero, hay que conseguir la ip y el puerto del servidor. Ya te las dejamos en el archivo de configuracion, asi que ahora toca levantarlas
	//las claves son PUERTO e IP


	//hecho esto, ahora toca conectarnos. No te olvides de asignarle el entero que devuelve a conexion!
	//crear_conexion(/*ip, puerto*/);

	return conexion;
}

void enviar_clave(t_config* config, int conexion)
{
	char* valor;

	//ahora que tenemos la conexion, es hora de empezar a enviar cosas. Primero, el mensaje.
	//Levantá el valor que le corresponde a CLAVE del archivo de configuracion de nuevo.

	//Ahora le podés mandar el mensaje al servidor!
	//enviar_mensaje(/*mensaje, entero de conexion*/)
}

void paquete(int conexion)
{
	//Ahora toca lo divertido!

	char* leido;
	t_paquete* paquete = crear_paquete();


	//De nuevo vas a tener que usar readline hasta que te llegue un nulo igual que antes, solo que ahora vas a agregar esa cadena al paquete!
	//Recomiendo revisar bien el enunciado del TP ya que ahi está explicado con detalles

	//agregar_a_paquete(/*paquete, mensaje, tamanio*/);

	//Una vez hayamos terminado, toca enviarlo
	//enviar_paquete(/*paquete, conexion*/);

	//Y no nos olvidemos de borrar el paquete con eliminar_paquete
}

void terminar_programa(t_log* logger, t_config* config, int conexion)
{
	//Y por ultimo, para cerrar, hay que liberar estas cosas con las funciones de las commons y del TP mencionadas en el enunciado
}
