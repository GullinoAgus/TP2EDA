#include <stdio.h>
//#include "limpiador.h"
#include "graphics.h"


ALLEGRO_DISPLAY* initAllegro5();


int main (void){
    srand(time(NULL));

    char baldosasList[5][5] = {0};
    piso_t piso = {.h = 5, .w = 5, .baldosas = baldosasList};
    robot_t robot[3] = {{3.5, 4, 260},{2.8, 1.4, 260},{-1, -1, -1}};

    ALLEGRO_DISPLAY *display = initAllegro5();
    ALLEGRO_EVENT evento;
    ALLEGRO_EVENT_QUEUE *colaEventos = al_create_event_queue();

    graficarPiso(display, 50, 50, &piso,robot);

    al_register_event_source(colaEventos, al_get_display_event_source(display));
    al_wait_for_event(colaEventos, &evento);

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
    if (!al_init_image_addon()){
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