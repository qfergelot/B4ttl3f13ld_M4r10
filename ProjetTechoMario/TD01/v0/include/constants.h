
#ifndef CONSTANTS_IS_DEF
#define CONSTANTS_IS_DEF


#define WIN_WIDTH   1920 // Width of window
#define WIN_HEIGHT  1080 //Height of window

#define MAP_WIDTH 400 // Width of map in block
#define MAP_HEIGHT 30 // Height of map in block

#define BLOCK_SIZE 64 // Scale of a block
#define BLOCK_NUMBER 9 // Number of types of blocks (solid, air, ...)

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