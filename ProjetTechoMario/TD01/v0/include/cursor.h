#ifndef CURSOR_IS_DEF
#define CURSOR_IS_DEF

#include "object.h"

extern dynamic_object_t cursor_obj;

void create_cursor(void);
void animation_cursor_moves(dynamic_object_t *obj, int left, int right, int up, int down, int space, int tab);
void animation_cursor_onestep (dynamic_object_t *obj);

#endif