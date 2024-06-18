#pragma once
#include "stdint.h"

class NvMemory
{
public:

	static void write(const uint8_t* data, const uint32_t len, const uint32_t address);
	static void read(uint8_t* data, const uint32_t len, const uint32_t address);

private:
};