#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include "constants.h"
#include "sprite.h"
#include "object.h"
#include "graphics.h"
#include "mario.h"

int** map;
//static int tmp = 0;

void map_new(unsigned width, unsigned height){
    map_object_add(NULL, 0, MAP_OBJECT_AIR, AIR);
    map_object_add("../images/wall.png", 1, MAP_OBJECT_SOLID, WALL);
    map_object_add("../images/ground.png", 1, MAP_OBJECT_SOLID, GROUND);
    map_object_add("../images/floor.png", 1, MAP_OBJECT_SEMI_SOLID, FLOOR);
    map_object_add("../images/flower.png", 1, MAP_OBJECT_TRANSPARENT, FLOWER);
    map_object_add("../images/flower2.png", 1, MAP_OBJECT_TRANSPARENT, FLOWER2);
    map_object_add("../images/grass.png", 1, MAP_OBJECT_SEMI_SOLID, GRASS);
    map_object_add("../images/herb.png", 1, MAP_OBJECT_TRANSPARENT, HERB);
    map_object_add("../images/coin.png", 10, MAP_OBJECT_COLLECTIBLE, COIN);

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

void map_set_at(int map_object, unsigned x_pixel, unsigned y_pixel){
    map_set(map_object, x_pixel/BLOCK_SIZE, y_pixel/BLOCK_SIZE);
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
    int x_camera = (current_object_focus->x_map - current_object_focus->x_screen);
    int y_camera = (current_object_focus->y_map - current_object_focus->y_screen);
    //tmp++;
    //if(tmp == 4){
        static_object[COIN]->anim_step ++;
        static_object[COIN]->anim_step %= static_object[COIN]->sprite->nb_images;
        //tmp = 0;
    //}
   


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
    printf("\n");
}

int get_state_of_map_object(int map_object){
    static_object_t* tmp = static_object[map_object];
    if (tmp == NULL){
        return MAP_OBJECT_AIR;
    }
    else return tmp->state;
}

int get_state_of_object_at(int x_block, int y_block){
    return get_state_of_map_object(map_get(x_block, y_block));
}

int get_state(int x_pixel, int y_pixel){
    return get_state_of_object_at(x_pixel/BLOCK_SIZE, y_pixel/BLOCK_SIZE);
}


void construct_str_line(char* line, int y){
    char tmp_obj[3];
    for(int x = 0; x<MAP_WIDTH; x++){
        sprintf(tmp_obj, "%d ", map_get(x, y));
        strcat(line, tmp_obj);
    }
    strcat(line, "\n");
}

void map_save(){
    int size;
    int MAX_ALLOWED = 2 * MAP_WIDTH + 1;
    char line[MAX_ALLOWED];
    int fd = open("save_map_default.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);

    //Dimensions
    sprintf(line, "%d %d\n", MAP_WIDTH, MAP_HEIGHT);
    size = write(fd, line, 6);
    if (size == -1){
        fprintf(stderr, "Saving issue\n");
        return;
    }
    memset(line, 0, sizeof(line));

    //Matrice
    for (int y = 0; y<MAP_HEIGHT; y++){
        construct_str_line(line, y);
        size = write(fd, line, MAX_ALLOWED);
        memset(line, 0, sizeof(line));
    }
    close(fd);
}

void load_map(char* map_to_load){
    
    if(map_to_load == NULL){
        map_to_load = "default_map.txt";
    }

    char number[5];
    memset(number, 0, 4);
    char c = '#';
    int size = -1;

    int fd = open(map_to_load, O_RDONLY, 0644);

    //GET/SET DIMENSIONS
    while(1){
        size += read(fd, &c, 1);
        if(c == ' ') break;
        number[size] = c;
    }
    dim_w = atoi(number);
    memset(number, 0, 4);
    size = -1;

    while(1){
        size += read(fd, &c, 1);
        if(c == '\n') break;
        number[size] = c;
    }
    dim_h = atoi(number);
    memset(number, 0, 4);
    size = -1;

    //printf("%d, %d\n", MAP_WIDTH, MAP_HEIGHT);
    //Create map
    map_new(MAP_WIDTH, MAP_HEIGHT);

    //GET/SET MATRICE
    for(int y = 0; y<MAP_HEIGHT; y++){
        for(int x = 0; x<MAP_WIDTH; x++){
            while(1){ // Each number will be followed by a space
                size += read(fd, &c, 1);
                if(c == ' ') break;
                number[size] = c;
            }
            map_set(atoi(number), x, y);
            memset(number, 0, 4);
            size = -1;
        }
        lseek(fd, 1, SEEK_CUR); // pass the \n
    }



    close(fd);
}
