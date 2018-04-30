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

/* Includes */
#include "stm32f4xx.h"

#include "ros.h"
#include "std_msgs/UInt16.h"
//

//#include "UInt16.h"


ros::NodeHandle  nh;

/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */


void servo_cb(const std_msgs::UInt16& cmd_msg)
{
    //servo.write(cmd_msg.data); //set servo angle, should be from 0-180
    //digitalWrite(13, HIGH-digitalRead(13));  //toggle led
}

ros::Subscriber<std_msgs::UInt16> sub("servo", servo_cb);


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


void LedBlink(void)
{
	volatile uint32_t i;

	for(i = 10000; i > 0; i--);
	GPIO_SetBits(GPIOD, GPIO_Pin_15); //ON

	for(i = 10000; i > 0; i--);
	GPIO_ResetBits(GPIOD, GPIO_Pin_15); //OFF
}

/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{
	//debug
	//LedInit();

  //nh.initNode();
  //nh.subscribe(sub);

  /* Infinite loop */
	while (1)
	{
        //nh.spinOnce();

		//debug
		//LedBlink();
	}
}



