#ifndef _PMC_H_
#define _PMC_H_

#include "samc21.h"

#ifdef __cplusplus
extern "C" {
#endif

/* lightweight pmc.h substitute */
uint32_t pmc_get_gck_clock(uint32_t id);
void pmc_set_gck_clock(uint32_t id, uint32_t value);

#ifdef __cplusplus
}
#endif
#endif
