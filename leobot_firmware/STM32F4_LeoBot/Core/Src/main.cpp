
extern "C"
{
	#include "main.h"
	#include "stm32f4xx_hal.h"
	#include "cmsis_os.h"
	#include "gpio.h"
	#include "i2c.h"

    #include "tim.h"
}

/* rosserial includes */
#include "ros.h"
//#include "std_msgs/UInt16.h"
//#include "std_msgs/String.h"

#include "spin_task.h"
#include "publisher_task.h"
#include "subscriber_task.h"


/* Private variables ---------------------------------------------------------*/
#ifdef __cplusplus
 extern "C" {
#endif

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
//void MX_FREERTOS_Init(void);

#ifdef __cplusplus
}
#endif
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
 ros::NodeHandle  nh;

/* USER CODE END 0 */

//https://github.com/alus96/STM32F407_Encoder/blob/master/Src/main.c

//volatile uint32_t cnt;
volatile uint32_t direction; //dir
volatile uint32_t rotationSpeed; //RPM
#define RESOLUTION (480)

#include "motor_unit.h"


/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  //MX_GPIO_Init();
  MX_I2C2_Init();




/* this code only for debug */

  /*MotorUnit_1 mu1;
  MotorUnit_2 mu2;
  MotorUnit_3 mu3;
  MotorUnit_4 mu4;

  mu1.motorInit();
  mu2.motorInit();
  mu3.motorInit();
  mu4.motorInit();

  while(1)
  {

	  mu1.move(FORWARD, 512);
	  mu2.move(FORWARD, 256);
	  mu3.move(FORWARD, 128);
	  mu4.move(FORWARD, 64);

	  HAL_Delay(50);

	  mu1.move(BACK, 0);
	  mu2.move(BACK, 0);
	  mu3.move(BACK, 0);
	  mu4.move(BACK, 0);

	  HAL_Delay(50);
  }*/
/* end of debug code */

  nh.initNode();

  if(RosPublisherTaskCreate(&nh)) while(1);
  if(RosSubscriberTaskCreate(&nh)) while(1);
  if(RosSpinTaskCreate(&nh)) while(1);


  /* Start scheduler */
  osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */
  while (1)
  {
	  /* should never be here, otherwise error */
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
