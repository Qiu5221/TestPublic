/**
  ******************************************************************
  * @file    app_debug.c
  * @author  QWX
  * @version V1.0
  * @date    2022-04-02
  * @brief   串口调试DEBUG使用
  ******************************************************************
  */
#include "app_debug.h"   



UART_HandleTypeDef hlpuart1;

/* LPUART1 init function */

void WX_LPUART1_Init(void)
{

  /* USER CODE BEGIN LPUART1_Init 0 */

  /* USER CODE END LPUART1_Init 0 */

  /* USER CODE BEGIN LPUART1_Init 1 */

  /* USER CODE END LPUART1_Init 1 */
  hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 115200;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  hlpuart1.FifoMode = UART_FIFOMODE_DISABLE;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&hlpuart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&hlpuart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LPUART1_Init 2 */

  /* USER CODE END LPUART1_Init 2 */

}



/*****************  发送字符串 **********************/
void Uart_SendString(uint8_t *str)
{
	unsigned int k=0;
  do 
  {
      HAL_UART_Transmit( &hlpuart1,(uint8_t *)(str + k) ,1,1000);
      k++;
  } while(*(str + k)!='\0');
}




/*
*********************************************************************************
*	功能说明: 两种方式支持printf
*********************************************************************************
*/

#if MY_DEBUG

//重定向c库函数printf到串口DEBUG_USART，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
	/* 发送一个字节数据到串口DEBUG_USART */
	HAL_UART_Transmit(&hlpuart1, (uint8_t *)&ch, 1, 1000);	
	
	return (ch);
}

///重定向c库函数scanf到串口DEBUG_USART，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
	int ch;
	HAL_UART_Receive(&hlpuart1, (uint8_t *)&ch, 1, 1000);	
	return (ch);
}

#else

#include <stdarg.h>      /*支持函数接收不定量参数*/  

/** 
* 简介:   一个简单的printf函数,支持\%c, \%d, \%p, \%s, \%u,\%x, and \%X. 
*/  
const char * const g_pcHex = "0123456789abcdef";  
void UARTprintf(const uint8_t *pcString, ...)  
{  
	uint32_t ulIdx;  
	uint32_t ulValue;       //保存从不定量参数堆栈中取出的数值型变量  
	uint32_t ulPos, ulCount;  
	uint32_t ulBase;        //保存进制基数,如十进制则为10,十六进制数则为16  
	uint32_t ulNeg;         //为1表示从变量为负数  
	uint8_t *pcStr;         //保存从不定量参数堆栈中取出的字符型变量  
	uint8_t pcBuf[32];      //保存数值型变量字符化后的字符  
	uint8_t cFill;          //'%08x'->不足8个字符用'0'填充,cFill='0';    
													//'%8x '->不足8个字符用空格填充,cFill=' '  
	va_list vaArgP;  

	va_start(vaArgP, pcString);  
	while(*pcString)  
	{  
		// 首先搜寻非%核字符串结束字符  
		for(ulIdx = 0; (pcString[ulIdx] != '%') && (pcString[ulIdx] != '\0'); ulIdx++)  
		{ }
		HAL_UART_Transmit(&hlpuart1, (uint8_t *)&pcString, ulIdx, 1000);	
		//UARTwrite(pcString, ulIdx);  

		pcString += ulIdx;  
		if(*pcString == '%')  
		{  
			pcString++;  

			ulCount = 0;  
			cFill = ' ';  
			again:  
			switch(*pcString++)  
			{  
				case '0': case '1': case '2': case '3': case '4':  
				case '5': case '6': case '7': case '8': case '9':  
				{  
					// 如果第一个数字为0, 则使用0做填充,则用空格填充)  
					if((pcString[-1] == '0') && (ulCount == 0))  
					{  
							cFill = '0';  
					}  
					ulCount *= 10;  
					ulCount += pcString[-1] - '0';  
					goto again;  
				}  
				case 'c':          
				{  
					ulValue = va_arg(vaArgP, unsigned long); 
					HAL_UART_Transmit(&hlpuart1, (uint8_t *)&ulValue, 1, 1000);	
					//UARTwrite((unsigned char *)&ulValue, 1);  
					break;  
				}  
				case 'd':     
				{  
					ulValue = va_arg(vaArgP, unsigned long);  
					ulPos = 0;  
						
					if((long)ulValue < 0)  
					{  
							ulValue = -(long)ulValue;  
							ulNeg = 1;  
					}  
					else  
					{  
							ulNeg = 0;  
					}  
					ulBase = 10;          
					goto convert;  
				}  
				case 's':  
				{  
					pcStr = va_arg(vaArgP, unsigned char *);  

					for(ulIdx = 0; pcStr[ulIdx] != '\0'; ulIdx++)  
					{  
					} 
					HAL_UART_Transmit(&hlpuart1, (uint8_t *)&pcStr, ulIdx, 1000);	
					//UARTwrite(pcStr, ulIdx);  

					if(ulCount > ulIdx)  
					{  
							ulCount -= ulIdx;  
							while(ulCount--)  
							{  
								HAL_UART_Transmit(&hlpuart1, (uint8_t *)" ", 1, 1000);	
								//UARTwrite(" ", 1);  
							}  
					}  
					break;  
				}  
				case 'u':  
				{  
					ulValue = va_arg(vaArgP, unsigned long);  
					ulPos = 0;  
					ulBase = 10;  
					ulNeg = 0;  
					goto convert;  
				}  
				case 'x': case 'X': case 'p':  
				{  
					ulValue = va_arg(vaArgP, unsigned long);  
					ulPos = 0;  
					ulBase = 16;  
					ulNeg = 0;  
					convert:   //将数值转换成字符  
					for(ulIdx = 1; (((ulIdx * ulBase) <= ulValue) &&(((ulIdx * ulBase) / ulBase) == ulIdx)); ulIdx *= ulBase, ulCount--)       
					{ }  
					if(ulNeg)  
					{  
						ulCount--;                        
					}  
					if(ulNeg && (cFill == '0'))  
					{  
						pcBuf[ulPos++] = '-';  
						ulNeg = 0;  
					}  
					if((ulCount > 1) && (ulCount < 16))  
					{  
						for(ulCount--; ulCount; ulCount--)  
						{  
							pcBuf[ulPos++] = cFill;  
						}  
					}  

					if(ulNeg)  
					{  
						pcBuf[ulPos++] = '-';  
					}  

					for(; ulIdx; ulIdx /= ulBase)  
					{  
						pcBuf[ulPos++] = g_pcHex[(ulValue / ulIdx) % ulBase]; 
					}
					HAL_UART_Transmit(&hlpuart1, (uint8_t *)pcBuf, ulPos, 1000);	
					//UARTwrite(pcBuf, ulPos);  
					break;  
				}  
				case '%':  
				{  
					HAL_UART_Transmit(&hlpuart1, (uint8_t *)(pcString - 1), 1, 1000);	
					//UARTwrite(pcString - 1, 1);                    
					break;  
				}  
				default:  
				{       
					HAL_UART_Transmit(&hlpuart1, (uint8_t *)"ERROR", 5, 1000);	
					//UARTwrite("ERROR", 5);                    
					break;  
				}  
			}  
		}  
	}  
	//可变参数处理结束  
	va_end(vaArgP);  
}

#endif




