#include "text.h"

    void animation_text_add (dynamic_object_t* obj){
        dynamic_object_t* text_obj = (dynamic_object_t*) malloc(sizeof(dynamic_object_t));
        if (text_obj == NULL)
            exit_with_error("Not Enough Memory\n");

        PRINT_DEBUG('m', "Malloc done on object %p\n", text_obj);
        object_object_init (text_obj, &text_ouch_sprite, OBJECT_TYPE_TEXT, OBJECT_STATE_IN_AIR, obj->x , obj->y, -1, 0, LEFT, 0);
        text_obj->zoom = 5;
        animation_mobile_object_add (text_obj);
    }

    int animation_text_onestep (dynamic_object_t *obj){
        if (obj->opacity <= 1) return 1;
        obj->x += obj->xs;
        SDL_SetTextureAlphaMod(obj->sprite->texture, obj->opacity-=2);
        return 0;
    }