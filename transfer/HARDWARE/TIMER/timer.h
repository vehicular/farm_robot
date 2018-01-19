#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"


extern TIM_HandleTypeDef TIM10_Handler;         //定时器10PWM句柄 
extern TIM_HandleTypeDef TIM11_Handler;         //定时器11PWM句柄

extern TIM_OC_InitTypeDef TIM10_CH1Handler;     //定时器10通道1句柄
extern TIM_OC_InitTypeDef TIM11_CH1Handler;     //定时器11通道1句柄


void TIM11_PWM_Init(u16 arr,u16 psc); //定时器11 PWM初始化
void TIM10_PWM_Init(u16 arr,u16 psc); //定时器10 PWM初始化

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim);
void TIM_SetCompare(TIM_HandleTypeDef *htim,u32 compare);
#endif

