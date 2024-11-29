/**
  ******************************************************************
  * @file    app_task_entry.c
  * @author  QWX
  * @version V1.0
  * @date    2024-11-29
  * @brief   FreeRTOS 创建任务
  ******************************************************************
  */
#include "app_task_entry.h"    

/* 创建AppTaskCreate任务句柄 */
static TaskHandle_t AppTaskCreate_Handle = NULL;


/* LED与KEY任务句柄 */
static TaskHandle_t LED_Task_Handle = NULL;
//static TaskHandle_t KEY_Task_Handle = NULL;
//哈哈哈


/********************************** 内核对象句柄 *********************************/
/*
 * 信号量，消息队列，事件标志组，软件定时器这些都属于内核的对象，要想使用这些内核
 * 对象，必须先创建，创建成功之后会返回一个相应的句柄。实际上就是一个指针，后续我
 * 们就可以通过这个句柄操作这些内核对象。
 *
 * 内核对象说白了就是一种全局的数据结构，通过这些数据结构我们可以实现任务间的通信，
 * 任务间的事件同步等各种功能。至于这些功能的实现我们是通过调用这些内核对象的函数
 * 来完成的
 * 
 */

 
/* 消息队列句柄 */
QueueHandle_t Test_Queue_Handle = NULL;
/* 二值信号量句柄 */
SemaphoreHandle_t Test_BinarySem_Handle = NULL;


/******************************* 全局变量声明 ************************************/
/*
 * 当我们在写应用程序的时候，可能需要用到一些全局变量。
 */


/******************************* 宏定义 ************************************/
/*
 * 当我们在写应用程序的时候，可能需要用到一些宏定义。
 */

#define QUEUE_LEN			4		/* 队列的长度，最大可包含多少个消息 */
#define QUEUE_SIZE		4		/* 队列中每个消息大小（字节） */

static void AppTaskCreate( void);






/**********************************************************************
  * @ 函数名  ： LED_Task
  * @ 功能说明： LED_Task 任务主体
  * @ 参数    ：   
  * @ 返回值  ： 无
  ********************************************************************/
static void LED_Task( void* parameter)
{
	BaseType_t xReturn	= pdTRUE;		/* 定义一个创建信息返回值，默认为 pdTRUE */
	uint32_t rec_queue =1;
	
	for(;;)
	{
		/* 接收（读取）消息队列信息 */
		xReturn = xQueueReceive( Test_Queue_Handle,		/* 消息队列的句柄 */
														 &rec_queue,					/* 发送的消息内容 */
														 portMAX_DELAY);			/* 超时时间一直等 */
		if( pdTRUE == xReturn)
		{
			DEBUG("触发中断的是按键%d\r\n",rec_queue);
		}
		else
		{
			DEBUG("消息队列接收:ERROR\r\n");
		}
		if(rec_queue == 1)
		{
			LED1_TOGGLE;/* LED1状态反转 */
		}
//		else if(rec_queue == 2)
//		{
//			LED2_TOGGLE;
//		}
		//vTaskDelay(50);	/* 延时20个tick */
	}
}

/**********************************************************************
  * @ 函数名  ： KEY_Task
  * @ 功能说明： KEY_Task 任务主体
  * @ 参数    ：   
  * @ 返回值  ： 无
  ********************************************************************/
//static void KEY_Task( void* parameter)
//{
////	BaseType_t xRetrrn = pdTRUE;	/* 定义一个创建信息返回值，默认为 pdTRUE */
//	

//	for(;;)
//	{
//		/*检测是否有按键按下 */
//		if(HAL_GPIO_ReadPin(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON )  
//		{	 
//			/*触发第一个事件 */

//			DEBUG("按键触发\r\n");
//		}
////		else if(HAL_GPIO_ReadPin(KEY2_GPIO_PORT,KEY2_PIN) == KEY_ON )
////		{
////			/*触发第二个事件 */
////			
////		}

//		vTaskDelay(20);	/* 延时2个tick */
//	}
//}




/***********************************************************************
  * @ 函数名  ： AppTaskCreate
  * @ 功能说明： 为了方便管理，所有的任务创建函数都放在这个函数里面
  * @ 参数    ： 无  
  * @ 返回值  ： 无
  **********************************************************************/
static void AppTaskCreate( void)
{
	BaseType_t xReturn = pdTRUE;/* 定义一个返回值，默认为pdTRUE */

	DEBUG("系统CPU时钟:%dHz\r\n",HAL_RCC_GetSysClockFreq());
	
	taskENTER_CRITICAL();/* 进入临界区 */
	{
		/* 创建 消息队列 */
		Test_Queue_Handle = xQueueCreate( (UBaseType_t ) QUEUE_LEN,		/* 消息队列的长度 */
																			(UBaseType_t ) QUEUE_SIZE);	/* 消息的大小 */
		if(NULL != Test_Queue_Handle)
		{
			/* 消息队列 创建成功*/
			DEBUG("消息队列 创建成功\r\n");
		}
		/* 创建 二值信号量 */
		Test_BinarySem_Handle = xSemaphoreCreateBinary();
		if(NULL != Test_BinarySem_Handle)
		{
			/* 二值信号量 创建成功*/
			DEBUG("二值信号量 创建成功\r\n");
		}
		/* 创建 LED 任务 */
		xReturn = xTaskCreate( (TaskFunction_t) LED_Task,         //LED_Task 任务函数
													 (const char*   ) "LED_Task",       //任务名称
													 (uint32_t      ) 512,              //任务堆栈大小
													 (void *        ) NULL,             //传递给任务函数的参数
													 (UBaseType_t   ) 2,                //任务优先级
													 (TaskHandle_t  ) &LED_Task_Handle);//任务控制块指针
		if(pdTRUE == xReturn)		/* 创建成功 */
		{
			//NULL;
			DEBUG("LED Task 创建成功\r\n");
		}
													 
//		/* 创建 KEY 任务 */
//		xReturn = xTaskCreate( (TaskFunction_t) KEY_Task,         //KEY_Task 任务函数
//													 (const char*   ) "KEY_Task",       //任务名称
//													 (uint32_t      ) 512,              //任务堆栈大小
//													 (void *        ) NULL,             //传递给任务函数的参数
//													 (UBaseType_t   ) 3,                //任务优先级
//													 (TaskHandle_t  ) &KEY_Task_Handle);//任务控制块指针
//		if(pdTRUE == xReturn)		/* 创建成功 */
//		{
//			//NULL;
//			DEBUG("KEY Task 创建成功\r\n");
//		}
		
		vTaskDelete(AppTaskCreate_Handle);/* 删除AppTaskCreate任务 */
		
	}
	taskEXIT_CRITICAL();/* 退出临界区 */
}



int WX_Task_Create(void)
{
	BaseType_t xReturn = pdTRUE;/* 定义一个创建信息返回值，默认为 pdTRUE */
	
	/* 创建 AppTaskCreate 任务 */
	xReturn = xTaskCreate(	(TaskFunction_t	)AppTaskCreate,			//任务函数
													(const char*		)"AppTaskCreate",		//任务名称
													(uint32_t				) 512,							//任务堆栈大小
													(void * 				) NULL,							//传递给任务函数的参数
													(UBaseType_t		) 1,								//任务优先级
													(TaskHandle_t * ) &AppTaskCreate_Handle);//任务控制块指针
	if(pdTRUE == xReturn)/* 创建成功 */
		vTaskStartScheduler();				/* 启动任务，开启调度 */
	else
		return -1;
	return 0;
}


