
#include "graphics.h"
#include <stdbool.h>

static void graficarEjes(int posx, int posy);

static void graficarPuntos(int posx, int posy);

static void graficarCuadricula(int posx, int posy, int width, int height, int cellWidth, int cellHeight);

static void graficarRobots(int cuadOriginX, int cuadOriginY,int scaleConst, robot_t *robotList);

static void draw_vector(double origx, double origy, double modulo, double angulo, ALLEGRO_COLOR color, double grosor);

static int contarPuntos(punto_t *listaPuntos);

static double getMaxY(punto_t *listaPuntos);

static double getMaxX(punto_t *listaPuntos);

void graficarPiso(ALLEGRO_DISPLAY *display, int posx, int posy, piso_t *piso, robot_t *listaRobots, double escala){

    al_clear_to_color(al_map_rgb(255,255,255));

    for (int i = 0; i < piso->h ; ++i) {
        for (int j = 0; j < piso->w; ++j) {
            if (piso->baldosas[i * piso->w + j]){

                al_draw_filled_rectangle(posx +  j*escala, posy + (piso->w-1)*escala - i*escala, posx + escala +  j*escala, posy + escala + (piso->w-1)*escala - i*escala, al_map_rgb(100,150,255));

            }
            else{

                al_draw_filled_rectangle(posx +  j*escala, posy + (piso->w-1)*escala - i*escala, posx + escala + j*escala, posy + escala + (piso->w-1)*escala - i*escala, al_map_rgb(150,150,150));

            }
        }

    }
    graficarCuadricula(posx, posy, piso->w, piso->h, escala, escala);
    graficarRobots(posx, posy + piso->w*escala, escala, listaRobots);

    al_flip_display();

}

void graficarFuncion(int posx, int posy, punto_t *listaPuntos, double escala){

    double maxXvalue = getMaxX(listaPuntos);
    double maxYvalue = getMaxY(listaPuntos);
    double maxScaleValue;

    if(maxXvalue > maxYvalue){
        maxScaleValue = maxXvalue;
    }
    else {
        maxScaleValue = maxYvalue;
    }

}

static void graficarEjes(int posx, int posy)
{

    punto_t origen;

    al_draw_line(posx, posy, posx, posy+500, al_map_rgb(0,0,0), 1);
    al_draw_line(posx, posy+500, posx+500, posy+500, al_map_rgb(0,0,0), 1);


}

static void graficarPuntos(int posx, int posy){



}

static void graficarCuadricula(int posx, int posy, int width, int height, int cellWidth, int cellHeight){

    for (int i = 0; i <= width; ++i) {

        al_draw_line(posx + i*cellWidth, posy, posx + i*cellWidth, posy + height*cellHeight, al_map_rgb(100,100,100), 1);

    }
    for (int i = 0; i <= height; ++i) {

        al_draw_line(posx, posy + i*cellHeight, posx + width*cellWidth, posy + i*cellHeight, al_map_rgb(100,100,100), 1);

    }

}

static void graficarRobots(int cuadOriginX, int cuadOriginY,const int scaleConst, robot_t *robotList){

    double posXaux, posYaux;

    //ALLEGRO_BITMAP *bitmap = al_load_bitmap("./arrow.png");

    for (int i = 0; robotList[i].x != -1 ; ++i) {

        posXaux = cuadOriginX + robotList[i].x*scaleConst;
        posYaux = cuadOriginY - robotList[i].y*scaleConst;

        draw_vector(posXaux, posYaux, 1, robotList[i].angle, al_map_rgb(0,0,255), scaleConst);

        al_draw_filled_circle( posXaux, posYaux, scaleConst/10, al_map_rgb(255,0,0));


    }

}

static void draw_vector(double origx, double origy, double modulo, double angulo, ALLEGRO_COLOR color, double escala){


    double cosAngl = cos(DEG2RAD(angulo))*escala;
    double senAngl = -sin(DEG2RAD(angulo))*escala;
    double cosAnglM30 = cos(DEG2RAD(angulo + 180 - 30))*escala;
    double senAnglM30 = -sin(DEG2RAD(angulo + 180 - 30))*escala;
    double cosAnglP30 = cos(DEG2RAD(angulo + 180 + 30))*escala;
    double senAnglP30 = -sin(DEG2RAD(angulo + 180 + 30))*escala;

    al_draw_line(origx, origy, origx + cosAngl, origy + senAngl, color, escala/25.0);
    al_draw_filled_triangle(origx + cosAngl*modulo, origy + senAngl*modulo, origx + cosAngl*modulo + cosAnglM30/5, origy + senAngl*modulo + senAnglM30/5, origx + cosAngl*modulo + cosAnglP30/5, origy + senAngl*modulo + senAnglP30/5, color);
}

static int contarPuntos(punto_t *listaPuntos){

    int contadorPuntos = 0;
    punto_t *puntoAux;

    while(listaPuntos != NULL){
        contadorPuntos++;
        puntoAux = listaPuntos->next;
        listaPuntos = puntoAux;
    }

    return contadorPuntos;
}

static double getMaxY(punto_t *listaPuntos){

    double Yvalue = 0;
    punto_t *puntoAux;

    while(listaPuntos != NULL){
        if (listaPuntos->y > Yvalue){
            Yvalue = listaPuntos->y;
        }
        puntoAux = listaPuntos->next;
        listaPuntos = puntoAux;
    }

    return Yvalue;

}

static double getMaxX(punto_t *listaPuntos){

    double Xvalue = 0;
    punto_t *puntoAux;

    while(listaPuntos != NULL){
        if (listaPuntos->x > Xvalue){
            Xvalue = listaPuntos->x;
        }
        puntoAux = listaPuntos->next;
        listaPuntos = puntoAux;
    }

    return Xvalue;

}