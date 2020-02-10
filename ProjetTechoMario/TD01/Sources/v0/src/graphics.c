#include <SDL_image.h>

#include "graphics.h"

#include "error.h"
#include "debug.h"
#include "constants.h"
#include "animation.h"

#include "sprite.h"
#include "mario.h"
#include "map.h"


static SDL_Window *win = NULL;
/*static int x_screen_map;
static int y_screen_map;*/

void graphics_init (Uint32 render_flags, char *background_skin)
{
  //x_screen_map = 0;
  //y_screen_map = 0;
  // Initialisation de SDL
  if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER ) != 0)
    exit_with_error ("SDL_Init");

  atexit (graphics_clean);

  // Create main window
  win = SDL_CreateWindow ("847723$1329 #4610", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			  WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
  if (win == NULL)
    exit_with_error ("SDL_CreateWindow");

  // Initialize graphical accelerated renderer
  ren = NULL;
  ren = SDL_CreateRenderer (win, -1, render_flags);
  if (ren == NULL)
    exit_with_error ("SDL_CreateRenderer");

  sprite_init(background_skin);
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

  dst.x = obj->x_screen;
  dst.y = obj->y_screen;
  dst.w = (obj->sprite)->display_width / obj->zoom;
  dst.h = (obj->sprite)->display_height / obj->zoom;

  if (obj->direction != obj->sprite->original_direction) flip = SDL_FLIP_HORIZONTAL;

  SDL_RenderCopyEx(ren, (obj->sprite)->texture, &src, &dst, 0, NULL, flip);

}

void graphics_render_static_object(static_object_t* obj, int x_map, int y_map){

  //mario_obj.x_map;//en pixel

  int x_screen = x_map;// * BLOCK_SIZE; //-> pixel
  int y_screen = y_map;// * BLOCK_SIZE;

    SDL_Rect src, dst;
    if (obj != NULL){
      if(obj->sprite != NULL){

        int nb_img_ligne = ((obj->sprite)->native_width/(obj->sprite)->display_width);
        int nb_img_col = ((obj->sprite)->native_height/(obj->sprite)->display_height);

        src.x = (obj->sprite)->display_width * (obj->anim_step % nb_img_ligne);
        src.y = (obj->sprite)->display_height * (obj->anim_step / nb_img_col %nb_img_col );
        src.w = (obj->sprite)->display_width;
        src.h = (obj->sprite)->display_height;

        dst.x = x_screen;
        dst.y = y_screen;
        dst.w = (obj->sprite)->display_width;
        dst.h = (obj->sprite)->display_height;


        SDL_RenderCopy(ren, (obj->sprite)->texture, &src, &dst);
      }
    }
}

/*int is_in_screen(int x, int y){
  return (x_screen_map <= x && x <= x_screen_map + WIN_WIDTH && y_screen_map <= y && y <= y_screen_map + WIN_HEIGHT);
}*/


void graphics_render_scrolling_object (dynamic_object_t *obj, int factor)
{

  SDL_Rect dst;

  dst.x = obj->xs;

  if (mario_obj.x_screen <= LEFT_LIMIT_SCROLLING){
    obj->xs -= mario_obj.xs/factor;
    obj->xs %= obj->sprite->native_width;
    //x_screen_map -= MARIO_SPEED ;
  }
  else if(mario_obj.x_screen >= RIGHT_LIMIT_SCROLLING)
  {
    obj->xs -= mario_obj.xs/factor;
    obj->xs %= obj->sprite->native_width;
    //x_screen_map += MARIO_SPEED;
  }

  dst.y = 0;
  dst.w = (obj->sprite)->display_width;
  dst.h = (obj->sprite)->display_height;

    while(dst.x <= WIN_WIDTH){
      SDL_RenderCopy (ren, obj->sprite->texture, NULL, &dst);
      dst.x += (obj->sprite)->native_width;
    }
    while(dst.x > 0){
      dst.x -= (obj->sprite)->native_width;
      SDL_RenderCopy (ren, obj->sprite->texture, NULL, &dst);
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

  //We display the static objects

  // We display the dynamics objects
  animation_render_objects();

  map_render_objects();

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
