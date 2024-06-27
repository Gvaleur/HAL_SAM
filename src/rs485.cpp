#include "rs485.h"
#include "threadPlus.h"

RS485::RS485(Uart& uart, Output& dir) : 
	mUart(uart), mDir(dir)
{
	mDir = false;
}

void RS485::write(uint8_t* data, int length)
{
	mDir = true;
	Thread::sleep(1);
	mUart.write(data, length);
	Thread::sleep(1);
	mDir = false;
}

void RS485::read(uint8_t* data, int length, uint32_t timeOut)
{
	mUart.read(data, length, timeOut);
}