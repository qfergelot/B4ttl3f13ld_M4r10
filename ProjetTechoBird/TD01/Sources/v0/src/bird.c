#include "bird.h"
#include "text.h"

dynamic_object_t bird_obj;

void create_bird(void){
    object_object_init (&bird_obj, &bird_sprite, OBJECT_TYPE_BIRD, OBJECT_STATE_IN_AIR, WIN_WIDTH/3 - bird_sprite.display_width/2, WIN_HEIGHT/2 - bird_sprite.display_height/2, 0, 0, RIGHT, 13);
}

void animation_bird_timer_expired (dynamic_object_t *obj){
    if (obj->state_of_blink){
        SDL_SetTextureAlphaMod(obj->sprite->texture, (Uint8) 0);
        obj->state_of_blink = 0;
    }
    else{
        SDL_SetTextureAlphaMod(obj->sprite->texture, (Uint8) 255);
        obj->state_of_blink = 1;
    }
}

void animation_dead_bird (dynamic_object_t* obj){
    obj->resting_toggle = 1;
    obj->ys = 0;
    obj->state = OBJECT_STATE_DEAD;
    animation_bird_timer_expired(obj);
    animation_timer_add (obj, 100);
    animation_text_add(obj);
}

void animation_bird_moves (dynamic_object_t *obj, int up, int down, int space){

    if (obj->state != OBJECT_STATE_DEAD){
        // Move the bird accordining
        if (obj->y > 1 && obj->y < WIN_HEIGHT){
            if (up){
                obj->resting_toggle = 0;
                obj->ys -= 6;
            }
            else if (down) obj->ys += 2;
            else obj->resting_toggle = 1;
        }

        //Tir de Missile
        if (space && obj->cd_count == 0){
            obj->cd_count = obj->cooldown;
            animation_missile_add(obj);
        }

        //Taking Damage
        if (obj->y == 0 ){
            animation_dead_bird(obj);
        }

    }
    else{
        //Recovery
        if (obj->y >= WIN_HEIGHT - obj->sprite->display_height){
            obj->state = OBJECT_STATE_IN_AIR;
            animation_timer_cancel(obj);
            SDL_SetTextureAlphaMod(obj->sprite->texture, (Uint8) 255);
            obj->state_of_blink = 1;
        }
    }
}

int animation_bird_onestep (dynamic_object_t *obj ){
    //Movement
    if(obj->ys < 3){
      obj->ys += 4;
    }

    obj->y += obj->ys;

    //Limites Physiques
    if (obj->y <0)
        obj->y = 0;

    if (obj->y > WIN_HEIGHT - obj->sprite->display_height)
        obj->y = WIN_HEIGHT - obj->sprite->display_height;

    //Ralentissement animation
    if(obj->resting_toggle){
        obj->cmp_rest++;
        if ((obj->cmp_rest %= 3) == 0)
            obj->resting_toggle = 0;
    }

    //Animation
    if(!obj->resting_toggle){
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
    }

    //Cooldaown missile
    if (obj->cd_count > 0){
        obj->cd_count --;
    }

    return 0;

}





