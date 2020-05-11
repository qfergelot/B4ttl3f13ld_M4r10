#include "dropbomb.h"
#include "missile.h"
#include "explosion.h"
#include "constants.h"
#include "animation.h"
#include "debug.h"
#include "error.h"
#include "map.h"
#include "generator.h"

int max_number = WIN_WIDTH/BLOCK_SIZE;
int latence_between_drops = 500;
int ptr_i[WIN_WIDTH/BLOCK_SIZE + 1][1];
timer_id_t id;


void animation_dropbomb_add (void* x){
    int tmp_x = *(int*)x ;
    //printf("%p->%d\n", x, tmp_x);
    dynamic_object_t* missile_obj = (dynamic_object_t*) malloc(sizeof(dynamic_object_t));
    if (missile_obj == NULL)
        exit_with_error("Not Enough Memory\n");

    PRINT_DEBUG('m', "Malloc done on object %p\n", missile_obj);
    
    object_object_init (missile_obj, &drop_sprite, OBJECT_TYPE_DROP, OBJECT_STATE_IN_AIR, tmp_x , BLOCK_SIZE, 0, MISSILE_SPEED, RIGHT, 0);
    animation_mobile_object_add (missile_obj);
}


int animation_dropbomb_onestep (dynamic_object_t *obj){
    //print position
    //printf("%d, %d\n", obj->x_screen, obj->y_screen);
    //printf("%d, %d\n", obj->x_map, obj->y_map);
    //printf("%d, %d\n", obj->x_map, obj->y_map + obj->sprite->display_height);
    //printf("%d, %d\n", obj->x_map/BLOCK_SIZE, obj->y_map/BLOCK_SIZE);
    if (obj->state == OBJECT_STATE_DESTROYED) return 1;

    obj->y_screen += obj->ys;
    obj->y_map += obj->ys;

    if(obj->y_map + obj->ys >= (MAP_HEIGHT - 1) * BLOCK_SIZE ||
        get_state(obj->x_map, obj->y_map + obj->ys) == MAP_OBJECT_SOLID ||
        get_state(obj->x_map, obj->y_map + obj->ys + obj->sprite->display_height) == MAP_OBJECT_SOLID)
    {
        animation_missile_dead(obj);
    }
    if( get_state(obj->x_map, obj->y_map ) == MAP_OBJECT_DESTRUCTIBLE)
    {
        map_set_at(AIR, obj->x_map, obj->y_map);
        animation_missile_dead(obj);
    }

    obj->anim_step++;
    obj->anim_step %= obj->sprite->nb_images;

    return 0;
}

Uint32 callback_create_bomb(Uint32 delay, void* param){
    SDL_Event event;
    SDL_UserEvent userevent;

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = animation_dropbomb_add;
    userevent.data2 = param;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);

    return(0);
}

void drop_the_bombs(){
    int left = current_object_focus->x_map - current_object_focus->x_screen;
    for(int cur = 0; cur < max_number; cur++){
        //animation_dropbomb_add(i*BLOCK_SIZE + left);
        //i[cur_bomb] = (cur_bomb+1)*BLOCK_SIZE + left;
        ptr_i[cur][0] = (cur+1) * BLOCK_SIZE + left;
        id = generator_init(cur * latence_between_drops, callback_create_bomb, ptr_i[cur]);
       // printf("%d\n", cur);
    }
    generator_clean(id);
}






