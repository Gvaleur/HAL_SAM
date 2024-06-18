#pragma once
#include "stdint.h"

class GenericClock
{
public:
	enum clock_t
	{
		FDPLL_CLOCK = 0,
		FDPLL_32_CLOCK = 1,
		EIC_CLOCK = 2,
		FREQM_MES_CLOCK = 3,
		FREQM_REF_CLOCK = 4,
		TSENS_CLOCK = 5,
		EVSYS_CHANNEL_0_CLOCK = 6,
		EVSYS_CHANNEL_1_CLOCK = 7,
		EVSYS_CHANNEL_2_CLOCK = 8,
		EVSYS_CHANNEL_3_CLOCK = 9,
		EVSYS_CHANNEL_4_CLOCK = 10,
		EVSYS_CHANNEL_5_CLOCK = 11,
		EVSYS_CHANNEL_6_CLOCK = 12,
		EVSYS_CHANNEL_7_CLOCK = 13,
		EVSYS_CHANNEL_8_CLOCK = 14,
		EVSYS_CHANNEL_9_CLOCK = 15,
		EVSYS_CHANNEL_10_CLOCK = 16,
		EVSYS_CHANNEL_11_CLOCK = 17,
		SERCOM0TO4_SLOW_CLOCK = 18,
		SERCOM0_CORE_CLOCK = 19,
		SERCOM1_CORE_CLOCK = 20,
		SERCOM2_CORE_CLOCK = 21,
		SERCOM3_CORE_CLOCK = 22,
		SERCOM4_CORE_CLOCK = 23,
		SERCOM5_SLOW_CLOCK = 24,
		SERCOM5_CORE_CLOCK = 25,
		CAN0_CLOCK = 26,
		CAN1_CLOCK = 27,
		TCC0TO1_CLOCK = 28,
		TCC2_CLOCK = 29,
		TC0TO1_CLOCK = 30,
		TC2TO3_CLOCK = 31,
		TC4_CLOCK = 32,
		ADC0_CLOCK = 33,
		ADC1_CLOCK = 34,
		SDADC_CLOCK = 35,
		DAC_CLOCK = 36,
		PTC_CLOCK = 37,
		CCL_CLOCK = 38,
		AC_CLOCK = 40,
		SERCOM6_CORE_CLOCK = 41,
		SERCOM7_CORE_CLOCK = 42,
		TC5_CLOCK = 43,
		TC6_CLOCK = 44,
		TC7_CLOCK = 45
	};

	enum input_t
	{
		XOSC = 0,
		GCLK_IN = 1,
		GCLK_GEN1 = 2,
		OSCULP32K = 3,
		OSCK32K = 4,
		XOSC32K = 5,
		OSC48M = 6,
		DPLL96M = 7
	};

	GenericClock(uint8_t generator, uint32_t outFreq, input_t input, bool enableOutput = false);

	void enableClock(clock_t clock);
	uint32_t getFreq();
private:
	uint8_t mGenerator;
	uint32_t mFreq;
};