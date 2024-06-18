#include "sdadc.h"
#include "samc21.h"
#include "gpio.h"
#include "clock.h"

#if configENABLE_SDADC == 1
Semaphore SdAdc::readSem(1, 0);
uint32_t SdAdc::rawVal = 0;
#endif

SdAdc::SdAdc(GenericClock& clock, refBuf_t refBuf, refRange_t refRange, refSel_t refSel, overSample_t overSample, input_t input)
{
	Clock::enableClock(Clock::SDADC_CLOCK);

	// set pin configuration
	switch (input)
	{
	case SdAdc::AIN0:
		AlternateFunction::setFunction(AlternateFunction::PORT_A, 6, AlternateFunction::B);
		AlternateFunction::setFunction(AlternateFunction::PORT_A, 7, AlternateFunction::B);
		break;
	case SdAdc::AIN1:
		AlternateFunction::setFunction(AlternateFunction::PORT_B, 8, AlternateFunction::B);
		AlternateFunction::setFunction(AlternateFunction::PORT_B, 9, AlternateFunction::B);
		break;
	case SdAdc::AIN2:
		AlternateFunction::setFunction(AlternateFunction::PORT_B, 6, AlternateFunction::B);
		AlternateFunction::setFunction(AlternateFunction::PORT_B, 7, AlternateFunction::B);
		break;
	}

	if (refSel == VREFB)
	{
		AlternateFunction::setFunction(AlternateFunction::PORT_A, 4, AlternateFunction::B);
	}

	SDADC->CTRLB.bit.PRESCALER = (clock.getFreq() / (1500000 * 2)) - 1;
	clock.enableClock(GenericClock::SDADC_CLOCK);

	NVIC_SetPriority(SDADC_IRQn, 3);
	NVIC_EnableIRQ(SDADC_IRQn);

	SDADC->REFCTRL.bit.ONREFBUF = refBuf;
	SDADC->REFCTRL.bit.REFRANGE = refRange;
	SDADC->REFCTRL.bit.REFSEL = refSel;

	SDADC->CTRLB.bit.OSR = overSample;

	SDADC->INPUTCTRL.reg = input;
	SDADC->INTENSET.bit.RESRDY = 1;

	SDADC->ANACTRL.bit.ONCHOP = 1;

	SDADC->CTRLA.bit.ENABLE = 1;

	while (SDADC->SYNCBUSY.reg)
	{
	}
}

#if configENABLE_SDADC == 1
uint32_t SdAdc::getValue()
{
	SDADC->SWTRIG.bit.START = 1;
	readSem.take(10000);
	return rawVal;
}

void SdAdc::onInterrupt()
{
	rawVal = SDADC->RESULT.reg;
	readSem.releaseInt();
}

void SDADC_Handler()
{
	SdAdc::onInterrupt();
}
#endif

