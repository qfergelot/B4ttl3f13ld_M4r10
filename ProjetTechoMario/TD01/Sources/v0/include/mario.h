#ifndef MARIO_IS_DEF
#define MARIO_IS_DEF

#include "object.h"

/* #include "text.h" */
/* #include "constants.h" */
/* #include "missile.h" */
/* #include "sprite.h" */
/* #include "map.h" */
/* #include "missile.h" */
/* #include "timer.h" */

extern dynamic_object_t mario_obj;

void animation_text_add(dynamic_object_t* obj);

void create_mario(void);
void animation_mario_moves (dynamic_object_t *obj, int left, int right, int up, int down, int space);
int animation_mario_onestep (dynamic_object_t *obj);
void animation_mario_timer_expired (dynamic_object_t *obj);
Uint32 mario_callback(Uint32 interval, void *param);
void animation_dead_mario (dynamic_object_t* obj);


#endif
