
/*
 * spin_task.cpp
 *
 *  Created on: 23 черв. 2018 р.
 *      Author: Nemo
 */

extern "C"
{
	#include "FreeRTOS.h"
	#include "task.h"
	#include "cmsis_os.h"
}

#include "spin_task.h"

static ros::NodeHandle *nh_;

// try to move spin task on virtual timer
/* RosSpinTask function */
void RosSpinTask(void const * argument)
{
  /* USER CODE BEGIN RosSpinTask */
  /* Infinite loop */
  for(;;)
  {
	  nh_->spinOnce();
	 // osDelay(1);
  }
  /* USER CODE END RosSpinTask */
}

/*
 * Create spin task
 */
uint32_t RosSpinTaskCreate(ros::NodeHandle *nh)
{
	osThreadId RosSpinHandle;

	nh_ = nh;

	/* definition and creation of RosSpin */
	osThreadDef(RosSpin, RosSpinTask,  osPriorityIdle /*osPriorityNormal*/, 0, 128);
	RosSpinHandle = osThreadCreate(osThread(RosSpin), NULL);

	if (NULL == RosSpinHandle)
	{
		return 1;
	}
	return 0;

}


