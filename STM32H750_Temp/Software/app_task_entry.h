/**
  ******************************************************************
  * @file    app_task_entry.h
  * @author  QWX
  * @version V1.0
  * @date    2022-04-02
  * @brief   FreeRTOS ��������
  ******************************************************************
  */
#ifndef __APP_TASK_ENTRY_H_
#define __APP_TASK_ENTRY_H_

#include "main.h"


//#include "core_delay.h"   
#include "app_debug.h"   

#include <limits.h>
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"			//�ź���


int WX_Task_Create(void);


#endif
