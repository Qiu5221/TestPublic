
#include "main.h"

#include "FreeRTOS.h"					/* FreeRTOS ͷ�ļ� 		*/
#include "task.h"							/* FreeRTOS ���� 			*/
#include "queue.h"						/* FreeRTOS ��Ϣ���� 	*/
#include "semphr.h"						/* FreeRTOS �ź��� 		*/
#include "event_groups.h"		  /* FreeRTOS �¼��� 		*/

#include "driver_sysclk.h"
#include "driver_gpio.h"  
#include "app_debug.h"  

#include "app_task_entry.h"  
 




//uint8_t Test[] = "�����Ŷ�����\r\n";

/***************************************************************
*	�� �� ��: int main(void)
*	����˵��: ������
*	��    ��: ��
*	�� �� ֵ: ��
****************************************************************/
int main(void)
{
	/* ϵͳʱ������ */
  WX_SysClk_Init();
	/* ϵͳGPIO���� */
  WX_GPIO_Init();
	/* ϵͳDEBUG���� */
  WX_LPUART1_Init();
	/* FreeRTOS�������� */
	WX_Task_Create();
	
  for (;;)
	{
		/* PCָ����Զִ�в������� */
	}
}


