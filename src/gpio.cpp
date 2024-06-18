#include "gpio.h"

Input::Input(port_t port, const uint8_t pin, const bool inverted, const input_pull pull)
	: mPort(port)
	, mPin(pin)
	, mInverted(inverted)
{
	PORT->Group[mPort].DIRCLR.reg = (1 << mPin);
	PORT->Group[mPort].PINCFG[pin].bit.INEN = true;

	switch (pull)
	{
	case NO_PULL_UP:
		PORT->Group[mPort].PINCFG[pin].bit.PULLEN = false;
		break;

	case PULL_UP:
		PORT->Group[mPort].OUTSET.reg = (1 << mPin);
		PORT->Group[mPort].PINCFG[pin].bit.PULLEN = true;
		break;

	case PULL_DOWN:
		PORT->Group[mPort].OUTCLR.reg = (1 << mPin);
		PORT->Group[mPort].PINCFG[pin].bit.PULLEN = true;
		break;
	}
}

Input::operator bool() const
{
	if (mInverted)
	{
		return !(PORT->Group[mPort].IN.reg & (1 << mPin));
	}
	else
	{
		return (PORT->Group[mPort].IN.reg & (1 << mPin));
	}
}

Output::Output(port_t port, const uint8_t pin, const bool inverted, const output_speed speed)
	: mPort(port)
	, mPin(pin)
	, mInverted(inverted)
{
	PORT->Group[mPort].DIRSET.reg = (1 << mPin);
	PORT->Group[mPort].PINCFG[pin].bit.INEN = true;
	PORT->Group[mPort].PINCFG[pin].bit.DRVSTR = speed;
}

Output* Output::operator= (bool state)
{
	if (state != mInverted)
	{
		PORT->Group[mPort].OUTSET.reg = (1 << mPin);
	}
	else
	{
		PORT->Group[mPort].OUTCLR.reg = (1 << mPin);
	}

	return this;
}

Output::operator bool() const
{
	if (mInverted)
	{
		return !(PORT->Group[mPort].IN.reg & (1 << mPin));
	}
	else
	{
		return (PORT->Group[mPort].IN.reg & (1 << mPin));
	}
}

void AlternateFunction::setFunction(port_t port, uint8_t pin, function_t function)
{
	if (pin % 2)
	{
		PORT->Group[port].PMUX[pin / 2].bit.PMUXO = function;
	}
	else
	{
		PORT->Group[port].PMUX[pin / 2].bit.PMUXE = function;
	}

	PORT->Group[port].PINCFG[pin].bit.PMUXEN = true;
	PORT->Group[port].PINCFG[pin].bit.INEN = true;
}