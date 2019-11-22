#ifndef SPRITE_IS_DEF
#define SPRITE_IS_DEF
#include <SDL.h>
#include "error.h"
#include "constants.h"

	typedef struct {
		SDL_Texture *texture;
		int native_width, native_height;
		int display_width, display_height;
		int original_direction;
		int nb_images;

	} sprite_t;

	extern sprite_t bird_sprite;
	extern sprite_t tree_background_sprite[3];
	extern sprite_t cloud_background_sprite;
	extern sprite_t missile_sprite;
	extern sprite_t explosion_sprite;
	extern sprite_t badbird_sprite;
	extern sprite_t text_ouch_sprite;

	// Initialize sprite_t global variables for each sprite
	void sprite_init (SDL_Renderer *ren, char *background_skin);

	// Destroys
	void sprite_clean (void);

#endif

