/*
 * motor_unit_hal.h
 *
 *  Created on: 23 ����. 2018 �.
 *      Author: Nemo
 */

#ifndef MOTOR_UNIT_MOTOR_UNIT_HARDWARE_H_
#define MOTOR_UNIT_MOTOR_UNIT_HARDWARE_H_

#include "stm32f4xx_ll_gpio.h"
#include "tim.h"

#define MU1_DRV_INA_SetHigh()   LL_GPIO_SetOutputPin(MU1_DRV_INA_GPIO_Port, MU1_DRV_INA_Pin)
#define MU1_DRV_INA_SetLow()    LL_GPIO_ResetOutputPin(MU1_DRV_INA_GPIO_Port, MU1_DRV_INA_Pin)
#define MU1_DRV_INB_SetHigh()   LL_GPIO_SetOutputPin(MU1_DRV_INB_GPIO_Port, MU1_DRV_INB_Pin)
#define MU1_DRV_INB_SetLow()    LL_GPIO_ResetOutputPin(MU1_DRV_INB_GPIO_Port, MU1_DRV_INB_Pin)

#define MU2_DRV_INA_SetHigh()   LL_GPIO_SetOutputPin(MU2_DRV_INA_GPIO_Port, MU2_DRV_INA_Pin)
#define MU2_DRV_INA_SetLow()    LL_GPIO_ResetOutputPin(MU2_DRV_INA_GPIO_Port, MU2_DRV_INA_Pin)
#define MU2_DRV_INB_SetHigh()   LL_GPIO_SetOutputPin(MU2_DRV_INB_GPIO_Port, MU2_DRV_INB_Pin)
#define MU2_DRV_INB_SetLow()    LL_GPIO_ResetOutputPin(MU2_DRV_INB_GPIO_Port, MU2_DRV_INB_Pin)

#define MU3_DRV_INA_SetHigh()   LL_GPIO_SetOutputPin(MU3_DRV_INA_GPIO_Port, MU3_DRV_INA_Pin)
#define MU3_DRV_INA_SetLow()    LL_GPIO_ResetOutputPin(MU3_DRV_INA_GPIO_Port, MU3_DRV_INA_Pin)
#define MU3_DRV_INB_SetHigh()   LL_GPIO_SetOutputPin(MU3_DRV_INB_GPIO_Port, MU3_DRV_INB_Pin)
#define MU3_DRV_INB_SetLow()    LL_GPIO_ResetOutputPin(MU3_DRV_INB_GPIO_Port, MU3_DRV_INB_Pin)

#define MU4_DRV_INA_SetHigh()   LL_GPIO_SetOutputPin(MU4_DRV_INA_GPIO_Port, MU4_DRV_INA_Pin)
#define MU4_DRV_INA_SetLow()    LL_GPIO_ResetOutputPin(MU4_DRV_INA_GPIO_Port, MU4_DRV_INA_Pin)
#define MU4_DRV_INB_SetHigh()   LL_GPIO_SetOutputPin(MU4_DRV_INB_GPIO_Port, MU4_DRV_INB_Pin)
#define MU4_DRV_INB_SetLow()    LL_GPIO_ResetOutputPin(MU4_DRV_INB_GPIO_Port, MU4_DRV_INB_Pin)


void ControlPins_GPIO_1_Init(void);
void ControlPins_GPIO_2_Init(void);
void ControlPins_GPIO_3_Init(void);
void ControlPins_GPIO_4_Init(void);

void PMW_Timer_Init(void);

void Encoder_Timer_1_Init(void);
void Encoder_Timer_2_Init(void);
void Encoder_Timer_3_Init(void);
void Encoder_Timer_8_Init(void);


//void PMW_Init(void);


#endif /* MOTOR_UNIT_MOTOR_UNIT_HARDWARE_H_ */
