#ifndef MISSILE_IS_DEF
#define MISSILE_IS_DEF

#include "object.h"
#include "constants.h"
#include "sprite.h"
#include "animation.h"
#include "debug.h"
#include "bird.h"

    //dynamic_object_t* create_missile(void);

    void animation_missile_add (dynamic_object_t *obj);

    int animation_missile_onestep (dynamic_object_t *obj);

    void animation_missile_dead (dynamic_object_t* obj);

#endif