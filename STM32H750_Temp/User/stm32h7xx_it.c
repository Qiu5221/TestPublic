
#include "main.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"




/* Tick 节拍定时器中断函数 */
extern void xPortSysTickHandler( void );


/* 消息队列句柄 引用*/
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

/* 按键1 中断服务函数*/
void KEY1_IRQHandler(void)
{
	static uint32_t send_data1 = 1;
	
	/* 入队导致任务解锁，且优先级更高 此值设置为pdTRUE
		 然后退出中断前进行上下文切换，去执行优先级更高的任务	*/
	BaseType_t pxHigherPriorityTaskWoken;
	
	/* 临界段返回值 */
	uint32_t ulReturn;
	
	/* 进入临界区，临界区可以嵌套,带中断保护 */
	ulReturn = taskENTER_CRITICAL_FROM_ISR();
	{
		
		/* 获取中断标志 */
		if(__HAL_GPIO_EXTI_GET_IT(KEY1_PIN) != RESET)
		{
			/* 将Send_data1发送（写入）消息队列 */
			xQueueSendFromISR( Test_Queue_Handle,						/* 消息队列的句柄 */
												 &send_data1,									/* 发送的消息内容 */
												 &pxHigherPriorityTaskWoken); /* V7.30版本后作为可选参数可设置为NULL */
			
			/* 如果需要的话进行一次任务切换 */
			portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);
			
			/* 清除中断标志bit */
			__HAL_GPIO_EXTI_CLEAR_IT(KEY1_PIN);
		}

	}
	taskEXIT_CRITICAL_FROM_ISR(ulReturn);/* 退出临界区 */
}



/* USER CODE END 1 */

