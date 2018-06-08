/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
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
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define DebugCommTx_Pin GPIO_PIN_2
#define DebugCommTx_GPIO_Port GPIOA
#define DebugCommRx_Pin GPIO_PIN_3
#define DebugCommRx_GPIO_Port GPIOA
#define S1_Pin GPIO_PIN_4
#define S1_GPIO_Port GPIOA
#define S2_Pin GPIO_PIN_5
#define S2_GPIO_Port GPIOA
#define S3_Pin GPIO_PIN_6
#define S3_GPIO_Port GPIOA
#define S4_Pin GPIO_PIN_7
#define S4_GPIO_Port GPIOA
#define S5_Pin GPIO_PIN_0
#define S5_GPIO_Port GPIOB
#define S6_Pin GPIO_PIN_1
#define S6_GPIO_Port GPIOB
#define S7_Pin GPIO_PIN_2
#define S7_GPIO_Port GPIOB
#define S8_Pin GPIO_PIN_10
#define S8_GPIO_Port GPIOB
#define S9_Pin GPIO_PIN_11
#define S9_GPIO_Port GPIOB
#define CCT_L_Pin GPIO_PIN_13
#define CCT_L_GPIO_Port GPIOB
#define CCT_H_Pin GPIO_PIN_8
#define CCT_H_GPIO_Port GPIOA
#define MainCommTX_Pin GPIO_PIN_9
#define MainCommTX_GPIO_Port GPIOA
#define MainCommRx_Pin GPIO_PIN_10
#define MainCommRx_GPIO_Port GPIOA
#define Brightness_Pin GPIO_PIN_6
#define Brightness_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define S1_PosMask (0x0)
#define S2_PosMask (0x1)
#define S3_PosMask (0x2)
#define S4_PosMask (0x3)
#define S5_PosMask (0x4)
#define S6_PosMask (0x5)
#define S7_PosMask (0x6)
#define S8_PosMask (0x7)
#define S9_PosMask (0x8)
/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
