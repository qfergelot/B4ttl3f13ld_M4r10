#include "animation.h"



LIST_HEAD(all_objects); //struct list_head all_objects = { &(all_objects), &(all_objects) }

int graphics_render_scrolling_object();


void animation_init (void){
    create_mario();
    create_trees();

    animation_mobile_object_add (&mario_obj);
}


void animation_one_step (int left, int right, int up, int down, int space){
    animation_mario_moves(&mario_obj, left, right, up, space);
    // Dans la liste des obj, pour chaque obj lancer la ligne
    // object_class[obj->type].animate_func(&obj)
    for_all_objects (obj)
    {
        //calcul de hitbox
        for_all_other_objects (oobj){
            if (collide(obj, oobj)){
                object_class[obj->type].dead_func(obj);
                object_class[oobj->type].dead_func(oobj);
                break;
            }
        }
        animate_func_t func = object_class[obj->type].animate_func;
        if (func != NULL){
            if(func(obj)){
                if (obj->type == OBJECT_TYPE_MISSILE){
                    animation_explosion_from_missile_add (obj);
                }
                animation_mobile_object_del(obj);
            }
        }
    }
}


void animation_render_objects (void){
    //ici on render tous les obj dynamic
    graphics_render_scrolling_object(&tree_obj[2], 4);
    graphics_render_scrolling_object(&tree_obj[1], 2);
    graphics_render_scrolling_object(&tree_obj[0], 1);

    for_all_objects (obj) {
        graphics_render_object (obj);
    }
}

void animation_mobile_object_add (dynamic_object_t *obj){
    list_add_tail(&(obj->global_chain), &all_objects);
}


void animation_mobile_object_del (dynamic_object_t *obj){
    list_del(&(obj->global_chain));
    free(obj);
    PRINT_DEBUG('m', "Free done on object %p\n", obj);
}

void animation_clean (void){
    for_all_objects (obj)
    {
        if (obj->type != OBJECT_TYPE_MARIO){
            animation_mobile_object_del(obj);
        }
    }
}

void animation_timer_add (dynamic_object_t *obj, Uint32 delay){
    obj->timer_id = timer_set(delay, obj);
}

void animation_timer_cancel(dynamic_object_t *obj){
    timer_cancel(obj->timer_id);
}

void animation_timer_expired (void *arg1, void *arg2){

}
