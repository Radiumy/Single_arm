#include "stm32f4xx.h"
#include "can.h"

extern CAN_TxHeaderTypeDef   TxHeader;
extern CAN_RxHeaderTypeDef   RxHeader;
extern uint8_t               TxData[8];
extern uint8_t               RxData[8];
extern uint32_t              TxMailbox;

void USER_CAN_Send(uint8_t* TxData);
void Motor_Init(void);
void Motor_Drive(int16_t speed_l, int16_t speed_r);

void Motor_Set_To_Vel_Mode();

void Motor_test();