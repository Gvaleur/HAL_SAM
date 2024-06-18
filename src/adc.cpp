#include "adc.h"
#include "math.h"
#include "gpio.h"
#include "clock.h"

AdcMaster* AdcMaster::mInstance[2];

AdcMaster::AdcMaster(adc0_t adc, GenericClock& gclk, avg_t avg)
	: mSem(1, 0)
	, mAdc(ADC0)
{
	mInstance[0] = this;
	Clock::enableClock(Clock::ADC0_CLOCK);
	gclk.enableClock(GenericClock::ADC0_CLOCK);

	uint32_t* nvmData;
	nvmData = reinterpret_cast<uint32_t*>(NVMCTRL_OTP5);
	uint8_t biasComp = (*nvmData & ADC0_FUSES_BIASCOMP_Msk) >> ADC0_FUSES_BIASCOMP_Pos;
	uint8_t biasRef = (*nvmData & ADC0_FUSES_BIASREFBUF_Msk) >> ADC0_FUSES_BIASREFBUF_Pos;

	initAdc(gclk.getFreq(), biasComp, biasRef, avg);
	NVIC_EnableIRQ(ADC0_IRQn);
}

void AdcMaster::initAdc(const uint32_t gFreq, const uint8_t biasComp, const uint8_t biasRef, avg_t avg)
{
	// set prescaler
	uint32_t div = gFreq / 12000000;
	div = log2l(div) /*- 1*/;
	mAdc->CTRLB.bit.PRESCALER = div;

	mAdc->CTRLA.bit.ONDEMAND = true;

	// set ref to full vcc ref
	mAdc->REFCTRL.reg = ADC_REFCTRL_REFCOMP | ADC_REFCTRL_REFSEL_INTVCC2;

	// set rail to rail input
	mAdc->CTRLC.reg = ADC_CTRLC_R2R | ADC_CTRLC_RESSEL_12BIT;

	// selct correct number of divisons to do on result
	uint32_t adjRes;
	switch (avg)
	{
	case AdcMaster::avg1:
		adjRes = 0;
		break;
	case AdcMaster::avg2:
		adjRes = 1;
		break;
	case AdcMaster::avg4:
		adjRes = 2;
		break;
	case AdcMaster::avg8:
		adjRes = 3;
		break;
	default:
		adjRes = 4;
		break;
	}

	// set averaging of results
	mAdc->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM(avg) | ADC_AVGCTRL_ADJRES(adjRes);

	// set offset compensation and sample length
	mAdc->SAMPCTRL.reg = ADC_SAMPCTRL_OFFCOMP;

	// load calibration data
	mAdc->CALIB.reg = (biasComp << ADC_CALIB_BIASCOMP_Pos) | (biasRef << ADC_CALIB_BIASREFBUF_Pos);

	// enable interrupt 
	mAdc->INTENSET.bit.RESRDY = true;

	// enable ADC
	mAdc->CTRLA.bit.ENABLE = true;
}

uint16_t AdcMaster::sampleChannel(uint8_t channel)
{
	EnterMutex lock(mLock);

	// set mux
	mAdc->INPUTCTRL.reg = (0x18 << ADC_INPUTCTRL_MUXNEG_Pos) | channel;

	// start conversion
	mAdc->SWTRIG.bit.START = true;

	mSem.take(200);

	// read result
	return mResult;
}

void AdcMaster::onInterrupt()
{
	// read result
	mResult = mAdc->RESULT.reg;
	mSem.release();
}

AdcMaster* AdcMaster::getInstance(uint8_t adc)
{
	return mInstance[adc];
}

AdcChannel::AdcChannel(AdcMaster& master, AdcChannel_t channel)
	: mMaster(master)
	, mChannel(channel & 0xF)
{
	AlternateFunction::setFunction(static_cast<AlternateFunction::port_t>((channel >> 4) & 0xF), (channel >> 8) & 0xF, AlternateFunction::B);
}

uint16_t AdcChannel::getValue()
{
	return mMaster.sampleChannel(mChannel);
}

#if configENABLE_ADC0 == 1
void ADC0_Handler()
{
	AdcMaster::getInstance(0)->onInterrupt();
}
#endif

#if configENABLE_ADC1 == 1
void ADC1_Handler()
{
	AdcMaster::getInstance(1)->onInterrupt();
}
#endif