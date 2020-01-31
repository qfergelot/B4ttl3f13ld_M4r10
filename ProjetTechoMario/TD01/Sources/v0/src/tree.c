
#include "tree.h"
#include "sprite.h"
#include "constants.h"


dynamic_object_t tree_obj[3];

void create_trees(void){
    for (int i =0 ; i<3; i++){
        object_object_init (&tree_obj[i], &tree_background_sprite[i], OBJECT_TYPE_TREE, OBJECT_STATE_NORMAL, tree_background_sprite[i].display_width, tree_background_sprite[i].display_height, 0, 0, RIGHT, 0);    }
}
