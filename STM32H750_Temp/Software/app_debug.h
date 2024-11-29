/**
  ******************************************************************
  * @file    app_debug.h
  * @author  QWX
  * @version V1.0
  * @date    2022-04-02
  * @brief   ���ڵ���DEBUGʹ��
  ******************************************************************
  */
#ifndef __APP_DEBUG_H_
#define __APP_DEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "main.h"

#include <stdio.h>
#include <string.h>


//�ṹ������
/*******************************************************/
extern UART_HandleTypeDef hlpuart1;


//��������
/*******************************************************/

void WX_LPUART1_Init(void);


void Uart_SendString(uint8_t *str);






/* ʹ��DEBUG���� */
#define MY_DEBUG 		1

/* ��װ���Զ���ĺ�����USE_Micro */
#ifdef MY_DEBUG  
	#define MY_DEBUGF(message)
#else    
	#define MY_DEBUGF(message)   UARTprintf message
#endif

/* ֱ�Ӷ�printf���з�װ */
#if MY_DEBUG
	#define DEBUG(format,...) printf("File: "__FILE__", Line: %05d: "format"\n", __LINE__, ##__VA_ARGS__) 												 
#else 
	#define DEBUG(format,...)
#endif  





#ifdef __cplusplus
}
#endif

#endif
