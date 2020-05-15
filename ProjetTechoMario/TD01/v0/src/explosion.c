#include "explosion.h"
#include "map.h"
#include "debug.h"
#include "animation.h"
#include "graphics.h"
#include "error.h"



void animation_explosion_from_missile_add (dynamic_object_t *missile){

    dynamic_object_t* exp_obj = (dynamic_object_t*) malloc(sizeof(dynamic_object_t));
    if (exp_obj == NULL)
        exit_with_error("Not Enough Memory\n");

    PRINT_DEBUG('m', "Malloc done on object %p\n", exp_obj);
    object_object_init (exp_obj, &explosion_sprite, OBJECT_TYPE_EXPLOSION, OBJECT_STATE_IN_AIR, missile->x_map, missile->y_map, 0, 0, RIGHT, 0);
    animation_mobile_object_add(exp_obj);
}

int animation_explosion_onestep (dynamic_object_t *obj){

    if (obj->anim_step == 1){
        for(int i = -1; i<2; i++){
            for(int j = -1; j<2; j++){
                if (get_state(obj->x_map + i*BLOCK_SIZE + 10, obj->y_map + j*BLOCK_SIZE + 10) == MAP_OBJECT_DESTRUCTIBLE){
                    map_set_at(AIR, obj->x_map + i*BLOCK_SIZE + 10, obj->y_map + j*BLOCK_SIZE + 10);
                }
            }
        }
    }

    obj->anim_step++;
    if(obj->anim_step == obj->sprite->nb_images)
        return 1;
    return 0;
}
