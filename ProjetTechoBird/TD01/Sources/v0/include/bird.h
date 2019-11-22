#ifndef BIRD_IS_DEF
#define BIRD_IS_DEF

#include "object.h"

#include "constants.h"
#include "missile.h"
#include "sprite.h"
#include "missile.h"
#include "timer.h"

extern dynamic_object_t bird_obj;

void animation_text_add(dynamic_object_t* obj);

void create_bird(void);
void animation_bird_moves (dynamic_object_t *obj, int up, int down, int space);
int animation_bird_onestep (dynamic_object_t *obj);
void animation_bird_timer_expired (dynamic_object_t *obj);
Uint32 bird_callback(Uint32 interval, void *param);
void animation_dead_bird (dynamic_object_t* obj);


#endif