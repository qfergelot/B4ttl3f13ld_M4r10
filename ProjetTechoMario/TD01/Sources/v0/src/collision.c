#include "collision.h"

//si le point en bas a droite ou en bas a gauche de l'obj2 est entre les 2 points en bas du obj1 -> true
//point entre deux points -> si xgobj1<xobj2<xdobj1
int hitbox_width(dynamic_object_t* obj1, dynamic_object_t* obj2){
    return (obj1->x < obj2->x && obj2->x < obj1->x + obj1->sprite->display_width);
}

int hitbox_height(dynamic_object_t* obj1, dynamic_object_t* obj2){
    return (obj1->y < obj2->y && obj2->y < obj1->y + obj1->sprite->display_height);
}

int collide(dynamic_object_t* obj1, dynamic_object_t* obj2){
    if (obj1->type == obj2->type) return 0;
    if (obj1->type == OBJECT_TYPE_EXPLOSION || obj2->type == OBJECT_TYPE_EXPLOSION) return 0;
    if (obj1->type == OBJECT_TYPE_TEXT || obj2->type == OBJECT_TYPE_TEXT) return 0;
    if ((obj1->type == OBJECT_TYPE_MARIO && obj2->type == OBJECT_TYPE_MISSILE) || (obj2->type == OBJECT_TYPE_MARIO && obj1->type == OBJECT_TYPE_MISSILE)) return 0;
    if ((obj1->type == OBJECT_TYPE_MARIO && obj1->state == OBJECT_STATE_DEAD) || (obj2->type == OBJECT_TYPE_MARIO && obj2->state == OBJECT_STATE_DEAD)) return 0;
    return (hitbox_width(obj1, obj2) && hitbox_height(obj1, obj2));
}

