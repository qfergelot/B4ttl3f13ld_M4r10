#ifndef MAP_IS_DEF
#define MAP_IS_DEF

/* #include "constants.h" */
/* #include "sprite.h" */
/* #include "object.h" */
/* #include "graphics.h" */

   

    extern int** map;

    void map_new(unsigned width, unsigned height);
    void map_allocate(unsigned width, unsigned height);
    void map_set(int map_object, unsigned x, unsigned y);
    int map_get(int x, int y);
    void map_object_add(char* path, int nb_sprites, int type, int map_object);
    void map_render_objects(void);
    void map_display();
    void map_save();

    void map_set_at(int map_object, unsigned x_pixel, unsigned y_pixel);

    int get_state_of_map_object(int map_object);
    int get_state_of_object_at(int x_block, int y_block);
    int get_state(int x_pixel, int y_pixel);

#endif
