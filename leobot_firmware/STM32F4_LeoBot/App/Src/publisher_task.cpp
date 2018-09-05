
/*
 * publisherer_task.cpp
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


#include "publisher_task.h"

#include "std_msgs/String.h"

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);
char hello[13] = "hello world!";


static ros::NodeHandle *nh_;


void RosPublisherTask(const void *argument)
{
	str_msg.data = hello;

	for(;;)
	{
		chatter.publish(&str_msg);
		osDelay(1000);
	}
}

/*
 * Create publish task
 */
uint32_t RosPublisherTaskCreate(ros::NodeHandle *nh)
{
	osThreadId RosPublisherHandle;

	nh_ = nh;
	nh_->advertise(chatter);

	/* definition and creation of RosPublisher */
	osThreadDef(RosPublisher, RosPublisherTask, osPriorityNormal, 0, 128);
	RosPublisherHandle = osThreadCreate(osThread(RosPublisher), NULL);

	if (NULL == RosPublisherHandle)
    {
		return 1;
	}

	return 0;
}
