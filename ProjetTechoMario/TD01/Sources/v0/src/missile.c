#include "missile.h"


void animation_missile_add (dynamic_object_t *bird){
    dynamic_object_t* missile_obj = (dynamic_object_t*) malloc(sizeof(dynamic_object_t));
    if (missile_obj == NULL)
        exit_with_error("Not Enough Memory\n");

    PRINT_DEBUG('m', "Malloc done on object %p\n", missile_obj);
    object_object_init (missile_obj, &missile_sprite, OBJECT_TYPE_MISSILE, OBJECT_STATE_IN_AIR, bird->x + 4*bird->sprite->display_width/5 , bird->y + bird->sprite->display_height/3 , 6, 0, RIGHT, 0);
    animation_mobile_object_add (missile_obj);
}


int animation_missile_onestep (dynamic_object_t *obj){
    if (obj->state == OBJECT_STATE_DESTROYED) return 1;

    obj->x += obj->xs;
    if (obj->x + obj->sprite->display_width >= WIN_WIDTH){
        return 1;
    }

    obj->anim_step++;
    obj->anim_step %= obj->sprite->nb_images;

    return 0;
}

void animation_missile_dead (dynamic_object_t* obj){
    obj->state = OBJECT_STATE_DESTROYED;
}