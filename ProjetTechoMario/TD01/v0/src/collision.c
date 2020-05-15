#include "collision.h"

//si le point en bas a droite ou en bas a gauche de l'obj2 est entre les 2 points en bas du obj1 -> true
//point entre deux points -> si xgobj1<xobj2<xdobj1
int hitbox_width(dynamic_object_t* obj1, dynamic_object_t* obj2){
    int a1 = obj1->x_map;
    int a2 = a1 + obj1->sprite->display_width;
    int b1 = obj2->x_map;
    int b2 = b1 + obj2->sprite->display_width;
    return((a1<=b1 && b1<=a2) || (a1<=b2 && b2<=a2) || (b1<a1 && a1<b2) || (b1<a2 && a2<b2));
}

int hitbox_height(dynamic_object_t* obj1, dynamic_object_t* obj2){
    int a1 = obj1->y_map;
    int a2 = a1 + obj1->sprite->display_height;
    int b1 = obj2->y_map;
    int b2 = b1 + obj2->sprite->display_height;
    return((a1<=b1 && b1<=a2) || (a1<=b2 && b2<=a2) || (b1<a1 && a1<b2) || (b1<a2 && a2<b2));
}

int collide(dynamic_object_t* obj1, dynamic_object_t* obj2){
    if (obj1->type == obj2->type) return 0;
    if (obj1->type == OBJECT_TYPE_EXPLOSION || obj2->type == OBJECT_TYPE_EXPLOSION) return 0;
    if (obj1->type == OBJECT_TYPE_TEXT || obj2->type == OBJECT_TYPE_TEXT) return 0;
    //if ((obj1->type == OBJECT_TYPE_MARIO && obj2->type == OBJECT_TYPE_MISSILE) || (obj2->type == OBJECT_TYPE_MARIO && obj1->type == OBJECT_TYPE_MISSILE)) return 0;
    //if ((obj1->type == OBJECT_TYPE_MARIO && obj1->state == OBJECT_STATE_DEAD) || (obj2->type == OBJECT_TYPE_MARIO && obj2->state == OBJECT_STATE_DEAD)) return 0;
    return (hitbox_width(obj1, obj2) && hitbox_height(obj1, obj2));
}

