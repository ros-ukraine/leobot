/*
 * motor.cpp
 *
 *  Created on: 6 трав. 2018 р.
 *      Author: Nemo
 */

#include "motor_unit.h"


void motorUnit_MotorInit(motorUnit_num motorUnitNumber)
{
	static uint32_t initiated = 0;

	//static const uint32_t presscaller = 8400; //10 hz
	//static const uint32_t presscaller = 840; //100 hz
	static const uint32_t presscaller = 168; //500 hz
	//static const uint32_t presscaller = 84; //1000 hz
	//static const uint32_t presscaller = 42; //2000 hz
	static const uint32_t period = 1000;
	static const uint32_t frequency = 500;//500;

	/*GPIO_InitTypeDef GPIO_InitStruct;
	//TIM_TimeBaseInitTypeDef TIM_TimeBase_InitStruct;
	//TIM_OCInitTypeDef TIM_OCStruct;


	TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;

	if (initiated == 0)
	{
		 Enable Clock for GPIO
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

		 Enable Clock for Timer
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

		TIM_TimeBaseStructInit(&TIM_TimeBase_InitStruct);

		TIM_TimeBase_InitStruct.TIM_Prescaler = presscaller - 1;
		TIM_TimeBase_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBase_InitStruct.TIM_Period = period;
		TIM_TimeBase_InitStruct.TIM_RepetitionCounter = 0;
		TIM_TimeBase_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM4, &TIM_TimeBase_InitStruct);


		TIM_OCStructInit(&TIM_OCStruct);
		TIM_Cmd(TIM4, ENABLE);

		initiated = 1;
	}*/

/*	switch(motorUnitNumber)
	{
	case M_UNIT_1:
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_Init(GPIOD, &GPIO_InitStruct);
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource12, GPIO_AF_TIM4);

		TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCStruct.TIM_Pulse = frequency;
		TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_High;

		break;

	case M_UNIT_2:
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_Init(GPIOD, &GPIO_InitStruct);
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource13, GPIO_AF_TIM4);
		break;

	case M_UNIT_3:
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_Init(GPIOD, &GPIO_InitStruct);
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource14, GPIO_AF_TIM4);
		break;

	case M_UNIT_4:
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_Init(GPIOD, &GPIO_InitStruct);
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource15, GPIO_AF_TIM4);
		break;

	default:
		break;
	}*/


}

void motorUnit_MotorMove(motorUnit_num motorUnitNumber, Direction dir, uint16_t speed)
{
/*	TIM_OCInitTypeDef TIM_OCStruct;

	TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;*/


	/* duty cycle controls motor speed*/
//	2099; /* 25% duty cycle */
//	4199; /* 50% duty cycle */
//	6299; /* 75% duty cycle */
//	8399; /* 100% duty cycle */

	/* add function to calculate duty cycle from percent value */

/*	switch(motorUnitNumber)
	{
	case M_UNIT_1:
		TIM_OCStruct.TIM_Pulse = speed;
		TIM_OC1Init(TIM4, &TIM_OCStruct);
		TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
		break;

	case M_UNIT_2:
		TIM_OCStruct.TIM_Pulse = speed;
		TIM_OC2Init(TIM4, &TIM_OCStruct);
		TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
		break;

	case M_UNIT_3:
		TIM_OCStruct.TIM_Pulse = speed;
		TIM_OC3Init(TIM4, &TIM_OCStruct);
		TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
		break;

	case M_UNIT_4:
		TIM_OCStruct.TIM_Pulse = speed;
		TIM_OC4Init(TIM4, &TIM_OCStruct);
		TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
		break;

	default:
		break;
	}*/

}

void motorUnit_EncoderInit(motorUnit_num motorUnitNumber)
{
	switch(motorUnitNumber)
	{
	case M_UNIT_1:
		break;

	case M_UNIT_2:
		break;

	case M_UNIT_3:
		break;

	case M_UNIT_4:
		break;

	default:
		break;
	}
}






