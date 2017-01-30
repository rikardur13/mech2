/*
 * math.c
 *
 * Created: 24.1.2017 18:33:59
 *  Author: nanna
 */ 

#include "math.h"



uint8_t interpolation(uint16_t value, uint16_t x1, uint16_t x2)
{
	if (value <= x1) // below or equal to lower bound
	return 0;

	if (value >= x2) // above or equal to upper bounds
	return 100;

	return ((long)(value - x1) * 100)/((x2 - x1));
}


uint16_t math_ign_time_teeth(uint8_t ign_degree)
{
	return	((((CRANK_DEGREE_INTERVAL - ign_degree) * 100) / CRANK_DEGREE_INTERVAL) * CRANK_TEETH)/TACH_EVENTS/100;
}


uint32_t math_ign_time_interval(uint8_t ign_degree, uint32_t toothInterval)
{
	uint32_t temp1 = ((((CRANK_DEGREE_INTERVAL - ign_degree) * 10000) / CRANK_DEGREE_INTERVAL) * CRANK_TEETH)/TACH_EVENTS;
	uint32_t temp2 = math_ign_time_teeth(ign_degree) *10000;
	return (10000 - (temp1 - temp2))*toothInterval/10000;
}