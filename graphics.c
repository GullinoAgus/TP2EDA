
#include "graphics.h"
#include <stdbool.h>

#define DIVISIONESDEGRAFICO 10

static void graficarPuntos(int posOrigX, int posOrigy, punto_t* listaPuntos, double avancePorUnidad, double avancePorUnidadY, double escala);

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

                al_draw_filled_rectangle(posx +  j*escala, posy + (piso->h-1)*escala - i*escala, posx + escala +  j*escala, posy + escala + (piso->h-1)*escala - i*escala, al_map_rgb(100,150,255));

            }
            else{

                al_draw_filled_rectangle(posx +  j*escala, posy + (piso->h-1)*escala - i*escala, posx + escala + j*escala, posy + escala + (piso->h-1)*escala - i*escala, al_map_rgb(150,150,150));

            }
        }

    }
    graficarCuadricula(posx, posy, piso->w, piso->h, escala, escala);
    graficarRobots(posx, posy + piso->h*escala, escala, listaRobots);

    al_flip_display();

}

void graficarFuncion(int posx, int posy, punto_t *listaPuntos, double escala){

    ALLEGRO_TRANSFORM t;
    ALLEGRO_FONT* font = al_load_ttf_font(FONTDIRECTORY, escala / 4, NULL);
    double maxXvalue = getMaxX(listaPuntos);
    double maxYvalue = getMaxY(listaPuntos);

    posx += 1.05 * escala;
    posy += escala;

    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_line(posx, posy - escala, posx, posy + escala* (DIVISIONESDEGRAFICO + 1), al_map_rgb(0, 0, 0), escala / 40);          //Eje Y
    al_draw_line(posx - escala, posy + escala*DIVISIONESDEGRAFICO, posx + escala*(DIVISIONESDEGRAFICO+1), posy + escala*DIVISIONESDEGRAFICO, al_map_rgb(0, 0, 0), escala / 40);   //EJE x
    graficarCuadricula(posx, posy, DIVISIONESDEGRAFICO, DIVISIONESDEGRAFICO, escala, escala);
    
    al_draw_text(font, al_map_rgb(0, 0, 0), (double)posx - escala * 0.1, (double)posy + escala * ((double)DIVISIONESDEGRAFICO + 0.1), ALLEGRO_ALIGN_RIGHT, "0");


    for (int i = 1; i <= DIVISIONESDEGRAFICO; i++)
    {
        al_draw_textf(font, al_map_rgb(0, 0, 0), posx, posy + (DIVISIONESDEGRAFICO - i) * escala - al_get_font_line_height(font) / 2, ALLEGRO_ALIGN_RIGHT, "%.2E", (maxYvalue / (double)DIVISIONESDEGRAFICO) * i);
    }
    al_identity_transform(&t);
    al_rotate_transform(&t, PI / 2.0f);
    al_translate_transform(&t, posx + escala * DIVISIONESDEGRAFICO + al_get_font_line_height(font) / 2, posy + escala * DIVISIONESDEGRAFICO);
    al_use_transform(&t);
    for (int i = 1; i <= DIVISIONESDEGRAFICO; i++)
    {
        al_draw_textf(font, al_map_rgb(0, 0, 0), 0, (DIVISIONESDEGRAFICO - i) * escala, ALLEGRO_ALIGN_LEFT, "%.2E", (maxXvalue/(double)DIVISIONESDEGRAFICO)*i);
    }
    al_identity_transform(&t);
    al_use_transform(&t);
    
    
    graficarPuntos(posx, posy + escala * DIVISIONESDEGRAFICO, listaPuntos, maxXvalue /((double) DIVISIONESDEGRAFICO), maxYvalue / ((double)DIVISIONESDEGRAFICO), escala);

    al_flip_display();

    al_destroy_font(font);
 }

static void graficarPuntos(int posOrigX, int posOrigY, punto_t *listaPuntos, double avancePorUnidadX, double avancePorUnidadY, double escala){

    punto_t* auxPunto;

    do
    {
        al_draw_filled_circle(posOrigX + (listaPuntos->x * escala)/avancePorUnidadX, posOrigY - (listaPuntos->y * escala) / avancePorUnidadY, escala/10, al_map_rgb(255,0,0));
        auxPunto = listaPuntos->next;
        listaPuntos = auxPunto;
    } while (listaPuntos != NULL);

}

static void graficarCuadricula(int posx, int posy, int width, int height, int cellWidth, int cellHeight){

    for (int i = 0; i <= width; ++i) {

        al_draw_line(posx + i*cellWidth, posy, posx + i*cellWidth, posy + height*cellHeight, al_map_rgb(100,100,100), 1);

    }
    for (int i = 0; i <= height; ++i) {

        al_draw_line(posx, posy + i*cellHeight, posx + width*cellWidth, posy + i*cellHeight, al_map_rgb(100,100,100), 1);

    }

}

static void graficarRobots(int cuadOriginX, int cuadOriginY, const int scaleConst, robot_t *robotList){

    double posXaux, posYaux;

    int escalaGraficaAux = scaleConst;
    if (scaleConst < 20)
    {
        escalaGraficaAux = 20;
    }

    for (int i = 0; robotList[i].x != -1 ; ++i) {

        posXaux = cuadOriginX + robotList[i].x*scaleConst;
        posYaux = cuadOriginY - robotList[i].y*scaleConst;

        draw_vector(posXaux, posYaux, 1, robotList[i].angle, al_map_rgb(0,0,255), scaleConst);

        al_draw_filled_circle( posXaux, posYaux, escalaGraficaAux/10, al_map_rgb(255,0,0));


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