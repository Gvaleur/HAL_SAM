#include "i2c.h"
#include "clock.h"
#include "assert.h"

I2C* I2C::instance[6];

I2C::I2C(GenericClock& gclk, i2c0SdaPin_t sdaPin, i2c0SclPin_t sclPin, int baud)
	: mSercom(SERCOM0), mSem(1, 0)
{
	instance[0] = this;
	gclk.enableClock(GenericClock::SERCOM0_CORE_CLOCK);

	Clock::enableClock(Clock::SERCOM0_CLOCK);
	NVIC_EnableIRQ(SERCOM0_IRQn);
	init(sdaPin, sclPin, gclk, baud);
}

I2C::I2C(GenericClock& gclk, i2c1SdaPin_t sdaPin, i2c1SclPin_t sclPin, int baud)
	: mSercom(SERCOM1), mSem(1, 0)
{
	instance[1] = this;
	gclk.enableClock(GenericClock::SERCOM1_CORE_CLOCK);

	Clock::enableClock(Clock::SERCOM1_CLOCK);
	NVIC_EnableIRQ(SERCOM1_IRQn);
	init(sdaPin, sclPin, gclk, baud);
}

void I2C::init(uint32_t sdaPin, uint32_t sclPin, GenericClock& gclk, int baud)
{
	assert(baud <= 400000);

	// setup pins
	AlternateFunction::port_t sdaPort = static_cast<AlternateFunction::port_t>((sdaPin >> 16) & 0xFF);
	AlternateFunction::function_t sdaFunction = static_cast<AlternateFunction::function_t>((sdaPin >> 8) & 0xFF);
	uint8_t sdaPinNum = sdaPin & 0xFF;
	AlternateFunction::setFunction(sdaPort, sdaPinNum, sdaFunction);

	AlternateFunction::port_t sclPort = static_cast<AlternateFunction::port_t>((sclPin >> 16) & 0xFF);
	AlternateFunction::function_t sclFunction = static_cast<AlternateFunction::function_t>((sclPin >> 8) & 0xFF);
	uint8_t sclPinNum = sclPin & 0xFF;
	AlternateFunction::setFunction(sclPort, sclPinNum, sclFunction);

	// set I2C to host mode
	mSercom->I2CM.CTRLA.bit.MODE = 0x05;

	// disable smart mode
	mSercom->I2CM.CTRLB.bit.SMEN = 0;

	// set baud rate
	mSercom->I2CM.BAUD.bit.BAUD = (gclk.getFreq() / (2 * baud)) - 5;

	// enable interrupts
	mSercom->I2CM.INTENSET.bit.SB = 1;
	mSercom->I2CM.INTENSET.bit.MB = 1;

	// enable I2C controller
	mSercom->I2CM.CTRLA.bit.ENABLE = 1;

	// whait for enable to be done
	while (mSercom->I2CM.SYNCBUSY.bit.ENABLE)
	{

	}

	// force BUS to idle
	mSercom->I2CM.STATUS.bit.BUSSTATE = 0x01;
}

bool I2C::write(uint8_t address, uint8_t* data, int length)
{
	EnterMutex em(mLock);

	mData = data;
	mLen = length;
	mCount = 0;

	// wait for idle
	while (mSercom->I2CM.STATUS.bit.BUSSTATE != 0x01)
	{

	}

	// start transaction by writing address
	mSercom->I2CM.ADDR.bit.ADDR = (address << 1) | 0;

	// wait for data to be sent in intterrupt
	mSem.take(portMAX_DELAY);

	return true;
}

bool I2C::read(uint8_t address, uint8_t* data, int length)
{
	EnterMutex em(mLock);

	mData = data;
	mLen = length;
	mCount = 0;

	// wait for idle
	while (mSercom->I2CM.STATUS.bit.BUSSTATE != 0x01)
	{

	}

	// start transaction by writing address
	mSercom->I2CM.ADDR.bit.ADDR = (address << 1) | 1;

	// wait for data to be sent in intterrupt
	mSem.take(portMAX_DELAY);

	return true;
}

void I2C::onInterrupt()
{
	// Reading
	if (mSercom->I2CM.ADDR.bit.ADDR & 0x1)
	{
		// read new byte
		mData[mCount] = mSercom->I2CM.DATA.bit.DATA;
		mCount++;

		if (mCount < mLen)
		{
			// send ACK and request next byte
			mSercom->I2CM.CTRLB.bit.ACKACT = 0;
			mSercom->I2CM.CTRLB.bit.CMD = 0x02;
		}
		else
		{
			// send NACK and stop condition
			mSercom->I2CM.CTRLB.bit.ACKACT = 1;
			mSercom->I2CM.CTRLB.bit.CMD = 0x03;
			mSem.releaseInt();
		}
	}
	// writing
	else
	{
		if (mCount < mLen)
		{
			// send next byte
			mSercom->I2CM.DATA.bit.DATA = mData[mCount];
			mCount++;
		}
		else
		{
			// send stop condition
			mSercom->I2CM.CTRLB.bit.CMD = 0x03;
			mSem.releaseInt();
		}
	}
}

#if configENABLE_I2C0 == 1
void SERCOM0_Handler()
{
	I2C::instance[0]->onInterrupt();
}
#endif

#if configENABLE_I2C1 == 1
void SERCOM1_Handler()
{
	I2C::instance[1]->onInterrupt();
}
#endif

#if configENABLE_I2C2 == 1
void SERCOM2_Handler()
{
	I2C::instance[2]->onInterrupt();
}
#endif

#if configENABLE_I2C3 == 1
void SERCOM3_Handler()
{
	I2C::instance[3]->onInterrupt();
}
#endif

#if configENABLE_I2C4 == 1
void SERCOM4_Handler()
{
	I2C::instance[4]->onInterrupt();
}
#endif

#if configENABLE_I2C5 == 1
void SERCOM5_Handler()
{
	I2C::instance[5]->onInterrupt();
}
#endif