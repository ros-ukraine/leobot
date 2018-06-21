/*
 * STM32Hardware.cpp
 *
 *  Created on: 29 квіт. 2018 р.
 *      Author: Nemo
 */


#include "stm32f4hardware.h"

#include "usart.h"

class STM32F4Hardware;

//https://github.com/robosavvy/rosserial_stm32f1_tutorials/blob/master/freertos/STM32Hardware_FreeRTOS.h


STM32F4Hardware::STM32F4Hardware()
{

}

void STM32F4Hardware::init()
{
	MX_USART2_UART_Init();
}


/*
 * name:   Read a byte of data from ROS connection
 * param:  none
 * retval: data, or -1 if there are no data
 */
int STM32F4Hardware::read()
{
	if (!LL_USART_IsActiveFlag_RXNE(USART2)) return -1;

	return LL_USART_ReceiveData8(USART2);
}


void STM32F4Hardware::write(uint8_t* data, uint32_t length)
{
	for(uint32_t i = 0; i < length; i++)
	{
		while (!LL_USART_IsActiveFlag_TXE(USART2));
		LL_USART_TransmitData8(USART2, data[i]);
		while(!LL_USART_IsActiveFlag_TC(USART2));
	}
}

//uint32_t STM32F4Hardware::time()
uint32_t STM32F4Hardware::time()
{
	uint32_t now;

	//return (uint32_t) xTaskGetTickCount();
	//EnterCritical();
	__disable_irq();
	//return HAL_GetTick();
	now = HAL_GetTick();
	__enable_irq();
		//ExitCritical();
	return now;
}


