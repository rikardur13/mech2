/*
 * interrupts.h
 *
 * Created: 24.1.2017 14:50:42
 *  Author: nanna
 */ 

#include <asf.h>
#include "global.h"

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

void enable_interrupt_vector(uint32_t irqn, uint32_t priority);
void interrupts_init1(void);
void interrupts_init2(void);



#endif /* INTERRUPTS_H_ */