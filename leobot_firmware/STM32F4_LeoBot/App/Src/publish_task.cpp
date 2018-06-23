
/*
 * publish_task.cpp
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

#include "../Inc/publish_task.h"

#include "std_msgs/String.h"

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);
char hello[13] = "hello world!";



osThreadId publishTaskHandle;
uint32_t publishTaskBuffer[ 128 ];
osStaticThreadDef_t publishTaskControlBlock;

static ros::NodeHandle *nh_;


void publishTask(const void *argument)
{
	str_msg.data = hello;

	for(;;)
	{
		chatter.publish( &str_msg );
		vTaskDelay(1000);
	}
}

/*
 * Create publish task
 */
uint32_t publishTaskCreate(ros::NodeHandle *nh)
{
	nh_ = nh;

	nh_->advertise(chatter);

		/* definition and creation of rosSpinTask */
		osThreadStaticDef(publishTask, publishTask, osPriorityAboveNormal, 0, 128, publishTaskBuffer, &publishTaskControlBlock);
		publishTaskHandle = osThreadCreate(osThread(publishTask), NULL);
		if (NULL == publishTaskHandle)
		{
			return 1;
		}
		return 0;
}
