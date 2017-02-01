/*
 * interrupts.c
 *
 * Created: 24.1.2017 14:50:55
 *  Author: nanna
 */ 

#include <asf.h>
#include "interrupts.h"
#include "uart.h"
#include "math.h"

/* Initialize nested vector interrupts */
/* Enable interrupt controller */
/************************************************************************/
	/*
	TC  Chan    NVIC "irq"  IRQ handler    function PMC id
	TC0    0    TC0_IRQn    TC0_Handler    ID_TC0
	TC0    1    TC1_IRQn    TC1_Handler    ID_TC1
	TC0    2    TC2_IRQn    TC2_Handler    ID_TC2
	TC1    0    TC3_IRQn    TC3_Handler    ID_TC3
	TC1    1    TC4_IRQn    TC4_Handler    ID_TC4
	TC1    2    TC5_IRQn    TC5_Handler    ID_TC5
	TC2    0    TC6_IRQn    TC6_Handler    ID_TC6
	TC2    1    TC7_IRQn    TC7_Handler    ID_TC7
	TC2    2    TC8_IRQn    TC8_Handler    ID_TC8                         
	*/
/************************************************************************/

void enable_interrupt_vector(uint32_t irqn, uint32_t priority)
{
	NVIC_DisableIRQ(irqn);
	NVIC_ClearPendingIRQ(irqn);
	NVIC_SetPriority(irqn, priority);
	NVIC_EnableIRQ(irqn);
}





/*
-----------------------------------------------------------------------
------------------------------Initialize ------------------------------
-----------------------------------------------------------------------
*/

// Crank sensor
void interrupts_init1(void)
{
	/* Enable interrupt registers */
	PMC->PMC_PCER0	=	(1 << ID_PIOA);			// Enable the peripheral clock for port A
	
	PIOA->PIO_IER	=	PIO_PA7;				// Enable the interrupt register on pin 7 in port A
	enable_interrupt_vector(PIOA_IRQn, 0);		// Enable nested interrupt vector and set priority 0 in port A
	
	/*	Interrupt on rising edge		*/
	PIOA->PIO_AIMER	=	PIO_PA7;				// Enable additional interrupt modes
	PIOA->PIO_ESR	=	PIO_PA7;				// Select edge detection
	PIOA->PIO_REHLSR=	PIO_PA7;				// Select rising edge detection
	
	
	
	/*	Debouncing filter for a mechanical switch on pin D31	*/
	// PIOA->PIO_IFER	=	PIO_PA15;				// Enable input glitch filter register
	// PIOA->PIO_DIFSR	=	PIO_PA15;				// Select debouncing filter
	// PIOA->PIO_SCDR	=	0x01;					/* Set debouncing frequency  DIV = (32768Hz*(1/frequency))/2 - 1  */
	
}



// Cam sensor
void interrupts_init2(void)
{
	/* Enable interrupt registers */
	PMC->PMC_PCER0	=	(1 << ID_PIOA);			// Enable the peripheral clock for port A
	
	PIOA->PIO_IER	=	PIO_PA15;				// Enable the interrupt register on pin 7 in port A
	enable_interrupt_vector(PIOA_IRQn, 0);		// Enable nested interrupt vector and set priority 0 in port A
	
	/*	Interrupt on rising edge		*/
	PIOA->PIO_AIMER	=	PIO_PA15;				// Enable additional interrupt modes
	PIOA->PIO_ESR	=	PIO_PA15;				// Select edge detection
	PIOA->PIO_REHLSR=	PIO_PA15;				// Select rising edge detection
	
	
	
	/*	Debouncing filter for a mechanical switch on pin D31	*/
	// PIOA->PIO_IFER	=	PIO_PA7;				// Enable input glitch filter register
	// PIOA->PIO_DIFSR	=	PIO_PA7;				// Select debouncing filter
	// PIOA->PIO_SCDR	=	0x01;					/* Set debouncing frequency  DIV = (32768Hz*(1/frequency))/2 - 1  */
	
}




/*
-----------------------------------------------------------------------
------------------------------ Handlers -------------------------------
-----------------------------------------------------------------------
*/


void PIOA_Handler(void)
{
	uint32_t readpio	=	PIOA->PIO_ISR;									// !!!!!CRUTIAL!!!!! for the handler to work
	
	CurrCycleTime	=	TC2->TC_CHANNEL[2].TC_CV - PrevCycleCounts;
	PrevCycleCounts = TC2->TC_CHANNEL[2].TC_CV;

	
	if (CurrCycleTime > (PrevCycleTime*15)/10)
	{
		CrankTooth = 0;
		SecondCrankInterval = 11 - math_ign_time_teeth(DEGREE_TEST);
	}
	else if (CrankTooth == 12)
	{
		FirtCrankInterval = 23 - math_ign_time_teeth(DEGREE_TEST);
	}
	
	if (CrankTooth == FirtCrankInterval)
	{		
		TC0->TC_CHANNEL[1].TC_RA	=	math_ign_time_interval(DEGREE_TEST, PrevCycleTime);
		TC0->TC_CHANNEL[1].TC_CCR	=	TC_CCR_SWTRG	|	TC_CCR_CLKEN;
	}
	if (CrankTooth == SecondCrankInterval)
	{
		TC0->TC_CHANNEL[0].TC_RA	=	math_ign_time_interval(DEGREE_TEST, PrevCycleTime);
		TC0->TC_CHANNEL[0].TC_CCR	=	TC_CCR_SWTRG	|	TC_CCR_CLKEN;
	}
	CrankTooth++;
	PrevCycleTime	=	CurrCycleTime;
}