
#include "motor_unit_hardware.h"

void ControlPins_GPIO_1_Init(void)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

    LL_GPIO_ResetOutputPin(GPIOB, MU1_DRV_INA|MU1_DRV_INB);

    GPIO_InitStruct.Pin = MU1_DRV_INA|MU1_DRV_INB;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}



void ControlPins_GPIO_2_Init(void)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);

    LL_GPIO_ResetOutputPin(GPIOB, MU2_DRV_INB);
    LL_GPIO_ResetOutputPin(GPIOD, MU2_DRV_INA);

    /* PD7 */
    GPIO_InitStruct.Pin = MU2_DRV_INA;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(GPIOD, &GPIO_InitStruct);


    /* PB3*/
    GPIO_InitStruct.Pin = MU2_DRV_INB;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


void ControlPins_GPIO_3_Init(void)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);

    LL_GPIO_ResetOutputPin(GPIOD, MU3_DRV_INA|MU3_DRV_INB);

    GPIO_InitStruct.Pin = MU3_DRV_INA|MU3_DRV_INB;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void ControlPins_GPIO_4_Init(void)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);

	LL_GPIO_ResetOutputPin(GPIOD, MU4_DRV_INA|MU4_DRV_INB);

	GPIO_InitStruct.Pin = MU4_DRV_INA|MU4_DRV_INB;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}


void PMW_Timer_Init(void)
{
	/* Init Timer for PWM mode */
	MX_TIM4_Init();

	LL_TIM_EnableCounter(TIM4);

	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH1);
	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH2);
	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH3);
	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH4);
}

void Encoder_Timer_1_Init(void)
{
	/* Init Timer for Encoder mode */
	MX_TIM1_Init();
	LL_TIM_EnableCounter(TIM1);
}

void Encoder_Timer_2_Init(void)
{
	/* Init Timer for Encoder mode */
	MX_TIM2_Init();
	LL_TIM_EnableCounter(TIM2);
}

void Encoder_Timer_3_Init(void)
{
	/* Init Timer for Encoder mode */
	MX_TIM3_Init();
	LL_TIM_EnableCounter(TIM3);
}

void Encoder_Timer_8_Init(void)
{
	/* Init Timer for Encoder mode */
	MX_TIM8_Init();
	LL_TIM_EnableCounter(TIM8);
}

