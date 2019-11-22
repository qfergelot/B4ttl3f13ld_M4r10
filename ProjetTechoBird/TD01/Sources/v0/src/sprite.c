#include <SDL_image.h>

#include "sprite.h"


sprite_t bird_sprite;
sprite_t tree_background_sprite[3];
sprite_t cloud_background_sprite;
sprite_t missile_sprite;
sprite_t explosion_sprite;
sprite_t badbird_sprite;
sprite_t text_ouch_sprite;
char name[128];

void sprite_create(SDL_Renderer *ren, sprite_t *sp, char* path, int width, int height, int nb_images, int direction){
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

void sprite_init (SDL_Renderer *ren, char *background_skin){

    sprite_create(ren, &bird_sprite, "../images/bird.png", 128, 128, 8, 1);

    for (int i = 0; i<3; i++){
        sprintf (name, "../images/%s-%d.png", background_skin, i);
        sprite_create(ren, &tree_background_sprite[i], name, 1024, WIN_HEIGHT, 1, 1);
    }

    sprite_create(ren, &cloud_background_sprite, "../images/trees-background.png", 1024, WIN_HEIGHT, 1, 1);
    sprite_create(ren, &missile_sprite, "../images/missiled.png", 64, 64, 12, 0);
    sprite_create(ren, &explosion_sprite, "../images/explosion.png", 64, 64, 25, 0);
    sprite_create(ren, &badbird_sprite, "../images/bad_bird.png", 128, 128, 8, 0);
    sprite_create(ren, &text_ouch_sprite, "../images/ouch.png", 512, 341, 1, 0);

}

void sprite_clean (void){
    if(cloud_background_sprite.texture != NULL)
        SDL_DestroyTexture (cloud_background_sprite.texture);

    for (int i = 0; i < 3; i++)
    if(tree_background_sprite[i].texture != NULL)
        SDL_DestroyTexture (tree_background_sprite[i].texture);

    if(bird_sprite.texture != NULL)
        SDL_DestroyTexture (bird_sprite.texture);

    if(missile_sprite.texture != NULL)
        SDL_DestroyTexture (missile_sprite.texture);

    if(explosion_sprite.texture != NULL)
        SDL_DestroyTexture (explosion_sprite.texture);

    if(badbird_sprite.texture != NULL)
        SDL_DestroyTexture (badbird_sprite.texture);

    if(badbird_sprite.texture != NULL)
        SDL_DestroyTexture (text_ouch_sprite.texture);

}
