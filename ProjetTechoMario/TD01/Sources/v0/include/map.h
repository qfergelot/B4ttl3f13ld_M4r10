#ifndef MAP_IS_DEF
#define MAP_IS_DEF

#include "constants.h"
#include "sprite.h"
#include "object.h"
#include "graphics.h"

    enum {
        MAP_OBJECT_SOLID,
        MAP_OBJECT_SEMI_SOLID,
        MAP_OBJECT_AIR,
        MAP_OBJECT_NUM
    };

    extern int** map;

    void map_new(unsigned width, unsigned height);
    void map_allocate(unsigned width, unsigned height);
    void map_set(int map_object, int x, int y);
    int map_get(int x, int y);
    void map_object_add(char* path, int nb_sprites, int type, int map_object);
    void map_render_objects(void);

#endif
