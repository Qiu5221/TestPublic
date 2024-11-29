/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#include "stm32h7xx.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */
//LED���Ŷ���
/*******************************************************/
//GPIOH15
#define LED1_PIN                  GPIO_PIN_3                 
#define LED1_GPIO_PORT            GPIOE                      
#define LED1_GPIO_CLK_ENABLE()    __GPIOE_CLK_ENABLE()

//GPIOC15
//#define LED2_PIN                  GPIO_PIN_14                 
//#define LED2_GPIO_PORT            GPIOE                      
//#define LED2_GPIO_CLK_ENABLE()    __GPIOE_CLK_ENABLE()

/** ����LED������ĺ꣬
	* LED�͵�ƽ��������ON=0��OFF=1
	* ��LED�ߵ�ƽ�����Ѻ����ó�ON=1 ��OFF=0 ����
	*/
#define ON  GPIO_PIN_SET
#define OFF GPIO_PIN_RESET

/* ���κ꣬��������������һ��ʹ�� */
#define LED1(a)	HAL_GPIO_WritePin(LED1_GPIO_PORT,LED1_PIN,a)
//#define LED2(a)	HAL_GPIO_WritePin(LED2_GPIO_PORT,LED2_PIN,a)

/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define digitalToggle(p,i)		{p->ODR ^=i;}						  //�����ת״̬

/* �������IO�ĺ� */
#define LED1_TOGGLE		digitalToggle(LED1_GPIO_PORT,LED1_PIN)
//#define LED2_TOGGLE		digitalToggle(LED2_GPIO_PORT,LED2_PIN)



//KEY���Ŷ���
/*******************************************************/
#define KEY1_PIN                  GPIO_PIN_13                 
#define KEY1_GPIO_PORT            GPIOC                      
#define KEY1_GPIO_CLK_ENABLE()    __GPIOC_CLK_ENABLE()

//#define KEY2_PIN                  GPIO_PIN_14                 
//#define KEY2_GPIO_PORT            GPIOC                      
//#define KEY2_GPIO_CLK_ENABLE()    __GPIOC_CLK_ENABLE()


//�����ж϶���
/*******************************************************/
#define KEY1_INT_EXTI_IRQn							EXTI15_10_IRQn						/* stm32h743.h�ļ��� */
#define KEY1_IRQHandler									EXTI15_10_IRQHandler			/* .s�ļ��� */

//#define KEY2_INT_EXTI_IRQn							EXTI15_10_IRQn						/* stm32h743.h�ļ��� */
//#define KEY2_IRQHandler									EXTI15_10_IRQHandler			/* .s�ļ��� */
/*******************************************************/


 /** �������±��ú�
	* ��������Ϊ�ߵ�ƽ������ KEY_ON=1�� KEY_OFF=0
	* ����������Ϊ�͵�ƽ���Ѻ����ó�KEY_ON=0 ��KEY_OFF=1 ����
	*/
#define KEY_ON		1
#define KEY_OFF		0

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
