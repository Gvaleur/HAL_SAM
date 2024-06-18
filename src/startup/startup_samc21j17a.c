/*
	This file contains the entry point (Reset_Handler) of your firmware project.
	The reset handled initializes the RAM and calls system library initializers as well as
	the platform-specific initializer and the main() function.
*/

#include <stddef.h>
extern void *_estack;

void Reset_Handler();
void Default_Handler();

#ifdef DEBUG_DEFAULT_INTERRUPT_HANDLERS
void __attribute__ ((weak)) NMI_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void NMI_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) HardFault_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void HardFault_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ReservedM12() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ReservedM12();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ReservedM11() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ReservedM11();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ReservedM10() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ReservedM10();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ReservedM9() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ReservedM9();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ReservedM8() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ReservedM8();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ReservedM7() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ReservedM7();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ReservedM6() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ReservedM6();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SVC_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SVC_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ReservedM4() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ReservedM4();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ReservedM3() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ReservedM3();
	asm("bkpt 255");
}

void __attribute__ ((weak)) PendSV_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PendSV_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SysTick_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SysTick_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SYSTEM_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SYSTEM_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) WDT_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void WDT_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) RTC_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void RTC_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) EIC_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void EIC_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) FREQM_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void FREQM_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) TSENS_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TSENS_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) NVMCTRL_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void NVMCTRL_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) DMAC_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void DMAC_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) EVSYS_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void EVSYS_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SERCOM0_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SERCOM0_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SERCOM1_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SERCOM1_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SERCOM2_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SERCOM2_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SERCOM3_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SERCOM3_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SERCOM4_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SERCOM4_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SERCOM5_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SERCOM5_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) CAN0_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void CAN0_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) CAN1_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void CAN1_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) TCC0_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TCC0_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) TCC1_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TCC1_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) TCC2_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TCC2_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) TC0_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TC0_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) TC1_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TC1_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) TC2_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TC2_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) TC3_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TC3_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) TC4_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void TC4_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ADC0_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ADC0_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) ADC1_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void ADC1_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) AC_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void AC_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) DAC_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void DAC_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) SDADC_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void SDADC_Handler();
	asm("bkpt 255");
}

void __attribute__ ((weak)) PTC_Handler() 
{
	//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void PTC_Handler();
	asm("bkpt 255");
}

#else
void NMI_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void HardFault_Handler()  __attribute__ ((weak, alias ("Default_Handler")));
void ReservedM12()        __attribute__ ((weak, alias ("Default_Handler")));
void ReservedM11()        __attribute__ ((weak, alias ("Default_Handler")));
void ReservedM10()        __attribute__ ((weak, alias ("Default_Handler")));
void ReservedM9()         __attribute__ ((weak, alias ("Default_Handler")));
void ReservedM8()         __attribute__ ((weak, alias ("Default_Handler")));
void ReservedM7()         __attribute__ ((weak, alias ("Default_Handler")));
void ReservedM6()         __attribute__ ((weak, alias ("Default_Handler")));
void SVC_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void ReservedM4()         __attribute__ ((weak, alias ("Default_Handler")));
void ReservedM3()         __attribute__ ((weak, alias ("Default_Handler")));
void PendSV_Handler()     __attribute__ ((weak, alias ("Default_Handler")));
void SysTick_Handler()    __attribute__ ((weak, alias ("Default_Handler")));
void SYSTEM_Handler()     __attribute__ ((weak, alias ("Default_Handler")));
void WDT_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void RTC_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void EIC_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void FREQM_Handler()      __attribute__ ((weak, alias ("Default_Handler")));
void TSENS_Handler()      __attribute__ ((weak, alias ("Default_Handler")));
void NVMCTRL_Handler()    __attribute__ ((weak, alias ("Default_Handler")));
void DMAC_Handler()       __attribute__ ((weak, alias ("Default_Handler")));
void EVSYS_Handler()      __attribute__ ((weak, alias ("Default_Handler")));
void SERCOM0_Handler()    __attribute__ ((weak, alias ("Default_Handler")));
void SERCOM1_Handler()    __attribute__ ((weak, alias ("Default_Handler")));
void SERCOM2_Handler()    __attribute__ ((weak, alias ("Default_Handler")));
void SERCOM3_Handler()    __attribute__ ((weak, alias ("Default_Handler")));
void SERCOM4_Handler()    __attribute__ ((weak, alias ("Default_Handler")));
void SERCOM5_Handler()    __attribute__ ((weak, alias ("Default_Handler")));
void CAN0_Handler()       __attribute__ ((weak, alias ("Default_Handler")));
void CAN1_Handler()       __attribute__ ((weak, alias ("Default_Handler")));
void TCC0_Handler()       __attribute__ ((weak, alias ("Default_Handler")));
void TCC1_Handler()       __attribute__ ((weak, alias ("Default_Handler")));
void TCC2_Handler()       __attribute__ ((weak, alias ("Default_Handler")));
void TC0_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void TC1_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void TC2_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void TC3_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void TC4_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void ADC0_Handler()       __attribute__ ((weak, alias ("Default_Handler")));
void ADC1_Handler()       __attribute__ ((weak, alias ("Default_Handler")));
void AC_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void DAC_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void SDADC_Handler()      __attribute__ ((weak, alias ("Default_Handler")));
void PTC_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
#endif

void * g_pfnVectors[0x2f] __attribute__ ((section (".isr_vector"), used)) = 
{
	&_estack,
	&Reset_Handler,
	&NMI_Handler,
	&HardFault_Handler,
	&ReservedM12,
	&ReservedM11,
	&ReservedM10,
	&ReservedM9,
	&ReservedM8,
	&ReservedM7,
	&ReservedM6,
	&SVC_Handler,
	&ReservedM4,
	&ReservedM3,
	&PendSV_Handler,
	&SysTick_Handler,
	&SYSTEM_Handler,
	&WDT_Handler,
	&RTC_Handler,
	&EIC_Handler,
	&FREQM_Handler,
	&TSENS_Handler,
	&NVMCTRL_Handler,
	&DMAC_Handler,
	&EVSYS_Handler,
	&SERCOM0_Handler,
	&SERCOM1_Handler,
	&SERCOM2_Handler,
	&SERCOM3_Handler,
	&SERCOM4_Handler,
	&SERCOM5_Handler,
	&CAN0_Handler,
	&CAN1_Handler,
	&TCC0_Handler,
	&TCC1_Handler,
	&TCC2_Handler,
	&TC0_Handler,
	&TC1_Handler,
	&TC2_Handler,
	&TC3_Handler,
	&TC4_Handler,
	&ADC0_Handler,
	&ADC1_Handler,
	&AC_Handler,
	&DAC_Handler,
	&SDADC_Handler,
	&PTC_Handler,
};

void SystemInit();
void __libc_init_array();
int main();

extern void *_sidata, *_sdata, *_edata;
extern void *_sbss, *_ebss;

void __attribute__((naked, noreturn)) Reset_Handler()
{
	//Normally the CPU should will setup the based on the value from the first entry in the vector table.
	//If you encounter problems with accessing stack variables during initialization, ensure the line below is enabled.
	#ifdef sram_layout
	asm ("ldr sp, =_estack");
	#endif

	void **pSource, **pDest;
	for (pSource = &_sidata, pDest = &_sdata; pDest != &_edata; pSource++, pDest++)
		*pDest = *pSource;

	for (pDest = &_sbss; pDest != &_ebss; pDest++)
		*pDest = 0;

	SystemInit();
	__libc_init_array();
	(void)main();
	for (;;) ;
}

void __attribute__((naked, noreturn)) Default_Handler()
{
	//If you get stuck here, your code is missing a handler for some interrupt.
	//Define a 'DEBUG_DEFAULT_INTERRUPT_HANDLERS' macro via VisualGDB Project Properties and rebuild your project.
	//This will pinpoint a specific missing vector.
	for (;;) ;
}
