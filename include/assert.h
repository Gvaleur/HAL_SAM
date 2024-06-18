#pragma once

#ifdef DEBUG
#define assert(x) if ((x) == 0) { asm("bkpt 255"); }
#else
#define assert(x) if ((x) == 0) { while(1); }
#endif