#include <stdlib.h>
#include <time.h>

#include "generator.h"
#include "constants.h"

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

timer_id_t generator_init(){
    timer_id_t tim = SDL_AddTimer(500, callback_gen, NULL);
    srand((unsigned) time(&t) );
    return tim;
}

void generator_clean(timer_id_t id){
    SDL_RemoveTimer(id);
}




