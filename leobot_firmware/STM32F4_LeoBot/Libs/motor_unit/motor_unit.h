/*
 * motor.h
 *
 *  Created on: 6 трав. 2018 р.
 *      Author: Nemo
 */

#ifndef MOTOR_UNIT_MOTOR_UNIT_H_
#define MOTOR_UNIT_MOTOR_UNIT_H_


#include <stdint.h>

enum Direction
{
	FORWARD,
	BACK
};

class MotorUnit
{
public:
	virtual void motorInit() = 0;
//	virtual void motorEnable() = 0;
//	virtual void motorDisable() = 0;
	virtual void move(Direction direction, uint32_t speed) = 0;
//
//	virtual void encoderInit() = 0;
//	virtual void encoderEnable() = 0;
//	virtual void encoderDisable() = 0;
//	virtual uint32_t encoderRead() = 0;
};

class MotorUnit_1:  public MotorUnit
{

public:
	void motorInit();
//	void motorEnable();
//	void motorDisable();
	//void move(uint32_t direction, uint32_t speed);
	void move(Direction direction, uint32_t speed);

	//void encoderInit();
	//void encoderEnable();
	//void encoderDisable();
	//uint32_t encoderRead();
};


class MotorUnit_2: public MotorUnit
{
public:
	void motorInit();
	void move(Direction direction, uint32_t speed);
};

class MotorUnit_3: public MotorUnit
{
public:
	void motorInit();
	void move(Direction direction, uint32_t speed);
};

class MotorUnit_4: public MotorUnit
{
public:
	void motorInit();
	void move(Direction direction, uint32_t speed);
};



#endif /* MOTOR_UNIT_MOTOR_UNIT_H_ */

