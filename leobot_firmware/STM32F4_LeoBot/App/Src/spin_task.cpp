
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



#include "../Inc/spin_task.h"


//static ros::NodeHandle *nh_;
static ros::NodeHandle *nh_;


osThreadId spinTaskHandle;
uint32_t spinTaskBuffer[ 128 ];
osStaticThreadDef_t spinTaskControlBlock;


// try to move spin task on virtual timer
void spinTask(const void *argument)
{
	for(;;)
	{
		nh_->spinOnce();
		//vTaskDelay(5);
	}
}


/*
 * Create spin task
 */
uint32_t spinTaskCreate(ros::NodeHandle *nh)
{
	nh_ = nh;

	/* definition and creation of rosSpinTask */
	osThreadStaticDef(spinTask, spinTask, osPriorityNormal, 0, 128, spinTaskBuffer, &spinTaskControlBlock);
	spinTaskHandle = osThreadCreate(osThread(spinTask), NULL);
	if (NULL == spinTaskHandle)
	{
		return 1;
	}
	return 0;

}


