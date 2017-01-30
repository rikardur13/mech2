/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include "uart.h"
#include "interrupts.h"
#include "timers.h"
#include "global.h"


void waste_of_time_delay(uint32_t delay);	// Time delay
void init_output(void);

int main (void)
{
	// Insert system clock initialization code here (sysclk_init()). 
	sysclk_init();
	board_init();
	
	uart_init();
	timers_init1();
	timers_init2();
	timers_init3();
	timers_init4();
	timers_init9();
	interrupts_init1();
	init_output();
	
	CrankTooth = 0;
	CurrCycleTime = 0;
	PrevCycleTime = 0;
	PrevCycleCounts	= 0;
	
	
	// Insert application code here, after the board has been initialized. 	

	/* Simple turn on program */
	
	while (1)
	{
			
	}
	return 0;
}







/* Time delay function of unspecified amount of time */
void waste_of_time_delay(uint32_t delay)
{
	for (uint32_t i = 0; i < delay; i++)
	{
		for (uint32_t j = 0; j < 1978; j++)
		{
			__asm__("nop");					// Assembly code that makes the processor do nothing
		}
	}
}

/*
-----------------------------------------------------------------------
------------------------------	Pins	 ------------------------------
-----------------------------------------------------------------------
*/

void init_output(void)
{
		/* Enable simple pin registers */
		PMC->PMC_PCER0	=	(1 << ID_PIOC);			// Peripheral clock enable register
		
		PIOC->PIO_PER	=	PIO_PC17 | PIO_PC23 | PIO_PC19 | PIO_PC28;				// PIO Enable Register			-	Enables the pin
		PIOC->PIO_OER	=	PIO_PC17 | PIO_PC23 | PIO_PC19 | PIO_PC28;				// Output Enable Register		-	Set pin PC23 as output
}

