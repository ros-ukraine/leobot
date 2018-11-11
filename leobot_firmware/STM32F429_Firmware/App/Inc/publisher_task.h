/*
 * publish_task.h
 *
 *  Created on: 23 черв. 2018 р.
 *      Author: Nemo
 */

#ifndef INC_PUBLISHER_TASK_H_
#define INC_PUBLISHER_TASK_H_

#include "stdint.h"
#include "ros.h"

uint32_t RosPublisherTaskCreate(ros::NodeHandle *nh);

#endif /* INC_PUBLISHER_TASK_H_ */
