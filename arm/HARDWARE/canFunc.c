#include "stm32f4xx.h"
#include "canFunc.h"
#include "usart.h"
#include "string.h"

/**
	*	@name		USER_CAN_Send
  * @brief  This function is used to Send data to motor,
						Set stdid before using the function.
  * @param  None
  * @retval None
  */
void USER_CAN_Send(uint8_t* TxData)
{
	CAN_TxHeaderTypeDef   TxHeader;
	
	TxHeader.StdId = 0x32; // YT: flags for controlling motor "1~4"
  TxHeader.ExtId = 0x00;
  TxHeader.RTR = CAN_RTR_DATA;
  TxHeader.IDE = CAN_ID_STD;
  TxHeader.DLC = 8;
  TxHeader.TransmitGlobalTime = DISABLE;
	
	uint32_t TxMailbox = 0;
	//	HAL_Delay(1000);

	if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK)
	{
//		HAL_UART_Transmit_IT(&huart2, (uint8_t*)"error\r\n", strlen("error\r\n"));
		/* Transmission request Error */
		Error_Handler();
	}	
//	HAL_UART_Transmit_IT(&huart2, (uint8_t*)"yes\r\n", strlen("yes\r\n"));
//	HAL_Delay(10);
//	TxData[0]++;
}

/**
	*	@name		Motor_Calibration
  * @brief  This function is used to Motor calibration before operation 
  * @param  None
  * @retval None
  */
//void Motor_Init(void)
//{
//	for(int i = 0; i < 8; i++) TxData[i] = 0x00;
//	TxData[0] = 0x02;
//	TxData[1] = 0x02;
//	TxHeader.StdId = 0x105;
//	USER_CAN_Send();
//}

/**
	*	@name		Send
  * @brief  This function is used to The driving motor changes the motion state
						If id = 2, the second data frame of speed or current position value
						is raised by eight bits and the third is lowered by eight bits. ID <= 8
						ID determines the data storage location of the data frame.
  * @param  Speed ID
  * @retval None
  */
void Motor_Drive(int16_t speed_l, int16_t speed_r)
{
	uint8_t TxData[8];
	for(int i = 0; i < 8; i++) TxData[i] = 0x00;
	speed_r = -speed_r;
	TxData[0] = speed_r >> 8;
	TxData[1] = speed_r;
	TxData[2] = speed_l >> 8;
	TxData[3] = speed_l;
	
	USER_CAN_Send(TxData);			
}

void Motor_Set_To_Vel_Mode()
{
	CAN_TxHeaderTypeDef   TxHeader;
	
	TxHeader.StdId = 0x105; // YT: flags for controlling motor "1~4"
  TxHeader.ExtId = 0x00;
  TxHeader.RTR = CAN_RTR_DATA;
  TxHeader.IDE = CAN_ID_STD;
  TxHeader.DLC = 8;
  TxHeader.TransmitGlobalTime = DISABLE;
	
	uint8_t TxData[8];
	for(int i = 0; i < 8; i++) TxData[i] = 0x00;
	TxData[0] = 0x02; 
	TxData[1] = 0x02;
	
//			HAL_Delay(1000);

	uint32_t TxMailbox = 0;
	if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK)
	{
		/* Transmission request Error */
		Error_Handler();
	}	
//	HAL_Delay(10);


}

void Motor_test()
{
	CAN_TxHeaderTypeDef   TxHeader;
	
	TxHeader.StdId = 0x104; 
  TxHeader.ExtId = 0x00;
  TxHeader.RTR = CAN_RTR_DATA;
  TxHeader.IDE = CAN_ID_STD;
  TxHeader.DLC = 8;
  TxHeader.TransmitGlobalTime = DISABLE;
	
	uint8_t TxData[8];
	for(int i = 0; i < 8; i++) TxData[i] = 0x00;
	
//			HAL_Delay(1000);

	uint32_t TxMailbox = 0;
	if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK)
	{
			HAL_UART_Transmit_IT(&huart2, (uint8_t*)"error\r\n", strlen("error\r\n"));

		/* Transmission request Error */
		Error_Handler();
	}	
		HAL_UART_Transmit_IT(&huart2, (uint8_t*)"yes\r\n", strlen("yes\r\n"));

//		HAL_Delay(10);


}