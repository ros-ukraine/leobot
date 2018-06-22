/*
 * motor.h
 *
 *  Created on: 6 трав. 2018 р.
 *      Author: Nemo
 */

#ifndef MOTOR_UNIT_MOTOR_UNIT_H_
#define MOTOR_UNIT_MOTOR_UNIT_H_


#include <stdint.h>

//

typedef enum motorUnit_num
{
	M_UNIT_1,
	M_UNIT_2,
	M_UNIT_3,
	M_UNIT_4
} motorUnit_num;

typedef enum Direction
{
	FORWARD,
	BACK
}
Direction;

class MotorUnit
{
public:
	MotorUnit();
	virtual void motorInit() = 0;
	virtual void motorEnable() = 0;
	virtual void motorDisable() = 0;
	virtual void move(uint32_t direction, uint32_t speed) = 0;

	virtual void encoderInit() = 0;
	virtual void encoderEnable() = 0;
	virtual void encoderDisable() = 0;
	virtual uint32_t encoderRead() = 0;
};

class MotorUnit_1: MotorUnit
{

	/*{
		 Init PWM
		 Init Encoder
	}*/
public:
	MotorUnit_1();
	void motorInit();
	void motorEnable();
	void motorDisable();
	void move(uint32_t direction, uint32_t speed);

	void encoderInit();
	void encoderEnable();
	void encoderDisable();
	uint32_t encoderRead();


};


class MotorUnit_2: MotorUnit
{
	MotorUnit_2();


};

class MotorUnit_3: MotorUnit
{
	MotorUnit_3();


};

class MotorUnit_4: MotorUnit
{
	MotorUnit_4();


};



#endif /* MOTOR_UNIT_MOTOR_UNIT_H_ */

