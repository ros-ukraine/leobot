/*
 * stm32_time.h
 *
 *  Created on: 30 квіт. 2018 р.
 *      Author: Nemo
 */

#ifndef ROS_LIB_STM32_TIME_H_
#define ROS_LIB_STM32_TIME_H_

#include "stm32f4xx.h"


void stm32_time_init(void);
uint32_t stm32_time_now(void);

#endif /* ROS_LIB_STM32_TIME_H_ */
