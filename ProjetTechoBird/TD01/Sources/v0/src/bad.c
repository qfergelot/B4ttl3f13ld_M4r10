#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bad.h"
#include "constants.h"


void animation_badbird_add (int height, int xs, float vs){
    dynamic_object_t* badbird_obj = (dynamic_object_t*) malloc(sizeof(dynamic_object_t));
    if (badbird_obj == NULL)
        exit_with_error("Not Enough Memory\n");

    PRINT_DEBUG('m', "Malloc done on object %p\n", badbird_obj);
    object_object_init (badbird_obj, &badbird_sprite, OBJECT_TYPE_BADBIRD, OBJECT_STATE_IN_AIR, WIN_WIDTH , height - badbird_sprite.display_height, xs, 0, LEFT, 0);
    badbird_obj->val_sin = vs;
    animation_mobile_object_add (badbird_obj);
}


int animation_badbird_onestep (dynamic_object_t *obj){
    if (obj->state == OBJECT_STATE_DESTROYED) return 1;

    //oscillation
    obj->val_sin += 0.06f ;
    if (obj->val_sin > 2*M_PI)
        obj->val_sin -= 2*M_PI;
    obj->ys = (int) ((float)sin(obj->val_sin) * (float)7);

    if (obj->y < 0) obj->y = 0;
    if (obj->y > WIN_HEIGHT - obj->sprite->display_height) obj->y = WIN_HEIGHT - obj->sprite->display_height;

    //vitesse verticale
    obj->y += obj->ys;

    //vitesse horizontale
    obj->x += obj->xs;

    //Limites Physiques
    if (obj->x + obj->sprite->display_width <= 0){
        return 1;
    }

    //Animation
    if (obj->reverse){
            obj->anim_step--;
            if (obj->anim_step == 0){
                obj->reverse--;
            }
        }
    else {
        obj->anim_step++;
        if (obj->anim_step % obj->sprite->nb_images == 0){
            obj->reverse++;
            obj->anim_step--;
        }
    }

    return 0;
}

void animation_badbird_dead(dynamic_object_t* obj){
    obj->state = OBJECT_STATE_DESTROYED;
}