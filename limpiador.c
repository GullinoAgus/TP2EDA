#include "limpiador.h"

int main (void)
{
    srand(time(NULL));

    return 0;
}

void fisicas (piso_t *piso, robot_t *r)
{
    char *aux = piso->baldosas;
    double xf, yf;
    int res;

    //A que (x, y) avanzaria el robot:
    xf = r->x + sin( dtoRad(r->angle) );  
    yf = r->y + cos( dtoRad(r->angle) );
    res = puedeAvanzar(xf, yf, piso->h, piso->w);

    if (res == 1) //Pudede avanzar
    {
        r->x = xf;
        r->y = yf;
        //Ahora debe limpiar la baldosa
        aux[ ((int)xf) * ((piso->w) -1) + ((int)yf) ] = 1;  //Limpia baldosa

    }
    else    //Debe cambiar su orientacion
    {
        r->angle = (rand() % 3600) / 10; //Angulo entre 0 y 359.9
    }

}

int puedeAvanzar (double x, double y, int alto, int ancho)    
{
    int res = 1;    
    //Primero analiza la coordenada x
    if ((x < 0) || (x > (double)ancho)) //Quiere decir que el robot chocaria
    {
        res = 0;    //Robot no puede avanzar
    }

    //Analiza la coordenada y
    if ((y < 0) || (y > (double)alto)) //Quiere decir que el robot chocaria
    {
        res = 0;    //Robot no puede avanzar
    }
    return res;
}

double dtoRad (double angle)
{
    double rad = (PI/180) * angle;
    return rad;
}