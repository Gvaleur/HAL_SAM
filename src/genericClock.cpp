#include "genericClock.h"
#include "clock.h"
#include "math.h"
#include "gpio.h"
#include "assert.h"

#ifndef SUPPORT_LOG2
#define SUPPORT_LOG2 1
#endif // !SUPPORT_LOG2

#ifdef SAMD20
#define SYNCBUSY STATUS
#endif


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
#if defined (SAMC21)
	case GenericClock::OSC48M:
		inFreq = 48000000;
		break;
	case GenericClock::DPLL96M:
		inFreq = 96000000;
		break;
#elif defined (SAMD20)
	case GenericClock::OSC8M:
		inFreq = 8000000;
		break;
	case GenericClock::DFLL48M:
		inFreq = 48000000;
		break;
#endif
	}

	// calculate div
	uint32_t div = inFreq / outFreq;
	uint32_t regVal = 0;
	if (div > 0xFF)
	{
#if SUPPORT_LOG2 == 1
		div = log2l(div);
		
#if defined (SAMC21)
		regVal |= (div << GCLK_GENCTRL_DIV_Pos) | GCLK_GENCTRL_DIVSEL;
#elif defined (SAMD20)
		GCLK->GENDIV.reg = (div << GCLK_GENDIV_DIV_Pos) | mGenerator;
		regVal |= GCLK_GENCTRL_DIVSEL;
#endif

#else
		assert(0);
#endif
	}
	else
	{
#if defined (SAMC21)
		regVal |= (div << GCLK_GENCTRL_DIV_Pos);
#elif defined (SAMD20)
		GCLK->GENDIV.reg = (div << GCLK_GENDIV_DIV_Pos) | mGenerator;
#endif
	}

	if (enableOutput)
	{
		AlternateFunction::setFunction(AlternateFunction::PORT_A, 17, AlternateFunction::H);
		regVal |= (GCLK_GENCTRL_IDC | GCLK_GENCTRL_OE);
	}

	regVal |= (input << GCLK_GENCTRL_SRC_Pos) | GCLK_GENCTRL_GENEN;

#if defined (SAMC21)
	GCLK->GENCTRL[mGenerator].reg = regVal;
#elif defined (SAMD20)
	GCLK->GENCTRL.reg = regVal | mGenerator;
#endif

	// wait for synchronization
	while (GCLK->SYNCBUSY.reg)
	{
	}
}

void GenericClock::enableClock(clock_t clock)
{
#if defined (SAMC21)
	GCLK->PCHCTRL[clock].reg = mGenerator | GCLK_PCHCTRL_CHEN;
#elif defined (SAMD20)
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN(mGenerator) | clock;
#endif
}

uint32_t GenericClock::getFreq()
{
	return mFreq;
}