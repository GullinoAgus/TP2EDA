
#include "graphics.h"


static void graficarEjes(int posx, int posy);

static void graficarPuntos(int posx, int posy);

static void graficarCuadricula(int posx, int posy, int width, int height, int cellWidth, int cellHeight)


void graficarPiso(ALLEGRO_DISPLAY *display, int posx, int posy, piso_t *piso, robot_t *listaRobots){

    al_clear_to_color(al_map_rgb(255,255,255));

    

    al_flip_display();

}

void graficarFuncion(int posx, int posy, punto_t *listaPuntos);


static void graficarEjes(int posx, int posy){

    punto_t origen;

    al_draw_line(posx, posy, posx, posy+500, al_map_rgb(0,0,0), 1);
    al_draw_line(posx, posy+500, posx+500, posy+500, al_map_rgb(0,0,0), 1);


}

static void graficarPuntos(int posx, int posy);

static void graficarCuadricula(int posx, int posy, int width, int height, int cellWidth, int cellHeight){



}