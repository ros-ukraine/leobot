/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#include "gpio.h"
#include "rtos.h"

#include "ros.h"
#include "std_msgs/UInt16.h"
//#include "std_msgs/String.h"
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
static ros::NodeHandle nh;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void motor_cb(const std_msgs::UInt16& cmd_msg);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);

//void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
	nh.initNode();
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

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
  MX_GPIO_Init();

  ros::Subscriber<std_msgs::UInt16> sub("motor", motor_cb);
  nh.subscribe(sub);

  //char hello[15] = "hello world!\r\n";
  //str_msg.data = hello;
  //nh.advertise(chatter);

  /* Infinite loop */
  for(;;)
  {
	  nh.spinOnce();
	  /*
	  LL_GPIO_SetOutputPin(LD3_GPIO_Port, LD3_Pin);
	  LL_GPIO_ResetOutputPin(LD2_GPIO_Port, LD2_Pin);
	  osDelay(200);

	  LL_GPIO_ResetOutputPin(LD3_GPIO_Port, LD3_Pin);
	  LL_GPIO_SetOutputPin(LD2_GPIO_Port, LD2_Pin);
	  osDelay(200);
	  */

  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void motor_cb(const std_msgs::UInt16& cmd_msg)
{
	//cmd_msg.data should be in range 0 - 100
	//nh.logdebug("motor_cb\r\n");

	switch(cmd_msg.data)
	{
		case 0: LL_GPIO_ResetOutputPin(LD2_GPIO_Port, LD2_Pin); break;
		case 1: LL_GPIO_SetOutputPin(LD2_GPIO_Port, LD2_Pin); break;
	}


	//ITM_SendChar('B');
}

     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
