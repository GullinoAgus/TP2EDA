#ifndef INIT_H
#define INIT_H


#include <stdio.h>
#include <stdlib.h>
#include "limpiador.h"


/*******************************************************************************
*	Esta funcion se encarga de recibir parametros por linea de comandos		   *
*	en tiempo de ejecucion. 												   *
*	Guarda el numero de robots, el largo y ancho del tablero y devuelve 	   *
*	el modo del juego. 														   *
*******************************************************************************/
int recieve_data (piso_t * floor, int * n_robots);

/*******************************************************************************
*	Esta funcion se encarga de reservar un lugar en el heap para las baldosas. *
*	Las inicializa en 0, lo que indica que estan sucias.					   *
*******************************************************************************/
void init_floor (piso_t floor);

/*******************************************************************************
*	Esta funcion se encarga de reservar un lugar en el heap para los robots.   *
*	Crea la lista e inicializa las coordenadas de los robots en el medio 	   *
*	de la pantalla. 														   *
*******************************************************************************/
void init_robot (robot_ t * robot_list, int n_robots, piso_t floor);


#endif
