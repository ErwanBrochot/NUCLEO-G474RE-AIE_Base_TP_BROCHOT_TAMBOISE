/**
  ******************************************************************************
  * @file    shell.c
  * @brief   This file provides code for motor control
  ******************************************************************************
  *  Created on: Nov 7, 2022
  *      Author: nicolas
  *
  ******************************************************************************
  */

#include "motor.h"
extern TIM_HandleTypeDef htim1;

/**
  * @brief  Switch on the motor driver
  * @retval None
  */
void motorPowerOn(void){
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin); // just for test, you can delete it
	//Phase de démarage//
	HAL_GPIO_WritePin(ISO_RESET_GPIO_Port, ISO_RESET_Pin,GPIO_PIN_SET );

	int i=0;
	while (i<33)
	{
		i++;
	}
		HAL_GPIO_WritePin(ISO_RESET_GPIO_Port, ISO_RESET_Pin, GPIO_PIN_RESET);
		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1 );
		HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2 );
		HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);

}

/**
  * @brief  Switch off the motor driver
  * @retval None
  */
void motorPowerOff(void){
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin); // just for test, you can delete it
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
void setAlpha(int alpha)
{
	TIM1->CCR1=alpha*(TIM1->ARR)/100;
	TIM1->CCR2=(100-alpha)*(TIM1->ARR)/100;
}
