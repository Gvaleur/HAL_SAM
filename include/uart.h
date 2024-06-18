#pragma once
#include "samc21.h"
#include "genericClock.h"
#include "gpio.h"
#include "HALConfig.h"
#include "mutexPlus.h"
#include "semaphorePlus.h"

class Uart
{
public: 
	enum uart0TxPin_t
	{
		PA_04_UART0 = 4 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_A << 16),
		PA_08_UART0 = 8 | (AlternateFunction::C << 8) | (AlternateFunction::PORT_A << 16)
	};

	enum uart0RxPin_t
	{
		PA_05_UART0 = 5 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_A << 16),
		PA_09_UART0 = 9 | (AlternateFunction::C << 8) | (AlternateFunction::PORT_A << 16)
	};

	enum uart1TxPin_t
	{
		PA_00_UART1 = 0 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_A << 16),
		PA_16_UART1 = 16 | (AlternateFunction::C << 8) | (AlternateFunction::PORT_A << 16)
	};

	enum uart1RxPin_t
	{
		PA_01_UART1 = 1 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_A << 16),
		PA_17_UART1 = 17 | (AlternateFunction::C << 8) | (AlternateFunction::PORT_A << 16)
	};

	enum uart2TxPin_t
	{
		PA_08_UART2 = 8 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_A << 16),
		PA_12_UART2 = 12 | (AlternateFunction::C << 8) | (AlternateFunction::PORT_A << 16)
	};

	enum uart2RxPin_t
	{
		PA_09_UART2 = 9 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_A << 16),
		PA_13_UART2 = 13 | (AlternateFunction::C << 8) | (AlternateFunction::PORT_A << 16)
	};

	enum uart3TxPin_t
	{
		PA_16_UART3 = 16 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_A << 16),
		PA_22_UART3 = 22 | (AlternateFunction::C << 8) | (AlternateFunction::PORT_A << 16)
	};

	enum uart3RxPin_t
	{
		PA_17_UART3 = 17 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_A << 16),
		PA_23_UART3 = 23 | (AlternateFunction::C << 8) | (AlternateFunction::PORT_A << 16)
	};

	enum uart4TxPin_t
	{
		PB_08_UART4 = 8 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_B << 16),
		PB_12_UART4 = 12 | (AlternateFunction::C << 8) | (AlternateFunction::PORT_B << 16),
		PA_12_UART4 = 12 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_A << 16)
	};

	enum uart4RxPin_t
	{
		PB_09_UART4 = 9 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_B << 16),
		PB_13_UART4 = 13 | (AlternateFunction::C << 8) | (AlternateFunction::PORT_B << 16),
		PA_13_UART4 = 13 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_A << 16)
	};

	enum uart5TxPin_t
	{
		PB_16_UART5 = 16 | (AlternateFunction::C << 8) | (AlternateFunction::PORT_B << 16),
		PA_22_UART5 = 22 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_A << 16),
		PB_30_UART5 = 30 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_B << 16),
		PB_02_UART5 = 2 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_B << 16)
	};

	enum uart5RxPin_t
	{
		PB_17_UART5 = 17 | (AlternateFunction::C << 8) | (AlternateFunction::PORT_B << 16),
		PA_23_UART5 = 23 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_A << 16),
		PB_31_UART5 = 31 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_B << 16),
		PB_03_UART5 = 3 | (AlternateFunction::D << 8) | (AlternateFunction::PORT_B << 16)
	};

	Uart(GenericClock& gclk, uart0TxPin_t txPin, uart0RxPin_t rxPin, int baud);
	Uart(GenericClock& gclk, uart1TxPin_t txPin, uart1RxPin_t rxPin, int baud);
	Uart(GenericClock& gclk, uart2TxPin_t txPin, uart2RxPin_t rxPin, int baud);
	Uart(GenericClock& gclk, uart3TxPin_t txPin, uart3RxPin_t rxPin, int baud);
	Uart(GenericClock& gclk, uart4TxPin_t txPin, uart4RxPin_t rxPin, int baud);
	Uart(GenericClock& gclk, uart5TxPin_t txPin, uart5RxPin_t rxPin, int baud);

	void write(uint8_t* data, int length);
	void read(uint8_t* data, int length, uint32_t timeOut = portMAX_DELAY);
	void clearReadBuf();

	static Uart* instance[6];
	void onInterrupt();
private:
	Sercom* mSercom;
	Mutex mLock;
	Semaphore mTxSem;
	Semaphore mRxSem;

	volatile int rxCount = 0;
	volatile int rxTarget = 0;
	uint8_t rxBuf[configUART_BUF_SIZE];

	uint8_t* txBuf;
	volatile int txCount;
	volatile int txTarget;
	bool mTransmitting = false;

	void init(uint32_t txPin, uint32_t rxPin, GenericClock& gclk, int baud);
	
};


extern "C"
{
#if configENABLE_UART0 == 1
	void SERCOM0_Handler();
#endif

#if configENABLE_UART1 == 1
	void SERCOM1_Handler();
#endif

#if configENABLE_UART2 == 1
	void SERCOM2_Handler();
#endif

#if configENABLE_UART3 == 1
	void SERCOM3_Handler();
#endif

#if configENABLE_UART4 == 1
	void SERCOM4_Handler();
#endif

#if configENABLE_UART5 == 1
	void SERCOM5_Handler();
#endif
}