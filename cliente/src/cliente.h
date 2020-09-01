/*
 * Cliente.h
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#ifndef CLIENTE_H__
#define CLIENTE_H_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>

#include "utils.h"

// Por lo general, a menos que tengan que tener recursos compartidos, no es buena práctica usar variables globales. Nosotros lo estamos haciendo por la simplicidad del TP0 :)
t_log* g_logger;
t_config* g_config;

void iniciar_logger(void);
void leer_config(void);
void leer_consola(void);
void paquete(int);
void terminar_programa(int);

#endif /* CLIENTE_H__H_ */
