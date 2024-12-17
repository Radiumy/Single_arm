/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
#include "stdio.h"
#include "control.h"
#include "main.h"
#include "stdint.h"
#include "stdlib.h"
/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */
HAL_UART_Receive_IT(&huart1,&UART1_temp[0],REC_LENGTH);
  /* USER CODE END USART1_Init 2 */

}
/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA10     ------> USART1_RX
    PB6     ------> USART1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA10     ------> USART1_RX
    PB6     ------> USART1_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_10);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */


unsigned char UART1_Rx_Buf[MAX_REC_LENGTH] = {0}; 
unsigned char UART1_Rx_flg = 0;                   
unsigned int  UART1_Rx_cnt = 0;                   
unsigned char UART1_temp[REC_LENGTH] = {0};       
unsigned char UART2_Rx_Buf[MAX_REC_LENGTH] = {0}; 
unsigned char UART2_Rx_flg = 0;                   
unsigned int  UART2_Rx_cnt = 0;                   
unsigned char UART2_temp[REC_LENGTH] = {0};

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance==USART1)
  {
   GetOneByte(UART1_temp[0]);
   HAL_UART_Receive_IT(&huart1,&UART1_temp[0],REC_LENGTH);
	 
  }
	if(huart->Instance==USART2)
  {
		
		HAL_UART_Receive_IT(&huart2,&UART2_temp[0],REC_LENGTH);
  }
}
/*
Ö¡Í· ¹¦ÄÜÂë  theta_l1  theta_l2 theta_r1 theta_r2 theta_l theta_r vel_l vel_r
0xAA 0x0A    4           4         4        4         4        4   4      4    0xBB
Reset 
0xAA  0x0B  0xBB
*/

void GetOneByte(uint8_t data)
{
	uint8_t buffer_index = 0;

	uint8_t frame_type; //1-contorl_frame , 2-reset_frame

	static uint8_t datatemp[50];

  static uint8_t rxstate = 0;

	if (rxstate == 0 && data == 0xAA)
	{
		rxstate = 1;
		buffer_index = 0;
		datatemp[buffer_index++] = data;
	}
	else if (rxstate == 1)
	{
		rxstate = 2;
		datatemp[buffer_index++] = data;
		if (data == 0x0A) frame_type = 1;
		else if (data == 0x0B) frame_type = 2;
		else if (data == 0xAA) rxstate = 1;
		else
		{
				rxstate = 0;			
		}
	}
	else if (rxstate == 2 && buffer_index < 35)
	{
		datatemp[buffer_index++] = data;
		if (frame_type == 2 && data == 0xBB) 
		{
			// reset frame
			reset_all();
			rxstate = 0;
		}
		if (frame_type == 1 && buffer_index == 35 && data == 0xBB)
		{
			// control frame
			Data_Anl(datatemp, 35); 
			rxstate = 0;
		}
	}
	else
	{
		rxstate = 0;
	}
}

// Data_AnlÎªï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ý½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Í¨ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ãµï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
static void Data_Anl(uint8_t *data, uint8_t len)
{
	//================================================================================

	latest_command.theta_l1[0] = data[2];
	latest_command.theta_l1[1] = data[3];
	latest_command.theta_l1[2] = data[4];
	latest_command.theta_l1[3] = data[5];

	latest_command.theta_l2[0] = data[6];
	latest_command.theta_l2[1] = data[7];
	latest_command.theta_l2[2] = data[8];
	latest_command.theta_l2[3] = data[9];

	latest_command.theta_r1[0] = data[10];
	latest_command.theta_r1[1] = data[11];
	latest_command.theta_r1[2] = data[12];
	latest_command.theta_r1[3] = data[13];

	latest_command.theta_r2[0] = data[14];
	latest_command.theta_r2[1] = data[15];
	latest_command.theta_r2[2] = data[16];
	latest_command.theta_r2[3] = data[17];

	latest_command.mm_l[0] = data[18];
	latest_command.mm_l[1] = data[19];
	latest_command.mm_l[2] = data[20];
	latest_command.mm_l[3] = data[21];

	latest_command.mm_r[0] = data[22];
	latest_command.mm_r[1] = data[23];
	latest_command.mm_r[2] = data[24];
	latest_command.mm_r[3] = data[25];

	latest_command.vel_l[0] = data[26];
	latest_command.vel_l[1] = data[27];
	latest_command.vel_l[2] = data[28];
	latest_command.vel_l[3] = data[29];

	latest_command.vel_r[0] = data[30];
	latest_command.vel_r[1] = data[31];
	latest_command.vel_r[2] = data[32];
	latest_command.vel_r[3] = data[33];

//int32_t tar_x,tar_y;

	//	tar_x = data[2]<<24|data[3]<<16|data[4]<<8|data[5];
		//tar_y = data[6]<<24|data[7]<<16|data[8]<<8|data[9];
		//printf("tar_x:%d,tar_y:%d\r\n",tar_x,tar_y);

// TODO: move to timer
//move(tar_x,tar_y);
}
/* USER CODE END 1 */
