/*
 * rtos.h
 *
 *  Created on: Dec 27, 2018
 *      Author: enko
 */

#ifndef RTOS_H_
#define RTOS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "gpio.h"
#include "tim.h"

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */


#ifdef __cplusplus
}
#endif

#endif /* INC_APP_H_ */
