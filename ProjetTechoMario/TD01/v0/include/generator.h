#ifndef GENERATOR_IS_DEF
#define GENERATOR_IS_DEF

#include "timer.h"
//#include "constants.h"

typedef Uint32 (* callback_func_t)(Uint32 delay, void* param);

//void generate_badbird(void* a);
timer_id_t generator_init(Uint32 interval, callback_func_t f, void* param);
Uint32 callback_gen(Uint32 delay, void* param);
void generator_clean(timer_id_t id);

#endif
