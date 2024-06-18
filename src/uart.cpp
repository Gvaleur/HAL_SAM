#include "uart.h"
#include <string.h>
#include "assert.h"
#include "clock.h"

Uart* Uart::instance[6];

Uart::Uart(GenericClock& gclk, uart0TxPin_t txPin, uart0RxPin_t rxPin, int baud)
	: mSercom(SERCOM0), mTxSem(1, 0), mRxSem(1, 0)
{
	instance[0] = this;
	gclk.enableClock(GenericClock::SERCOM0_CORE_CLOCK);
	
	Clock::enableClock(Clock::SERCOM0_CLOCK);
	NVIC_EnableIRQ(SERCOM0_IRQn);
	init(txPin, rxPin, gclk, baud);
}

Uart::Uart(GenericClock& gclk, uart1TxPin_t txPin, uart1RxPin_t rxPin, int baud)
	: mSercom(SERCOM1), mTxSem(1, 0), mRxSem(1, 0)
{
	instance[1] = this;
	gclk.enableClock(GenericClock::SERCOM1_CORE_CLOCK);

	Clock::enableClock(Clock::SERCOM1_CLOCK);
	NVIC_EnableIRQ(SERCOM1_IRQn);
	init(txPin, rxPin, gclk, baud);
}

Uart::Uart(GenericClock& gclk, uart2TxPin_t txPin, uart2RxPin_t rxPin, int baud)
	: mSercom(SERCOM2), mTxSem(1, 0), mRxSem(1, 0)
{
	instance[2] = this;
	gclk.enableClock(GenericClock::SERCOM2_CORE_CLOCK);

	Clock::enableClock(Clock::SERCOM2_CLOCK);
	NVIC_EnableIRQ(SERCOM2_IRQn);
	init(txPin, rxPin, gclk, baud);
}

Uart::Uart(GenericClock& gclk, uart3TxPin_t txPin, uart3RxPin_t rxPin, int baud)
	: mSercom(SERCOM3), mTxSem(1, 0), mRxSem(1, 0)
{
	instance[3] = this;
	gclk.enableClock(GenericClock::SERCOM3_CORE_CLOCK);

	Clock::enableClock(Clock::SERCOM3_CLOCK);
	NVIC_EnableIRQ(SERCOM3_IRQn);
	init(txPin, rxPin, gclk, baud);
}

#if !(defined(__SAMC21E15A__) || defined(__SAMC21E16A__) || defined(__SAMC21E17A__) || defined(__SAMC21E18A__))

Uart::Uart(GenericClock& gclk, uart4TxPin_t txPin, uart4RxPin_t rxPin, int baud)
	: mSercom(SERCOM4), mTxSem(1, 0), mRxSem(1, 0)
{
	instance[4] = this;
	gclk.enableClock(GenericClock::SERCOM4_CORE_CLOCK);

	Clock::enableClock(Clock::SERCOM4_CLOCK);
	NVIC_EnableIRQ(SERCOM4_IRQn);
	init(txPin, rxPin, gclk, baud);
}

Uart::Uart(GenericClock& gclk, uart5TxPin_t txPin, uart5RxPin_t rxPin, int baud)
	: mSercom(SERCOM5), mTxSem(1, 0), mRxSem(1, 0)
{
	instance[5] = this;
	gclk.enableClock(GenericClock::SERCOM5_CORE_CLOCK);

	Clock::enableClock(Clock::SERCOM5_CLOCK);
	NVIC_EnableIRQ(SERCOM5_IRQn);
	init(txPin, rxPin, gclk, baud);
}

#endif

void Uart::init(uint32_t txPin, uint32_t rxPin, GenericClock& gclk, int baud)
{
	// setup pins
	AlternateFunction::port_t txPort = static_cast<AlternateFunction::port_t>((txPin >> 16) & 0xFF);
	AlternateFunction::function_t txFunction = static_cast<AlternateFunction::function_t>((txPin >> 8) & 0xFF);
	uint8_t txPinNum = txPin & 0xFF;
	PORT->Group[txPort].PINCFG[txPinNum].bit.DRVSTR = 1;
	AlternateFunction::setFunction(txPort, txPinNum, txFunction);

	AlternateFunction::port_t rxPort = static_cast<AlternateFunction::port_t>((rxPin >> 16) & 0xFF);
	AlternateFunction::function_t rxFunction = static_cast<AlternateFunction::function_t>((rxPin >> 8) & 0xFF);
	uint8_t rxPinNum = rxPin & 0xFF;
	AlternateFunction::setFunction(rxPort, rxPinNum, rxFunction);

	// set USART pad connection
	mSercom->USART.CTRLA.bit.RXPO = 1;
	mSercom->USART.CTRLA.bit.TXPO = 2;
	mSercom->USART.CTRLA.bit.DORD = 1;

	// set internal clock
	mSercom->USART.CTRLA.bit.MODE = 1;

	// enable rx and tx
	mSercom->USART.CTRLB.bit.RXEN = 1;
	mSercom->USART.CTRLB.bit.TXEN = 1;

	// set baud rate
	uint32_t baudReg = 65536 * (1 - 16 * (static_cast<double>(baud) / static_cast<double>(gclk.getFreq())));
	if (baudReg <= 0xFFFF)
	{
		mSercom->USART.BAUD.reg = baudReg;
	}
	else
	{
		assert(0);
	}

	// enable interrupts
	//mSercom->USART.INTENSET.bit.TXC = 1;
	mSercom->USART.INTENSET.bit.RXC = 1;

	// wait for CTRLB is in sync
	while (mSercom->USART.SYNCBUSY.bit.CTRLB)
	{

	}

	// enable the USART
	mSercom->USART.CTRLA.bit.ENABLE = 1;

	// wait for it to finish enable
	while (mSercom->USART.SYNCBUSY.bit.ENABLE)
	{

	}
}

void Uart::write(uint8_t* data, int length)
{
	EnterMutex em(mLock);

	txBuf = data;
	txCount = 0;
	txTarget = length;
	mTransmitting = true;
	mSercom->USART.INTENSET.bit.DRE = 1;
	mTxSem.take(10000);
}

void Uart::read(uint8_t* data, int length, uint32_t timeOut)
{
	EnterMutex em(mLock);

	// disable read intterupt
	mSercom->USART.INTENCLR.bit.RXC = 1;

	// if we do not have all the data allready
	if (length > rxCount)
	{
		// set target enable interrupts and wait
		rxTarget = length;
		mSercom->USART.INTENSET.bit.RXC = 1;
		mRxSem.take(timeOut);
		mSercom->USART.INTENCLR.bit.RXC = 1;
	}

	// read data
	memcpy(data, &rxBuf[rxCount - length], length);

	rxCount = 0;
	rxTarget = 0;

	// enable read interrupt
	mSercom->USART.INTENSET.bit.RXC = 1;
}

void Uart::clearReadBuf()
{
	EnterMutex em(mLock);

	// disable read intterupt
	mSercom->USART.INTENCLR.bit.RXC = 1;

	rxCount = 0;
	rxTarget = 0;

	// enable read interrupt
	mSercom->USART.INTENSET.bit.RXC = 1;
}

void Uart::onInterrupt()
{
	if (mSercom->USART.INTFLAG.bit.RXC)
	{
		volatile uint16_t tempData = mSercom->USART.DATA.reg;
		rxBuf[rxCount] = tempData;
		rxCount++;

		if ((rxTarget != 0) && (rxCount >= rxTarget))
		{
			mRxSem.releaseInt();
		}
	}

	if (mSercom->USART.INTFLAG.bit.DRE && mTransmitting)
	{
		if (txCount < txTarget)
		{
			mSercom->USART.DATA.reg = txBuf[txCount];
			txCount++;
		}
		else
		{
			mSercom->USART.INTENCLR.bit.DRE = 1;
			mTxSem.releaseInt();
			mTransmitting = false;
		}
	}
}


#if configENABLE_UART0 == 1
void SERCOM0_Handler()
{
	Uart::instance[0]->onInterrupt();
}
#endif

#if configENABLE_UART1 == 1
void SERCOM1_Handler()
{
	Uart::instance[1]->onInterrupt();
}
#endif

#if configENABLE_UART2 == 1
void SERCOM2_Handler()
{
	Uart::instance[2]->onInterrupt();
}
#endif

#if configENABLE_UART3 == 1
void SERCOM3_Handler()
{
	Uart::instance[3]->onInterrupt();
}
#endif

#if configENABLE_UART4 == 1
void SERCOM4_Handler()
{
	Uart::instance[4]->onInterrupt();
}
#endif

#if configENABLE_UART5 == 1
void SERCOM5_Handler()
{
	Uart::instance[5]->onInterrupt();
}
#endif