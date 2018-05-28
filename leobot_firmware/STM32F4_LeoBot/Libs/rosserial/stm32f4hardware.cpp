/*
 * STM32Hardware.cpp
 *
 *  Created on: 29 квіт. 2018 р.
 *      Author: Nemo
 */


#include "stm32f4hardware.h"

#include "ringbuffer.h"

class STM32F4Hardware;

Ringbuffer uartTxRingBuff;
Ringbuffer uartRxRingBuff;

//https://github.com/robosavvy/rosserial_stm32f1_tutorials/blob/master/freertos/STM32Hardware_FreeRTOS.h


STM32F4Hardware::STM32F4Hardware()
{
	//Ringbuffer uartTxRingBuff;
}

void STM32F4Hardware::init()
{
	MX_USART2_UART_Init();
	//stm32_uart_init();

	// init buffers for tx and rx

	//__enable_irq();
}

// Read a byte of data from ROS connection.
    // If no data, returns -1
uint8_t STM32F4Hardware::read()
{
	//return stm32_uart_receive_byte();
	return 1; //only for debug
}


void STM32F4Hardware::write(uint8_t* data, uint32_t length)
{
	for(uint32_t i = 0; i < length; i++)
	{
		// if ring buffer is empty
		if (uartTxRingBuff.size())
		{
			// send byte to trigger uart send interrupt

			// write date to the fing buffer
			uartTxRingBuff.write(data[i]);
		}
		else
		{
			uartTxRingBuff.write(data[i]);
		}

		//stm32_uart_send_byte(data[i]);
		uartTxRingBuff.write(data[i]);

	}
}

uint32_t STM32F4Hardware::time()
{
	return (uint32_t) xTaskGetTickCount();
}

//extern "C"
//{
#include "stm32f4xx_hal_uart.h"
//}

//*** Interrupt mode IO operation ***
//     ===================================
//     [..]
//       (+) Send an amount of data in non blocking mode using HAL_UART_Transmit_IT()
//       (+) At transmission end of transfer HAL_UART_TxCpltCallback is executed and user can
//            add his own code by customization of function pointer HAL_UART_TxCpltCallback
//       (+) Receive an amount of data in non blocking mode using HAL_UART_Receive_IT()
//       (+) At reception end of transfer HAL_UART_RxCpltCallback is executed and user can
//            add his own code by customization of function pointer HAL_UART_RxCpltCallback
//       (+) In case of transfer Error, HAL_UART_ErrorCallback() function is executed and user can
//            add his own code by customization of function pointer HAL_UART_ErrorCallback


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{

}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

}

/*
extern "C"
{
	void USART2_IRQHandler()
	{
		//USART2, USART_IT_TC

		if (USART2->SR & USART_SR_TXE) // TXE
		{
			USART1->DR = uartTxRingBuff.read();

			//USART_ClearITPendingBit

			USART2->SR &= USART_SR_TXE;
		}

		if (USART2->SR & USART_SR_RXNE)
		{

		}


		 UART in mode Transmitter ------------------------------------------------
		  if(((isrflags & USART_SR_TXE) != RESET) && ((cr1its & USART_CR1_TXEIE) != RESET))
		  {
		    UART_Transmit_IT(huart);
		    return;
		  }


		//USART_ClearITPendingBit(USART2, USART_IT_TC);


		 get data from ring buffer
		//uartTxRingBuff.read();

		 send it via uart*

		 HAL_UART_Transmit_IT(&s_UARTHandle, (uint8_t *)buffer, sizeof(buffer));


		// TX the next available char on the buffer
	}
}

*/
