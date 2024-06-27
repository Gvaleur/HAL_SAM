#pragma once
#include "uart.h"
#include "gpio.h"

class RS485
{
public:
	RS485(Uart& uart, Output& dir);

	void write(uint8_t* data, int length);
	void read(uint8_t* data, int length, uint32_t timeOut = portMAX_DELAY);
private:
	Uart& mUart;
	Output& mDir;
};