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

	AdcMaster(adc0_t adc, GenericClock& gclk, avg_t avg);
	AdcMaster(adc1_t adc, GenericClock& gclk, avg_t avg);

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
		// ADC0
		PA02 = 0 | (0 << 4) | (2 << 8),
		PA03 = 1 | (0 << 4) | (3 << 8),
		PB08ADC0 = 2 | (1 << 4) | (8 << 8),
		PB09ADC0 = 3 | (1 << 4) | (9 << 8),
		PA04 = 4 | (0 << 4) | (4 << 8),
		PA05 = 5 | (0 << 4) | (5 << 8),
		PA06 = 6 | (0 << 4) | (6 << 8),
		PA07 = 7 | (0 << 4) | (7 << 8),
		PA08ADC0 = 8 | (0 << 4) | (8 << 8),
		PA09ADC0 = 9 | (0 << 4) | (9 << 8),
		PA10 = 10 | (0 << 4) | (10 << 8),
		PA11 = 11 | (0 << 4) | (11 << 8),

		// ADC1
		PB04 = 6 | (1 << 4) | (4 << 8),
		PB05 = 7 | (1 << 4) | (5 << 8),
		PB06 = 8 | (1 << 4) | (6 << 8),
		PB07 = 9 | (1 << 4) | (7 << 8),
		PB08ADC1 = 4 | (1 << 4) | (8 << 8),
		PB09ADC1 = 5 | (1 << 4) | (9 << 8),
		PA08ADC1 = 10 | (0 << 4) | (8 << 8),
		PA09ADC1 = 11 | (0 << 4) | (9 << 8),
		PB00 = 0 | (1 << 4) | (0 << 8),
		PB01 = 1 | (1 << 4) | (1 << 8),
		PB02 = 2 | (1 << 4) | (2 << 8),
		PB03 = 3 | (1 << 4) | (3 << 8)
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
}