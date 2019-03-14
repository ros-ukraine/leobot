/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "cmsis_os.h"
//#include "tim.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "rtos.h"
#include <stdio.h>
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
//void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */
void LL_Init(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface */
  LL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();
  // ToDo: increase speed of MCU to 216 Mhz
  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  //MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  printf("start\r\n");

  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}



/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_7);

  if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_7)
  {
  Error_Handler();  
  }
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
  LL_PWR_EnableOverDriveMode();
  LL_RCC_HSE_EnableBypass();
  LL_RCC_HSE_Enable();

   /* Wait till HSE is ready */
  while(LL_RCC_HSE_IsReady() != 1)
  {
    
  }
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_4, 216, LL_RCC_PLLP_DIV_2);
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
  LL_Init1msTick(216000000);
  LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
  LL_SetSystemCoreClock(216000000);
  LL_RCC_SetUSARTClockSource(LL_RCC_USART3_CLKSOURCE_PCLK1);
}

/* USER CODE BEGIN 4 */
//int __io_putchar(int ch)
//{
//	return 1;
//}


void LL_Init(void)
{
	/* This code is moved from HAL_Init */
	// ToDo: check if this code can be removed or simplified

	/* Configure Instruction cache through ART accelerator */
	/* Enable the FLASH Adaptive Real-Time memory accelerator. */
	/* The ART accelerator is available only for flash access on ITCM interface. */
	SET_BIT(FLASH->ACR, FLASH_ACR_ARTEN);

	/* Enable the FLASH prefetch buffer. */
	FLASH->ACR |= FLASH_ACR_PRFTEN;

	/* HAL_MspInit part of code */

	//__HAL_RCC_PWR_CLK_ENABLE();
	  //APB1 Peripheral Clock Enable
	  //Enable the Low Speed APB (APB1) peripheral clock.
	  //@note   After reset, the peripheral clock (used for registers read/write access)
	  //  *         is disabled and the application software has to enable this clock before
	  //  *         using it.
	 __IO uint32_t tmpreg;
	 SET_BIT(RCC->APB1ENR, RCC_APB1ENR_WWDGEN);
	 /* Delay after an RCC peripheral clock enabling */
	 tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_WWDGEN);
	 tmpreg = tmpreg;


	 //__HAL_RCC_SYSCFG_CLK_ENABLE();
	 /** @defgroup RCC_APB2_Clock_Enable_Disable APB2 Peripheral Clock Enable Disable
	   * @brief  Enable or disable the High Speed APB (APB2) peripheral clock.
	   * @note   After reset, the peripheral clock (used for registers read/write access)
	   *         is disabled and the application software has to enable this clock before
	   *         using it.
	   * @{
	   */
	 SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);
	 /* Delay after an RCC peripheral clock enabling */
	 tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);
	 tmpreg = tmpreg;


	 /* looks line this part of code is configured in FreeRTOS: Make PendSV and SysTick the lowest priority interrupts. */

	 /* System interrupt init*/
	 /* PendSV_IRQn interrupt configuration */
	 //HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);
	 uint32_t prioritygroup = 0x00;

	 prioritygroup = NVIC_GetPriorityGrouping();

	 //NVIC_SetPriority(IRQn, NVIC_EncodePriority(prioritygroup, PreemptPriority, SubPriority));
	 NVIC_SetPriority(PendSV_IRQn, NVIC_EncodePriority(prioritygroup, 15, 0));
}




/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
