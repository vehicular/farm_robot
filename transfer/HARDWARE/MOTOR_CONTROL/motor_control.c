#include "motor_control.h"
#include "timer.h"
#include "delay.h"

//��ʼ��PD4,PD6Ϊʹ�����.��ʹ�����ĸ����ڵ�ʱ��		
//PD5 ��PD11 Ϊ������ƿ�
//Motor IO��ʼ��
void Server_Motor_IO_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOD_CLK_ENABLE();			//����GPIODʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_11; //PD4,6,5,11
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,GPIO_PIN_SET);	//PD4��1
	  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,GPIO_PIN_SET);	//PD6��1 
	
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,GPIO_PIN_RESET);	//PD5��0
	  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET);	//PD11��0 
}


//move forward
void Server_Motor_Move_Forward(u16 speed)
{
		ServerMotor_L_EN_ON;//enable the Left motor
	  ServerMotor_R_EN_ON;//enable the Right motor
	  //both motors are forward
	  ServerMotor_L_DIR_Forward;
	  ServerMotor_R_DIR_Forward;
	  
	  TIM_SetCompare(&TIM10_Handler, speed);
	  TIM_SetCompare(&TIM11_Handler, speed);
	
	  
}


//move back
void Server_Motor_Move_Back(u16 speed)
{
	  ServerMotor_L_EN_ON;//enable the Left motor
	  ServerMotor_R_EN_ON;//enable the Right motor
	
	  //both motors are back
	  ServerMotor_L_DIR_Back;
	  ServerMotor_R_DIR_Back;
    
		TIM_SetCompare(&TIM10_Handler, speed);
	  TIM_SetCompare(&TIM11_Handler, speed);
	

	
}

//turn left
void Server_Motor_Turn_Left(u16 angle)
{

	  ServerMotor_L_DIR_Back;
	  ServerMotor_R_DIR_Forward;
		TIM_SetCompare(&TIM10_Handler,300);
	  TIM_SetCompare(&TIM11_Handler, 300);
	  ServerMotor_L_EN_ON;//enable the Left motor
	  ServerMotor_R_EN_ON;//enable the Right motor
	  delay_ms(68 * angle); // the time of change angle
	  ServerMotor_L_EN_OFF;//enable the Left motor
	  ServerMotor_R_EN_OFF;//enable the Right motor    
}

//turn right
void Server_Motor_Turn_Right(u16 angle)
{
	  ServerMotor_L_DIR_Forward;
	  ServerMotor_R_DIR_Back;
		TIM_SetCompare(&TIM10_Handler,300);
	  TIM_SetCompare(&TIM11_Handler, 300);
	  ServerMotor_L_EN_ON;//enable the Left motor
	  ServerMotor_R_EN_ON;//enable the Right motor
	  delay_ms(68 * angle);  // the time of change angle
	  ServerMotor_L_EN_OFF;//enable the Left motor
	  ServerMotor_R_EN_OFF;//enable the Right motor  
  
}

//stop
void Server_Motor_Stop(void)
{
		ServerMotor_L_EN_OFF;
		ServerMotor_R_EN_OFF;
}


