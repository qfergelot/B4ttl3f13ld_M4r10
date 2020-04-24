#include "cursor.h"
#include "sprite.h"
#include "map.h"

dynamic_object_t cursor_obj;

void create_cursor(void){
    object_object_init (&cursor_obj, &cursor_sprite, OBJECT_TYPE_CURSOR, OBJECT_STATE_NORMAL, BLOCK_SIZE*2, BLOCK_SIZE*2, 0, 0, RIGHT, 15);
}

void animation_cursor_moves(dynamic_object_t* obj, int left, int right, int up, int down, int space, int tab) {
    obj->xs = 0;
    obj->ys = 0;
    //Mouvement 
    if(right || left || up || down){
        obj->cd_count++;
        if(obj->cd_count >= obj->cooldown){
            obj->cd_count = 0;
            if (right) obj->xs += BLOCK_SIZE;
            else if (left) obj->xs -= BLOCK_SIZE; 
            if(up) obj->ys -= BLOCK_SIZE;
            else if(down) obj->ys += BLOCK_SIZE;
        }
    }


    if(tab){
        obj->cd_count++;
        if(obj->cd_count >= obj->cooldown){
            obj->cd_count = 0;
            obj->cursor_sprite_to_display_index ++;
            obj->cursor_sprite_to_display_index %= BLOCK_NUMBER;
        }
    }

    if(space){
        map_set_at(obj->cursor_sprite_to_display_index, obj->x_map, obj->y_map);
    }
    

}

void animation_cursor_onestep (dynamic_object_t *obj){

    //Changer le sprite du curseur
    if (obj->cursor_sprite_to_display_index == AIR){
        obj->sprite = &cursor_sprite;
    }else
    {
        obj->sprite = static_object[obj->cursor_sprite_to_display_index]->sprite;
    }
    

    //Déplacement
    obj->y_screen += obj->ys;
    obj->x_screen += obj->xs;
    obj->x_map += obj->xs;
    obj->y_map += obj->ys;


    if (obj->x_map >= MAP_WIDTH * BLOCK_SIZE - DECAL || obj->x_map <= DECAL ) obj->you_shall_not_pass = 0;
    if (obj->y_map + obj->sprite->display_height >=  MAP_HEIGHT * BLOCK_SIZE - 3*BLOCK_SIZE/ 2 || obj->y_map < WIN_HEIGHT/5) obj->you_shall_fall = 0;

    if (obj->you_shall_not_pass && obj->x_screen < LEFT_LIMIT_SCROLLING) obj->x_screen = LEFT_LIMIT_SCROLLING;
    if (obj->you_shall_not_pass && obj->x_screen > RIGHT_LIMIT_SCROLLING) obj->x_screen = RIGHT_LIMIT_SCROLLING;

    if (obj->you_shall_fall && obj->y_screen > 4*WIN_HEIGHT/5) obj->y_screen = 4*WIN_HEIGHT/5;
    if (obj->you_shall_fall && obj->y_screen < WIN_HEIGHT/5) obj->y_screen = WIN_HEIGHT/5;

    if (obj->x_map <= LEFT_MAP_LIMIT) {obj->x_map = LEFT_MAP_LIMIT; obj->x_screen = LEFT_MAP_LIMIT;}
    if (obj->x_map >= RIGHT_MAP_LIMIT) {obj->x_map = RIGHT_MAP_LIMIT; obj->x_screen = WIN_WIDTH - BLOCK_SIZE;}

    if (obj->y_map > BLOCK_SIZE * (MAP_HEIGHT -1)) {obj->y_map = BLOCK_SIZE * (MAP_HEIGHT -1); obj->y_screen = WIN_HEIGHT - BLOCK_SIZE;}
    if (obj->y_map < 0) {obj->y_map = 0; obj->y_screen = 0;}

    if (obj->x_screen >= LEFT_LIMIT_SCROLLING && obj->x_screen <= RIGHT_LIMIT_SCROLLING) obj->you_shall_not_pass = 1;
    if (obj->y_screen <= MAP_HEIGHT * BLOCK_SIZE - 3*BLOCK_SIZE/ 2) obj->you_shall_fall = 1;

    //print position
    //printf("%d, %d\n", obj->x_screen, obj->y_screen);
    //printf("%d, %d\n", obj->x_map, obj->y_map);
    //printf("%d, %d\n\n", obj->x_map/BLOCK_SIZE, obj->y_map/BLOCK_SIZE);
}