#include <SDL_image.h>

#include "object.h"

#include "bird.h"
#include "missile.h"
#include "explosion.h"
#include "bad.h"
#include "text.h"

object_type_t object_class [6];



void object_init (void){
    //initialisation de object_class

    object_class[OBJECT_TYPE_BIRD].animate_func = animation_bird_onestep;
    object_class[OBJECT_TYPE_MISSILE].animate_func = animation_missile_onestep;
    object_class[OBJECT_TYPE_EXPLOSION].animate_func = animation_explosion_onestep;
    object_class[OBJECT_TYPE_TEXT].animate_func = animation_text_onestep;
    object_class[OBJECT_TYPE_BADBIRD].animate_func = animation_badbird_onestep;

    object_class[OBJECT_TYPE_BIRD].timer_func = animation_bird_timer_expired;
    object_class[OBJECT_TYPE_MISSILE].timer_func = NULL;
    object_class[OBJECT_TYPE_EXPLOSION].timer_func = NULL;
    object_class[OBJECT_TYPE_TEXT].timer_func = NULL;
    object_class[OBJECT_TYPE_BADBIRD].timer_func = NULL;

    object_class[OBJECT_TYPE_BIRD].dead_func = animation_dead_bird;
    object_class[OBJECT_TYPE_MISSILE].dead_func = animation_missile_dead;
    object_class[OBJECT_TYPE_EXPLOSION].dead_func = NULL;
    object_class[OBJECT_TYPE_TEXT].dead_func = NULL;
    object_class[OBJECT_TYPE_BADBIRD].dead_func = animation_badbird_dead;
}


void object_object_init (dynamic_object_t *obj, sprite_t *sp, int type, int state, int x, int y, int xs, int ys, int direction, int cooldown){
    obj->sprite = sp;
    obj->type = type;
    obj->state = state;
    obj->x = x;
    obj->y = y;
    obj->xs = xs;
    obj->ys = ys;
    obj->direction = direction;
    obj->anim_step = 0;
    obj->reverse = 0;
    obj->cmp_rest = 0;
    obj->resting_toggle = 1;
    obj->cooldown = cooldown;
    obj->cd_count = 0;
    obj->state_of_blink = 1;
    obj->val_sin = 0;
    obj->opacity = 255;
    obj->zoom = 1;

    obj->global_chain.next = &(obj->global_chain);
    obj->global_chain.prev = &(obj->global_chain);


}