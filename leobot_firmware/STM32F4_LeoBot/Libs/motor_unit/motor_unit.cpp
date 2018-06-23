/*
 * motor.cpp
 *
 *  Created on: 6 трав. 2018 р.
 *      Author: Nemo
 */

#include "motor_unit.h"

extern "C"
{
	#include "stm32f4xx_hal.h"
	#include "tim.h"
	#include "gpio.h"

	#include "motor_unit_hal.h"
}




//

  //LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH1);
  //LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH2); m2
  //LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH3); m3
  //LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH4); m4

/*
  LL_TIM_OC_SetCompareCH1(TIM4,512);
  LL_TIM_OC_SetCompareCH2(TIM4,128);
  LL_TIM_OC_SetCompareCH3(TIM4,64);
  LL_TIM_OC_SetCompareCH4(TIM4,32);
*/

/* TO-Do: separate GPIO pins for each peripheral */

MotorUnit_1::MotorUnit_1()
{
	/* Init Timer for PWM mode */
	MX_TIM4_Init();

	/* Init Timer for Encoder mode */
	 //MX_TIM1_Init();
	//Encoder_Timer_1_Init();

	//LL_TIM_EnableCounter(TIM1);

	/* Init  GPIO */
	ControlPins_GPIO_1_Init();
}

void MotorUnit_1::motorEnable()
{
	LL_TIM_EnableCounter(TIM4);

	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH1);
}


void MotorUnit_1::motorDisable()
{
	LL_TIM_DisableCounter(TIM4);

	LL_TIM_CC_DisableChannel(TIM4, LL_TIM_CHANNEL_CH1);
}


void MotorUnit_1::move(uint32_t direction, uint32_t speed)
{
	if (direction)
	{
		MU1_DRV_INA_SetHigh();
		MU1_DRV_INB_SetLow();
	}
	else
	{
		MU1_DRV_INA_SetLow();
		MU1_DRV_INB_SetHigh();
	}
}


MotorUnit_2::MotorUnit_2()
{
	/* Init Timer for PWM mode */
	MX_TIM4_Init();

	/* Init Timer for Encoder mode */
	MX_TIM2_Init();
	LL_TIM_EnableCounter(TIM2);

	/* Init  GPIO */
	ControlPins_GPIO_2_Init();
}

MotorUnit_3::MotorUnit_3()
{
	/* Init Timer for PWM mode */
	MX_TIM4_Init();

	/* Init Timer for Encoder mode */
	MX_TIM3_Init();
	LL_TIM_EnableCounter(TIM3);

	/* Init  GPIO */
	ControlPins_GPIO_3_Init();
}

MotorUnit_4::MotorUnit_4()
{
	/* Init Timer for PWM mode */
	MX_TIM4_Init();

	/* Init Timer for Encoder mode */
	MX_TIM8_Init();
	LL_TIM_EnableCounter(TIM8);

	/* Init  GPIO */
	ControlPins_GPIO_4_Init();
}



void MotorUnit_1::encoderInit()
{

}

uint32_t MotorUnit_1::encoderRead()
{
	 //volatile uint32_t currentEncoderVal;
	  //volatile uint32_t previousEncoderVal;
	  //volatile uint32_t direction; //dir
	  //x4


	/*currentEncoderVal = LL_TIM_GetCounter(TIM8);
		  // LL_TIM_COUNTERMODE_UP
		  // LL_TIM_COUNTERMODE_DOWN
		  direction = LL_TIM_GetCounterMode(TIM8); // 16 or 0

		  //HAL_Delay(500);

		  rotationSpeed = ((currentEncoderVal - previousEncoderVal)/RESOLUTION) * 50;

		  previousEncoderVal = currentEncoderVal;

		  HAL_Delay(50); //50 ms*/

	return 1000; //debug
}









