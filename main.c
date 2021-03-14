#include <stdio.h>
//#include "limpiador.h"
#include "graphics.h"


#define FPS 2.0

ALLEGRO_DISPLAY* initAllegro5();


int main (void){
    srand(time(NULL));
    int exit = 0;

    baldosa_t baldosasList[5][5] = {0};
    //baldosasList[1][3] = 1;
    piso_t piso = {.h = 5, .w = 5, .baldosas = baldosasList};
    robot_t robot[3] = {{3.5, 4, 125},{2.8, 1.4, 260},{-1, -1, -1}};

    ALLEGRO_DISPLAY *display = initAllegro5();
    ALLEGRO_TIMER *timer = al_create_timer(1/FPS);
    ALLEGRO_EVENT evento;
    ALLEGRO_EVENT_QUEUE *colaEventos = al_create_event_queue();

    al_register_event_source(colaEventos, al_get_display_event_source(display));
    al_register_event_source(colaEventos, al_get_timer_event_source(timer));
    al_start_timer(timer);
    while (!exit) {
        al_wait_for_event(colaEventos, &evento);
        switch (evento.type) {
            case ALLEGRO_EVENT_TIMER:
                fisicas(&piso, robot);
                graficarPiso(display, 50, 50, &piso,robot, 100);
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                exit = 1;
                break;
        }

    }
    al_destroy_display(display);
    return 0;
}


ALLEGRO_DISPLAY* initAllegro5(){

    ALLEGRO_DISPLAY *display;

    if (!al_init()){
        return NULL;
    }
    if (!al_init_primitives_addon()){
        return NULL;
    }
    if (!al_init_font_addon()){
        return NULL;
    }
    if (!al_init_ttf_addon()){
        return NULL;
    }
    if (!al_install_keyboard()){
        return NULL;
    }
    display = al_create_display(WINDOWWIDHT, WINDOWHEIGHT);
    if (display == NULL){
        return NULL;
    }

    return display;

}