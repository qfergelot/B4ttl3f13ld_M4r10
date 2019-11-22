#include <stdlib.h>
#include <time.h>
#include "bad.h"
#include "generator.h"
#include "constants.h"

time_t t;

void generate_badbird(void* a){
    int height = rand()%WIN_HEIGHT;
    int xs = (rand()%4) + 2;
    xs -= 2*xs;
    float vs = rand()%2 - 1;
    animation_badbird_add(height, xs, vs);
}

Uint32 callback_gen(Uint32 delay, void* param){
    SDL_Event event;
    SDL_UserEvent userevent;

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = &generate_badbird;
    userevent.data2 = param;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);

    delay = (rand()%1500) + 500;
    return(delay);
}

timer_id_t generator_init(){
    timer_id_t tim = SDL_AddTimer(500, callback_gen, NULL);
    srand((unsigned) time(&t) );
    return tim;
}

void generator_clean(timer_id_t id){
    SDL_RemoveTimer(id);
}




