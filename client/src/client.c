#include "client.h"
#include <readline/readline.h>

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	log_info(logger, "Hola capo, soy un log");
	log_info(logger, "Bata bata eu bata");

	//log_destroy(logger);


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	// Loggeamos el valor de config

	if (config == NULL) {
		log_info(logger, "No existe el archivo config.");
		return 0;
	}else{
		log_info(logger, "Existe el archivo config.");

		if(config_has_property(config, "CLAVE")){
			log_info(logger, "Existe la propiedad CLAVE en el archivo config !");
			valor = config_get_string_value(config, "CLAVE");
			log_info(logger, "Este valor se asocia a la propiedad CLAVE: %s", valor);

			ip = config_get_string_value(config, "IP");
			log_info(logger, "Este valor se asocia a la propiedad IP: %s", ip);

			puerto = config_get_string_value(config, "PUERTO");
			log_info(logger, "Este valor se asocia a la propiedad PUERTO: %s", puerto);

		}else{
			log_info(logger, "Che capo, no habia un atributo con CLAVE...");
			return 0;
		}
	}
	
	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor, conexion);

	// Armamos y enviamos el paquete
	//paquete(conexion);

	terminar_programa(conexion, logger, config);
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	nuevo_logger = log_create("/home/utnso/Desktop/TP0/Logs/logTP0.log", "TP0", true, LOG_LEVEL_INFO);

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	nuevo_config = config_create("/home/utnso/Desktop/TP0/Config/client.config");

	return nuevo_config;
}

void leer_consola(t_log* logger)
{    
    do {
		char* leido = readline("> ");

        if (leido == NULL || strlen(leido) == 0) {  
            //free(leido);  
            break;
        }

        log_info(logger, leido);
        //free(leido);
    } while (1);
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	// Leemos y esta vez agregamos las lineas al paquete


	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
