#ifndef MINE_IS_DEF
#define MINE_IS_DEF

#include "object.h"


    //dynamic_object_t* create_missile(void);

    void animation_mine_add (int x_block, int y_block);

    int animation_mine_onestep (dynamic_object_t *obj);

    void animation_mine_dead (dynamic_object_t* obj);

#endif