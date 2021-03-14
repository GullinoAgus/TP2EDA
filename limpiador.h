
#ifndef LIMPIADOR_H
#define LIMPIADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//Macros
#define PI 3.14159265359
#define DEG2RAD(x) ((x) * (PI)/(180))

typedef char baldosa_t;

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
    baldosa_t *baldosas; //Baldosa en 1 --> Esta limpia

} piso_t;

//Prototipos

/*Se encarga del movimiento de los robots, cambiar la direccion de ellos en caso 
de colision, y limpia las baldosas */
void fisicas(piso_t *piso, robot_t *r);

//Devuelve 1 si el robot puede avanzar, o 0 si no puede.
int puedeAvanzar(double x, double y, int alto, int ancho);

#endif