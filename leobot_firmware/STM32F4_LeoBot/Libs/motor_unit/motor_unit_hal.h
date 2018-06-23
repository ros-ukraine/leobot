/*
 * motor_unit_hal.h
 *
 *  Created on: 23 черв. 2018 р.
 *      Author: Nemo
 */

#ifndef MOTOR_UNIT_MOTOR_UNIT_HAL_H_
#define MOTOR_UNIT_MOTOR_UNIT_HAL_H_


#include "stm32f4xx.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_gpio.h"


#define MU1_DRV_INA     (LL_GPIO_PIN_4)
#define MU1_DRV_INB     (LL_GPIO_PIN_5)

#define MU2_DRV_INA 	(LL_GPIO_PIN_7)
#define MU2_DRV_INB 	(LL_GPIO_PIN_3)

#define MU3_DRV_INA     (LL_GPIO_PIN_5)
#define MU3_DRV_INB     (LL_GPIO_PIN_6)

#define MU4_DRV_INA     (LL_GPIO_PIN_3)
#define MU4_DRV_INB     (LL_GPIO_PIN_4)



#define MU1_DRV_INA_SetHigh() LL_GPIO_SetOutputPin(GPIOB, MU1_DRV_INA)
#define MU1_DRV_INA_SetLow()  LL_GPIO_ResetOutputPin(GPIOB, MU1_DRV_INA)

#define MU1_DRV_INB_SetHigh() LL_GPIO_SetOutputPin(GPIOB, MU1_DRV_INB)
#define MU1_DRV_INB_SetLow()  LL_GPIO_ResetOutputPin(GPIOB, MU1_DRV_INB)




void ControlPins_GPIO_1_Init(void);
void ControlPins_GPIO_2_Init(void);
void ControlPins_GPIO_3_Init(void);
void ControlPins_GPIO_4_Init(void);



//void GPIO_Init(void);
//void PMW_Init(void);


#endif /* MOTOR_UNIT_MOTOR_UNIT_HAL_H_ */
