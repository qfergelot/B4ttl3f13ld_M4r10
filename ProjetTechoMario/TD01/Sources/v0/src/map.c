#include "map.h"
#include <stdlib.h>
#include <stdio.h>


int** map;

void map_new(unsigned width, unsigned height){
    map_object_add(NULL, 0, MAP_OBJECT_AIR, AIR);
    map_object_add("../images/wall.png", 1, MAP_OBJECT_SOLID, WALL);
    map_object_add("../images/ground.png", 1, MAP_OBJECT_SOLID, GROUND);
    map_object_add("../images/floor.png", 1, MAP_OBJECT_SEMI_SOLID, FLOOR);

    map_allocate(width, height);
    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++){
            if(y == WIN_HEIGHT/BLOCK_SIZE){//Le Sol
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

    map_set(FLOOR, 5, WIN_HEIGHT/BLOCK_SIZE - 3);
    map_set(FLOOR, 6, WIN_HEIGHT/BLOCK_SIZE - 3);
    map_set(FLOOR, 7, WIN_HEIGHT/BLOCK_SIZE - 3);
    map_set(FLOOR, 8, WIN_HEIGHT/BLOCK_SIZE - 3);
    map_set(FLOOR, 8, WIN_HEIGHT/BLOCK_SIZE - 6);
    map_set(FLOOR, 10, WIN_HEIGHT/BLOCK_SIZE - 6);
    map_set(FLOOR, 7, WIN_HEIGHT/BLOCK_SIZE - 9);
}

void map_allocate(unsigned width, unsigned height){
    map = (int **) malloc(width * sizeof(int*));
    for (int x = 0; x < width; x++){
        map[x] = (int *) malloc(height * sizeof(int));
    }
}

void map_set(int map_object, int x, int y){
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
        sprite_t sp;
        static_object_t obj;
        sprite_create(&sp, path, BLOCK_SIZE, BLOCK_SIZE, nb_sprites, RIGHT);
        static_object_init(&obj, &sp, type);
        static_object[map_object] = &obj;
    }
}

void map_render_objects(){
    for(int x = 0; x < MAP_WIDTH; x++){
        for(int y = 0; y < MAP_HEIGHT; y++){
            int map_object = map_get(x, y);
            if (map_object != AIR){
                graphics_render_static_object(static_object[map_object], x, y);
            }
        }
    }
}