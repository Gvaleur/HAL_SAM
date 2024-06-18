#pragma once
#include "gpio.h"
#include "genericClock.h"
#include "mutexPlus.h"
#include "semaphorePlus.h"
#include "HALConfig.h"

class I2C
{
public:
	enum i2c0SdaPin_t
	{
		PA_04_I2C0 = 4 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_A << 16),
		PA_08_I2C0 = 8 | (AlternateFunction::C << 8) | (AlternateFunction::PORT_A << 16)
	};

	enum i2c0SclPin_t
	{
		PA_05_I2C0 = 5 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_A << 16),
		PA_09_I2C0 = 9 | (AlternateFunction::C << 8) | (AlternateFunction::PORT_A << 16)
	};

	enum i2c1SdaPin_t
	{
		PA_00_I2C1 = 0 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_A << 16),
		PA_16_I2C1 = 16 | (AlternateFunction::C << 8) | (AlternateFunction::PORT_A << 16)
	};

	enum i2c1SclPin_t
	{
		PA_01_I2C1 = 1 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_A << 16),
		PA_17_I2C1 = 17 | (AlternateFunction::C << 8) | (AlternateFunction::PORT_A << 16)
	};

	enum i2c2SdaPin_t
	{
		PA_08_I2C2 = 8 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_A << 16),
		PA_12_I2C2 = 12 | (AlternateFunction::C << 8) | (AlternateFunction::PORT_A << 16)
	};

	enum i2c2SclPin_t
	{
		PA_09_I2C2 = 9 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_A << 16),
		PA_13_I2C2 = 13 | (AlternateFunction::C << 8) | (AlternateFunction::PORT_A << 16)
	};

	enum i2c3SdaPin_t
	{
		PA_16_I2C3 = 16 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_A << 16),
		PA_22_I2C3 = 22 | (AlternateFunction::C << 8) | (AlternateFunction::PORT_A << 16)
	};

	enum i2c3SclPin_t
	{
		PA_17_I2C3 = 17 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_A << 16),
		PA_23_I2C3 = 23 | (AlternateFunction::C << 8) | (AlternateFunction::PORT_A << 16)
	};

	enum i2c4SdaPin_t
	{
		PB_08_I2C4 = 8 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_B << 16),
		PB_12_I2C4 = 12 | (AlternateFunction::C << 8) | (AlternateFunction::PORT_B << 16),
		PA_12_I2C4 = 12 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_A << 16)
	};

	enum i2c4SclPin_t
	{
		PB_09_I2C4 = 9 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_B << 16),
		PB_13_I2C4 = 13 | (AlternateFunction::C << 8) | (AlternateFunction::PORT_B << 16),
		PA_13_I2C4 = 13 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_A << 16)
	};

	enum i2c5SdaPin_t
	{
		PB_16_I2C5 = 16 | (AlternateFunction::C << 8) | (AlternateFunction::PORT_B << 16),
		PA_22_I2C5 = 22 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_A << 16),
		PB_30_I2C5 = 30 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_B << 16),
		PB_02_I2C5 = 2 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_B << 16)
	};

	enum i2c5SclPin_t
	{
		PB_17_I2C5 = 17 | (AlternateFunction::C << 8) | (AlternateFunction::PORT_B << 16),
		PA_23_I2C5 = 23 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_A << 16),
		PB_31_I2C5 = 31 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_B << 16),
		PB_03_I2C5 = 3 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_B << 16)
	};

	I2C(GenericClock& gclk, i2c0SdaPin_t sdaPin, i2c0SclPin_t sclPin, int baud);
	I2C(GenericClock& gclk, i2c1SdaPin_t sdaPin, i2c1SclPin_t sclPin, int baud);
	I2C(GenericClock& gclk, i2c2SdaPin_t sdaPin, i2c2SclPin_t sclPin, int baud);
	I2C(GenericClock& gclk, i2c3SdaPin_t sdaPin, i2c3SclPin_t sclPin, int baud);
	I2C(GenericClock& gclk, i2c4SdaPin_t sdaPin, i2c4SclPin_t sclPin, int baud);
	I2C(GenericClock& gclk, i2c5SdaPin_t sdaPin, i2c5SclPin_t sclPin, int baud);

	bool write(uint8_t address, uint8_t* data, int length);
	bool read(uint8_t address, uint8_t* data, int length);

	static I2C* instance[6];
	void onInterrupt();
private:
	Sercom* mSercom;
	Mutex mLock;
	Semaphore mSem;

	uint8_t* mData;
	uint8_t mLen;
	uint8_t mCount;

	void init(uint32_t sdaPin, uint32_t sclPin, GenericClock& gclk, int baud);
};

extern "C"
{
#if configENABLE_I2C0 == 1
	void SERCOM0_Handler();
#endif

#if configENABLE_I2C1 == 1
	void SERCOM1_Handler();
#endif

#if configENABLE_I2C2 == 1
	void SERCOM2_Handler();
#endif

#if configENABLE_I2C3 == 1
	void SERCOM3_Handler();
#endif

#if configENABLE_I2C4 == 1
	void SERCOM4_Handler();
#endif

#if configENABLE_I2C5 == 1
	void SERCOM5_Handler();
#endif
}