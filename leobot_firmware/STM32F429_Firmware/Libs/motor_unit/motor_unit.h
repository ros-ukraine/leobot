/*
 * motor.h
 *
 *  Created on: 6 ����. 2018 �.
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
	virtual void move(Direction direction, uint32_t speed) = 0;

    virtual void encoderInit() = 0;
	//virtual uint32_t encoderRead() = 0;
};

class MotorUnit_1:  public MotorUnit
{

public:
	void motorInit();
	void move(Direction direction, uint32_t speed);

	void encoderInit();
	//uint32_t encoderRead();
};


class MotorUnit_2: public MotorUnit
{
public:
	void motorInit();
	void move(Direction direction, uint32_t speed);

	void encoderInit();
};

class MotorUnit_3: public MotorUnit
{
public:
	void motorInit();
	void move(Direction direction, uint32_t speed);

	void encoderInit();
};

class MotorUnit_4: public MotorUnit
{
public:
	void motorInit();
	void move(Direction direction, uint32_t speed);

	void encoderInit();
};



#endif /* MOTOR_UNIT_MOTOR_UNIT_H_ */

