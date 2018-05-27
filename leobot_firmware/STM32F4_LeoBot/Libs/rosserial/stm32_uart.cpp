/*
 * stm32_uart.cpp
 *
 *  Created on: 30 квіт. 2018 р.
 *      Author: Nemo
 */

#include "stm32_uart.h"


void stm32_uart_init(void)
{
	/* USART configuration structure for USART1 */
	USART_InitTypeDef USART_InitStructure;

	/* Bit configuration structure for GPIOA PIN9 and PIN10 */
	GPIO_InitTypeDef GPIOA_InitStructure;

	/* Enable clock for GPIOA */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* Enable clock for USART2 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2 ,GPIO_AF_USART2); //TX
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3 ,GPIO_AF_USART2); //RX

	/* PA2 - Tx, PA3 - Rx */
	GPIOA_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIOA_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIOA_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIOA_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOA_InitStructure);

	USART_InitStructure.USART_BaudRate = UART_BAUDRATE;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);

	/* Enable USART2 */
	USART_Cmd(USART2, ENABLE);
}

void stm32_uart_send_byte(uint8_t tx_byte)
{
	//USART_FLAG_TXE: to indicate the status of the transmit buffer register.
	//USART_FLAG_TC: to indicate the status of the transmit operation.

	//To-DO: very inefficient solution, change after debug

	/* Loop until USART2 DR register is empty */
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);

	USART_SendData(USART2, tx_byte);

	// Wait to be able to transmit
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
}

int16_t stm32_uart_receive_byte(void)
{
	if (USART_GetFlagStatus(USART2, USART_SR_RXNE) != 0)
	{
		return (USART_ReceiveData(USART2));
	}
	else
	{
		return -1;
	}
}


