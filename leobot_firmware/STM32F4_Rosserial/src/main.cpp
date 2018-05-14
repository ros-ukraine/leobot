/*
******************************************************************************
File:     main.cpp
Info:     Generated by Atollic TrueSTUDIO(R) 9.0.1   2018-04-29

The MIT License (MIT)
Copyright (c) 2018 STMicroelectronics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************
*/

// example from
//http://wiki.ros.org/rosserial_arduino/Tutorials/Servo%20Controller
//http://wiki.ros.org/rosserial_client/Tutorials/Using%20rosserial%20with%20AVR%20and%20UART
//http://electronics-homemade.com/STM32F4-Turn-on-LED.html

//http://wiki.ros.org/roscpp/Overview/Callbacks%20and%20Spinning

/* Includes */
#include "stm32f4xx.h"


/* rosserial includes */
#include "ros.h"
#include "std_msgs/UInt16.h"
#include <std_msgs/String.h>
//

/* user library includes */


#include "../Libraries/motor_unit/motor_unit.h"


ros::NodeHandle  nh;

/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */


void motor_cb(const std_msgs::UInt16& cmd_msg)
{
	//cmd_msg.data should be in range 0 - 100

}

ros::Subscriber<std_msgs::UInt16> sub("motor", motor_cb);


std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);
char hello[13] = "hello world!";



int main(void)
{

	//LedInit();

	motorUnit_Init(M_UNIT_1);
	motorUnit_Init(M_UNIT_2);
	motorUnit_Init(M_UNIT_3);
	motorUnit_Init(M_UNIT_4);

	motorUnit_MotorMove(M_UNIT_1, FORWARD, 1000);
	motorUnit_MotorMove(M_UNIT_2, FORWARD, 2000);
	motorUnit_MotorMove(M_UNIT_3, FORWARD, 4000);
	motorUnit_MotorMove(M_UNIT_4, FORWARD, 8000);

	nh.initNode();
	nh.subscribe(sub);
	nh.advertise(chatter);

	//ros::Rate rate( 2 );
	//ros::Rate r(1); // 1 hz

	//ros::Duration d(0.5);

    /* Infinite loop */
	while (1)
	{
		 str_msg.data = hello;
		 chatter.publish( &str_msg );

		 nh.spinOnce();

		 //ros::Duration(0.5).sleep(); // sleep for half a second

		 //rate.sleep();
	}
}


// debug functions
void LedInit(void)
{


	  // GPIOD Configuration
	  GPIO_InitTypeDef GPIO_InitStruct;

	  //Enable the GPIOD Clock
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

	  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;

	  GPIO_Init(GPIOD, &GPIO_InitStruct);

	  // GPIOD-PIN-15 ON
	  GPIO_SetBits(GPIOD, GPIO_Pin_15);
}

void LedBlink(uint32_t current_ms, uint32_t interval_ms)
{
	static uint32_t state = 0;
	static uint32_t currentMillis = 0;
	static uint32_t previousMillis = 0;

	currentMillis = current_ms;

	if (currentMillis - previousMillis >= interval_ms)
	{

		state = !state;

		if (state)
			GPIO_SetBits(GPIOD, GPIO_Pin_15); //ON
		else
			GPIO_ResetBits(GPIOD, GPIO_Pin_15); //OFF

		// save the last time you blinked the LED
		previousMillis = currentMillis;  // Remember the time
	}
}