#include "can.h"
#include "mcan/mcan.h"
#include "clock.h"
#include "mcan/compiler.h"
#include "mcan/pmc.h"

#include <cstring>

CanBus* CanBus::canInstance[2];

CanBus::CanBus(GenericClock& gclk, can0TxPin_t txPin, can0RxPin_t rxPin, uint32_t bitRate, uint32_t bitRateFd, mcan_can_mode mode, bool disableRetrans)
{
	AlternateFunction::setFunction(AlternateFunction::PORT_A, txPin, AlternateFunction::G);
	AlternateFunction::setFunction(AlternateFunction::PORT_A, rxPin, AlternateFunction::G);

	pmc_set_gck_clock(ID_CAN0, gclk.getFreq());
	canInstance[0] = this;
	initCanBus(gclk, ID_CAN0, bitRate, bitRateFd, mode, disableRetrans);
}

CanBus::CanBus(GenericClock& gclk, can1TxPin_t txPin, can1RxPin_t rxPin, uint32_t bitRate, uint32_t bitRateFd, mcan_can_mode mode, bool disableRetrans)
{
	AlternateFunction::setFunction(AlternateFunction::PORT_B, txPin, AlternateFunction::G);
	AlternateFunction::setFunction(AlternateFunction::PORT_B, rxPin, AlternateFunction::G);

	pmc_set_gck_clock(ID_CAN1, gclk.getFreq());
	canInstance[1] = this;
	initCanBus(gclk, ID_CAN1, bitRate, bitRateFd, mode, disableRetrans);
}

void CanBus::initCanBus(GenericClock& gclk, uint32_t id, uint32_t bitRate, uint32_t bitRateFd, mcan_can_mode mode, bool disableRetrans)
{
	mcan_config config;
	config.id = id;

	if (config.id == ID_CAN0)
	{
		config.regs = CAN0;
	}
	else
	{
		config.regs = CAN1;
	}

	config.msg_ram = mMcanMsgRam;
	config.array_size_filt_std = RAM_ARRAY_SIZE_FILT_STD;
	config.array_size_filt_ext = RAM_ARRAY_SIZE_FILT_EXT;
	config.fifo_size_rx0 = RAM_FIFO_SIZE_RX0;
	config.fifo_size_rx1 = 0;
	config.array_size_rx = RAM_ARRAY_SIZE_RX;
	config.fifo_size_tx_evt = 0;
	config.array_size_tx = RAM_ARRAY_SIZE_TX;
	config.fifo_size_tx = RAM_FIFO_SIZE_TX;

	config.buf_size_rx_fifo0 = 64;
	config.buf_size_rx_fifo1 = 0;
	config.buf_size_rx = 64;
	config.buf_size_tx = 64;

	// using values from AT6493
	config.bit_rate = bitRate;
	config.quanta_before_sp = 10 + 2;
	config.quanta_after_sp = 3 + 1;
	config.quanta_sync_jump = 3 + 1;

	config.bit_rate_fd = bitRateFd;
	config.quanta_before_sp_fd = 10;
	config.quanta_after_sp_fd = 2;
	config.quanta_sync_jump_fd = 2;

	config.disable_retransmission = disableRetrans;

	uint32_t mcanMsgRamSize = ARRAY_SIZE(mMcanMsgRam);

	if (config.id == ID_CAN0)
	{
		gclk.enableClock(GenericClock::CAN0_CLOCK);
		Clock::enableClock(Clock::CAN0_CLOCK);
		NVIC_EnableIRQ(CAN0_IRQn);
	}
	else
	{
		gclk.enableClock(GenericClock::CAN1_CLOCK);
		Clock::enableClock(Clock::CAN1_CLOCK);
		NVIC_EnableIRQ(CAN1_IRQn);
	}

	if (!mcan_configure_msg_ram(&config, &mcanMsgRamSize))
	{
		assert(0);
	}

	if (!mcan_initialize(&mMcan, &config))
	{
		assert(0);
	}
	mcan_set_mode(&mMcan, mode);

	mcan_enable(&mMcan);
	mcan_enable_rx_fifo_new_message_flag(&mMcan, 0, 0);
}

void CanBus::attach(bool extId, const uint32_t id)
{
	// check that we are not already attached
	for (int i = 0; i < RAM_ARRAY_SIZE_FILT_EXT; i++)
	{
		if (mRxFilters[i] == id)
		{
			return;
		}
	}

	// find first empty spot to add filter to
	for (int i = 0; i < RAM_ARRAY_SIZE_FILT_EXT; i++)
	{
		if (mRxFilters[i] == 0)
		{
			mRxFilters[i] = id;
			if (extId)
			{
				mcan_filter_id_mask(&mMcan, 0, i, CAN_EXT_MSG_ID | id, 0x1FFFFFFF);
			}
			else
			{
				mcan_filter_id_mask(&mMcan, 0, i, id, 0x7ff);
			}
			return;
		}
	}
	assert(0); // out of filter spots
}

void CanBus::detach(bool extId, const uint32_t id)
{
	for (int i = 0; i < RAM_ARRAY_SIZE_FILT_EXT; i++)
	{
		if (mRxFilters[i] == id)
		{
			if (extId)
			{
				mcan_remove_filter(&mMcan, i, CAN_EXT_MSG_ID | id);
			}
			else
			{
				mcan_remove_filter(&mMcan, i, id);
			}
			mRxFilters[i] = 0;
			return;
		}
	}
}

bool CanBus::send(bool extId, uint32_t id, uint8_t len, const uint8_t* data)
{
	uint8_t transmitBuf;
	if (extId)
	{
		transmitBuf = mcan_enqueue_outgoing_msg(&mMcan, CAN_EXT_MSG_ID | id, len, data);
	}
	else
	{
		transmitBuf = mcan_enqueue_outgoing_msg(&mMcan, id, len, data);
	}
	if (transmitBuf != 255)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CanBus::setIntHandler(CanInt* handler)
{
	mIntHandler = handler;
}

void CanBus::onInterrupt()
{
	uint8_t mcanMessageData[64];
	mcan_msg_info mcanMessage;
	mcanMessage.data = mcanMessageData;
	uint8_t fifoEntries;
	
	// Poll for new CAN messages in RX FIFO
	do {
		fifoEntries = mcan_dequeue_received_msg(&mMcan, 0, &mcanMessage);
		
		if (fifoEntries > 0)
		{
			if (mIntHandler != 0)
			{
				mIntHandler->vOnMessage(mcanMessage);
			}
		}
	} while (fifoEntries > 1);

	mcan_clear_rx_fifo_flag(&mMcan, 0);
}

void CanBus::interrupt(uint8_t canBus)
{
	canInstance[canBus]->onInterrupt();
}

#if configENABLE_CAN0 == 1
void CAN0_Handler()
{
	CanBus::interrupt(0);
}
#endif

#if configENABLE_CAN1 == 1
void CAN1_Handler()
{
	CanBus::interrupt(1);
}
#endif