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
	//stm32_time_init();


	//stm32_uart_init();

	__enable_irq();
}

// Read a byte of data from ROS connection.
    // If no data, returns -1
uint8_t STM32F4Hardware::read()
{
	//return stm32_uart_receive_byte();
	return 1;
}


void STM32F4Hardware::write(uint8_t* data, uint32_t length)
{
	for(uint32_t i = 0; i < length; i++)
	{
		//stm32_uart_send_byte(data[i]);
	}
}

uint32_t STM32F4Hardware::time()
{
	return (uint32_t) xTaskGetTickCount();
}


