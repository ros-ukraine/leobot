/*
 * stm32_uart.h
 *
 *  Created on: 30 квіт. 2018 р.
 *      Author: Nemo
 */

#ifndef ROS_LIB_STM32_UART_H_
#define ROS_LIB_STM32_UART_H_

#include "stm32f4xx.h"

void stm32_uart_init(void);
void stm32_uart_send_byte(uint8_t tx_byte);
int16_t avr_uart_receive_byte(void);



#endif /* ROS_LIB_STM32_UART_H_ */
