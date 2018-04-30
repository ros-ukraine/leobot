/*
 * STM32Hardware.cpp
 *
 *  Created on: 29 квіт. 2018 р.
 *      Author: Nemo
 */


#include "stm32f4hardware.h"

class STM32F4Hardware;

STM32F4Hardware::STM32F4Hardware()
{

}

void STM32F4Hardware::init()
{
	//wdt_disable();

	stm32_time_init();
	stm32_uart_init();
	//sei();
}

// Read a byte of data from ROS connection.
    // If no data, returns -1
int STM32F4Hardware::read()
{
	//return avr_uart_receive_byte();
	return -1;
}


void STM32F4Hardware::write(uint8_t* data, int length)
{

}

unsigned long STM32F4Hardware::time()
{
	return 1000;
}


