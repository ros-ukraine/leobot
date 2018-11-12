/*
 * motor.cpp
 *
 *  Created on: 6 ����. 2018 �.
 *      Author: Nemo
 */

#include "motor_unit.h"

extern "C"
{
	#include "motor_unit_hardware.h"
}


void MotorUnit_1::motorInit()
{
	PMW_Timer_Init();
//	/* Init Timer for PWM mode */
//	MX_TIM4_Init();
//
//	LL_TIM_EnableCounter(TIM4);
//
//	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH1);
//	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH2);
//	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH3);
//	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH4);

	/* Init  GPIO */
	ControlPins_GPIO_1_Init();

	/* Motor is disabled at start */
	MU1_DRV_INA_SetLow();
	MU1_DRV_INB_SetLow();
}

void MotorUnit_2::motorInit()
{
	PMW_Timer_Init();
//	/* Init Timer for PWM mode */
//	MX_TIM4_Init();
//
//	LL_TIM_EnableCounter(TIM4);
//
//	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH1);
//    LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH2);
//	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH3);
//	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH4);

	/* Init  GPIO */
	ControlPins_GPIO_2_Init();

	/* Motor is disabled at start */
	MU2_DRV_INA_SetLow();
	MU2_DRV_INB_SetLow();
}

void MotorUnit_3::motorInit()
{
	PMW_Timer_Init();
//	/* Init Timer for PWM mode */
//	MX_TIM4_Init();
//	LL_TIM_EnableCounter(TIM4);
//	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH1);
//	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH2);
//	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH3);
//	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH4);

	/* Init  GPIO */
	ControlPins_GPIO_3_Init();

	/* Motor is disabled at start */
	MU3_DRV_INA_SetLow();
	MU3_DRV_INB_SetLow();
}

void MotorUnit_4::motorInit()
{
	PMW_Timer_Init();

//	/* Init Timer for PWM mode */
//	MX_TIM4_Init();
//	LL_TIM_EnableCounter(TIM4);
//	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH1);
//	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH2);
//	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH3);
//	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH4);
//
//	/* Init  GPIO */
	ControlPins_GPIO_4_Init();

	/* Motor is disabled at start */
	MU4_DRV_INA_SetLow();
	MU4_DRV_INB_SetLow();
}


void MotorUnit_1::encoderInit()
{
	Encoder_Timer_1_Init();
}

void MotorUnit_2::encoderInit()
{
	Encoder_Timer_2_Init();
}

void MotorUnit_3::encoderInit()
{
	Encoder_Timer_3_Init();
}

void MotorUnit_4::encoderInit()
{
	Encoder_Timer_8_Init();
}



void MotorUnit_1::move(Direction direction, uint32_t speed)
{
	if (FORWARD == direction)
	{
		MU1_DRV_INA_SetHigh();
		MU1_DRV_INB_SetLow();
	}
	else
	{
		MU1_DRV_INA_SetLow();
		MU1_DRV_INB_SetHigh();
	}

	if (speed >= 0) LL_TIM_OC_SetCompareCH1(TIM4, speed);
}

void MotorUnit_2::move(Direction direction, uint32_t speed)
{
	if (FORWARD == direction )
	{
		MU2_DRV_INA_SetHigh();
		MU2_DRV_INB_SetLow();
	}
	else
	{
		MU2_DRV_INA_SetLow();
		MU2_DRV_INB_SetHigh();
	}

	if (speed >= 0) LL_TIM_OC_SetCompareCH2(TIM4, speed);
}

void MotorUnit_3::move(Direction direction, uint32_t speed)
{
	if (FORWARD == direction )
	{
		MU3_DRV_INA_SetHigh();
		MU3_DRV_INB_SetLow();
	}
	else
	{
		MU3_DRV_INA_SetLow();
		MU3_DRV_INB_SetHigh();
	}

	if (speed >= 0) LL_TIM_OC_SetCompareCH3(TIM4, speed);
}

void MotorUnit_4::move(Direction direction, uint32_t speed)
{
	if (FORWARD == direction)
	{
		MU4_DRV_INA_SetHigh();
		MU4_DRV_INB_SetLow();
	}
	else
	{
		MU4_DRV_INA_SetLow();
		MU4_DRV_INB_SetHigh();
	}

	if (speed >= 0) LL_TIM_OC_SetCompareCH4(TIM4, speed);
}




//
//uint32_t MotorUnit_1::encoderRead()
//{
//	 //volatile uint32_t currentEncoderVal;
//	  //volatile uint32_t previousEncoderVal;
//	  //volatile uint32_t direction; //dir
//	  //x4
//
//
//	/*currentEncoderVal = LL_TIM_GetCounter(TIM8);
//		  // LL_TIM_COUNTERMODE_UP
//		  // LL_TIM_COUNTERMODE_DOWN
//		  direction = LL_TIM_GetCounterMode(TIM8); // 16 or 0
//
//		  //HAL_Delay(500);
//
//		  rotationSpeed = ((currentEncoderVal - previousEncoderVal)/RESOLUTION) * 50;
//
//		  previousEncoderVal = currentEncoderVal;
//
//		  HAL_Delay(50); //50 ms*/
//
//	return 1000; //debug
//}
//








