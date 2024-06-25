#pragma once
#include "sam.h"
#include "genericClock.h"
#include "semaphorePlus.h"
#include "mutexPlus.h"
#include "HALConfig.h"

class AdcMaster
{
public: 
	enum adc0_t
	{
		adc0
	};

	enum adc1_t
	{
		adc1
	};

	enum avg_t
	{
		avg1 = 0,
		avg2 = 1,
		avg4 = 2,
		avg8 = 3,
		avg16 = 4,
		avg32 = 5,
		avg64 = 6,
		avg128 = 7,
		avg256 = 8,
		avg512 = 9,
		avg1024 = 10
	};

#if defined (SAMC21)
	AdcMaster(adc0_t adc, GenericClock& gclk, avg_t avg);
	AdcMaster(adc1_t adc, GenericClock& gclk, avg_t avg);
#elif defined (SAMD20)
	AdcMaster(GenericClock& gclk, avg_t avg);
#endif

	uint16_t sampleChannel(uint8_t channel);

	void onInterrupt();

	static AdcMaster* getInstance(uint8_t adc);
private: 
	Mutex mLock;
	Semaphore mSem;
	Adc* mAdc;
	uint16_t mResult;

	static AdcMaster* mInstance[2];

	void initAdc(const uint32_t gFreq, const uint8_t biasComp, const uint8_t biasRef, avg_t avg);
};

class AdcChannel
{
public: 
	enum AdcChannel_t
	{
#if defined (SAMC21)
		// ADC0
		PA02 = 0 | (0 << 8) | (2 << 16),
		PA03 = 1 | (0 << 8) | (3 << 16),
		PB08ADC0 = 2 | (1 << 8) | (8 << 16),
		PB09ADC0 = 3 | (1 << 8) | (9 << 16),
		PA04 = 4 | (0 << 8) | (4 << 16),
		PA05 = 5 | (0 << 8) | (5 << 16),
		PA06 = 6 | (0 << 8) | (6 << 16),
		PA07 = 7 | (0 << 8) | (7 << 16),
		PA08ADC0 = 8 | (0 << 8) | (8 << 16),
		PA09ADC0 = 9 | (0 << 8) | (9 << 16),
		PA10 = 10 | (0 << 8) | (10 << 16),
		PA11 = 11 | (0 << 8) | (11 << 16),

		// ADC1
		PB04 = 6 | (1 << 8) | (4 << 16),
		PB05 = 7 | (1 << 8) | (5 << 16),
		PB06 = 8 | (1 << 8) | (6 << 16),
		PB07 = 9 | (1 << 8) | (7 << 16),
		PB08ADC1 = 4 | (1 << 8) | (8 << 16),
		PB09ADC1 = 5 | (1 << 8) | (9 << 16),
		PA08ADC1 = 10 | (0 << 8) | (8 << 16),
		PA09ADC1 = 11 | (0 << 8) | (9 << 16),
		PB00 = 0 | (1 << 8) | (0 << 16),
		PB01 = 1 | (1 << 8) | (1 << 16),
		PB02 = 2 | (1 << 8) | (2 << 16),
		PB03 = 3 | (1 << 8) | (3 << 16)

#elif defined (SAMD20)
		PA02 = 0 | (0 << 8) | (2 << 16),
		PA03 = 1 | (0 << 8) | (3 << 16),
		PB08 = 2 | (1 << 8) | (8 << 16),
		PB09 = 3 | (1 << 8) | (9 << 16),
		PA04 = 4 | (0 << 8) | (4 << 16),
		PA05 = 5 | (0 << 8) | (5 << 16),
		PA06 = 6 | (0 << 8) | (6 << 16),
		PA07 = 7 | (0 << 8) | (7 << 16),
		PB00 = 8 | (1 << 8) | (0 << 16),
		PB01 = 9 | (1 << 8) | (1 << 16),
		PB02 = 10 | (1 << 8) | (2 << 16),
		PB03 = 11 | (1 << 8) | (3 << 16),
		PB04 = 12 | (1 << 8) | (4 << 16),
		PB05 = 13 | (1 << 8) | (5 << 16),
		PB06 = 14 | (1 << 8) | (6 << 16),
		PB07 = 15 | (1 << 8) | (7 << 16),
		PA08 = 16 | (0 << 8) | (8 << 16),
		PA09 = 17 | (0 << 8) | (9 << 16),
		PA10 = 18 | (0 << 8) | (10 << 16),
		PA11 = 19 | (0 << 8) | (11 << 16)
#endif
	};

	AdcChannel(AdcMaster& master, AdcChannel_t channel);

	uint16_t getValue();

private:
	AdcMaster& mMaster;
	uint8_t mChannel;
};

extern "C"
{
#if configENABLE_ADC0 == 1
	void ADC0_Handler();
#endif
#if configENABLE_ADC1 == 1
	void ADC1_Handler();
#endif
#if configENABLE_ADC == 1
	void ADC_Handler();
#endif
}