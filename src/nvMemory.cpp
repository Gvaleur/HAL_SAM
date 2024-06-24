#include "nvMemory.h"
#include "sam.h"
#include <assert.h>
#include <cstring>
#include <algorithm>

#define NVM_MEMORY        ((volatile uint32_t *)FLASH_ADDR)

void NvMemory::write(const uint8_t* data, const uint32_t len, const uint32_t address)
{
	// wait for flash controller to be ready
	while (NVMCTRL->INTFLAG.bit.READY == 0)
	{

	}

	// disable flash cache and interrupts
	uint32_t cacheState = NVMCTRL->CTRLB.bit.CACHEDIS;
	if (address <= FLASH_SIZE)
	{
		NVMCTRL->CTRLB.bit.CACHEDIS = 0b11;
		__disable_irq();
	}

	// enable manual page writes
	NVMCTRL->CTRLB.bit.MANW = true;

	// Clear error flags
	NVMCTRL->STATUS.reg = NVMCTRL_STATUS_MASK;

	const uint32_t actualAddress = address - (address % NVMCTRL_ROW_SIZE);
	const uint32_t endAddress = address + len;
	static uint8_t rowBuffer[NVMCTRL_ROW_SIZE];
	for (int rowAddress = actualAddress; rowAddress < endAddress; rowAddress += NVMCTRL_ROW_SIZE)
	{
		// align data to rows
		if (rowAddress < address)
		{
			read(rowBuffer, NVMCTRL_ROW_SIZE, rowAddress);
			memcpy(&rowBuffer[address - rowAddress], data, std::min(NVMCTRL_ROW_SIZE - address - rowAddress, len));
		}
		else if ((rowAddress + NVMCTRL_ROW_SIZE) > endAddress)
		{
			read(rowBuffer, NVMCTRL_ROW_SIZE, rowAddress);
			memcpy(rowBuffer, &data[rowAddress - address], endAddress - rowAddress);
		}
		else
		{
			memcpy(rowBuffer, &data[rowAddress - address], NVMCTRL_ROW_SIZE);
		}

		// delete 256 byte row
		NVMCTRL->ADDR.bit.ADDR = rowAddress / 2;
		if (address > FLASH_SIZE)
		{
			NVMCTRL->CTRLA.reg = NVMCTRL_CTRLA_CMD_RWWEEER | NVMCTRL_CTRLA_CMDEX_KEY;
		}
		else
		{
			NVMCTRL->CTRLA.reg = NVMCTRL_CTRLA_CMD_ER | NVMCTRL_CTRLA_CMDEX_KEY;
		}

		// wait for flash controller to finish command
		while (NVMCTRL->INTFLAG.bit.READY == 0)
		{

		}

		for (int j = 0; j < NVMCTRL_ROW_SIZE; j += NVMCTRL_PAGE_SIZE)
		{
			// clear page buffer
			NVMCTRL->CTRLA.reg = NVMCTRL_CTRLA_CMD_PBC | NVMCTRL_CTRLA_CMDEX_KEY;

			// wait for flash controller to finish command
			while (NVMCTRL->INTFLAG.bit.READY == 0)
			{

			}

			// write new data
			for (int k = 0; k < NVMCTRL_PAGE_SIZE; k += sizeof(uint32_t))
			{
				uint32_t tempData;
				tempData = rowBuffer[j + k];
				tempData |= (rowBuffer[j + k + 1] << 8);
				tempData |= (rowBuffer[j + k + 2] << 16);
				tempData |= (rowBuffer[j + k + 3] << 24);
				NVM_MEMORY[(rowAddress + j + k) / 4] = tempData;
			}

			if (address > FLASH_SIZE)
			{
				NVMCTRL->CTRLA.reg = NVMCTRL_CTRLA_CMD_RWWEEWP | NVMCTRL_CTRLA_CMDEX_KEY;
			}
			else
			{
				NVMCTRL->CTRLA.reg = NVMCTRL_CTRLA_CMD_WP | NVMCTRL_CTRLA_CMDEX_KEY;
			}

			// wait for flash controller to finish command
			while (NVMCTRL->INTFLAG.bit.READY == 0)
			{

			}
		}
	}

	// reset cache settings and interrupts
	if (address <= FLASH_SIZE)
	{
		NVMCTRL->CTRLB.bit.CACHEDIS = cacheState;
		__enable_irq();
	}
}

void NvMemory::read(uint8_t* data, const uint32_t len, const uint32_t address)
{
	memcpy(data, reinterpret_cast<void*>(address), len);
}