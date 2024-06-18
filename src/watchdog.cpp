#include "watchdog.h"
#include "samc21.h"

Watchdog::Watchdog(timeOut_t timeOut)
{
	WDT->CONFIG.bit.PER = timeOut;
	WDT->CTRLA.reg = WDT_CTRLA_ALWAYSON;
}

void Watchdog::kick()
{
	WDT->CLEAR.reg = WDT_CLEAR_CLEAR_KEY;
}