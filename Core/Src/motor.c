/**
 ******************************************************************************
 * @file    motor.c
 * @brief   This file provides code for motor control
 ******************************************************************************
 *  Created on: Nov 7, 2022
 *      Author: nicolas
 *
 ******************************************************************************
 */

#include "motor.h"
extern TIM_HandleTypeDef htim1;


extern float consignCurrent;
extern float hallCurrentValue;
extern int adcDMAflag;
extern int startFlag;

float alphaKp=0.0;
float alphaKi=0.0;
float alphaKiOld=0.5;
int alpha=50;
float eps=0.0;
float epsOld=0.0;
extern float speed;
extern int codeurValue;

/**
 * @brief  Switch on the motor driver
 * @retval None
 */
void motorPowerOn(void){
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin); // just for test, you can delete it
	//Phase de démarage//
	HAL_GPIO_WritePin(ISO_RESET_GPIO_Port, ISO_RESET_Pin,GPIO_PIN_SET );
	setAlpha(50);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1 );
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2 );
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);


	int i=0;
	while (i<33)
	{
		i++;
	}
	HAL_GPIO_WritePin(ISO_RESET_GPIO_Port, ISO_RESET_Pin, GPIO_PIN_RESET);

	consignCurrent=0;
	startFlag=1;
	alphaKiOld=0.5;
	epsOld=0;


}

/**
 * @brief  Switch off the motor driver
 * @retval None
 */
void motorPowerOff(void){
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin); // just for test, you can delete it
	startFlag=0;
}

/**
 * @brief  Set the motor speed
 * @param  speed : target speed of the motor
 * @retval None
 */
void motorSetSpeed(int speed){
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin); // just for test, you can delete it

}

/**
 * @brief  Set the dutyCycle
 * @param  alpha : target alpha of the Transitors
 * @retval None
 */
void setAlpha(int alpha1)
{
	TIM1->CCR1=alpha1*(TIM1->ARR)/100;
	TIM1->CCR2=(100-alpha1)*(TIM1->ARR)/100;
}

/**
 * @brief Set the duty cycle thanks to a PI regulation to match with the wanted value.
 * It use a parallel PI regulation
 * @retval None
 */
void asserCurrent (void)
{
	meanADCValue();

	float eps= consignCurrent - hallCurrentValue;

	// Proportional part
	if (Kp*eps < 0){
		alphaKp=0.0;
	}
	else if (Kp*eps > 1) {
		alphaKp=1.0;
	}
	else {
		alphaKp=eps*(float)Kp;
	}

	// Integral part

	alphaKi=alphaKiOld+((Ki*Te)/2)*(eps+epsOld);
	if (alphaKi < 0){
		alphaKi=0.0;
	}
	else if (alphaKi > 1) {
		alphaKi=1.0;
	}

	alphaKiOld=alphaKi;
	epsOld=eps;

	// Summ of the two coeff

	alpha=(int)((alphaKi+alphaKp)*100);

	if (alpha < 0){
		alpha=0;
	}
	else if (alpha > 100) {
		alpha=100;
	}
	setAlpha(alpha);

}

void calcSpeed (void){
	speed=(codeurValue-((TIM3->ARR)/2.0))*FREQ_ECH_SPEED*60.0/NUMBER_OF_POINT;
}
