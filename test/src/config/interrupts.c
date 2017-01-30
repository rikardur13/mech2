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
	// PIOA->PIO_IFER	=	PIO_PA7;				// Enable input glitch filter register
	// PIOA->PIO_DIFSR	=	PIO_PA7;				// Select debouncing filter
	// PIOA->PIO_SCDR	=	0x01;					/* Set debouncing frequency  DIV = (32768Hz*(1/frequency))/2 - 1  debouncing frequency of 333Hz	(20.000rpm)*/
	
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
		
		uint32_t status =	PIOC->PIO_ODSR;			// Store the status on pins in port C

		/*	Toggle output pin PC17	*/
		if (status & PIO_ODSR_P17)					// AND the status on pins in port C and the status of pin 17
		{
			PIOC->PIO_CODR	=	PIO_PC17;			// If PC17 is high,	Clear Output Data Register	-	Sets pin PC17 to low
		}
		else
		{
			PIOC->PIO_SODR	=	PIO_PC17;			// If PC17 is low,	Set Output Data Register	-	Sets pin PC17 to high
		}
		
		// SecondCrankInterval = 12 - math_ign_time_teeth(36);
		
				
		/*
		TC0->TC_CHANNEL[0].TC_RA	=	TC0->TC_CHANNEL[0].TC_CV;
		TC0->TC_CHANNEL[0].TC_CCR	=	TC_CCR_SWTRG	|	TC_CCR_CLKEN;
		*/
	}
	else if (CrankTooth == 12)
	{

		
		uint32_t status =	PIOC->PIO_ODSR;			// Store the status on pins in port C

		/*	Toggle output pin PC17	*/
		if (status & PIO_ODSR_P23)					// AND the status on pins in port C and the status of pin 23
		{
			PIOC->PIO_CODR	=	PIO_PC23;			// If PC23 is high,	Clear Output Data Register	-	Sets pin PC23 to low
		}
		else
		{
			PIOC->PIO_SODR	=	PIO_PC23;			// If PC23 is low,	Set Output Data Register	-	Sets pin PC23 to high
		}
		
		
		
		
		// FirtCrankInterval = 24 - math_ign_time_teeth(36);
		
		
		/*
		TC0->TC_CHANNEL[1].TC_RA	=	TC0->TC_CHANNEL[1].TC_CV;
		TC0->TC_CHANNEL[1].TC_CCR	=	TC_CCR_SWTRG	|	TC_CCR_CLKEN;
		*/
	}
	
	
	if (CrankTooth == SecondCrankInterval)
	{
		/*
		TC0->TC_CHANNEL[0].TC_RA	=	TC0->TC_CHANNEL[0].TC_CV + math_ign_time_interval(36, PrevCycleTime);
		TC0->TC_CHANNEL[0].TC_CCR	=	TC_CCR_SWTRG	|	TC_CCR_CLKEN;
		*/
		// uart_print_int(1);
	}
	if (CrankTooth == FirtCrankInterval)
	{
		/*
		TC0->TC_CHANNEL[1].TC_RA	=	TC0->TC_CHANNEL[1].TC_CV + math_ign_time_interval(36, PrevCycleTime);
		TC0->TC_CHANNEL[1].TC_CCR	=	TC_CCR_SWTRG	|	TC_CCR_CLKEN;
		*/
		// uart_print_int(2);
	}
	




	// Toggle 4 ignition pins 
	/*
	TC0->TC_CHANNEL[0].TC_CCR	=	TC_CCR_SWTRG	|	TC_CCR_CLKEN;
	TC0->TC_CHANNEL[1].TC_CCR	=	TC_CCR_SWTRG	|	TC_CCR_CLKEN;
	TC0->TC_CHANNEL[2].TC_CCR	=	TC_CCR_SWTRG	|	TC_CCR_CLKEN;
	TC1->TC_CHANNEL[0].TC_CCR	=	TC_CCR_SWTRG	|	TC_CCR_CLKEN;
	
	
	TC0->TC_CHANNEL[0].TC_RA	=	TC0->TC_CHANNEL[0].TC_CV	+	105000;	// Make timer interrupt trigger after 0,5 seconds
	TC0->TC_CHANNEL[1].TC_RA	=	TC0->TC_CHANNEL[1].TC_CV	+	210000;
	TC0->TC_CHANNEL[2].TC_RA	=	TC0->TC_CHANNEL[2].TC_CV	+	315000;
	TC1->TC_CHANNEL[0].TC_RA	=	TC1->TC_CHANNEL[0].TC_CV	+	420000;
	*/
	
	uart_print_int(CrankTooth);
	CrankTooth++;
	PrevCycleTime	=	CurrCycleTime;
}