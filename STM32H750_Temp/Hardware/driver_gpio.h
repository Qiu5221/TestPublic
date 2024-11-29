/**
  ******************************************************************
  * @file    driver_gpio.h
  * @author  QWX
  * @version V1.0
  * @date    2022-04-02
  * @brief   ����GPIO�ڵ�ʹ��
  ******************************************************************
  */
#ifndef __DRIVER_GPIO_H_
#define __DRIVER_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"



/* ����ʹ���жϵķ�ʽ */
#define USE_INT_KEY  	1


//��������
/*******************************************************/

int WX_GPIO_Init(void);


uint8_t WX_Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);









#ifdef __cplusplus
}
#endif

#endif
