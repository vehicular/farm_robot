#include "timer.h"
#include "led.h"

//�޸�˵��
//V1.1 20160711
//����TIM3_PWM_Init����,����PWM���
//TIM10  ch1  PF6
//TIM11  ch1  PF7
////////////////////////////////////////////////////////////////////////////////// 	 

TIM_HandleTypeDef TIM10_Handler;         //��ʱ��10��� 
TIM_HandleTypeDef TIM11_Handler;         //��ʱ��11���
TIM_OC_InitTypeDef TIM10_CH1Handler;     //��ʱ��10ͨ��1���
TIM_OC_InitTypeDef TIM11_CH1Handler;     //��ʱ��11ͨ��1���

//Right motor
//TIM11 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��//TIM PWM���ֳ�ʼ�� 
void TIM11_PWM_Init(u16 arr,u16 psc)
{ 
    TIM11_Handler.Instance=TIM11;           
    TIM11_Handler.Init.Prescaler=psc;    //��ʱ����Ƶ    
    TIM11_Handler.Init.CounterMode=TIM_COUNTERMODE_UP; //���ϼ���ģʽ
    TIM11_Handler.Init.Period=arr;       //�Զ���װ��ֵ   
    TIM11_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM11_Handler);        //��ʼ��PWM
    
    TIM11_CH1Handler.OCMode=TIM_OCMODE_PWM1;  //ģʽѡ��PWM1
    TIM11_CH1Handler.Pulse = arr * 0.5;      //���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�     
                                            //Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50%
    TIM11_CH1Handler.OCPolarity=TIM_OCPOLARITY_LOW; //����Ƚϼ���Ϊ�� 
    HAL_TIM_PWM_ConfigChannel(&TIM11_Handler,&TIM11_CH1Handler,TIM_CHANNEL_1); //����TIM11ͨ��1
    HAL_TIM_PWM_Start(&TIM11_Handler,TIM_CHANNEL_1); //����PWMͨ��1
}

//Left motor
//TIM10 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��//TIM PWM���ֳ�ʼ�� 
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

//��ʱ���ײ�������ʱ��ʹ�ܣ���������
//�˺����ᱻHAL_TIM_PWM_Init()����
//htim:��ʱ�����
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
