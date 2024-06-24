#pragma once
#include "stdint.h"
#include "sam.h"

class Clock
{
public:
	enum clockType_t
	{
		CRYSTAL,
		OSC48M,
		EXTERNAL_CLOCK
	};

	enum APBCClock_t
	{
#if defined(SAMC21)
		CCL_CLOCK = MCLK_APBCMASK_CCL,
		PTC_CLOCK = MCLK_APBCMASK_PTC,
		DAC_CLOCK = MCLK_APBCMASK_DAC,
		AC_CLOCK = MCLK_APBCMASK_AC,
		SDADC_CLOCK = MCLK_APBCMASK_SDADC,
		ADC1_CLOCK = MCLK_APBCMASK_ADC1,
		ADC0_CLOCK = MCLK_APBCMASK_ADC0,
		TC4_CLOCK = MCLK_APBCMASK_TC4,
		TC3_CLOCK = MCLK_APBCMASK_TC3,
		TC2_CLOCK = MCLK_APBCMASK_TC2,
		TC1_CLOCK = MCLK_APBCMASK_TC1,
		TC0_CLOCK = MCLK_APBCMASK_TC0,
		TCC2_CLOCK = MCLK_APBCMASK_TCC2,
		TCC1_CLOCK = MCLK_APBCMASK_TCC1,
		TCC0_CLOCK = MCLK_APBCMASK_TCC0,
		SERCOM5_CLOCK = MCLK_APBCMASK_SERCOM5,
		SERCOM4_CLOCK = MCLK_APBCMASK_SERCOM4,
		SERCOM3_CLOCK = MCLK_APBCMASK_SERCOM3,
		SERCOM2_CLOCK = MCLK_APBCMASK_SERCOM2,
		SERCOM1_CLOCK = MCLK_APBCMASK_SERCOM1,
		SERCOM0_CLOCK = MCLK_APBCMASK_SERCOM0,
		EVSYS_CLOCK = MCLK_APBCMASK_EVSYS,
#elif defined(SAMD20)
		PTC_CLOCK = PM_APBCMASK_PTC,
		DAC_CLOCK = PM_APBCMASK_DAC,
		AC_CLOCK = PM_APBCMASK_AC,
		ADC0_CLOCK = PM_APBCMASK_ADC,
		TC4_CLOCK = PM_APBCMASK_TC4,
		TC3_CLOCK = PM_APBCMASK_TC3,
		TC2_CLOCK = PM_APBCMASK_TC2,
		TC1_CLOCK = PM_APBCMASK_TC1,
		TC0_CLOCK = PM_APBCMASK_TC0,
		SERCOM5_CLOCK = PM_APBCMASK_SERCOM5,
		SERCOM4_CLOCK = PM_APBCMASK_SERCOM4,
		SERCOM3_CLOCK = PM_APBCMASK_SERCOM3,
		SERCOM2_CLOCK = PM_APBCMASK_SERCOM2,
		SERCOM1_CLOCK = PM_APBCMASK_SERCOM1,
		SERCOM0_CLOCK = PM_APBCMASK_SERCOM0,
		EVSYS_CLOCK = PM_APBCMASK_EVSYS,
#endif
	};

#ifdef SAMC21
	enum AHBClock_t
	{
		CAN0_CLOCK = MCLK_AHBMASK_CAN0,
		CAN1_CLOCK = MCLK_AHBMASK_CAN1,
	};
#endif

	static void setMainClock(const clockType_t clockType, const uint32_t frequency);
	static void enableClock(const APBCClock_t clock);
#ifdef SAMC21
	static void enableClock(const AHBClock_t clock);
#endif

	static uint32_t getXosc();

private:
	static uint32_t mXosc;
};