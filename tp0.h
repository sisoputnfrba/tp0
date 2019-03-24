/*
 * Cliente.h
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#ifndef TP0_H_
#define TP0_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>

#include "utils.h"

void iniciar_logger(t_log*);
void leer_config(t_config*, t_log*);
void leer_consola(t_log*);
void enviar_clave(t_config*, int);
void paquete(int);
void terminar_programa(t_log*, t_config*, int);

#endif /* TP0_H_ */
