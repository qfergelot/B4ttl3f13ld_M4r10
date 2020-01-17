#ifndef GENERATOR_IS_DEF
#define GENERATOR_IS_DEF

#include "timer.h"
#include "constants.h"

//void generate_badbird(void* a);
timer_id_t generator_init();
Uint32 callback_gen(Uint32 delay, void* param);
void generator_clean(timer_id_t id);

#endif
