/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

extern UART_HandleTypeDef huart2;

/* USER CODE BEGIN Private defines */
#define REC_LENGTH  1
#define MAX_REC_LENGTH  1024 
extern unsigned char UART1_Rx_Buf[MAX_REC_LENGTH] ; 	//USART1
extern unsigned char UART1_Rx_flg ;                   //USART1
extern unsigned int  UART1_Rx_cnt ;                   //USART1
extern unsigned char UART1_temp[REC_LENGTH] ;       	//USART1
extern unsigned char UART2_Rx_Buf[MAX_REC_LENGTH] ; 	//USART1
extern unsigned char UART2_Rx_flg ;                   //USART1
extern unsigned int  UART2_Rx_cnt ;                   //USART1
extern unsigned char UART2_temp[REC_LENGTH] ;       	//USART1





void GetOneByte(uint8_t data);
static void Data_Anl(uint8_t *data, uint8_t len);
void send_right(float right_speed);
void send_left(float right_speed);

/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

