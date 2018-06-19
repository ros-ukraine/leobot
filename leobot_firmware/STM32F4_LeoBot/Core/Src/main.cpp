
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/

extern "C"
{
	#include "main.h"
	#include "stm32f4xx_hal.h"
	#include "cmsis_os.h"
	#include "i2c.h"
	#include "tim.h"
	#include "gpio.h"

}

/* rosserial includes */
#include "ros.h"
#include "std_msgs/UInt16.h"
#include "std_msgs/String.h"

//http://blablacode.ru/mikrokontrollery/450

//https://stm32f4-discovery.net/2014/10/use-printf-output-stream-stm32f4/

//#include "stm32f4hardware.h"

//STM32F4Hardware debug;

// https://stackoverflow.com/questions/35288808/first-project-for-stm32-with-hal-in-c/35334043

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
#ifdef __cplusplus
 extern "C" {
#endif
/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


#ifdef __cplusplus
}
#endif
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
 ros::NodeHandle  nh;

 void motor_cb(const std_msgs::UInt16& cmd_msg);

 ros::Subscriber<std_msgs::UInt16> sub("motor", motor_cb);

 std_msgs::String str_msg;
 ros::Publisher chatter("chatter", &str_msg);
 char hello[13] = "hello world!";

 void motor_cb(const std_msgs::UInt16& cmd_msg)
  {
  	//cmd_msg.data should be in range 0 - 100

 	 str_msg.data = hello;
 	 chatter.publish( &str_msg );

  }

void *TaskSpin(void *param)
{
	for(;;)
	{
		//nh.spinOnce();

		vTaskDelay(500);
	}
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */

//https://github.com/alus96/STM32F407_Encoder/blob/master/Src/main.c

//volatile uint32_t cnt;

volatile uint32_t direction; //dir
volatile uint32_t rotationSpeed; //RPM
#define RESOLUTION (480)


#ifdef __cplusplus
 extern "C" {
#endif

//int __io_putchar(int ch)
 PUTCHAR_PROTOTYPE
 {
  ITM_SendChar(ch);
  return ch;
}

#ifdef __cplusplus
}
#endif


int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM8_Init();
  MX_TIM4_Init();
  MX_USART2_UART_Init(); /* initialized in rosserial */
  MX_I2C2_Init();


  LL_TIM_EnableCounter(TIM1);
  LL_TIM_EnableCounter(TIM2);
  LL_TIM_EnableCounter(TIM3);

  LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH1);
  LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH2);
  LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH3);
  LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH4);

  LL_TIM_EnableCounter(TIM4); // pwm
  LL_TIM_EnableCounter(TIM8); //enable timer 8

  LL_TIM_OC_SetCompareCH1(TIM4,512);
  LL_TIM_OC_SetCompareCH2(TIM4,128);
  LL_TIM_OC_SetCompareCH3(TIM4,64);
  LL_TIM_OC_SetCompareCH4(TIM4,32);

  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(chatter);


  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */
  //MX_FREERTOS_Init();


  /* Start scheduler */
  //osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  //debug.init();

  //volatile uint32_t currentEncoderVal;
  //volatile uint32_t previousEncoderVal;


  //volatile uint32_t direction; //dir
  //x4



  while (1)
  {
	  printf("hello!\r\n");

	  //ITM_SendChar('A');
	  //ITM_SendChar('\r');
	  //ITM_SendChar('\n');

	  HAL_Delay(500);

	  /*currentEncoderVal = LL_TIM_GetCounter(TIM8);
	  // LL_TIM_COUNTERMODE_UP
	  // LL_TIM_COUNTERMODE_DOWN
	  direction = LL_TIM_GetCounterMode(TIM8); // 16 or 0

	  //HAL_Delay(500);

	  rotationSpeed = ((currentEncoderVal - previousEncoderVal)/RESOLUTION) * 50;

	  previousEncoderVal = currentEncoderVal;

	  HAL_Delay(50); //50 ms*/

	  //str_msg.data = hello;
	  //chatter.publish( &str_msg );

	  //nh.spinOnce();


	  //vTaskDelay(100);


  }

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  LL_FLASH_SetLatency(LL_FLASH_LATENCY_5);

  if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_5)
  {
	  Error_Handler();
  }
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);

  LL_RCC_HSE_Enable();

   /* Wait till HSE is ready */
  while(LL_RCC_HSE_IsReady() != 1)
  {

  }
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_8, 336, LL_RCC_PLLP_DIV_2);

  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);

  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);

  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {

  }
  LL_Init1msTick(168000000);

  LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);

  LL_SetSystemCoreClock(168000000);

  /* SysTick_IRQn interrupt configuration */
  NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),15, 0));
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM5 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM5) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(const char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
