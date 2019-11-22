#ifndef BADBIRD_IS_DEF
#define BADBIRD_IS_DEF

#include "object.h"

#include "constants.h"
#include "sprite.h"
#include "animation.h"
#include "debug.h"

    void animation_badbird_add (int height, int xs, float vs);

    int animation_badbird_onestep (dynamic_object_t *obj);

    void animation_badbird_dead(dynamic_object_t* obj);

#endif
