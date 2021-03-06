#ifndef GRAPHICS_IS_DEF
#define GRAPHICS_IS_DEF

#include <SDL.h>

#include "object.h"

#define GFX_NONE      0
#define GFX_BLINK     1
#define GFX_FADE      2
#define GFX_CENTER    4
#define GFX_SCALE     8
#define GFX_ROTATE   16

extern SDL_Renderer *ren;

void graphics_init (Uint32 render_flags, char *background_skin);
void graphics_render (void);
void graphics_clean (void);
void graphics_render_object (dynamic_object_t *obj);
void graphics_render_static_object (static_object_t *obj, int x_map, int y_map);
void graphics_render_scrolling_trees (dynamic_object_t *tree, int factor);
int is_in_screen(int x_screen, int y_screen);

#endif
