#include "map.h"
#include <stdlib.h>
#include <stdio.h>

#include "constants.h"
#include "sprite.h"
#include "object.h"
#include "graphics.h"
#include "mario.h"


int** map;

void map_new(unsigned width, unsigned height){
    map_object_add(NULL, 0, MAP_OBJECT_AIR, AIR);
    map_object_add("../images/wall.png", 1, MAP_OBJECT_SOLID, WALL);
    map_object_add("../images/ground.png", 1, MAP_OBJECT_SOLID, GROUND);
    map_object_add("../images/floor.png", 1, MAP_OBJECT_SEMI_SOLID, FLOOR);

    map_allocate(width, height);
    for (unsigned x = 0; x < width; x++){
        for (unsigned y = 0; y < height; y++){
            if(y == height - 1 || y == 0){//Le Sol
                map_set(GROUND, x, y);
            }
            else{
                if (x == 0 || x == width - 1){//Les Murs de debut et fin
                    map_set(WALL, x, y);
                }
                else{// Le Reste
                    map_set(AIR, x, y);
                }
            }
        }
    }


    map_set(FLOOR, 12, MAP_HEIGHT - 1);
    map_set(FLOOR, 11, MAP_HEIGHT - 2);
    map_set(FLOOR, 10, MAP_HEIGHT - 3);
    map_set(FLOOR, 9, MAP_HEIGHT - 3);
    map_set(FLOOR, 8, MAP_HEIGHT - 6);
    map_set(FLOOR, 7, MAP_HEIGHT- 9);
    map_set(WALL, 13, MAP_HEIGHT - 5);
    map_set(WALL, 14, MAP_HEIGHT - 5);
    map_set(WALL, 15, MAP_HEIGHT - 5);
    map_set(WALL, 17, MAP_HEIGHT - 2);
    map_set(WALL, 18, MAP_HEIGHT - 2);
    map_set(GROUND, 20, MAP_HEIGHT - 3);
    map_set(GROUND, 21, MAP_HEIGHT - 3);
}

void map_allocate(unsigned width, unsigned height){
    map = (int **) malloc(width * sizeof(int*));
    for (unsigned x = 0; x < width; x++){
        map[x] = (int *) malloc(height * sizeof(int));
    }
}

void map_set(int map_object, unsigned x, unsigned y){
    map[x][y] = map_object;
}

int map_get(int x, int y){
    return map[x][y];
}

void map_object_add(char* path, int nb_sprites, int type, int map_object){
    if (path == NULL){
        static_object[map_object] = NULL;
    }
    else{
        sprite_t* sp = (sprite_t*) malloc(sizeof(sprite_t));
        static_object_t* obj = (static_object_t*) malloc(sizeof(static_object_t));
        sprite_create(sp, path, BLOCK_SIZE, BLOCK_SIZE, nb_sprites, RIGHT);
        static_object_init(obj, sp, type);
        static_object[map_object] = obj;
    }
}

void map_render_objects(){
    int x_camera = (mario_obj.x_map - mario_obj.x_screen);
    int y_camera = (mario_obj.y_map - mario_obj.y_screen);

    for (int i = x_camera/BLOCK_SIZE; i <= (WIN_WIDTH + x_camera)/BLOCK_SIZE ; i++){
        for (int j = y_camera/BLOCK_SIZE; j <= (WIN_HEIGHT+ y_camera)/BLOCK_SIZE; j++){
            if (i < MAP_WIDTH && j < MAP_HEIGHT) {
                int map_object = map_get(i, j);
                if (map_object != AIR){
                    graphics_render_static_object(static_object[map_object], i * BLOCK_SIZE  - x_camera, j * BLOCK_SIZE - y_camera);
                }
            }
        }
    }
}

void map_display(){
    for (unsigned y = 0; y < MAP_HEIGHT; y++){
        for (unsigned x = 0; x < MAP_WIDTH; x++){
            printf("%d", map_get(x, y));
        }
        printf("\n");
    }
}
