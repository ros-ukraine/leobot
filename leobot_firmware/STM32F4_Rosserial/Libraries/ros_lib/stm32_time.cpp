/*
 * stm32_time.cpp
 *
 *  Created on: 30 квіт. 2018 р.
 *      Author: Nemo
 */


#include "stm32_time.h"

//To-DO: Add defines for critical sections
//example: https://mcuoneclipse.com/2014/01/26/entercritical-and-exitcritical-why-things-are-failing-badly/

void stm32_time_init(void)
{

}

// Get the current time in milliseconds
uint32_t stm32_time_now(void)
{
	uint32_t now;

	//EnterCritical();
	//cli();
	//now = overflow_ms;
	//ExitCritical();
	//sei();

	return now;
}
