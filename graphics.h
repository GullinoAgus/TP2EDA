#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "limpiador.h"

#define WINDOWWIDHT 1280
#define WINDOWHEIGHT 720

typedef struct punto {

    double x;
    double y;
    struct punto *next;

} punto_t;

// Funciones globales

void graficarPiso(ALLEGRO_DISPLAY *display, int posx, int posy, piso_t *piso, robot_t *listaRobots, double escala);

void graficarFuncion(int posx, int posy, punto_t *listaPuntos, double escala);


#endif