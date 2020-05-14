#ifndef OBJECT_IS_DEF
#define OBJECT_IS_DEF

#include <SDL.h>
#include "sprite.h"
#include "list.h"
/* #include "missile.h" */
/* #include "explosion.h" */

/* #include "text.h" */
#include "constants.h"



typedef SDL_TimerID timer_id_t;

    enum { // TYPE D'OBJETS
        OBJECT_TYPE_MARIO,
        OBJECT_TYPE_MISSILE,
        OBJECT_TYPE_EXPLOSION,
        OBJECT_TYPE_TEXT,
        OBJECT_TYPE_TREE,
        OBJECT_TYPE_CURSOR,
        OBJECT_TYPE_DROP,
        OBJECT_TYPE_MINE,
        __OBJECT_TYPE_NUM
    };

    enum { // ÉTATS DES OBJETS
        OBJECT_STATE_NORMAL,
        OBJECT_STATE_IN_AIR,
        OBJECT_STATE_DESTROYED,
        OBJECT_STATE_DEAD
    };

    enum { // TYPE DE BLOCS
        AIR,
        WALL,
        GROUND,
        FLOOR,
        GRASS,
        FLOWER,
        FLOWER2,
        HERB,
        COIN,
        MARBLE,
        MINE
        
    };

    enum { // PROPRIÉTÉS DES BLOCS
        MAP_OBJECT_AIR,
        MAP_OBJECT_SOLID,
        MAP_OBJECT_SEMI_SOLID,
        MAP_OBJECT_LIQUID,
        MAP_OBJECT_COLLECTIBLE,
        MAP_OBJECT_DESTRUCTIBLE,
        MAP_OBJECT_EXPLOSIVE,
        MAP_OBJECT_TRANSPARENT,
        MAP_OBJECT_ACTIVABLE
    };

    enum{
        RED,
        GREEN
    };

    typedef struct _stat_obj{
        sprite_t *sprite;
        int state;
        int anim_step;
    } static_object_t;

    extern static_object_t* static_object[BLOCK_NUMBER];

    typedef struct _dyn_obj {
        sprite_t *sprite;
        // can be OBJECT_TYPE_BIRD, ...
        int type;
        // can be OBJECT_STATE_NORMAL, ...
        int state;
        // position
        int x_screen, y_screen;
        int x_map, y_map;
        // speed
        int xs, ys;

        int direction; // 0 = left, 1 = right
        int direction_factor;   // -1 = left, 1 = right
        int anim_step;
        int reverse;

        int cooldown;
        int cd_count;
        int shoot_offset;

        int state_of_blink;

        float val_sin;
        int opacity;
        int zoom;

        int in_movement;
        int you_shall_not_pass;
        int you_shall_fall;

        int number_piece;

        int cursor_sprite_to_display_index;
        int mine_color;

        timer_id_t timer_id;

        //struct list_head *global_chain;
        struct list_head global_chain;

    } dynamic_object_t;

    extern dynamic_object_t* current_object_focus;

    typedef int (* animate_func_t)(dynamic_object_t *obj);
    typedef void (* timer_func_t)(dynamic_object_t *obj);
    typedef void (* dead_func_t)(dynamic_object_t *obj);

    /* int animation_badbird_onestep(dynamic_object_t* obj); */
    /* void animation_badbird_dead(dynamic_object_t* obj); */
    /* int animation_text_onestep(dynamic_object_t* obj); */


    typedef struct {
        animate_func_t animate_func;
        timer_func_t timer_func;
        dead_func_t dead_func;
    } object_type_t;

    extern object_type_t object_class [];

    // Initialize the object_class array
    void object_init (void);

    // Initialize fields of s_object obj
    void static_object_init (static_object_t *obj, sprite_t *sp, int state);
    // Initialize fields of object obj
    void object_object_init (dynamic_object_t *obj, sprite_t *sp, int type, int state, int x, int y, int xs, int ys, int direction, int cooldown);

#endif
