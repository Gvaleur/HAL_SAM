#pragma once
#include "gpio.h"
#include "genericClock.h"
#include "mcan/mcan.h"
#include <array>
#include "HALConfig.h"

/* size of our custom Rx and Tx Buffer Elements, in words */
#define RAM_BUF_SIZE                  (MCAN_RAM_BUF_HDR_SIZE + 64u / 4)

#define RAM_ARRAY_SIZE_FILT_STD       (2u)
#define RAM_ARRAY_SIZE_FILT_EXT       (configMAX_ATTACHES)
#define RAM_FIFO_SIZE_RX0             (12u)
/* no Rx FIFO 1 in our Message RAM */
#define RAM_ARRAY_SIZE_RX             (4u)
/* no Tx Event FIFO in our Message RAM */
#define RAM_ARRAY_SIZE_TX             (4u)
#define RAM_FIFO_SIZE_TX              (4u)

/* size of our custom Message RAM, in words */
#define MSG_RAM_SIZE      ( \
      RAM_ARRAY_SIZE_FILT_STD * MCAN_RAM_FILT_STD_SIZE \
    + RAM_ARRAY_SIZE_FILT_EXT * MCAN_RAM_FILT_EXT_SIZE \
    + RAM_FIFO_SIZE_RX0 * RAM_BUF_SIZE \
    + RAM_ARRAY_SIZE_RX * RAM_BUF_SIZE \
    + RAM_ARRAY_SIZE_TX * RAM_BUF_SIZE \
    + RAM_FIFO_SIZE_TX * RAM_BUF_SIZE )

class CanInt
{
private:
	virtual void vOnMessage(mcan_msg_info msg) = 0;
	friend class CanBus;
};

class CanBus
{
public:
	enum can0TxPin_t
	{
		PA_24 = 24
	};

	enum can0RxPin_t
	{
		PA_25 = 25
	};

	enum can1TxPin_t
	{
		PB_10 = 10,
		PB_14 = 14
	};

	enum can1RxPin_t
	{
		PB_11 = 11,
		PB_15 = 15
	};

	CanBus(GenericClock& gclk, can0TxPin_t txPin, can0RxPin_t rxPin, uint32_t bitRate, uint32_t bitRateFd, mcan_can_mode mode, bool disableRetrans = false);
	CanBus(GenericClock& gclk, can1TxPin_t txPin, can1RxPin_t rxPin, uint32_t bitRate, uint32_t bitRateFd, mcan_can_mode mode, bool disableRetrans = false);

	void attach(bool extId, const uint32_t id);
	bool send(bool extId, uint32_t id, uint8_t len, const uint8_t* data);
	void detach(bool extId, const uint32_t id);
	void setIntHandler(CanInt* handler);

	static void interrupt(uint8_t canBus);
private:
	static CanBus* canInstance[2];
	CanInt* mIntHandler = 0;
	mcan_set mMcan;
	uint32_t mMcanMsgRam[MSG_RAM_SIZE] __attribute__((aligned(4)));
	uint32_t mRxFilters[RAM_ARRAY_SIZE_FILT_EXT] = { 0 };
	
	void initCanBus(GenericClock& gclk, uint32_t id, uint32_t bitRate, uint32_t bitRateFd, mcan_can_mode mode, bool disableRetrans);
	void onInterrupt();
};

extern "C"
{
#if configENABLE_CAN0 == 1
	void CAN0_Handler();
#endif

#if configENABLE_CAN1 == 1
	void CAN1_Handler();
#endif
}