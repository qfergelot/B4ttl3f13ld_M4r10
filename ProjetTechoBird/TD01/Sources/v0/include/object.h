#ifndef OBJECT_IS_DEF
#define OBJECT_IS_DEF

#define RIGHT 1
#define LEFT 0

#include <SDL.h>
#include "sprite.h"
#include "list.h"



typedef SDL_TimerID timer_id_t;

    enum {
        OBJECT_TYPE_BIRD,
        OBJECT_TYPE_MISSILE,
        OBJECT_TYPE_EXPLOSION,
        OBJECT_TYPE_TEXT,
        OBJECT_TYPE_TREE,
        OBJECT_TYPE_BADBIRD,
        __OBJECT_TYPE_NUM
    };

    enum {
        OBJECT_STATE_NORMAL,
        OBJECT_STATE_IN_AIR,
        OBJECT_STATE_DESTROYED,
        OBJECT_STATE_DEAD
    };

    typedef struct _dyn_obj {
        sprite_t *sprite;
        // can be OBJECT_TYPE_BIRD, ...
        int type;
        // can be OBJECT_STATE_NORMAL, ...
        int state;
        // position
        int x, y;
        // speed
        int xs, ys;

        int direction; // 0 = left, 1 = right
        int anim_step;
        int reverse;

        int cmp_rest;
        int resting_toggle;

        int cooldown;
        int cd_count;

        int state_of_blink;

        float val_sin;
        int opacity;
        int zoom;

        timer_id_t timer_id;

        //struct list_head *global_chain;
        struct list_head global_chain;

    } dynamic_object_t;

    typedef int (* animate_func_t)(dynamic_object_t *obj);
    typedef void (* timer_func_t)(dynamic_object_t *obj);
    typedef void (* dead_func_t)(dynamic_object_t *obj);

    int animation_badbird_onestep(dynamic_object_t* obj);
    void animation_badbird_dead(dynamic_object_t* obj);
    int animation_text_onestep(dynamic_object_t* obj);


    typedef struct {
        animate_func_t animate_func;
        timer_func_t timer_func;
        dead_func_t dead_func;
    } object_type_t;

    extern object_type_t object_class [];

    // Initialize the object_class array
    void object_init (void);

    // Initialize fields of object obj
    void object_object_init (dynamic_object_t *obj, sprite_t *sp, int type, int state, int x, int y, int xs, int ys, int direction, int cooldown);

#endif