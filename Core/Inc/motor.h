/*
 * motor.h
 *
 *  Created on: Nov 8, 2022
 *      Author: nicolas
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "main.h"

void motorPowerOn(void);
void motorPowerOff(void);
void motorSetSpeed(int speed);
void setAlpha(int alpha);
void asserCurrent (void);
void calcSpeed (void);
void asserSpeed(void);

#endif /* INC_MOTOR_H_ */
