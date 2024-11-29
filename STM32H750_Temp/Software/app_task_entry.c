/**
  ******************************************************************
  * @file    app_task_entry.c
  * @author  QWX
  * @version V1.0
  * @date    2024-11-29
  * @brief   FreeRTOS ��������
  ******************************************************************
  */
#include "app_task_entry.h"    

/* ����AppTaskCreate������ */
static TaskHandle_t AppTaskCreate_Handle = NULL;


/* LED��KEY������ */
static TaskHandle_t LED_Task_Handle = NULL;
//static TaskHandle_t KEY_Task_Handle = NULL;
//������


/********************************** �ں˶����� *********************************/
/*
 * �ź�������Ϣ���У��¼���־�飬�����ʱ����Щ�������ں˵Ķ���Ҫ��ʹ����Щ�ں�
 * ���󣬱����ȴ����������ɹ�֮��᷵��һ����Ӧ�ľ����ʵ���Ͼ���һ��ָ�룬������
 * �ǾͿ���ͨ��������������Щ�ں˶���
 *
 * �ں˶���˵���˾���һ��ȫ�ֵ����ݽṹ��ͨ����Щ���ݽṹ���ǿ���ʵ��������ͨ�ţ�
 * �������¼�ͬ���ȸ��ֹ��ܡ�������Щ���ܵ�ʵ��������ͨ��������Щ�ں˶���ĺ���
 * ����ɵ�
 * 
 */

 
/* ��Ϣ���о�� */
QueueHandle_t Test_Queue_Handle = NULL;
/* ��ֵ�ź������ */
SemaphoreHandle_t Test_BinarySem_Handle = NULL;


/******************************* ȫ�ֱ������� ************************************/
/*
 * ��������дӦ�ó����ʱ�򣬿�����Ҫ�õ�һЩȫ�ֱ�����
 */


/******************************* �궨�� ************************************/
/*
 * ��������дӦ�ó����ʱ�򣬿�����Ҫ�õ�һЩ�궨�塣
 */

#define QUEUE_LEN			4		/* ���еĳ��ȣ����ɰ������ٸ���Ϣ */
#define QUEUE_SIZE		4		/* ������ÿ����Ϣ��С���ֽڣ� */

static void AppTaskCreate( void);






/**********************************************************************
  * @ ������  �� LED_Task
  * @ ����˵���� LED_Task ��������
  * @ ����    ��   
  * @ ����ֵ  �� ��
  ********************************************************************/
static void LED_Task( void* parameter)
{
	BaseType_t xReturn	= pdTRUE;		/* ����һ��������Ϣ����ֵ��Ĭ��Ϊ pdTRUE */
	uint32_t rec_queue =1;
	
	for(;;)
	{
		/* ���գ���ȡ����Ϣ������Ϣ */
		xReturn = xQueueReceive( Test_Queue_Handle,		/* ��Ϣ���еľ�� */
														 &rec_queue,					/* ���͵���Ϣ���� */
														 portMAX_DELAY);			/* ��ʱʱ��һֱ�� */
		if( pdTRUE == xReturn)
		{
			DEBUG("�����жϵ��ǰ���%d\r\n",rec_queue);
		}
		else
		{
			DEBUG("��Ϣ���н���:ERROR\r\n");
		}
		if(rec_queue == 1)
		{
			LED1_TOGGLE;/* LED1״̬��ת */
		}
//		else if(rec_queue == 2)
//		{
//			LED2_TOGGLE;
//		}
		//vTaskDelay(50);	/* ��ʱ20��tick */
	}
}

/**********************************************************************
  * @ ������  �� KEY_Task
  * @ ����˵���� KEY_Task ��������
  * @ ����    ��   
  * @ ����ֵ  �� ��
  ********************************************************************/
//static void KEY_Task( void* parameter)
//{
////	BaseType_t xRetrrn = pdTRUE;	/* ����һ��������Ϣ����ֵ��Ĭ��Ϊ pdTRUE */
//	

//	for(;;)
//	{
//		/*����Ƿ��а������� */
//		if(HAL_GPIO_ReadPin(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON )  
//		{	 
//			/*������һ���¼� */

//			DEBUG("��������\r\n");
//		}
////		else if(HAL_GPIO_ReadPin(KEY2_GPIO_PORT,KEY2_PIN) == KEY_ON )
////		{
////			/*�����ڶ����¼� */
////			
////		}

//		vTaskDelay(20);	/* ��ʱ2��tick */
//	}
//}




/***********************************************************************
  * @ ������  �� AppTaskCreate
  * @ ����˵���� Ϊ�˷���������е����񴴽����������������������
  * @ ����    �� ��  
  * @ ����ֵ  �� ��
  **********************************************************************/
static void AppTaskCreate( void)
{
	BaseType_t xReturn = pdTRUE;/* ����һ������ֵ��Ĭ��ΪpdTRUE */

	DEBUG("ϵͳCPUʱ��:%dHz\r\n",HAL_RCC_GetSysClockFreq());
	
	taskENTER_CRITICAL();/* �����ٽ��� */
	{
		/* ���� ��Ϣ���� */
		Test_Queue_Handle = xQueueCreate( (UBaseType_t ) QUEUE_LEN,		/* ��Ϣ���еĳ��� */
																			(UBaseType_t ) QUEUE_SIZE);	/* ��Ϣ�Ĵ�С */
		if(NULL != Test_Queue_Handle)
		{
			/* ��Ϣ���� �����ɹ�*/
			DEBUG("��Ϣ���� �����ɹ�\r\n");
		}
		/* ���� ��ֵ�ź��� */
		Test_BinarySem_Handle = xSemaphoreCreateBinary();
		if(NULL != Test_BinarySem_Handle)
		{
			/* ��ֵ�ź��� �����ɹ�*/
			DEBUG("��ֵ�ź��� �����ɹ�\r\n");
		}
		/* ���� LED ���� */
		xReturn = xTaskCreate( (TaskFunction_t) LED_Task,         //LED_Task ������
													 (const char*   ) "LED_Task",       //��������
													 (uint32_t      ) 512,              //�����ջ��С
													 (void *        ) NULL,             //���ݸ��������Ĳ���
													 (UBaseType_t   ) 2,                //�������ȼ�
													 (TaskHandle_t  ) &LED_Task_Handle);//������ƿ�ָ��
		if(pdTRUE == xReturn)		/* �����ɹ� */
		{
			//NULL;
			DEBUG("LED Task �����ɹ�\r\n");
		}
													 
//		/* ���� KEY ���� */
//		xReturn = xTaskCreate( (TaskFunction_t) KEY_Task,         //KEY_Task ������
//													 (const char*   ) "KEY_Task",       //��������
//													 (uint32_t      ) 512,              //�����ջ��С
//													 (void *        ) NULL,             //���ݸ��������Ĳ���
//													 (UBaseType_t   ) 3,                //�������ȼ�
//													 (TaskHandle_t  ) &KEY_Task_Handle);//������ƿ�ָ��
//		if(pdTRUE == xReturn)		/* �����ɹ� */
//		{
//			//NULL;
//			DEBUG("KEY Task �����ɹ�\r\n");
//		}
		
		vTaskDelete(AppTaskCreate_Handle);/* ɾ��AppTaskCreate���� */
		
	}
	taskEXIT_CRITICAL();/* �˳��ٽ��� */
}



int WX_Task_Create(void)
{
	BaseType_t xReturn = pdTRUE;/* ����һ��������Ϣ����ֵ��Ĭ��Ϊ pdTRUE */
	
	/* ���� AppTaskCreate ���� */
	xReturn = xTaskCreate(	(TaskFunction_t	)AppTaskCreate,			//������
													(const char*		)"AppTaskCreate",		//��������
													(uint32_t				) 512,							//�����ջ��С
													(void * 				) NULL,							//���ݸ��������Ĳ���
													(UBaseType_t		) 1,								//�������ȼ�
													(TaskHandle_t * ) &AppTaskCreate_Handle);//������ƿ�ָ��
	if(pdTRUE == xReturn)/* �����ɹ� */
		vTaskStartScheduler();				/* �������񣬿������� */
	else
		return -1;
	return 0;
}


