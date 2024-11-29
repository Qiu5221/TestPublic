/**
  ******************************************************************
  * @file    app_gpio.c
  * @author  QWX
  * @version V1.0
  * @date    2022-04-02
  * @brief   板载GPIO口的使用
  ******************************************************************
  */
#include "driver_gpio.h"        





/*
*********************************************************************************************************
*	函 数 名: MX_GPIO_Init
*	功能说明: 板级引脚初始化
*	形    参: 无
*	返 回 值: 0表示成功，其他值按照main.h中函数返回值的定义
*********************************************************************************************************
*/
int WX_GPIO_Init(void)
{
	HAL_Init();
	
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	/* 中断优先级分组 */
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	
	/** Configure pins
			 PC14-OSC32_IN (OSC32_IN)   ------> RCC_OSC32_IN
			 PC15-OSC32_OUT (OSC32_OUT)   ------> RCC_OSC32_OUT
			 PH0-OSC_IN (PH0)   ------> RCC_OSC_IN
			 PH1-OSC_OUT (PH1)   ------> RCC_OSC_OUT
	*/

  /* 外部时钟GPIOH口使能（外部晶振使用） */
  __HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	/* 时钟配置 */
	LED1_GPIO_CLK_ENABLE();												/*开启LED相关的GPIO外设时钟*/
//	LED2_GPIO_CLK_ENABLE();												/*开启LED相关的GPIO外设时钟*/
	KEY1_GPIO_CLK_ENABLE();
//	KEY2_GPIO_CLK_ENABLE();
//	KEY3_GPIO_CLK_ENABLE();												/*开启按键GPIO口的时钟*/

	/* 端口配置 */
	GPIO_InitStruct.Pin 	= LED1_PIN;							/*选择要控制的GPIO引脚*/	
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;  /*设置引脚的输出类型为推挽输出*/
	GPIO_InitStruct.Pull  = GPIO_PULLUP;					/*设置引脚为上拉模式*/
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; /*设置引脚速率为高速 */   

	/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
	HAL_GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStruct);	

	//GPIO_InitStruct.Pin 	= LED1_PIN;							/*选择要控制的GPIO引脚*/	

	/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
//	HAL_GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStruct);	


#if USE_INT_KEY		/* 按键使用中断的方式 */
	
	GPIO_InitStruct.Pin = KEY1_PIN; 			/*选择按键的引脚*/	
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING; 	/*设置引脚为下降沿触发*/
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;						/*设置引脚上拉*/
	/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
	HAL_GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStruct);
	
//	GPIO_InitStruct.Pin = KEY2_PIN; 			/*选择按键的引脚*/
//	/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
//	HAL_GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStruct); 

  /* 中断配置 */
  HAL_NVIC_SetPriority(KEY1_INT_EXTI_IRQn, 7, 0);
  HAL_NVIC_EnableIRQ(KEY1_INT_EXTI_IRQn);

//  HAL_NVIC_SetPriority(KEY2_INT_EXTI_IRQn, 7, 0);
//  HAL_NVIC_EnableIRQ(KEY2_INT_EXTI_IRQn);
	
#else							/* 按键使用任务方式 */

	GPIO_InitStruct.Pin = KEY1_PIN; 							/*选择按键的引脚*/	
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT; 			/*设置引脚为输入模式*/
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;						/*设置引脚上拉*/
	/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
	HAL_GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStruct);
	
//	GPIO_InitStruct.Pin = KEY2_PIN; 							/*选择按键的引脚*/
//	/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
//	HAL_GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStruct);  
	

	
#endif


	LED1(ON);/*测试LED开启*/
//	LED2(OFF);/*测试LED开启*/


	return 0;
}



/*
*********************************************************************************
*	函 数 名: WX_Key_Scan
*	功能说明: 获取输入口的的电平状态
*	形    参: GPIOx,GPIO_Pin
			  GPIO口与Pin
*	返 回 值: KEY_ON:按键按下、KEY_OFF:按键未按下
*********************************************************************************
*/

uint8_t WX_Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
	/*检测是否有按键按下 */
	if(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == KEY_ON )  
	{	 
		/*等待按键释放 */
		while(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == KEY_ON);   
		return 	KEY_ON;	 
	}
	else
		return KEY_OFF;
}

