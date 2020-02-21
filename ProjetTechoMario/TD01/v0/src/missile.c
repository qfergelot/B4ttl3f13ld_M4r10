#include "missile.h"
#include "explosion.h"
#include "constants.h"
#include "animation.h"
#include "debug.h"
#include "error.h"
#include "map.h"


void animation_missile_add (dynamic_object_t *obj){
    dynamic_object_t* missile_obj = (dynamic_object_t*) malloc(sizeof(dynamic_object_t));
    if (missile_obj == NULL)
        exit_with_error("Not Enough Memory\n");

    PRINT_DEBUG('m', "Malloc done on object %p\n", missile_obj);
    object_object_init (missile_obj, &missile_sprite, OBJECT_TYPE_MISSILE, OBJECT_STATE_IN_AIR, obj->x_screen + obj->shoot_offset * obj->direction_factor, obj->y_screen + obj->sprite->display_height/3 , MISSILE_SPEED, 0, obj->direction, 0);
    missile_obj->x_map = obj->x_map;
    missile_obj->y_map = obj->y_map;
    animation_mobile_object_add (missile_obj);
}


int animation_missile_onestep (dynamic_object_t *obj){
    //print position
    //printf("%d, %d\n", obj->x_screen, obj->y_screen);
    //printf("%d, %d\n", obj->x_map, obj->y_map);
    //printf("%d, %d\n", obj->x_map, obj->y_map + obj->sprite->display_height);
    //printf("%d, %d\n", obj->x_map/BLOCK_SIZE, obj->y_map/BLOCK_SIZE);
    if (obj->state == OBJECT_STATE_DESTROYED) return 1;

    if (obj->direction == RIGHT){
        obj->x_screen += obj->xs;
        obj->x_map += obj->xs;
    }
    else{
        obj->x_screen -= obj->xs;
        obj->x_map -= obj->xs;
    }

    if(get_state(obj->x_map + obj->xs, obj->y_map + BLOCK_SIZE) == MAP_OBJECT_SOLID ||
        get_state(obj->x_map + obj->xs + obj->sprite->display_width, obj->y_map + BLOCK_SIZE) == MAP_OBJECT_SOLID ||
        get_state(obj->x_map + obj->xs, obj->y_map + obj->sprite->display_height + 15) == MAP_OBJECT_SOLID ||
        get_state(obj->x_map + obj->xs + obj->sprite->display_width, obj->y_map + obj->sprite->display_height + 15) == MAP_OBJECT_SOLID){
        animation_missile_dead(obj);
    }

    obj->anim_step++;
    obj->anim_step %= obj->sprite->nb_images;

    return 0;
}

void animation_missile_dead (dynamic_object_t* obj){
    obj->state = OBJECT_STATE_DESTROYED;
    animation_explosion_from_missile_add(obj);
}
