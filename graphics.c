
#include "graphics.h"

#define SCALE 40

static void graficarEjes(int posx, int posy);

static void graficarPuntos(int posx, int posy);

static void graficarCuadricula(int posx, int posy, int width, int height, int cellWidth, int cellHeight);

static void graficarRobots(int cuadOriginX, int cuadOriginY,int scaleConst, robot_t *robotList);

static void draw_vector(double origx, double origy, double modulo, double angulo, ALLEGRO_COLOR color, double grosor);

void graficarPiso(ALLEGRO_DISPLAY *display, int posx, int posy, piso_t *piso, robot_t *listaRobots){

    al_clear_to_color(al_map_rgb(255,255,255));

    graficarCuadricula(posx, posy, piso->w, piso->h, SCALE, SCALE);
    graficarRobots(posx + piso->h*SCALE, posy + piso->w*SCALE, SCALE, listaRobots);

    al_flip_display();

}

void graficarFuncion(int posx, int posy, punto_t *listaPuntos);


static void graficarEjes(int posx, int posy){

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

        posXaux = cuadOriginX - robotList[i].x*scaleConst;
        posYaux = cuadOriginY - robotList[i].y*scaleConst;

        draw_vector(posXaux, posYaux, 1, robotList[i].angle, al_map_rgb(0,0,255), scaleConst);

        al_draw_filled_circle( posXaux, posYaux, scaleConst/10, al_map_rgb(255,0,0));


    }

}

static void draw_vector(double origx, double origy, double modulo, double angulo, ALLEGRO_COLOR color, double escala){


    double cosAngl = cos(DEG2RAD(angulo))*escala;
    double senAngl = sin(DEG2RAD(angulo))*escala;
    double cosAnglM30 = cos(DEG2RAD(angulo + 180 - 30))*escala;
    double senAnglM30 = sin(DEG2RAD(angulo + 180 - 30))*escala;
    double cosAnglP30 = cos(DEG2RAD(angulo + 180 + 30))*escala;
    double senAnglP30 = sin(DEG2RAD(angulo + 180 + 30))*escala;

    al_draw_line(origx, origx, origx + cosAngl, origy + senAngl, color, escala/25.0);
    al_draw_filled_triangle(origx + cosAngl*modulo, origy + senAngl*modulo, origx + cosAngl*modulo - cosAnglM30/5, origy + senAngl*modulo - senAnglM30/5, origx + cosAngl*modulo - cosAnglP30/5, origy + senAngl*modulo - senAnglP30/5, color);

}