#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"


extern TIM_HandleTypeDef TIM10_Handler;         //��ʱ��10PWM��� 
extern TIM_HandleTypeDef TIM11_Handler;         //��ʱ��11PWM���

extern TIM_OC_InitTypeDef TIM10_CH1Handler;     //��ʱ��10ͨ��1���
extern TIM_OC_InitTypeDef TIM11_CH1Handler;     //��ʱ��11ͨ��1���


void TIM11_PWM_Init(u16 arr,u16 psc); //��ʱ��11 PWM��ʼ��
void TIM10_PWM_Init(u16 arr,u16 psc); //��ʱ��10 PWM��ʼ��

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim);
void TIM_SetCompare(TIM_HandleTypeDef *htim,u32 compare);
#endif

