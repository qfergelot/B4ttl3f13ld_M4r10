#include <SDL_image.h>

#include "graphics.h"



static SDL_Window *win = NULL;
SDL_Renderer *ren = NULL;

void graphics_init (Uint32 render_flags, char *background_skin)
{
  // Initialisation de SDL
  if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER ) != 0)
    exit_with_error ("SDL_Init");

  atexit (graphics_clean);

  // Create main window
  win = SDL_CreateWindow ("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			  WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
  if (win == NULL)
    exit_with_error ("SDL_CreateWindow");

  // Initialize graphical accelerated renderer
  ren = SDL_CreateRenderer (win, -1, render_flags);
  if (ren == NULL)
    exit_with_error ("SDL_CreateRenderer");

  sprite_init(ren, background_skin);
}

static void graphics_render_background (sprite_t *sp)
{
  SDL_Rect dst;

  dst.x = 0;
  dst.y = 0;
  dst.w = sp->display_width;
  dst.h = sp->display_height;

  while(dst.x<=WIN_WIDTH){
    SDL_RenderCopy (ren, sp->texture, NULL, &dst);
    dst.x += sp->native_width;
  }
}

void graphics_render_object (dynamic_object_t *obj)
{
  SDL_Rect src, dst;
  int flip = SDL_FLIP_NONE;

  int nb_img_ligne = ((obj->sprite)->native_width/(obj->sprite)->display_width);
  int nb_img_col = ((obj->sprite)->native_height/(obj->sprite)->display_height);

  src.x = (obj->sprite)->display_width * (obj->anim_step % nb_img_ligne);
  src.y = (obj->sprite)->display_height * (obj->anim_step / nb_img_col %nb_img_col );
  src.w = (obj->sprite)->display_width;
  src.h = (obj->sprite)->display_height;

  dst.x = obj->x;
  dst.y = obj->y;
  dst.w = (obj->sprite)->display_width / obj->zoom;
  dst.h = (obj->sprite)->display_height / obj->zoom;

  if (obj->direction != obj->sprite->original_direction) flip = SDL_FLIP_HORIZONTAL;

  SDL_RenderCopyEx(ren, (obj->sprite)->texture, &src, &dst, 0, NULL, flip);

}


void graphics_render_scrolling_trees (dynamic_object_t *tree, int factor)
{

  SDL_Rect dst;

  dst.x = tree->xs;
  tree->xs -= X_SPEED_BIRD/factor;
  tree->xs %= tree->sprite->native_width;
  dst.y = 0;
  dst.w = (tree->sprite)->display_width;
  dst.h = (tree->sprite)->display_height;

  while(dst.x<=WIN_WIDTH){
    SDL_RenderCopy (ren, tree->sprite->texture, NULL, &dst);
    dst.x += (tree->sprite)->native_width;
  }
}


void graphics_render (void)
{
  static Uint32 prev = 0;
  Uint32 begin, end, interm;

  begin = SDL_GetTicks ();
  
  // We clear the renderer's buffer
  SDL_RenderClear (ren);

  // We display the background clouds
  graphics_render_background (&cloud_background_sprite);

  // We display the dynamics objects
  animation_render_objects();


  interm = SDL_GetTicks ();

  // We update the visible screen. SDL uses a double buffering, so
  // previous modifications are not yet visible
  SDL_RenderPresent (ren);

  end =  SDL_GetTicks ();

  if (debug_enabled ('p')) {
    printf ("Animation: %2d, Rendering: %2d ms, VSync: %2d, Total: %2d ms)\r",
	    begin - prev,
	    interm - begin,
	    end - interm,
	    end - prev);
    fflush (stdout);
  }

  prev = end;
}

void graphics_clean (void)
{
  if(ren != NULL)
    SDL_DestroyRenderer (ren);
  else
    return;

  if(win != NULL)
    SDL_DestroyWindow (win);
  else
    return;

  sprite_clean();
  animation_clean();

  IMG_Quit ();
  SDL_Quit ();
}
