#pragma once
#include "sam.h"

class Input
{
public:
	enum port_t
	{
		PORT_A = 0,
		PORT_B = 1
	};

	enum input_pull
	{
		NO_PULL_UP = 0,
		PULL_UP = 1,
		PULL_DOWN = 2
	};

	Input(port_t port, const uint8_t pin, const bool inverted = false, const input_pull pull = NO_PULL_UP);

	operator bool() const;

private:
	port_t mPort;
	const uint8_t mPin;
	const bool mInverted;
};

class Output
{
public:
	enum port_t
	{
		PORT_A = 0,
		PORT_B = 1
	};

	enum output_speed
	{
		NORMAL_SPEED = 0,
		HIGH_SPEED = 1
	};

	Output(port_t port, const uint8_t pin, const bool inverted = false, const output_speed speed = NORMAL_SPEED);

	Output* operator= (bool state);
	operator bool() const;

private:
	port_t mPort;
	const uint8_t mPin;
	const bool mInverted;
};

class AlternateFunction
{
public:
	enum port_t
	{
		PORT_A = 0,
		PORT_B = 1
	};

	enum function_t
	{
		A = 0,
		B = 1,
		C = 2,
		D = 3,
		E = 4,
		F = 5,
		G = 6,
		H = 7,
		I = 8
	};

	static void setFunction(port_t port, uint8_t pin, function_t function);
};