#include <SDL_image.h>

#include "sprite.h"
#include "error.h"
#include "constants.h"
#include "graphics.h"

SDL_Renderer *ren;

sprite_t mario_sprite;
sprite_t cursor_sprite;
sprite_t tree_background_sprite[3];
sprite_t cloud_background_sprite;
sprite_t missile_sprite;
sprite_t explosion_sprite;
sprite_t text_ouch_sprite;
char name[128];

void sprite_create(sprite_t *sp, char* path, int width, int height, int nb_images, int direction){
    sp->texture = IMG_LoadTexture (ren, path);
    if (sp->texture == NULL)
        exit_with_error ("IMG_LoadTexture");

    int nwidth, nheight;
    SDL_QueryTexture (sp->texture, NULL, NULL, &nwidth, &nheight);

    sp->native_width = nwidth;
    sp->display_width = width;
    sp->native_height = nheight;
    sp->display_height = height;
    sp->original_direction = direction;
    sp->nb_images = nb_images;


}

void sprite_init (char *background_skin){

    sprite_create(&mario_sprite, "../images/mario2.png", 64, 128, 11, RIGHT);
    sprite_create(&cursor_sprite, "../images/cursor.png", 64, 64, 1, RIGHT);

    for (int i = 0; i<3; i++){
        sprintf (name, "../images/%s-%d.png", background_skin, i);
        sprite_create(&tree_background_sprite[i], name, 1024, WIN_HEIGHT, 1, 1);
    }

    sprite_create(&cloud_background_sprite, "../images/trees-background.png", 1024, WIN_HEIGHT, 1, 1);
    sprite_create(&missile_sprite, "../images/missiled.png", 64, 64, 12, RIGHT);
    sprite_create(&explosion_sprite, "../images/explosion.png", 64, 64, 25, RIGHT);
    sprite_create(&text_ouch_sprite, "../images/ouch.png", 512, 341, 1, RIGHT);

}

void sprite_clean (void){
    if(cloud_background_sprite.texture != NULL)
        SDL_DestroyTexture (cloud_background_sprite.texture);

    for (int i = 0; i < 3; i++)
    if(tree_background_sprite[i].texture != NULL)
        SDL_DestroyTexture (tree_background_sprite[i].texture);

    if(mario_sprite.texture != NULL)
        SDL_DestroyTexture (mario_sprite.texture);

    if(missile_sprite.texture != NULL)
        SDL_DestroyTexture (missile_sprite.texture);

    if(explosion_sprite.texture != NULL)
        SDL_DestroyTexture (explosion_sprite.texture);

    if(text_ouch_sprite.texture != NULL)
        SDL_DestroyTexture (text_ouch_sprite.texture);

}
