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
	USART_InitTypeDef usart1_init_struct;

	/* Bit configuration structure for GPIOA PIN9 and PIN10 */
	GPIO_InitTypeDef gpioa_init_struct;

	/* Enalbe clock for USART1 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	/* Enalbe clock for GPIOA */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* GPIOA PIN9 alternative function Tx */
	gpioa_init_struct.GPIO_Pin = GPIO_Pin_9;
	gpioa_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	gpioa_init_struct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA, &gpioa_init_struct);

	/* GPIOA PIN9 alternative function Rx */
	gpioa_init_struct.GPIO_Pin = GPIO_Pin_10;
    gpioa_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	gpioa_init_struct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA, &gpioa_init_struct);

	/* Enable USART1 */
	USART_Cmd(USART1, ENABLE);

	/* Baud rate 57600, 8-bit data, One stop bit
	 * No parity, Do both Rx and Tx, No HW flow control
	 */
	usart1_init_struct.USART_BaudRate = UART_BAUDRATE;
	usart1_init_struct.USART_WordLength = USART_WordLength_8b;
	usart1_init_struct.USART_StopBits = USART_StopBits_1;
	usart1_init_struct.USART_Parity = USART_Parity_No ;
	usart1_init_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usart1_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

	 /* Configure USART1 */
	 USART_Init(USART1, &usart1_init_struct);

}

void stm32_uart_send_byte(uint8_t tx_byte)
{
	USART_SendData(USART1, tx_byte);


	//To-DO: very inefficient solution, change after debug
	// Wait to be able to transmit
	/* Loop until USART2 DR register is empty */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

int16_t stm32_uart_receive_byte(void)
{

	if ((USART1->SR & USART_SR_RXNE) != 0)
	{
		return (USART_ReceiveData(USART1));
	}
	else
	{
		return -1;
	}

}


