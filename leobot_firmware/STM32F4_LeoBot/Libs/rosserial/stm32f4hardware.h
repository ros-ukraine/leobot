/*
 * STM32Hardware.h
 *
 *  Created on: 29 квіт. 2018 р.
 *      Author: Nemo
 */

#ifndef STM32F4HARDWARE_H_
#define STM32F4HARDWARE_H_

extern "C"
{
	#include "usart.h"
	#include "FreeRTOS.h"
    #include "task.h"
}

//#include "ringbuffer.h"

class STM32F4Hardware
{
public:
	STM32F4Hardware();

	// Initialize the STM32
	void init();

	//
	uint8_t read();

	// Send a byte of data to ROS connection
	void write(uint8_t* data, uint32_t length);

	// Returns milliseconds since start of program
	uint32_t time();

};

#endif /* STM32F4HARDWARE_H_ */
