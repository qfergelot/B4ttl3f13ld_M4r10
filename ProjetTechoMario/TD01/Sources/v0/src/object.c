#include <SDL_image.h>

#include "object.h"
#include "missile.h"
#include "explosion.h"
#include "text.h"
#include "mario.h"



object_type_t object_class [6];



void object_init (void){
    //initialisation de object_class
    object_class[OBJECT_TYPE_MARIO].animate_func = animation_mario_onestep;
    object_class[OBJECT_TYPE_MISSILE].animate_func = animation_missile_onestep;
    object_class[OBJECT_TYPE_EXPLOSION].animate_func = animation_explosion_onestep;
    object_class[OBJECT_TYPE_TEXT].animate_func = animation_text_onestep;

    object_class[OBJECT_TYPE_MARIO].timer_func = animation_mario_timer_expired;
    object_class[OBJECT_TYPE_MISSILE].timer_func = NULL;
    object_class[OBJECT_TYPE_EXPLOSION].timer_func = NULL;
    object_class[OBJECT_TYPE_TEXT].timer_func = NULL;

    object_class[OBJECT_TYPE_MARIO].dead_func = animation_dead_mario;
    object_class[OBJECT_TYPE_MISSILE].dead_func = animation_missile_dead;
    object_class[OBJECT_TYPE_EXPLOSION].dead_func = NULL;
    object_class[OBJECT_TYPE_TEXT].dead_func = NULL;
}

void static_object_init(static_object_t *obj, sprite_t *sp, int state){
    obj->sprite = sp;
    obj->state = state;
    obj->anim_step = 0;
}


void object_object_init (dynamic_object_t *obj, sprite_t *sp, int type, int state, int x, int y, int xs, int ys, int direction, int cooldown){
    obj->sprite = sp;
    obj->type = type;
    obj->state = state;
    obj->x_screen = x;
    obj->x_map = x;
    obj->y_screen = y;
    obj->y_map = y;
    obj->xs = xs;
    obj->ys = ys;
    obj->direction = direction;
    obj->anim_step = 0;
    obj->reverse = 0;
        obj->direction_factor = 1;
    if (obj->direction == LEFT)
        obj->direction_factor = -1;


    obj->cooldown = cooldown;
    obj->cd_count = 0;
    obj->shoot_offset = sp->display_width/2;
    obj->state_of_blink = 1;
    obj->val_sin = 0;
    obj->opacity = 255;
    obj->zoom = 1;
    obj->you_shall_not_pass = 1;

    obj->in_movement = 0;

    obj->global_chain.next = &(obj->global_chain);
    obj->global_chain.prev = &(obj->global_chain);
}

int get_state_of_map_object(int map_object){
    static_object_t* tmp = static_object[map_object];
    if (tmp == NULL){
        return MAP_OBJECT_AIR;
    }
    else return tmp->state;
}
