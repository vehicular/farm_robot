#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"
#include "motor_control.h"
#include "key.h"
#include "can.h"

int main(void)
{
	  u8 move_forward_key_count = 0, move_back_key_count = 0,turn_left_key_count = 0,turn_right_key_count = 0;
	  u16 speed_value[7] = {SpeedLevel_1,SpeedLevel_2,Speedlevel_3,SpeedLevel_4,Speedlevel_3,SpeedLevel_2,SpeedLevel_1};
		u16 angle_value[6] = {AngleLevel_1,AngleLevel_2,AngleLevel_3,AngleLevel_2,AngleLevel_1};
    u8 key_value;
   // u16 led0pwmval=0; 
	  u8 led0sta=1,led1sta=1;		    //LED0,LED1的当前状态
    Cache_Enable();                 //打开L1-Cache
    HAL_Init();				        //初始化HAL库
    Stm32_Clock_Init(432,25,2,9);   //设置时钟,216Mhz 
    delay_init(216);                //延时初始化
	  uart_init(115200);		        //串口初始化
	//	CAN1_Mode_Init(CAN_SJW_1TQ,CAN_BS2_6TQ,CAN_BS1_11TQ,6,CAN_MODE_LOOPBACK);//CAN初始化环回模式,波特率500Kbps  
	  CAN1_Mode_Init(CAN_SJW_1TQ,CAN_BS2_6TQ,CAN_BS1_11TQ,6,CAN_MODE_NORMAL);   //CAN初始化普通模式,波特率500Kbps  
	  KEY_Init();                     //按键初始化
    LED_Init();                     //初始化LED
	  Server_Motor_IO_Init();  //初始化电机IO
	  TIM11_PWM_Init(480-1, 1-1); //定时器11 PWM初始化 
	  TIM10_PWM_Init(480-1, 1-1); //定时器10 PWM初始化  
    // TIM3_PWM_Init(500-1,108-1);     //108M/108=1M的计数频率，自动重装载为500，那么PWM频率为1M/500=2kHZ
  	Server_Motor_IO_Init();
	  
    while(1)
    {
		key_value = KEY_Scan(0); 		    //得到键值
	   	if(key_value)
		{						   
			switch(key_value)
			{				 
				case WKUP_PRES:	//控制LED0,LED1互斥点亮   move forward
					led1sta=!led1sta;
					led0sta=!led1sta;
				  if(move_forward_key_count == 8)
					{
				       move_forward_key_count = 0;
					}
					Server_Motor_Move_Forward(speed_value[move_forward_key_count]);
		      move_forward_key_count++;
					break;
				case KEY2_PRES:	//控制LED0翻转   turn left
					led0sta=!led0sta;
				  if(turn_left_key_count == 7)
					{
				       turn_left_key_count = 0;
					}
					Server_Motor_Turn_Left(angle_value[turn_left_key_count]);
		      turn_left_key_count++;
					break;
				case KEY1_PRES:	//控制LED1翻转   Move back 
					led1sta=!led1sta;
				  if(move_back_key_count == 8)
					{
				       move_back_key_count = 0;
					}
					Server_Motor_Move_Back(speed_value[move_back_key_count]);
		      move_back_key_count++;				
					break;
				case KEY0_PRES:	//同时控制LED0,LED1翻转 Turn right
					led0sta=!led0sta;
					led1sta=!led1sta;
				  if(turn_right_key_count == 7)
					{
				       turn_right_key_count = 0;
					}
					Server_Motor_Turn_Right(angle_value[turn_right_key_count]);
		      turn_right_key_count++;
					break;
			}
			LED0(led0sta);		//控制LED0状态
			LED1(led1sta);		//控制LED1状态 
		}else delay_ms(10);
    } 
}
