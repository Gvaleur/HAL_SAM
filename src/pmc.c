#include "mcan/pmc.h"

/* lightweight pmc.h substitute */

uint32_t pmc_gck_clock_freq[2];

uint32_t pmc_get_gck_clock(uint32_t id)
{
	if (id == ID_CAN0)
	{
		return pmc_gck_clock_freq[0];
	}
	else
	{
		return pmc_gck_clock_freq[1];
	}
}

void pmc_set_gck_clock(uint32_t id, uint32_t value)
{
	if (id == ID_CAN0)
	{
		pmc_gck_clock_freq[0] = value;
	}
	else
	{
		pmc_gck_clock_freq[1] = value;
	}
}