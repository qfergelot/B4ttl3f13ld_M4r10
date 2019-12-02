#include "mario.h"
#include "text.h"
#include "constants.h"


dynamic_object_t mario_obj;

void create_mario(void){
    object_object_init (&mario_obj, &mario_sprite, OBJECT_TYPE_MARIO, OBJECT_STATE_IN_AIR, 64, 1, 0, 0, RIGHT, 13);
}

void animation_mario_timer_expired (dynamic_object_t *obj){
    if (obj->state_of_blink){
        SDL_SetTextureAlphaMod(obj->sprite->texture, (Uint8) 0);
        obj->state_of_blink = 0;
    }
    else{
        SDL_SetTextureAlphaMod(obj->sprite->texture, (Uint8) 255);
        obj->state_of_blink = 1;
    }
}

void animation_dead_mario (dynamic_object_t* obj){
    obj->ys = 0;
    obj->state = OBJECT_STATE_DEAD;
    animation_mario_timer_expired(obj);
    animation_timer_add (obj, 100);
    animation_text_add(obj);
}

void animation_mario_moves (dynamic_object_t *obj, int left, int right, int up, int space){

    if (obj->state != OBJECT_STATE_DEAD){
        obj->xs = 0;
        // Move the mario accordining
        if (obj->x_screen >= 0 && obj->x_screen < WIN_WIDTH){
            if (left){
                obj->xs -= MARIO_SPEED;
                obj->in_movement = 1;
                obj->direction = LEFT;
                obj->direction_factor = -1;
            }
            else if (right){
                obj->xs += MARIO_SPEED;
                obj->in_movement = 1;
                obj->direction = RIGHT;
                obj->direction_factor = 1;
            }
            else obj->in_movement = 0;

            if(up && obj->state == OBJECT_STATE_NORMAL){
                obj->state = OBJECT_STATE_IN_AIR;
                obj->ys = -22;
            }
        }

        //Tir de Missile
        if (space && obj->cd_count == 0){
            obj->cd_count = obj->cooldown;
            animation_missile_add(obj);
        }

        //Taking Damage
        if (obj->y_screen == 0 ){
            animation_dead_mario(obj);
        }

    }
    else{
        //Recovery
        if (obj->y_screen >= WIN_HEIGHT - obj->sprite->display_height){
            obj->state = OBJECT_STATE_NORMAL;
            animation_timer_cancel(obj);
            SDL_SetTextureAlphaMod(obj->sprite->texture, (Uint8) 255);
            obj->state_of_blink = 1;
        }
    }
}

int animation_mario_onestep (dynamic_object_t *obj ){
    //Gestion du saut
    if (obj->state == OBJECT_STATE_IN_AIR && obj->ys < 0){
        obj->ys += 1;
    }
    else if (obj->state == OBJECT_STATE_IN_AIR)
        obj->ys += 1;
    if(obj->y_screen + obj->sprite->display_height >= WIN_HEIGHT){
        obj->state = OBJECT_STATE_NORMAL;
    }

    //TODO FAIRE UN xmap

    //Limites Artificielles(BLOCKS)

    if (map[obj->x_map/BLOCK_SIZE][(obj->y_map + obj->ys + obj->sprite->display_height)/BLOCK_SIZE + 1 ] == MAP_OBJECT_SOLID){
        //if (obj->y_map + obj->ys > BLOCK_SIZE){
            //obj->y_screen = WIN_HEIGHT - obj->sprite->display_height - BLOCK_SIZE;
            obj->ys = 0;
            obj->state = OBJECT_STATE_NORMAL;
        //}
    }

    if(map[(obj->x_map + obj->xs)/BLOCK_SIZE][obj->y_map/BLOCK_SIZE] == MAP_OBJECT_SOLID || map[(obj->x_map + obj->xs + obj->sprite->display_width)/BLOCK_SIZE][obj->y_map/BLOCK_SIZE] == MAP_OBJECT_SOLID){
        obj-> xs = 0;
    }

    printf("%d, %d\n", obj->x_screen, obj->y_screen);
    printf("%d, %d\n\n", obj->x_map, obj->y_map);

    obj->y_screen += obj->ys;
    obj->x_screen += obj->xs;
    obj->x_map += obj->xs;
    obj->y_map += obj->ys;

    //Limites Physiques
    if (obj->y_screen <0) obj->y_screen = 0;

    if (obj->y_screen > WIN_HEIGHT - obj->sprite->display_height) obj->y_screen = WIN_HEIGHT - obj->sprite->display_height;

    if (obj->x_screen < LEFT_LIMIT_SCROLLING) obj->x_screen = LEFT_LIMIT_SCROLLING;

    if (obj->x_screen > RIGHT_LIMIT_SCROLLING) obj->x_screen = RIGHT_LIMIT_SCROLLING;

    if (obj->x_map < LEFT_MAP_LIMIT) obj->x_map = LEFT_MAP_LIMIT;

    if (obj->x_map > RIGHT_MAP_LIMIT) obj->x_map = RIGHT_MAP_LIMIT;

    //Animation
    if (obj->in_movement){
        obj->anim_step++;
        obj->anim_step %= obj->sprite->nb_images;
        // if (obj->reverse){
        //     obj->anim_step--;
        //     if (obj->anim_step == 0){
        //         obj->reverse--;
        //     }
        // }
        // else {
        //     obj->anim_step++;
        //     if (obj->anim_step % obj->sprite->nb_images == 0){
        //         obj->reverse++;
        //         obj->anim_step--;
        //     }
        // }
    }


    //Cooldaown missile
    if (obj->cd_count > 0){
        obj->cd_count --;
    }

    return 0;

}





