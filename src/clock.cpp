#include "clock.h"
#include "samc21.h"

uint32_t Clock::mXosc = 0;

void Clock::setMainClock(const clockType_t clockType, const uint32_t frequency)
{
	if (clockType == CRYSTAL)
	{
		mXosc = frequency;

		// set flash wait states
		NVMCTRL->CTRLB.bit.RWS = 3;

		// start external OSC
		OSCCTRL->XOSCCTRL.reg = (OSCCTRL_XOSCCTRL_STARTUP(0x8u) | OSCCTRL_XOSCCTRL_GAIN(0x4u) | OSCCTRL_XOSCCTRL_XTALEN | OSCCTRL_XOSCCTRL_ENABLE);

		// wait for stable crystal
		while (!OSCCTRL->STATUS.bit.XOSCRDY)
		{
		}

		OSCCTRL->XOSCCTRL.bit.AMPGC = 1;

		// set DPLL output to 96MHz
		OSCCTRL->DPLLCTRLB.bit.DIV = ((frequency / 1000000) / 2) - 1;
		OSCCTRL->DPLLRATIO.bit.LDRFRAC = 0;
		OSCCTRL->DPLLRATIO.bit.LDR = 95;
		OSCCTRL->DPLLPRESC.reg = 0;
		OSCCTRL->DPLLCTRLA.bit.ONDEMAND = 0;
		OSCCTRL->DPLLCTRLB.bit.REFCLK = 1;
		OSCCTRL->DPLLCTRLA.bit.ENABLE = 1;

		// wait for DPLL to stabelise
		while (!OSCCTRL->DPLLSTATUS.bit.LOCK)
		{
		}

		// set system clock to DPLL
		GCLK->GENCTRL[0].bit.DIV = 2;
		GCLK->GENCTRL[0].bit.OE = 1;
		GCLK->GENCTRL[0].bit.IDC = 1;
		GCLK->GENCTRL[0].bit.SRC = GCLK_GENCTRL_SRC_DPLL96M_Val;
		GCLK->GENCTRL[0].bit.GENEN = 1;
	}
}

void Clock::enableClock(const APBCClock_t clock)
{
	MCLK->APBCMASK.reg |= clock;
}

void Clock::enableClock(const AHBClock_t clock)
{
	MCLK->AHBMASK.reg |= clock;
}

uint32_t Clock::getXosc()
{
	return mXosc;
}
