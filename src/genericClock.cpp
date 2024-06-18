#include "genericClock.h"
#include "samc21.h"
#include "clock.h"
#include "math.h"
#include "gpio.h"
#include "assert.h"

#ifndef SUPPORT_LOG2
#define SUPPORT_LOG2 1
#endif // !SUPPORT_LOG2


GenericClock::GenericClock(uint8_t generator, uint32_t outFreq, input_t input, bool enableOutput)
	: mGenerator(generator)
	, mFreq(outFreq)
{
	uint32_t inFreq;

	switch (input)
	{
	case GenericClock::XOSC:
		inFreq = Clock::getXosc();
		break;
	case GenericClock::OSCULP32K:
	case GenericClock::OSCK32K:
	case GenericClock::XOSC32K:
		inFreq = 32768;
		break;
	case GenericClock::OSC48M:
		inFreq = 48000000;
		break;
	case GenericClock::DPLL96M:
		inFreq = 96000000;
		break;
	}

	// calculate div
	uint32_t div = inFreq / outFreq;
	uint32_t regVal = 0;
	if (div > 0xFF)
	{
#if SUPPORT_LOG2 == 1
		div = log2l(div);
		regVal |= (div << GCLK_GENCTRL_DIV_Pos) | GCLK_GENCTRL_DIVSEL;
#else
		assert(0);
#endif
	}
	else
	{
		regVal |= (div << GCLK_GENCTRL_DIV_Pos);
	}

	if (enableOutput)
	{
		AlternateFunction::setFunction(AlternateFunction::PORT_A, 17, AlternateFunction::H);
		GCLK->GENCTRL[mGenerator].bit.IDC = enableOutput;
		GCLK->GENCTRL[mGenerator].bit.OE = enableOutput;
		regVal |= (GCLK_GENCTRL_IDC | GCLK_GENCTRL_OE);
	}

	regVal |= (input << GCLK_GENCTRL_SRC_Pos) | GCLK_GENCTRL_GENEN;

	GCLK->GENCTRL[mGenerator].reg = regVal;

	// wait for synchronization
	while (GCLK->SYNCBUSY.reg)
	{
	}
}

void GenericClock::enableClock(clock_t clock)
{
	GCLK->PCHCTRL[clock].reg = mGenerator | GCLK_PCHCTRL_CHEN;
}

uint32_t GenericClock::getFreq()
{
	return mFreq;
}