/*
 * subscriber_task.cpp
 *
 *  Created on: 5 вер. 2018 р.
 *      Author: Nemo
 */

extern "C"
{
	#include "FreeRTOS.h"
	#include "task.h"
	#include "cmsis_os.h"
}

#include "std_msgs/UInt16.h"

#include "subscriber_task.h"


static ros::NodeHandle *nh_;

 void motor_cb(const std_msgs::UInt16& cmd_msg)
 {
  	//cmd_msg.data should be in range 0 - 100

 	 //str_msg.data = hello;
 	 //chatter.publish( &str_msg );
 }

 ros::Subscriber<std_msgs::UInt16> sub("motor", motor_cb);

 /* RosSubscriberTask function */
 void RosSubscriberTask(void const * argument)
 {
   /* USER CODE BEGIN RosSubscriberTask */
   /* Infinite loop */
   for(;;)
   {
     osDelay(1000);
   }
   /* USER CODE END RosSubscriberTask */
 }


 /*
  * Create publish task
  */
 uint32_t RosSubscriberTaskCreate(ros::NodeHandle *nh)
 {
	 osThreadId RosSubscriberHandle;

	 nh_ = nh;

	 nh_-> subscribe(sub);

	 /* definition and creation of RosSubscriber */
	 osThreadDef(RosSubscriber, RosSubscriberTask, osPriorityNormal, 0, 128);
	 RosSubscriberHandle = osThreadCreate(osThread(RosSubscriber), NULL);
	 if (NULL == RosSubscriberHandle)
	 {
		 return 1;
	 }
	 return 0;
 }


