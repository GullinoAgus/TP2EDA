#ifndef INIT_H
#define INIT_H

/**************HEADER FILES************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "limpiador.h"
#include "parser.h"

/**************STRUCTURES**************/
typedef struct {

	int largo;
	int ancho;
	int modo;
	int robots;

}data_t;

/************************************************************************************
*	Esta funcion es el callback llamado por parseCmdLine. Se encarga de	verificar	*
*	si las opciones ingresadas son correctas y llena la estructura.					*
*	En el caso de tener un error devuelve 0, sino devuelve 1.						*
*************************************************************************************/
int recieve_data(char* key, char* value, void* userData);


/************************************************************************************
*	Esta funcion se encarga de reservar un lugar en el heap para las baldosas		*
*	Las inicializa en 0, lo que indica que estan sucias.							*
*************************************************************************************/
void init_floor(piso_t* floor, data_t* userData);

/************************************************************************************
*	Esta funcion se encarga de reservar un lugar en el heap para los robots.		*
*	Crea la lista e inicializa las coordenadas de los robots en el medio			*
*	de la pantalla. 																*
*	Devuelve un puntero al arreglo que contiene a los robots.						*
*************************************************************************************/
robot_t* init_robot(int n_robots, piso_t* floor);


#endif
