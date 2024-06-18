#pragma once
#include "semaphorePlus.h"
#include "genericClock.h"
#include "HALConfig.h"

class SdAdc
{
public:
	enum refBuf_t
	{
		REF_BUF_ON = 1,
		REF_BUF_OFF = 0
	};

	enum refRange_t
	{
		ref00To14 = 0,
		ref14to24 = 1,
		ref24to36 = 2,
		ref36to55 = 3
	};

	enum refSel_t
	{
		INTREF = 0,
		VREFB = 1,
		DAC_REF = 2,
		VDDANA = 3
	};

	enum overSample_t
	{
		OSR64 = 0,
		OSR128 = 1,
		OSR256 = 2,
		OSR512 = 3,
		OSR1024 = 4
	};

	enum input_t
	{
		AIN0 = 0,
		AIN1 = 1,
		AIN2 = 2
	};

	SdAdc(GenericClock& clock, refBuf_t refBuf, refRange_t refRange, refSel_t refSel, overSample_t overSample, input_t input);

	uint32_t getValue();

	static void onInterrupt();

private:
#if configENABLE_SDADC == 1
	static Semaphore readSem;
	static uint32_t rawVal;
#endif
};

extern "C"
{
#if configENABLE_SDADC == 1
	void SDADC_Handler();
#endif
}