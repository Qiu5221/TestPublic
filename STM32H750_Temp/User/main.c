
#include "main.h"

#include "FreeRTOS.h"					/* FreeRTOS 头文件 		*/
#include "task.h"							/* FreeRTOS 任务 			*/
#include "queue.h"						/* FreeRTOS 消息队列 	*/
#include "semphr.h"						/* FreeRTOS 信号量 		*/
#include "event_groups.h"		  /* FreeRTOS 事件组 		*/

#include "driver_sysclk.h"
#include "driver_gpio.h"  
#include "app_debug.h"  

#include "app_task_entry.h"  
 




//uint8_t Test[] = "桥西桥东测试\r\n";

/***************************************************************
*	函 数 名: int main(void)
*	功能说明: 主函数
*	形    参: 无
*	返 回 值: 无
****************************************************************/
int main(void)
{
	/* 系统时钟配置 */
  WX_SysClk_Init();
	/* 系统GPIO配置 */
  WX_GPIO_Init();
	/* 系统DEBUG配置 */
  WX_LPUART1_Init();
	/* FreeRTOS创建任务 */
	WX_Task_Create();
	
  for (;;)
	{
		/* PC指针永远执行不到这里 */
	}
}


