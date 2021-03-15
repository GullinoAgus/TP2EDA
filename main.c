#include <stdio.h>
#include <time.h>
//#include "limpiador.h"
#include "init.h"
#include "graphics.h"


#define FPS 2.0
#define REPESPARAPROMEDIO 1000

int initAllegro5(ALLEGRO_DISPLAY** p2display);


int main (void){
    srand(time(NULL));
    int exit = 0;

    piso_t piso;
    robot_t* robots = NULL;
    int cantRobots = 1;
    int calcDone = false;
    int contBaldosasLimpias = 0;
    double difTiempo, actualTime;
    punto_t* listaPuntos = NULL, *puntoNuevo = NULL, *puntoAnterior = NULL;



    ALLEGRO_DISPLAY *display;
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT evento;
    ALLEGRO_EVENT_QUEUE *colaEventos;
    


    //int modo = recieve_data(&piso, &cantRobots);
    int modo = 2;
    piso.h = 100;
    piso.w = 70;
    init_floor(&piso);
    if (modo == 1)
    {
        cantRobots = 10;
        robots = init_robot(cantRobots, &piso);
    }
    


    if (initAllegro5(&display) == -1) {
        return -1;
    }

    timer = al_create_timer(1 / FPS);
    colaEventos = al_create_event_queue();

    al_register_event_source(colaEventos, al_get_display_event_source(display));
    al_register_event_source(colaEventos, al_get_timer_event_source(timer));
    if (modo == 1) {
        al_start_timer(timer);
    }
    while (!exit) {
        if (!al_event_queue_is_empty(colaEventos))
        {
            al_get_next_event(colaEventos, &evento);
            switch (evento.type) {
            case ALLEGRO_EVENT_TIMER:
                contBaldosasLimpias += fisicas(&piso, robots);
                graficarPiso(display, 0, 0, &piso, robots, 15);
                if (contBaldosasLimpias == piso.h*piso.w)
                {
                    al_stop_timer(timer);
                    free(robots);
                    free(piso.baldosas);
                }
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                exit = 1;
                break;
            }
        }
        if (modo == 2 && !calcDone)
        {
            do{
                
                actualTime = 0;
                for (int i = 0; i < REPESPARAPROMEDIO; i++)
                {
                    init_floor(&piso);
                    contBaldosasLimpias = 0;
                    robots = init_robot(cantRobots, &piso);
                    while (piso.h * piso.w != contBaldosasLimpias)
                    {
                        contBaldosasLimpias += fisicas(&piso, robots);
                        actualTime++;
                    }
                    free(robots);
                    free(piso.baldosas);
                }
                if (cantRobots == 1)
                {
                    listaPuntos = calloc(1, sizeof(punto_t));
                    puntoNuevo = listaPuntos;
                    puntoNuevo->x = cantRobots;
                    puntoNuevo->y = actualTime / REPESPARAPROMEDIO;
                    puntoAnterior = puntoNuevo;
                }
                else
                {
                    puntoAnterior = puntoNuevo;
                    puntoNuevo = calloc(1, sizeof(punto_t));
                    puntoAnterior->next = puntoNuevo;
                    puntoNuevo->x = cantRobots;
                    puntoNuevo->y = actualTime / REPESPARAPROMEDIO;
                }
                cantRobots++;
                printf("t(n)-t(n-1) = %.2f   n = %d\n", fabs(puntoNuevo->y - puntoAnterior->y), cantRobots-1);
            }while (fabs(puntoNuevo->y - puntoAnterior->y) >=0.1 || puntoAnterior == puntoNuevo);
            calcDone = 1;
            graficarFuncion(50, 50, listaPuntos, 40);
        }
        
    }
    al_destroy_display(display);
    al_destroy_event_queue(colaEventos);
    al_destroy_timer(timer);
    return 0;
}


int initAllegro5(ALLEGRO_DISPLAY **p2display){


    if (!al_init()){
        return -1;
    }
    if (!al_init_primitives_addon()){
        return -1;
    }
    if (!al_init_font_addon()){
        return -1;
    }
    if (!al_init_ttf_addon()){
        return -1;
    }
    if (!al_install_keyboard()){
        return -1;
    }
    *p2display = al_create_display(WINDOWWIDHT, WINDOWHEIGHT);
    if (*p2display == NULL){
        return -1;
    }

    return 0;

}