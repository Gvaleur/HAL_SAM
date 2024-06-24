#include "watchdog.h"
#include "sam.h"

#ifdef SAMD20
#define CTRLA CTRL
#define WDT_CTRLA_ALWAYSON WDT_CTRL_ALWAYSON
#endif

Watchdog::Watchdog(timeOut_t timeOut)
{
	WDT->CONFIG.bit.PER = timeOut;
	WDT->CTRLA.reg = WDT_CTRLA_ALWAYSON;
}

void Watchdog::kick()
{
	WDT->CLEAR.reg = WDT_CLEAR_CLEAR_KEY;
}