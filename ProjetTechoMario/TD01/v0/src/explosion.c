#include "explosion.h"
#include "debug.h"
#include "animation.h"
#include "graphics.h"
#include "error.h"



void animation_explosion_from_missile_add (dynamic_object_t *missile){

    dynamic_object_t* exp_obj = (dynamic_object_t*) malloc(sizeof(dynamic_object_t));
    if (exp_obj == NULL)
        exit_with_error("Not Enough Memory\n");


    PRINT_DEBUG('m', "Malloc done on object %p\n", exp_obj);
    object_object_init (exp_obj, &explosion_sprite, OBJECT_TYPE_EXPLOSION, OBJECT_STATE_IN_AIR, missile->x_screen, missile->y_screen, 0, -5, RIGHT, 0);
    animation_mobile_object_add (exp_obj);
}

int animation_explosion_onestep (dynamic_object_t *obj){
    obj->y_screen += obj->ys;

    obj->anim_step++;
    if(obj->anim_step == obj->sprite->nb_images)
        return 1;
    return 0;
}
