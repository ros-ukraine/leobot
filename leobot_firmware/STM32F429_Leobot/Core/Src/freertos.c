/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
//static ros::NodeHandle nh;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId LedBlinkTaskHandle;
osThreadId EncoderTaskHandle;
osThreadId RosTaskHandle;
osMutexId rosPublishMutexHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
//void motor_cb(const std_msgs::UInt16& cmd_msg);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void LedBlinkTaskHandler(void const * argument);
void EncoderTaskHandler(void const * argument);
void RosTaskHandler(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* Create the mutex(es) */
  /* definition and creation of rosPublishMutex */
  osMutexDef(rosPublishMutex);
  rosPublishMutexHandle = osMutexCreate(osMutex(rosPublishMutex));

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of LedBlinkTask */
  osThreadDef(LedBlinkTask, LedBlinkTaskHandler, osPriorityIdle, 0, 128);
  LedBlinkTaskHandle = osThreadCreate(osThread(LedBlinkTask), NULL);

  /* definition and creation of EncoderTask */
  osThreadDef(EncoderTask, EncoderTaskHandler, osPriorityNormal, 0, 128);
  EncoderTaskHandle = osThreadCreate(osThread(EncoderTask), NULL);

  /* definition and creation of RosTask */
  osThreadDef(RosTask, RosTaskHandler, osPriorityNormal, 0, 128);
  RosTaskHandle = osThreadCreate(osThread(RosTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_LedBlinkTaskHandler */
/**
* @brief Function implementing the LedBlinkTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LedBlinkTaskHandler */
void LedBlinkTaskHandler(void const * argument)
{
  /* USER CODE BEGIN LedBlinkTaskHandler */
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
	  ITM_SendChar(28);
	  osDelay(500);
  }
  /* USER CODE END LedBlinkTaskHandler */
}

/* USER CODE BEGIN Header_EncoderTaskHandler */
/**
* @brief Function implementing the EncoderTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_EncoderTaskHandler */
void EncoderTaskHandler(void const * argument)
{
  /* USER CODE BEGIN EncoderTaskHandler */
	static uint32_t testcnt;

	//MX_TIM2_Init();
	//MX_TIM3_Init();
	//MX_TIM4_Init();
	//MX_TIM8_Init();
  /* Infinite loop */
  for(;;)
  {
	  /* make for cycle with array of pointers to timer functions */
/*
	  encoder[0].direction = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim2);
	  encoder[1].direction = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim3);
	  encoder[2].direction = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim4);
	  encoder[3].direction = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim8);
*/
	  /* only for debug, for real work should be added formula for speed calculation */
/*
	  encoder[0].speed = __HAL_TIM_GET_COUNTER(&htim2);
	  encoder[1].speed = __HAL_TIM_GET_COUNTER(&htim3);
	  encoder[2].speed = __HAL_TIM_GET_COUNTER(&htim4);
	  encoder[3].speed = __HAL_TIM_GET_COUNTER(&htim8);
*/
	  testcnt++;
	  osDelay(100);
  }
  /* USER CODE END EncoderTaskHandler */
}

/* USER CODE BEGIN Header_RosTaskHandler */
/**
* @brief Function implementing the RosTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_RosTaskHandler */
void RosTaskHandler(void const * argument)
{
  /* USER CODE BEGIN RosTaskHandler */
  //ros::Subscriber<std_msgs::UInt16> sub("motor", motor_cb);

  /* Infinite loop */
  for(;;)
  {
	  //nh_->spinOnce();
	  osDelay(1);
  }
  /* USER CODE END RosTaskHandler */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/*
static void motor_cb(const std_msgs::UInt16& cmd_msg)
 {
  	//cmd_msg.data should be in range 0 - 100

 	 //str_msg.data = hello;
 	 //chatter.publish( &str_msg );
 }
*/
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
