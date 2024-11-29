/**
  ******************************************************************
  * @file    driver_gpio.h
  * @author  QWX
  * @version V1.0
  * @date    2022-04-02
  * @brief   板载GPIO口的使用
  ******************************************************************
  */
#ifndef __DRIVER_GPIO_H_
#define __DRIVER_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"



/* 按键使用中断的方式 */
#define USE_INT_KEY  	1


//函数声明
/*******************************************************/

int WX_GPIO_Init(void);


uint8_t WX_Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);









#ifdef __cplusplus
}
#endif

#endif
