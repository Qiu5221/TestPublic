/**
  ******************************************************************
  * @file    app_gpio.c
  * @author  QWX
  * @version V1.0
  * @date    2022-04-02
  * @brief   ����GPIO�ڵ�ʹ��
  ******************************************************************
  */
#include "driver_gpio.h"        





/*
*********************************************************************************************************
*	�� �� ��: MX_GPIO_Init
*	����˵��: �弶���ų�ʼ��
*	��    ��: ��
*	�� �� ֵ: 0��ʾ�ɹ�������ֵ����main.h�к�������ֵ�Ķ���
*********************************************************************************************************
*/
int WX_GPIO_Init(void)
{
	HAL_Init();
	
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	/* �ж����ȼ����� */
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	
	/** Configure pins
			 PC14-OSC32_IN (OSC32_IN)   ------> RCC_OSC32_IN
			 PC15-OSC32_OUT (OSC32_OUT)   ------> RCC_OSC32_OUT
			 PH0-OSC_IN (PH0)   ------> RCC_OSC_IN
			 PH1-OSC_OUT (PH1)   ------> RCC_OSC_OUT
	*/

  /* �ⲿʱ��GPIOH��ʹ�ܣ��ⲿ����ʹ�ã� */
  __HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	/* ʱ������ */
	LED1_GPIO_CLK_ENABLE();												/*����LED��ص�GPIO����ʱ��*/
//	LED2_GPIO_CLK_ENABLE();												/*����LED��ص�GPIO����ʱ��*/
	KEY1_GPIO_CLK_ENABLE();
//	KEY2_GPIO_CLK_ENABLE();
//	KEY3_GPIO_CLK_ENABLE();												/*��������GPIO�ڵ�ʱ��*/

	/* �˿����� */
	GPIO_InitStruct.Pin 	= LED1_PIN;							/*ѡ��Ҫ���Ƶ�GPIO����*/	
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;  /*�������ŵ��������Ϊ�������*/
	GPIO_InitStruct.Pull  = GPIO_PULLUP;					/*��������Ϊ����ģʽ*/
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; /*������������Ϊ���� */   

	/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
	HAL_GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStruct);	

	//GPIO_InitStruct.Pin 	= LED1_PIN;							/*ѡ��Ҫ���Ƶ�GPIO����*/	

	/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
//	HAL_GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStruct);	


#if USE_INT_KEY		/* ����ʹ���жϵķ�ʽ */
	
	GPIO_InitStruct.Pin = KEY1_PIN; 			/*ѡ�񰴼�������*/	
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING; 	/*��������Ϊ�½��ش���*/
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;						/*������������*/
	/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
	HAL_GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStruct);
	
//	GPIO_InitStruct.Pin = KEY2_PIN; 			/*ѡ�񰴼�������*/
//	/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
//	HAL_GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStruct); 

  /* �ж����� */
  HAL_NVIC_SetPriority(KEY1_INT_EXTI_IRQn, 7, 0);
  HAL_NVIC_EnableIRQ(KEY1_INT_EXTI_IRQn);

//  HAL_NVIC_SetPriority(KEY2_INT_EXTI_IRQn, 7, 0);
//  HAL_NVIC_EnableIRQ(KEY2_INT_EXTI_IRQn);
	
#else							/* ����ʹ������ʽ */

	GPIO_InitStruct.Pin = KEY1_PIN; 							/*ѡ�񰴼�������*/	
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT; 			/*��������Ϊ����ģʽ*/
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;						/*������������*/
	/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
	HAL_GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStruct);
	
//	GPIO_InitStruct.Pin = KEY2_PIN; 							/*ѡ�񰴼�������*/
//	/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
//	HAL_GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStruct);  
	

	
#endif


	LED1(ON);/*����LED����*/
//	LED2(OFF);/*����LED����*/


	return 0;
}



/*
*********************************************************************************
*	�� �� ��: WX_Key_Scan
*	����˵��: ��ȡ����ڵĵĵ�ƽ״̬
*	��    ��: GPIOx,GPIO_Pin
			  GPIO����Pin
*	�� �� ֵ: KEY_ON:�������¡�KEY_OFF:����δ����
*********************************************************************************
*/

uint8_t WX_Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
	/*����Ƿ��а������� */
	if(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == KEY_ON )  
	{	 
		/*�ȴ������ͷ� */
		while(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == KEY_ON);   
		return 	KEY_ON;	 
	}
	else
		return KEY_OFF;
}

