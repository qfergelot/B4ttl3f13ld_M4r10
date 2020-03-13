#include "cursor.h"

dynamic_object_t cursor_obj;

void create_cursor(void){
    object_object_init (&cursor_obj, NULL, OBJECT_TYPE_CURSOR, OBJECT_STATE_NORMAL, 0, 0, 0, 0, RIGHT, 14);
}

void animation_cursor_moves(dynamic_object_t* obj, int left, int right, int up, int down, int space, int tab) {

}