DSO PB1 (Time3 ch4)

	
Ӳ����Դ:
	1,DS0(������PB1)  
	2,��ʱ��3(TIM3),ʹ��TIM3ͨ��4(CH4),��TIM3_CH4�����PB1.�Ӷ�ʵ��PWM��
	������DS0����. 	



key A0 C13 PH2,PH3
//TIM10  ch1  PF6 left motor
//TIM11  ch1  PF7 right motor

#define KEY0        HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_3)  //KEY0����PH3
#define KEY1        HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_2)  //KEY1����PH2
#define KEY2        HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13) //KEY2����PC13
#define WK_UP       HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)  //WKUP����PA0


//CAN Bus
GPIO_Initure.Pin=GPIO_PIN_11|GPIO_PIN_12;   //PA11,12


#define ServerMotor_L_EN_OFF (HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET))

#define ServerMotor_R_EN_ON  (HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,GPIO_PIN_SET))


//Right motor
#define ServerMotor_R_DIR_Forward  (HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,GPIO_PIN_SET))
#define ServerMotor_R_DIR_Back    (HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,GPIO_PIN_RESET))

//Left motor
#define ServerMotor_L_DIR_Forward  (HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,GPIO_PIN_SET))
#define ServerMotor_L_DIR_Back    (HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,GPIO_PIN_RESET))
