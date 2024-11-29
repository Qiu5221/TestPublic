
#include "main.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"




/* Tick ���Ķ�ʱ���жϺ��� */
extern void xPortSysTickHandler( void );


/* ��Ϣ���о�� ����*/
extern QueueHandle_t Test_Queue_Handle;

void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
//void SVC_Handler(void)
//{
//  /* USER CODE BEGIN SVCall_IRQn 0 */

//  /* USER CODE END SVCall_IRQn 0 */
//  /* USER CODE BEGIN SVCall_IRQn 1 */

//  /* USER CODE END SVCall_IRQn 1 */
//}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
//void PendSV_Handler(void)
//{
//  /* USER CODE BEGIN PendSV_IRQn 0 */

//  /* USER CODE END PendSV_IRQn 0 */
//  /* USER CODE BEGIN PendSV_IRQn 1 */

//  /* USER CODE END PendSV_IRQn 1 */
//}

/**
  * @brief This function handles System tick timer.
  */

void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */
#if (INCLUDE_xTaskGetSchedulerState == 1)
	if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
	{
#endif
		xPortSysTickHandler();
#if (INCLUDE_xTaskGetSchedulerState == 1)
	}
#endif
  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32H7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32h7xx.s).                    */
/******************************************************************************/

/* USER CODE BEGIN 1 */

/* ����1 �жϷ�����*/
void KEY1_IRQHandler(void)
{
	static uint32_t send_data1 = 1;
	
	/* ��ӵ�����������������ȼ����� ��ֵ����ΪpdTRUE
		 Ȼ���˳��ж�ǰ�����������л���ȥִ�����ȼ����ߵ�����	*/
	BaseType_t pxHigherPriorityTaskWoken;
	
	/* �ٽ�η���ֵ */
	uint32_t ulReturn;
	
	/* �����ٽ������ٽ�������Ƕ��,���жϱ��� */
	ulReturn = taskENTER_CRITICAL_FROM_ISR();
	{
		
		/* ��ȡ�жϱ�־ */
		if(__HAL_GPIO_EXTI_GET_IT(KEY1_PIN) != RESET)
		{
			/* ��Send_data1���ͣ�д�룩��Ϣ���� */
			xQueueSendFromISR( Test_Queue_Handle,						/* ��Ϣ���еľ�� */
												 &send_data1,									/* ���͵���Ϣ���� */
												 &pxHigherPriorityTaskWoken); /* V7.30�汾����Ϊ��ѡ����������ΪNULL */
			
			/* �����Ҫ�Ļ�����һ�������л� */
			portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);
			
			/* ����жϱ�־bit */
			__HAL_GPIO_EXTI_CLEAR_IT(KEY1_PIN);
		}

	}
	taskEXIT_CRITICAL_FROM_ISR(ulReturn);/* �˳��ٽ��� */
}



/* USER CODE END 1 */

