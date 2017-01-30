/*
 * math.h
 *
 * Created: 24.1.2017 18:34:11
 *  Author: nanna
 */ 

#include <asf.h>
#include "global.h"

#ifndef MATH_H_
#define MATH_H_

uint8_t interpolation(uint16_t value, uint16_t x1, uint16_t x2);

uint16_t math_ign_time_teeth(uint8_t ign_degree);
uint32_t math_ign_time_interval(uint8_t ign_degree, uint32_t toothInterval);



#endif /* MATH_H_ */