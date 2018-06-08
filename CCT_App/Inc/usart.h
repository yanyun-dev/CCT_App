/**
  ******************************************************************************
  * File Name          : USART.h
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __usart_H
#define __usart_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "main.h"

/* USER CODE BEGIN Includes */
#include "string.h"
/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

/* USER CODE BEGIN Private defines */
#define MAIN_COMM_SERIAL (&huart1)
#define DEBUG_COMM_SERIAL (&huart2)
	 
	 
#define MainComm_SendString(string) do { \
	uint8_t* _s = string; \
	while(*_s++ != '\0') { \
		HAL_USART_Transmit_IT(MAIN_COMM_SERIAL, _s, 1, 0); \
	} \
}while(0)

#define DebugComm_SendString(string) do { \
	uint8_t* _s = string; \
	while(*_s++ != '\0') { \
		HAL_UART_Transmit(DEBUG_COMM_SERIAL, _s, 1, 0); \
	} \
}while(0)

#define MainComm_SendData(pData, size) HAL_UART_Transmit_IT(MAIN_COMM_SERIAL, pData, size, 0)
#define DebugComm_SendData(pData, size) HAL_UART_Transmit(DEBUG_COMM_SERIAL, pData, size, 0)

#define MainComm_PutChar(c) HAL_UART_Transmit_IT(MAIN_COMM_SERIAL, &c, 1, 0)
#define MainComm_GetChar(pc) HAL_UART_Receive_IT(MAIN_COMM_SERIAL, pc, 1, 0)

#define DebugComm_PutChar(c) HAL_UART_Transmit(DEBUG_COMM_SERIAL, &c, 1, 0)
#define DebugComm_GetChar(pc) HAL_UART_Receive(DEBUG_COMM_SERIAL, pc, 1, 0)

/* USER CODE END Private defines */

extern void Error_Handler(void);

void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void iprintf(char *fmt,...) ;
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
