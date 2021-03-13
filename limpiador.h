
#ifndef LIMPIADOR_H
#define LIMPIADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//Macros
#define DEG2RAD(x) ((x)*M_PI/180)

//Estructuras
typedef struct 
{
    double x;
    double y;
    double angle;   //En grados

} robot_t;

typedef struct 
{
    int h;
    int w;
    char *baldosas; //Baldosa en 1 --> Esta limpia

} piso_t;

//Prototipos

/*Se encarga del movimiento de los robots, cambiar la direccion de ellos en caso 
de colision, y limpia las baldosas */
void fisicas(piso_t *piso, robot_t *r);

//Convierte un angulo en grados a radianes.
double dtoRad (double angle);

//Devuelve 1 si el robot puede avanzar, o 0 si no puede.
int puedeAvanzar(double x, double y, int alto, int ancho);

#endif