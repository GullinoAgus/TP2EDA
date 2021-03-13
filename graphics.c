
#include "graphics.h"

#define SCALE 40

static void graficarEjes(int posx, int posy);

static void graficarPuntos(int posx, int posy);

static void graficarCuadricula(int posx, int posy, int width, int height, int cellWidth, int cellHeight);

static void graficarRobots(int cuadOriginX, int cuadOriginY,int scaleConst, robot_t *robotList);


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

    //ALLEGRO_BITMAP *bitmap = al_load_bitmap("./arrow.png");

    for (int i = 0; robotList[i].x != -1 ; ++i) {

        al_draw_filled_circle(cuadOriginX - robotList[i].x*scaleConst, cuadOriginY - robotList[i].y*scaleConst, scaleConst/10, al_map_rgb(255,0,0));


    }

}