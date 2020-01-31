#ifndef ANIMATION_IS_DEF
#define ANIMATION_IS_DEF

//#include "graphics.h"
//#include "list.h"
#include "object.h"
//#include "timer.h"
//#include "collision.h"

//#include "mario.h"
//#include "debug.h"

//#include "tree.h"
//#include "explosion.h"



//extern struct list_head all_objects;

void animation_init (void);
void animation_one_step (int left, int right, int up, int down, int space);
void animation_render_objects (void);
void animation_mobile_object_add (dynamic_object_t *obj);
void animation_mobile_object_del (dynamic_object_t *obj);
void create_all_objects(void);
void animation_clean (void);
void animation_timer_add (dynamic_object_t *obj, Uint32 delay);
void animation_timer_cancel(dynamic_object_t *obj);
void animation_timer_expired (void *arg1, void *arg2);


/* //For (DYNAMIC_OBJECT_T *obj = HEAD(all_object); obj->next != HEAD(all_objects); obj=obj->next) */
/* #define for_all_objects(var) \ */
/*     list_for_each_entry_safe(dynamic_object_t, var, &(all_objects), global_chain) */

/* #define for_all_other_objects(var) \ */
/*     list_for_each_entry_safe(dynamic_object_t, var, obj->global_chain.next, global_chain) */

#endif
