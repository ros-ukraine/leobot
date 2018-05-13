/*
 * motor.h
 *
 *  Created on: 6 трав. 2018 р.
 *      Author: Nemo
 */

#ifndef MOTOR_UNIT_MOTOR_UNIT_H_
#define MOTOR_UNIT_MOTOR_UNIT_H_

#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"

typedef enum motorUnit_num
{
	M_UNIT_1,
	M_UNIT_2,
	M_UNIT_3,
	M_UNIT_4
} motorUnit_num;

typedef enum Direction
{
	FORWARD,
	BACK
}
Direction;

void motorUnit_Init(motorUnit_num motorUnitNumber);
void motorUnit_MotorEnable(motorUnit_num motorUnitNumber);
void motorUnit_MotorDisable(motorUnit_num motorUnitNumber);
void motorUnit_MotorStop(motorUnit_num motorUnitNumber);
void motorUnit_MotorMove(motorUnit_num motorUnitNumber, Direction dir, uint16_t speed);
uint16_t motorUnit_EncoderGetValue(motorUnit_num motorUnitNumber);

#endif /* MOTOR_UNIT_MOTOR_UNIT_H_ */

