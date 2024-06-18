#pragma once
#include "stdint.h"

class Watchdog
{
public: 
	enum timeOut_t
	{
		CYC8 = 0,
		CYC16 = 1,
		CYC32 = 2,
		CYC64 = 3,
		CYC128 = 4,
		CYC256 = 5,
		CYC512 = 6,
		CYC1024 = 7,
		CYC2048 = 8,
		CYC4096 = 9,
		CYC8192 = 10,
		CYC16384 = 11,
	};

	Watchdog(timeOut_t timeOut);

	void kick();
};