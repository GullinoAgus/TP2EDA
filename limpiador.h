#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//Constantes
#define PI 3.14159265359

//Estructuras
typedef struct 
{
    double x;
    double y;
    double angle;

}robot_t;

typedef struct 
{
    int h;
    int w;
    char *baldosas;

}piso_t;

//Prototipos

/*Se encarga del movimiento de los robots, cambiar la direccion de ellos en caso 
de colision, y limpia las baldosas */
int fisicas(piso_t *piso, robot_t *r);

//Convierte un angulo en grados a radianes.
double dtoRad (double angle);