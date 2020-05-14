#include "mine.h"
#include "collision.h"
#include "dropbomb.h"
#include "generator.h"
#include "explosion.h"
#include "constants.h"
#include "animation.h"
#include "debug.h"
#include "error.h"
#include "map.h"

void animation_mine_add (int x_block, int y_block){
    dynamic_object_t* missile_obj = (dynamic_object_t*) malloc(sizeof(dynamic_object_t));
    if (missile_obj == NULL)
        exit_with_error("Not Enough Memory\n");

    PRINT_DEBUG('m', "Malloc done on object %p\n", missile_obj);
    object_object_init (missile_obj, &mine_sprite, OBJECT_TYPE_MINE, OBJECT_STATE_NORMAL, x_block * BLOCK_SIZE, y_block * BLOCK_SIZE , 0, 0, RIGHT, MINE_IMAGE_SAME_COLOR);
    missile_obj->mine_color = rand() & 1; // Comme il n'y a que deux couleurs c'est ok, avec plus de couleur ce sera un %NB_COLOR
    missile_obj->anim_step = missile_obj->mine_color * MINE_IMAGE_SAME_COLOR;
    animation_mobile_object_add (missile_obj);
}

void advance_anim(dynamic_object_t* obj){
    if(obj->anim_step == (obj->mine_color * MINE_IMAGE_SAME_COLOR) + MINE_IMAGE_SAME_COLOR){
        if(obj->cd_count == obj->cooldown){
            if(obj->mine_color == GREEN){
                drop_the_bombs();
                animation_mine_dead(obj);
            }else {
                animation_mine_dead(obj);
            }
        }else{
            obj->cd_count ++;
            obj->anim_step = obj->mine_color * MINE_IMAGE_SAME_COLOR;
        }
    }else{
        obj->anim_step ++;
    }

}

int animation_mine_onestep (dynamic_object_t *obj){
    //print position
    //printf("%d, %d\n", obj->x_screen, obj->y_screen);
    //printf("%d, %d\n", obj->x_map, obj->y_map);
    //printf("%d, %d\n", obj->x_map, obj->y_map + obj->sprite->display_height);
    //printf("%d, %d\n", obj->x_map/BLOCK_SIZE, obj->y_map/BLOCK_SIZE);
    if (obj->state == OBJECT_STATE_DESTROYED) return 1;

    if(!obj->in_movement){
        if (collide(obj, current_object_focus)){
            obj->in_movement = 1;
        }
    }

    if(obj->in_movement){ // si la mine est activée, elle ne sera jamais désactivée
        advance_anim(obj);
    }

    return 0;
}

void animation_mine_dead (dynamic_object_t* obj){
    //printf("%d, %d\n", obj->x_map, obj->y_map);
    obj->state = OBJECT_STATE_DESTROYED;
    map_set_at(AIR, obj->x_map, obj->y_map);
    animation_explosion_from_missile_add(obj);
}
