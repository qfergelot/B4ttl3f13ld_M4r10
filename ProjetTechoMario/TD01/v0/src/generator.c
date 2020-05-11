#include <stdlib.h>
#include <time.h>

#include "generator.h"

time_t t;

Uint32 callback_gen(Uint32 delay, void* param){
    SDL_Event event;
    SDL_UserEvent userevent;

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = NULL;
    userevent.data2 = param;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);

    return(delay);
}

timer_id_t generator_init(Uint32 interval, callback_func_t f, void* param){
    timer_id_t tid = SDL_AddTimer(interval, f, param);
    srand((unsigned) time(&t) );
    return tid;
}

void generator_clean(timer_id_t id){
    SDL_RemoveTimer(id);
}




