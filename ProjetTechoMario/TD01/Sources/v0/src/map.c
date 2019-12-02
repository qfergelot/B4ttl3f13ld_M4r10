#include "map.h"
#include <stdlib.h>
#include "constants.h"

int** map;

void map_new(unsigned width, unsigned height){
    map_object_add("../images/wall.png", 1, MAP_OBJECT_SOLID);
    map_object_add("../images/ground.png.png", 1, MAP_OBJECT_SOLID);

    map_allocate(width, height);
    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++){
            if(y == WIN_HEIGHT/BLOCK_SIZE){//Le Sol
                map_set(MAP_OBJECT_SOLID, x, y);
            }
            else{
                if (x == 0 || x == width - 1){//Les Murs
                    map_set(MAP_OBJECT_SOLID, x, y);
                }
                else{// Le Reste
                    map_set(MAP_OBJECT_AIR, x, y);
                }
            }
        }
    }
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

void map_object_add(const char* path, int nb_sprites, int type){

}