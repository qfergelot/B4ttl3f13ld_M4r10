
#ifndef CONSTANTS_IS_DEF
#define CONSTANTS_IS_DEF

enum {  // Modes de jeu
  GAME_MODE_PLAY,
  GAME_MODE_EDITOR
};

extern int game_mode;
extern int dim_w;
extern int dim_h;

#define WIN_WIDTH   1920 // Width of window  1280  1920
#define WIN_HEIGHT  1080//Height of window   720   1080

#define MAP_WIDTH dim_w // Width of map in block
#define MAP_HEIGHT dim_h // Height of map in block

#define BLOCK_SIZE 64 // Scale of a block
#define BLOCK_NUMBER 10 // Number of types of blocks (solid, air, ...)

#define MARIO_SPEED 4 // Horizontal speed of mario
#define MARIO_JUMP_IMPULSE -22 //Jump Strenght of mario
#define MISSILE_SPEED 6 // horizontal speed of a missile

#define DECAL 8 * BLOCK_SIZE // Set the scrolling distance

#define RIGHT_LIMIT_SCROLLING WIN_WIDTH - DECAL // scrolling distance to the right
#define LEFT_LIMIT_SCROLLING  DECAL // scrolling distance to the left

#define RIGHT_MAP_LIMIT BLOCK_SIZE * (MAP_WIDTH - 1) //
#define LEFT_MAP_LIMIT 0 //

#define LEFT 1 //
#define RIGHT 0 //

#define RANDMAX = 1280 //



#endif
