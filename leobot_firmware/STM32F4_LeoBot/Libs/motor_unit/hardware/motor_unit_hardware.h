/*
 * motor_unit_hal.h
 *
 *  Created on: 23 черв. 2018 р.
 *      Author: Nemo
 */

#ifndef MOTOR_UNIT_MOTOR_UNIT_HARDWARE_H_
#define MOTOR_UNIT_MOTOR_UNIT_HARDWARE_H_

#include "stm32f4xx_ll_gpio.h"
#include "tim.h"


#define MU1_DRV_INA     		(LL_GPIO_PIN_4) /* PB4 */
#define MU1_DRV_INB     		(LL_GPIO_PIN_5) /* PB5 */

#define MU2_DRV_INA 			(LL_GPIO_PIN_7) /* PD7*/
#define MU2_DRV_INB 			(LL_GPIO_PIN_3) /* PB3 */

#define MU3_DRV_INA     		(LL_GPIO_PIN_5) /* PD5*/
#define MU3_DRV_INB     		(LL_GPIO_PIN_6) /* PD6*/

#define MU4_DRV_INA     		(LL_GPIO_PIN_3) /* PD3*/
#define MU4_DRV_INB     		(LL_GPIO_PIN_4) /* PD4*/


#define MU1_DRV_INA_SetHigh()   LL_GPIO_SetOutputPin(GPIOB, MU1_DRV_INA)
#define MU1_DRV_INA_SetLow()    LL_GPIO_ResetOutputPin(GPIOB, MU1_DRV_INA)
#define MU1_DRV_INB_SetHigh()   LL_GPIO_SetOutputPin(GPIOB, MU1_DRV_INB)
#define MU1_DRV_INB_SetLow()    LL_GPIO_ResetOutputPin(GPIOB, MU1_DRV_INB)

#define MU2_DRV_INA_SetHigh()   LL_GPIO_SetOutputPin(GPIOD, MU2_DRV_INA)
#define MU2_DRV_INA_SetLow()    LL_GPIO_ResetOutputPin(GPIOD, MU2_DRV_INA)
#define MU2_DRV_INB_SetHigh()   LL_GPIO_SetOutputPin(GPIOB, MU2_DRV_INB)
#define MU2_DRV_INB_SetLow()    LL_GPIO_ResetOutputPin(GPIOB, MU2_DRV_INB)

#define MU3_DRV_INA_SetHigh()   LL_GPIO_SetOutputPin(GPIOD, MU3_DRV_INA)
#define MU3_DRV_INA_SetLow()    LL_GPIO_ResetOutputPin(GPIOD, MU3_DRV_INA)
#define MU3_DRV_INB_SetHigh()   LL_GPIO_SetOutputPin(GPIOD, MU3_DRV_INB)
#define MU3_DRV_INB_SetLow()    LL_GPIO_ResetOutputPin(GPIOD, MU3_DRV_INB)

#define MU4_DRV_INA_SetHigh()   LL_GPIO_SetOutputPin(GPIOD, MU4_DRV_INA)
#define MU4_DRV_INA_SetLow()    LL_GPIO_ResetOutputPin(GPIOD, MU4_DRV_INA)
#define MU4_DRV_INB_SetHigh()   LL_GPIO_SetOutputPin(GPIOD, MU4_DRV_INB)
#define MU4_DRV_INB_SetLow()    LL_GPIO_ResetOutputPin(GPIOD, MU4_DRV_INB)


void ControlPins_GPIO_1_Init(void);
void ControlPins_GPIO_2_Init(void);
void ControlPins_GPIO_3_Init(void);
void ControlPins_GPIO_4_Init(void);


//void PMW_Init(void);


#endif /* MOTOR_UNIT_MOTOR_UNIT_HARDWARE_H_ */
