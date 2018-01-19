#ifndef _MOTOR_CONTROL_H
#define _MOTOR_CONTROL_H
#include "sys.h"

//enable /dinable the motor
#define ServerMotor_L_EN_ON  (HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_SET))
#define ServerMotor_L_EN_OFF (HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET))

#define ServerMotor_R_EN_ON  (HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,GPIO_PIN_SET))
#define ServerMotor_R_EN_OFF (HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,GPIO_PIN_RESET) )


//control motor direction move foward / back

//Right motor
#define ServerMotor_R_DIR_Forward  (HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,GPIO_PIN_SET))
#define ServerMotor_R_DIR_Back    (HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,GPIO_PIN_RESET))

//Left motor
#define ServerMotor_L_DIR_Forward  (HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,GPIO_PIN_SET))
#define ServerMotor_L_DIR_Back    (HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,GPIO_PIN_RESET))

void Server_Motor_IO_Init(void);
void Server_Motor_Move_Forward(u16 speed);
void Server_Motor_Move_Back(u16 speed); 
void Server_Motor_Turn_Left(u16 angle);
void Server_Motor_Turn_Right(u16 angle);
void Server_Motor_Stop(void);

#define MAXSPEED  (500)
#define SpeedLevel_0  (500)
#define SpeedLevel_1  (450)   
#define SpeedLevel_2  (400)
#define Speedlevel_3  (350)
#define SpeedLevel_4  (300)


#define AngleLevel_1 (20)   
#define AngleLevel_2 (40)
#define AngleLevel_3 (90)

//control server motor driver alarm on /off
//todo
//#define ALARM_ON ()
//#define ALARM_OFF


#endif
