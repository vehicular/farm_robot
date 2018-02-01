#include "timer.h"
#include "led.h"

//修改说明
//V1.1 20160711
//新增TIM3_PWM_Init函数,用于PWM输出
//TIM10  ch1  PF6
//TIM11  ch1  PF7
////////////////////////////////////////////////////////////////////////////////// 	 

TIM_HandleTypeDef TIM10_Handler;         //定时器10句柄 
TIM_HandleTypeDef TIM11_Handler;         //定时器11句柄
TIM_OC_InitTypeDef TIM10_CH1Handler;     //定时器10通道1句柄
TIM_OC_InitTypeDef TIM11_CH1Handler;     //定时器11通道1句柄

//Right motor
//TIM11 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数//TIM PWM部分初始化 
void TIM11_PWM_Init(u16 arr,u16 psc)
{ 
    TIM11_Handler.Instance=TIM11;           
    TIM11_Handler.Init.Prescaler=psc;    //定时器分频    
    TIM11_Handler.Init.CounterMode=TIM_COUNTERMODE_UP; //向上计数模式
    TIM11_Handler.Init.Period=arr;       //自动重装载值   
    TIM11_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM11_Handler);        //初始化PWM
    
    TIM11_CH1Handler.OCMode=TIM_OCMODE_PWM1;  //模式选择PWM1
    TIM11_CH1Handler.Pulse = arr * 0.5;      //设置比较值,此值用来确定占空比，     
                                            //默认比较值为自动重装载值的一半,即占空比为50%
    TIM11_CH1Handler.OCPolarity=TIM_OCPOLARITY_LOW; //输出比较极性为低 
    HAL_TIM_PWM_ConfigChannel(&TIM11_Handler,&TIM11_CH1Handler,TIM_CHANNEL_1); //配置TIM11通道1
    HAL_TIM_PWM_Start(&TIM11_Handler,TIM_CHANNEL_1); //开启PWM通道1
}

//Left motor
//TIM10 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数//TIM PWM部分初始化 
void TIM10_PWM_Init(u16 arr,u16 psc)
{ 
    TIM10_Handler.Instance=TIM10;           
    TIM10_Handler.Init.Prescaler=psc;     
    TIM10_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;
    TIM10_Handler.Init.Period=arr;         
    TIM10_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM10_Handler);       
    
    TIM10_CH1Handler.OCMode=TIM_OCMODE_PWM1; 
    TIM10_CH1Handler.Pulse = arr * 0.5;            
                                          
    TIM10_CH1Handler.OCPolarity=TIM_OCPOLARITY_LOW; 
    HAL_TIM_PWM_ConfigChannel(&TIM10_Handler,&TIM10_CH1Handler,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&TIM10_Handler,TIM_CHANNEL_1);
}

//定时器底层驱动，时钟使能，引脚配置
//此函数会被HAL_TIM_PWM_Init()调用
//htim:定时器句柄
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{

	if(htim->Instance == TIM10){
		GPIO_InitTypeDef GPIO_Initure;
		__HAL_RCC_TIM10_CLK_ENABLE();			
		__HAL_RCC_GPIOF_CLK_ENABLE();			
		
		GPIO_Initure.Pin=GPIO_PIN_6;           
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;  
		GPIO_Initure.Pull=GPIO_PULLUP;          
		GPIO_Initure.Speed=GPIO_SPEED_HIGH;     
		GPIO_Initure.Alternate=GPIO_AF3_TIM10;	
		HAL_GPIO_Init(GPIOF,&GPIO_Initure);
	}
	if(htim->Instance == TIM11){
		GPIO_InitTypeDef GPIO_Initure;
		__HAL_RCC_TIM11_CLK_ENABLE();			
		__HAL_RCC_GPIOF_CLK_ENABLE();		
		
		GPIO_Initure.Pin=GPIO_PIN_7;           
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;  
		GPIO_Initure.Pull=GPIO_PULLUP;         
		GPIO_Initure.Speed=GPIO_SPEED_HIGH;    
		GPIO_Initure.Alternate=GPIO_AF3_TIM11;	
		HAL_GPIO_Init(GPIOF,&GPIO_Initure);
	}
}

void TIM_SetCompare(TIM_HandleTypeDef *htim,u32 compare)
{
	if(htim->Instance == TIM11 || htim->Instance == TIM10){
		htim->Instance->ARR = 2 * compare -1;	
		htim->Instance->CCR1 =(int)2 * compare/2; 	
	}else{	
		htim->Instance->ARR = compare -1;
		htim->Instance->CCR1 =(int)compare/2;
	}
}
