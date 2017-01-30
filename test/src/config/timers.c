/*
 * timers.c
 *
 * Created: 24.1.2017 14:49:34
 *  Author: nanna
 */ 


#include "timers.h"
#include "uart.h"
#include "interrupts.h"
#include <asf.h>

/*
-----------------------------------------------------------------------
------------------------------	Timers	 ------------------------------
-----------------------------------------------------------------------
*/

// Cylinder 1
void timers_init1(void)
{
	PMC->PMC_PCER0	=	(1 << ID_TC0);									// Enable peripheral clock for timer 0
	enable_interrupt_vector(TC0_IRQn, 1);								// Enable nested vector interrupt for timer 0
	
	TC0->TC_CHANNEL[0].TC_IER	=	TC_IER_COVFS	|	TC_IER_CPAS;	// Enable Counter overflow interrupt (COVFS) and RA compare interrupt (CPAS)
	
	/*
	TIMER_CLOCK1	-	MCK/2
	TIMER_CLOCK2	-	MCK/8
	TIMER_CLOCK3	-	MCK/32
	TIMER_CLOCK4	-	MCK/128
	TIMER_CLOCK5	-	SLCK
	
	Where MCK is the master clock (84 MHz for the Arduino Due) and SLCK is the slow clock 
	(which can be clocked at 32.768 kHz by Y2 on the Arduino Due).
	*/	
	/* TC Channel mode register (MCK / 2) */
	TC0->TC_CHANNEL[0].TC_CMR	=	TC_CMR_TCCLKS_TIMER_CLOCK1	|	TC_CMR_WAVE;	
	
	/* TC channel control register, enable counter */
	TC0->TC_CHANNEL[0].TC_CCR	=	TC_CCR_SWTRG	|	TC_CCR_CLKEN;		
}

// Cylinder 2
void timers_init2(void)
{
	PMC->PMC_PCER0	=	(1 << ID_TC1);			// Enable peripheral clock for timer 0
	enable_interrupt_vector(TC1_IRQn, 2);		// Enable nested vector interrupt for timer 0
	
	TC0->TC_CHANNEL[1].TC_IER	=	TC_IER_COVFS	|	TC_IER_CPAS;
	
	/*
	TIMER_CLOCK1	-	MCK/2
	TIMER_CLOCK2	-	MCK/8
	TIMER_CLOCK3	-	MCK/32
	TIMER_CLOCK4	-	MCK/128
	TIMER_CLOCK5	-	SLCK
	
	Where MCK is the master clock (84 MHz for the Arduino Due) and SLCK is the slow clock 
	(which can be clocked at 32.768 kHz by Y2 on the Arduino Due).
	*/	
	/* TC Channel mode register (MCK / 2) */
	TC0->TC_CHANNEL[1].TC_CMR	=	TC_CMR_TCCLKS_TIMER_CLOCK1	|	TC_CMR_WAVE;
		
	/* TC channel control register, enable counter */
	TC0->TC_CHANNEL[1].TC_CCR	=	TC_CCR_SWTRG	|	TC_CCR_CLKEN;
}

// Cylinder 3
void timers_init3(void)
{
	PMC->PMC_PCER0	=	(1 << ID_TC2);			// Enable peripheral clock for timer 0
	enable_interrupt_vector(TC2_IRQn, 3);		// Enable nested vector interrupt for timer 0
	
	TC0->TC_CHANNEL[2].TC_IER	=	TC_IER_COVFS	|	TC_IER_CPAS;
	
	/*
	TIMER_CLOCK1	-	MCK/2
	TIMER_CLOCK2	-	MCK/8
	TIMER_CLOCK3	-	MCK/32
	TIMER_CLOCK4	-	MCK/128
	TIMER_CLOCK5	-	SLCK
	
	Where MCK is the master clock (84 MHz for the Arduino Due) and SLCK is the slow clock 
	(which can be clocked at 32.768 kHz by Y2 on the Arduino Due).
	*/	
	/* TC Channel mode register (MCK / 2) */
	TC0->TC_CHANNEL[2].TC_CMR	=	TC_CMR_TCCLKS_TIMER_CLOCK1	|	TC_CMR_WAVE;
	
	/* TC channel control register, enable counter */
	TC0->TC_CHANNEL[2].TC_CCR	=	TC_CCR_SWTRG	|	TC_CCR_CLKEN;
}

// Cylinder 4
void timers_init4(void)
{
	PMC->PMC_PCER0	=	(1 << ID_TC3);			// Enable peripheral clock for timer 0
	enable_interrupt_vector(TC3_IRQn, 4);		// Enable nested vector interrupt for timer 0
	
	TC1->TC_CHANNEL[0].TC_IER	=	TC_IER_COVFS	|	TC_IER_CPAS;
	
	/*
	TIMER_CLOCK1	-	MCK/2
	TIMER_CLOCK2	-	MCK/8
	TIMER_CLOCK3	-	MCK/32
	TIMER_CLOCK4	-	MCK/128
	TIMER_CLOCK5	-	SLCK
	
	Where MCK is the master clock (84 MHz for the Arduino Due) and SLCK is the slow clock 
	(which can be clocked at 32.768 kHz by Y2 on the Arduino Due).
	*/	
	/* TC Channel mode register (MCK / 2) */
	TC1->TC_CHANNEL[0].TC_CMR	=	TC_CMR_TCCLKS_TIMER_CLOCK1	|	TC_CMR_WAVE;
		
	/* TC channel control register, enable counter */
	TC1->TC_CHANNEL[0].TC_CCR	=	TC_CCR_SWTRG	|	TC_CCR_CLKEN;
}

// Global timer
void timers_init9(void)
{
	PMC->PMC_PCER1	=	(1 << (ID_TC8 - 32));			// Enable peripheral clock for timer 0
	enable_interrupt_vector(TC8_IRQn, 9);		// Enable nested vector interrupt for timer 0
	
	TC2->TC_CHANNEL[2].TC_IER	=	TC_IER_COVFS;
	
	/*
	TIMER_CLOCK1	-	MCK/2
	TIMER_CLOCK2	-	MCK/8
	TIMER_CLOCK3	-	MCK/32
	TIMER_CLOCK4	-	MCK/128
	TIMER_CLOCK5	-	SLCK
	
	Where MCK is the master clock (84 MHz for the Arduino Due) and SLCK is the slow clock 
	(which can be clocked at 32.768 kHz by Y2 on the Arduino Due).
	*/	
	/* TC Channel mode register (MCK / 2) */
	TC2->TC_CHANNEL[2].TC_CMR	=	TC_CMR_TCCLKS_TIMER_CLOCK1	|	TC_CMR_WAVE;
		
	/* TC channel control register, enable counter */
	TC2->TC_CHANNEL[2].TC_CCR	=	TC_CCR_SWTRG	|	TC_CCR_CLKEN;
}



/*
-----------------------------------------------------------------------
------------------------------	Handlers ------------------------------
-----------------------------------------------------------------------
*/


void TC0_Handler(void)
{
	uint32_t readtc0	=	TC0->TC_CHANNEL[0].TC_SR;	// Read the Timer/Counter TC0, channel 0, status register
	uint32_t status =	PIOC->PIO_ODSR;			// Store the status on pins in port C

	/*	Toggle output pin PC23	*/
	if (status & PIO_ODSR_P17)					// AND the status on pins in port C and the status of pin 23
	{
		PIOC->PIO_CODR	=	PIO_PC17;			// If PC23 is high,	Clear Output Data Register	-	Sets pin PC23 to low
	}
	else
	{
		PIOC->PIO_SODR	=	PIO_PC17;			// If PC23 is low,	Set Output Data Register	-	Sets pin PC23 to high
	}
	TC0->TC_CHANNEL[0].TC_CCR	=	TC_CCR_CLKDIS;
}

void TC1_Handler(void)
{
	uint32_t readtc1	=	TC0->TC_CHANNEL[1].TC_SR;	// Read the Timer/Counter TC0, channel 1, status register
	uint32_t status =	PIOC->PIO_ODSR;			// Store the status on pins in port C

	/*	Toggle output pin PC23	*/
	if (status & PIO_ODSR_P23)					// AND the status on pins in port C and the status of pin 23
	{
		PIOC->PIO_CODR	=	PIO_PC23;			// If PC23 is high,	Clear Output Data Register	-	Sets pin PC23 to low
	}
	else
	{
		PIOC->PIO_SODR	=	PIO_PC23;			// If PC23 is low,	Set Output Data Register	-	Sets pin PC23 to high
	}
	TC0->TC_CHANNEL[1].TC_CCR	=	TC_CCR_CLKDIS;
}

void TC2_Handler(void)
{
	uint32_t readtc2	=	TC0->TC_CHANNEL[2].TC_SR;	// Read the Timer/Counter TC0, channel 2, status register
	uint32_t status =	PIOC->PIO_ODSR;			// Store the status on pins in port C
	
	/*	Toggle output pin PC19	*/
	if (status & PIO_ODSR_P19)					// AND the status on pins in port C and the status of pin 19
	{
		PIOC->PIO_CODR	=	PIO_PC19;			// If PC19 is high,	Clear Output Data Register	-	Sets pin PC19 to low
	}
	else
	{
		PIOC->PIO_SODR	=	PIO_PC19;			// If PC19 is low,	Set Output Data Register	-	Sets pin PC19 to high
	}
	TC0->TC_CHANNEL[2].TC_CCR	=	TC_CCR_CLKDIS;
}


void TC3_Handler(void)
{
	uint32_t readtc3	=	TC1->TC_CHANNEL[0].TC_SR;	// Read the Timer/Counter TC1, channel 0, status register
	uint32_t status =	PIOC->PIO_ODSR;			// Store the status on pins in port C
	
	/*	Toggle output pin PC28	*/
	if (status & PIO_ODSR_P28)					// AND the status on pins in port C and the status of pin 28
	{
		PIOC->PIO_CODR	=	PIO_PC28;			// If PC28 is high,	Clear Output Data Register	-	Sets pin PC28 to low
	}
	else
	{
		PIOC->PIO_SODR	=	PIO_PC28;			// If PC28 is low,	Set Output Data Register	-	Sets pin PC28 to high
	}
	TC1->TC_CHANNEL[0].TC_CCR	=	TC_CCR_CLKDIS;
}

void TC8_Handler(void)
{
	// uint32_t readtc8	=	TC2->TC_CHANNEL[2].TC_SR;
}
