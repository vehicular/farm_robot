//å®šæ—¶å™¨åº•å±‚é©±åŠ¨ï¼Œæ—¶é’Ÿä½¿èƒ½ï¼Œå¼•è„šé… ç½®
//æ­¤å‡½æ•°ä¼šè¢«HAL_TIM_PWM_Init()è°ƒç”¨
//htim:å®šæ—¶å™¨å ¥æŸ„
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM10){
		GPIO_InitTypeDef GPIO_Initure;
		__HAL_RCC_TIM10_CLK_ENABLE();			//ä½¿èƒ½å®šæ—¶å™¨3
		__HAL_RCC_GPIOF_CLK_ENABLE();			//å¼€å ¯GPIOBæ—¶é’Ÿ
		
		GPIO_Initure.Pin=GPIO_PIN_6;           	//PA6
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//å¤ ç”¨æŽ¨å®Œè¾“å‡º
		GPIO_Initure.Pull=GPIO_PULLUP;          //ä¸Šæ‹‰
		GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //é«˜é€Ÿ
		GPIO_Initure.Alternate=GPIO_AF3_TIM10;	//PC6å¤ ç”¨ä¸ºTIM3_CH1
		HAL_GPIO_Init(GPIOF,&GPIO_Initure);
	}
	if(htim->Instance == TIM11){
		GPIO_InitTypeDef GPIO_Initure;
		__HAL_RCC_TIM11_CLK_ENABLE();			//ä½¿èƒ½å®šæ—¶å™¨11
		__HAL_RCC_GPIOF_CLK_ENABLE();			//å¼€å ¯GPIOFæ—¶é’Ÿ
		
		GPIO_Initure.Pin=GPIO_PIN_7;           	//PF7
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//å¤ ç”¨æŽ¨å®Œè¾“å‡º
		GPIO_Initure.Pull=GPIO_PULLUP;          //ä¸Šæ‹‰
		GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //é«˜é€Ÿ
		GPIO_Initure.Alternate=GPIO_AF3_TIM11;	//PF7å¤ ç”¨ä¸ºTIM11_CH1
		HAL_GPIO_Init(GPIOF,&GPIO_Initure);
	}

}


//******************************************************************************
//åŽŸåœ°æ—‹è½¬å‡½æ•°void Xiuanzhuan(u8 LR,int ANG)
//å ‚æ•°1ï¼šå ‘å·¦å ‘å ³æ—‹è½¬
//å ‚æ•°2ï¼šæ—‹è½¬è§’åº¦
//ANGç­‰äºŽ10æ—¶ï¼Œå±¥å¸¦èµ°äº†12CMç¨ å¤šï¼Œå®žåœ°60æ—¶æ—‹è½¬äº†90åº¦å·¦å ³
//é‚£å°±æ˜¯å¢žé•¿äº†
//******************************************************************************
void Rotate(u8 LR, int ANG) {
  TIM_SetCompare(&TIM11_Handler, StartSpeed); //ä¿®æ”¹å®šæ—¶å™¨3æ¯”è¾ƒå€¼ï¼Œä¿®æ”¹é¢‘çŽ‡æˆ–å  ç©ºæ¯”
  TIM_SetCompare(&TIM3_Handler, StartSpeed); //ä¿®æ”¹å®šæ—¶å™¨3æ¯”è¾ƒå€¼ï¼Œä¿®æ”¹é¢‘çŽ‡æˆ–å  ç©ºæ¯”
  if (LR == 0) { //åŽŸåœ°å ³è½¬
    ServeMotor_L_DIR_Jee;	//HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET); 	//æ–¹å ‘ç›¸å  ä¸€ä¸ªè½®å­ å¾€å‰ ä¸€ä¸ªå¾€å Ž
    ServeMotor_R_DIR_Back;	//HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET); //æ–¹å ‘ç›¸å  
  } else {   //åŽŸåœ°å·¦è½¬
    ServeMotor_R_DIR_Jee;	//HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET); //æ–¹å ‘ç›¸å  
    ServeMotor_L_DIR_Back;	//HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET); //æ–¹å ‘ç›¸å  
  }
  ServeMotor_L_EN_ON;	//HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET); //ä½¿èƒ½æ—‹è½¬
  ServeMotor_R_EN_ON;	//HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET); //ä½¿èƒ½æ—‹è½¬
  delay_ms(ANG * 68);  //æ—‹è½¬çš„å»¶æ—¶æ—¶é—´
  ServeMotor_L_EN_OFF;	//HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_RESET); //å…³é—­ä½¿èƒ½æ—‹è½¬å°±æ˜¯å œè½¦
  ServeMotor_R_EN_OFF;	//HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET); //å…³é—­ä½¿èƒ½æ—‹è½¬å°±æ˜¯å œè½¦
  speed = StartSpeed ;
}


//******************************************************************************
//ç”µæœºåŠ å‡ å ˜é€Ÿå‡½æ•°
//å ‚æ•°è¯´æ˜Žï¼š
//startspeedå¼€å§‹é€Ÿåº¦å –å€¼èŒƒå›´135-1000ï¼Œè¶Šå° è¶Šå¿«ï¼Œ135æ—¶ç”µæœºè½¬é€Ÿè¾¾åˆ°2866è½¬
//endspeedç»“æ Ÿé€Ÿåº¦å –å€¼èŒƒå›´135-1000
//åŠ é€Ÿå¿«æ…¢ï¼šfast_or_slowå –å€¼èŒƒå›´10-1000ï¼Œå –å€¼è¶Šå° è¶Šå¿«è¾¾åˆ°ç›®æ ‡
//******************************************************************************
void ChangeSpeed(u16 startspeed,u16 endspeed,u16 fast_or_slow)
{
  u16 i = 0;
  startspeed = startspeed < MaxSpeed ? MaxSpeed : startspeed;	//å¦‚æžœéœ€è¦ åŠ é€Ÿçš„å¼€å§‹é€Ÿåº¦æ¯”æœ€å¤§é€Ÿåº¦éƒ½å¤§ï¼Œç”¨æœ€å¤§é€Ÿåº¦
  endspeed = endspeed < MaxSpeed ? MaxSpeed : endspeed;			//å¦‚æžœéœ€è¦ å‡ é€Ÿçš„ç»“æ Ÿé€Ÿåº¦æ¯”æœ€å¤§é€Ÿåº¦éƒ½å¤§ï¼Œç”¨æœ€å¤§é€Ÿåº¦
  //å¦‚æžœç”µæœºå°šæœªå ¯åŠ¨ï¼Œåˆ™ä¸ èƒ½èµ·å§‹é€Ÿåº¦å¤§äºŽç»ˆç»“é€Ÿåº¦ï¼Œåº”è¯¥å…ˆå ¯åŠ¨åˆ°æŒ‡å®šé€Ÿåº¦
  if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_4) && HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_6)) {
    if (startspeed > endspeed) {
      for (i = startspeed; i > endspeed; i--) {
        TIM_SetCompare(&TIM11_Handler, i); //ä¿®æ”¹å®šæ—¶å™¨11æ¯”è¾ƒå€¼ï¼Œä¿®æ”¹é¢‘çŽ‡æˆ–å  ç©ºæ¯”
        TIM_SetCompare(&TIM3_Handler, i);  //ä¿®æ”¹å®šæ—¶å™¨ 3æ¯”è¾ƒå€¼ï¼Œä¿®æ”¹é¢‘çŽ‡æˆ–å  ç©ºæ¯”
        delay_ms(fast_or_slow);	//æŒ‰è¿™ä¸ªé€Ÿåº¦å·¥ä½œå¤šé•¿æ—¶é—´å† æ”¹å ˜å°±ä¼šé€ æˆ åŠ é€Ÿçš„å¿«æ…¢
      }
    } else {
      for (i = startspeed; i < endspeed; i++) {
        TIM_SetCompare(&TIM11_Handler, i); //ä¿®æ”¹å®šæ—¶å™¨11æ¯”è¾ƒå€¼ï¼Œä¿®æ”¹é¢‘çŽ‡æˆ–å  ç©ºæ¯”
        TIM_SetCompare(&TIM3_Handler, i);  //ä¿®æ”¹å®šæ—¶å™¨ 3æ¯”è¾ƒå€¼ï¼Œä¿®æ”¹é¢‘çŽ‡æˆ–å  ç©ºæ¯”
        delay_ms(fast_or_slow);
      }
    }
  } else {
    ServeMotor_L_EN_ON;	//HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET); //ä½¿èƒ½å·¦ç”µæœº
    ServeMotor_R_EN_ON;	//HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET);  //ä½¿èƒ½å ³ç”µæœº

    for (i = StartSpeed; i > endspeed; i--) {
      TIM_SetCompare(&TIM11_Handler, i); //ä¿®æ”¹å®šæ—¶å™¨11æ¯”è¾ƒå€¼ï¼Œä¿®æ”¹é¢‘çŽ‡æˆ–å  ç©ºæ¯”
      TIM_SetCompare(&TIM3_Handler, i);  //ä¿®æ”¹å®šæ—¶å™¨ 3æ¯”è¾ƒå€¼ï¼Œä¿®æ”¹é¢‘çŽ‡æˆ–å  ç©ºæ¯”
      delay_ms(fast_or_slow);
    }
  }
  speed = i ;
}



//å·¦ç”µæœº
void TIM11_PWM_Init(u16 arr,u16 psc)
{ 
    TIM11_Handler.Instance=TIM11;            //å®šæ—¶å™¨3
    TIM11_Handler.Init.Prescaler=psc;       //å®šæ—¶å™¨åˆ†é¢‘
    TIM11_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//å ‘ä¸Šè®¡æ•°æ¨¡å¼ 
    TIM11_Handler.Init.Period=arr;          //è‡ªåŠ¨é‡ è£…è½½å€¼
    TIM11_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM11_Handler);       //åˆ å§‹åŒ–PWM
    
    TIM11_CH1Handler.OCMode=TIM_OCMODE_PWM1; //æ¨¡å¼ é€‰æ‹©PWM1
    TIM11_CH1Handler.Pulse = arr * 0.5;            //è®¾ç½®æ¯”è¾ƒå€¼,æ­¤å€¼ç”¨æ ¥ç¡®å®šå  ç©ºæ¯”ï¼Œ
                                            //é»˜è®¤æ¯”è¾ƒå€¼ä¸ºè‡ªåŠ¨é‡ è£…è½½å€¼çš„ä¸€å Š,å ³å  ç©ºæ¯”ä¸º50%
    TIM11_CH1Handler.OCPolarity=TIM_OCPOLARITY_LOW; //è¾“å‡ºæ¯”è¾ƒæž æ€§ä¸ºä½Ž 
    HAL_TIM_PWM_ConfigChannel(&TIM11_Handler,&TIM11_CH1Handler,TIM_CHANNEL_1);//é… ç½®TIM3é€šé “1
    HAL_TIM_PWM_Start(&TIM11_Handler,TIM_CHANNEL_1);//å¼€å ¯PWMé€šé “4
}
//å ³ç”µæœº
void TIM10_PWM_Init(u16 arr,u16 psc)
{ 
    TIM11_Handler.Instance=TIM10;            //å®šæ—¶å™¨3
    TIM11_Handler.Init.Prescaler=psc;       //å®šæ—¶å™¨åˆ†é¢‘
    TIM11_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//å ‘ä¸Šè®¡æ•°æ¨¡å¼ 
    TIM11_Handler.Init.Period=arr;          //è‡ªåŠ¨é‡ è£…è½½å€¼
    TIM11_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM10_Handler);       //åˆ å§‹åŒ–PWM
    
    TIM11_CH1Handler.OCMode=TIM_OCMODE_PWM1; //æ¨¡å¼ é€‰æ‹©PWM1
    TIM11_CH1Handler.Pulse = arr * 0.5;            //è®¾ç½®æ¯”è¾ƒå€¼,æ­¤å€¼ç”¨æ ¥ç¡®å®šå  ç©ºæ¯”ï¼Œ
                                            //é»˜è®¤æ¯”è¾ƒå€¼ä¸ºè‡ªåŠ¨é‡ è£…è½½å€¼çš„ä¸€å Š,å ³å  ç©ºæ¯”ä¸º50%
    TIM11_CH1Handler.OCPolarity=TIM_OCPOLARITY_LOW; //è¾“å‡ºæ¯”è¾ƒæž æ€§ä¸ºä½Ž 
    HAL_TIM_PWM_ConfigChannel(&TIM10_Handler,&TIM10_CH1Handler,TIM_CHANNEL_1);//é… ç½®TIM3é€šé “1
    HAL_TIM_PWM_Start(&TIM10_Handler,TIM_CHANNEL_1);//å¼€å ¯PWMé€šé “4
}



//è®¾ç½®TIMé€šé “4çš„é¢‘çŽ‡å’Œå  ç©ºæ¯”
//compare:æ¯”è¾ƒå€¼
void TIM_SetCompare(TIM_HandleTypeDef *htim,u32 compare)
{
	if(htim->Instance == TIM11 || htim->Instance == TIM10){	//TIM11çš„æ—¶é’Ÿä¸º216MHZ
		htim->Instance->ARR = 2 * compare -1;	//æ”¹å ˜é‡ è£…çš„æ•°å€¼çš„å ‚æ•°ï¼Œå°±æ˜¯é¢‘çŽ‡æ”¹å ˜
		htim->Instance->CCR1 =(int)2 * compare/2; 	//æ”¹å ˜PWMç‚¹ç©ºæ¯”çš„å ‚æ•°
	}else{	//TIM2-5æ—¶é’Ÿä¸º108MHZ
		htim->Instance->ARR = compare -1;	//æ”¹å ˜é‡ è£…çš„æ•°å€¼çš„å ‚æ•°ï¼Œå°±æ˜¯é¢‘çŽ‡æ”¹å ˜		
		htim->Instance->CCR1 =(int)compare/2; 	//æ”¹å ˜PWMç‚¹ç©ºæ¯”çš„å ‚æ•°
	}
}