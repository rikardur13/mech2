/*
 * global.h
 *
 * Created: 24.1.2017 15:12:32
 *  Author: nanna
 */ 


#ifndef GLOBAL_H_
#define GLOBAL_H_

#define MAX_RPM_TABLE_LENGTH		8
#define MAX_LOAD_TABLE_LENGTH		8

#define CRANK_TEETH					24
#define CYLINDERS					4
#define TACH_EVENTS					2
#define CRANK_DEGREE_INTERVAL		180




uint32_t	PrevCycleCounts;
uint32_t	CurrCycleTime;
uint32_t	PrevCycleTime;
uint8_t		FirtCrankInterval;
uint8_t		SecondCrankInterval;


uint16_t	IGN[MAX_RPM_TABLE_LENGTH][MAX_LOAD_TABLE_LENGTH];
uint8_t		TEETH[CRANK_TEETH];
uint32_t	CrankTooth;



#endif /* GLOBAL_H_ */