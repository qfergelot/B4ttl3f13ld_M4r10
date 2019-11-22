#include "timer.h"

int timer_init (void){

    return 0;
}

timer_id_t timer_set (Uint32 delay, void *param){
    timer_id_t timer_id = SDL_AddTimer(delay, timer_init_callback, param);
    return timer_id;
}

int timer_cancel (timer_id_t timer_id){
    SDL_RemoveTimer(timer_id);
    return 0;
}

Uint32 timer_init_callback(Uint32 interval, void *param){
    dynamic_object_t* obj = (dynamic_object_t*) param;
    SDL_Event event;
    SDL_UserEvent userevent;

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = object_class[obj->type].timer_func;
    userevent.data2 = param;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return(interval);
}
