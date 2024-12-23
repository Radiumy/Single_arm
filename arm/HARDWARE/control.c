#include "control.h"
#include "math.h"
#include "tim.h"
#include "stdio.h"
#include "usart.h"
#include <stdlib.h>
#include <string.h>


int32_t l1_min_degree = -90, l1_max_degree = 90;
int32_t l2_min_degree = -30, l2_max_degree = 30;
int32_t r1_min_degree = -90, r1_max_degree = 90;
int32_t r2_min_degree = -30, r2_max_degree = 30;
int32_t l_min_mm = 0, l_max_mm = 100;
int32_t r_min_mm = 0, r_max_mm = 100;

uint8_t data_frame_head[2] = {0xAA, 0x0A}; 

uint8_t frame_foot[1] = {0xBB}; 

ControlFrame latest_command = {0,0,0,0,0,0,0,0};
ControlFrame current_pos = {0,0,0,0,0,0,0,0};


void send_data()
{
//	uint8_t cur_frame[35]={0};
//	memcpy(cur_frame, data_frame_head, 2);

//	cur_frame[2] = (uint8_t)(current_pos.theta_l1 >> 24);
//	cur_frame[3] = (uint8_t)(current_pos.theta_l1 >> 16);
//	cur_frame[4] = (uint8_t)(current_pos.theta_l1 >> 8);
//	cur_frame[5] = (uint8_t)(current_pos.theta_l1);
//	cur_frame[6] = (uint8_t)(current_pos.theta_l2 >> 24);
//	cur_frame[7] = (uint8_t)(current_pos.theta_l2 >> 16);
//	cur_frame[8] = (uint8_t)(current_pos.theta_l2 >> 8);
//	cur_frame[9] = (uint8_t)(current_pos.theta_l2);
//	
//	cur_frame[10] = (uint8_t)(current_pos.theta_r1 >> 24);
//	cur_frame[11] = (uint8_t)(current_pos.theta_r1 >> 16);
//	cur_frame[12] = (uint8_t)(current_pos.theta_r1 >> 8);
//	cur_frame[13] = (uint8_t)(current_pos.theta_r1);
//	cur_frame[14] = (uint8_t)(current_pos.theta_r2 >> 24);
//	cur_frame[15] = (uint8_t)(current_pos.theta_r2 >> 16);
//	cur_frame[16] = (uint8_t)(current_pos.theta_r2 >> 8);
//	cur_frame[17] = (uint8_t)(current_pos.theta_r2);
//	
//	cur_frame[18] = (uint8_t)(current_pos.mm_l >> 24);
//	cur_frame[19] = (uint8_t)(current_pos.mm_l >> 16);
//	cur_frame[20] = (uint8_t)(current_pos.mm_l >> 8);
//	cur_frame[21] = (uint8_t)(current_pos.mm_l);
//	cur_frame[22] = (uint8_t)(current_pos.mm_r >> 24);
//	cur_frame[23] = (uint8_t)(current_pos.mm_r >> 16);
//	cur_frame[24] = (uint8_t)(current_pos.mm_r >> 8);
//	cur_frame[25] = (uint8_t)(current_pos.mm_r);

//	cur_frame[26] = (uint8_t)(current_pos.vel_l >> 24);
//	cur_frame[27] = (uint8_t)(current_pos.vel_l >> 16);
//	cur_frame[28] = (uint8_t)(current_pos.vel_l >> 8);
//	cur_frame[29] = (uint8_t)(current_pos.vel_l);
//	cur_frame[30] = (uint8_t)(current_pos.vel_r >> 24);
//	cur_frame[31] = (uint8_t)(current_pos.vel_r >> 16);
//	cur_frame[32] = (uint8_t)(current_pos.vel_r >> 8);
//	cur_frame[33] = (uint8_t)(current_pos.vel_r);
//	
//	memcpy(cur_frame+34, frame_foot, 1);
//	HAL_UART_Transmit(&huart2, cur_frame , 35, 100);
		char printBuffer[256];
		sprintf(printBuffer, "l1 = %.2f, l1 = %.2f, r1 = %.2f, r2 = %.2f, mm_l = %.2f, mm_r = %.2f, vel_l = %.2f, vel_r = %.2f\r\n", 
													current_pos.theta_l1, current_pos.theta_l2, current_pos.theta_r1, current_pos.theta_r2, current_pos.mm_l, current_pos.mm_r, current_pos.vel_l, current_pos.vel_r);
		HAL_UART_Transmit(&huart2, (uint8_t*)printBuffer, strlen(printBuffer), 0xFFFF);
}

// l1: delta<0 cw   l2: delta>0 cw
// r1: delta<0 cw   r2: delta<0 cw
// YZL: TODO define dirs[4] dirs[5]
// true: cw, false: ccw



// l1: + ccw set 1    - cw reset -1
// l2: + cw  reset 1  - ccw ser -1 
// r1: + ccw set 1    - cw reset -1 
// r2: + ccw set 1    - cw reset -1
// l:
// r: 


void Calculate_dirs()
{
	
	if ((latest_command.theta_l1 - current_pos.theta_l1) >0 ) dirs[0] = 1;
	else dirs[0] = -1;
	
	
	if ((latest_command.theta_l2 - current_pos.theta_l2) >0 ) dirs[1] = 1;
	else dirs[1] = -1;
	
	if ((latest_command.theta_r1 - current_pos.theta_r1) >0 ) dirs[2] = 1;
	else dirs[2] = -1;
	
	if ((latest_command.theta_r2 - current_pos.theta_r2) >0 ) dirs[3] = 1;
	else dirs[3] = -1;
	
	if ((latest_command.mm_l - current_pos.mm_l) >0 ) dirs[4] = 1;
	else dirs[4] = -1;
	
	if ((latest_command.mm_r - current_pos.mm_r) >0 ) dirs[5] = 1;
	else dirs[5] = -1;
}


// l1: + ccw set 1    - cw reset -1
// l2: + cw  reset 1  - ccw ser -1 
// r1: + ccw set 1    - cw reset -1 
// r2: + ccw set 1    - cw reset -1
// l:
// r: 
void set_dirs(int8_t *dirs)
{
	//l1
	if(dirs[0] == -1)
	{
		HAL_GPIO_WritePin(Motor_l1_DIR_GPIO_Port, Motor_l1_DIR_Pin, GPIO_PIN_RESET);	// 顺时针
	}
	else
	{
		HAL_GPIO_WritePin(Motor_l1_DIR_GPIO_Port, Motor_l1_DIR_Pin, GPIO_PIN_SET);
	}
	//l2
	if(dirs[1]==1)
	{
		HAL_GPIO_WritePin(Motor_l2_DIR_GPIO_Port, Motor_l2_DIR_Pin, GPIO_PIN_RESET);		// 顺时针
	}
	else
	{
		HAL_GPIO_WritePin(Motor_l2_DIR_GPIO_Port, Motor_l2_DIR_Pin, GPIO_PIN_SET);
	}
	//r1
	if(dirs[2]== -1)
	{
		HAL_GPIO_WritePin(Motor_r1_DIR_GPIO_Port, Motor_r1_DIR_Pin, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(Motor_r1_DIR_GPIO_Port, Motor_r1_DIR_Pin, GPIO_PIN_SET);
	}
	//r2
	if(dirs[3]== -1)
	{
		HAL_GPIO_WritePin(Motor_r2_DIR_GPIO_Port, Motor_r2_DIR_Pin, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(Motor_r2_DIR_GPIO_Port, Motor_r2_DIR_Pin, GPIO_PIN_SET);
	}
	//l
	if(dirs[4]==1)
	{
		HAL_GPIO_WritePin(Motor_l_DIR_GPIO_Port, Motor_l_DIR_Pin, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(Motor_l_DIR_GPIO_Port, Motor_l_DIR_Pin, GPIO_PIN_RESET);
	}
	//r
	if(dirs[5]==1)
	{
		
		HAL_GPIO_WritePin(Motor_r_DIR_GPIO_Port, Motor_r_DIR_Pin, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(Motor_r_DIR_GPIO_Port, Motor_r_DIR_Pin, GPIO_PIN_RESET);
	}
	
}
	void reset_all()
{
	current_pos.theta_l1 = 0;
	current_pos.theta_l2 = 0;
	
	current_pos.theta_r1 = 0;
	current_pos.theta_r2 = 0;
	
	current_pos.mm_l = 0;
	current_pos.mm_r = 0;
	
	current_pos.vel_l = 0;
	current_pos.vel_r = 0;
}

// steps for each motor 


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{  
	if(htim->Instance == TIM8)
	{
		static uint8_t count = 0;
		if_move[0] = (fabs(latest_command.theta_l1 - current_pos.theta_l1) > 0.1 );
		if_move[1] = (fabs(latest_command.theta_l2 - current_pos.theta_l2) > 0.1 );
		if_move[2] = (fabs(latest_command.theta_r1 - current_pos.theta_r1) > 0.1 );
		if_move[3] = (fabs(latest_command.theta_r2 - current_pos.theta_r2) > 0.1 );
		if_move[4] = (fabs(latest_command.mm_l - current_pos.mm_l) > 1 );
		if_move[5] = (fabs(latest_command.mm_r - current_pos.mm_r) > 1 );
//		uint8_t frame[8];
//		int32_t delta_r1 = (latest_command.theta_r1 - current_pos.theta_r1);  
//		int32_t delta_r2 = (latest_command.theta_r2 - current_pos.theta_r2);  
//		frame[0] = (uint8_t) (delta_r1>>24);
//		frame[1] = (uint8_t) (delta_r1>>16);
//		frame[2] = (uint8_t) (delta_r1>>8);
//		frame[3] = (uint8_t) (delta_r1);
//		frame[4] = (uint8_t) (delta_r2>>24);
//		frame[5] = (uint8_t) (delta_r2>>16);
//		frame[6] = (uint8_t) (delta_r2>>8);
//		frame[7] = (uint8_t) (delta_r2);
//		HAL_UART_Transmit(&huart2, frame , 8, 100);
		//HAL_UART_Transmit(&huart2, (uint8_t *)if_move , 6, 100);

		Calculate_dirs();
		set_dirs(dirs);
		//l1
		if(if_move[0])
		{
			// 1.if((count % PERIOD_PER_PULSE_L1 <= (PERIOD_PER_PULSE_L1 / 2)))
			// 2. count 越界
			if((count % PERIOD_PER_PULSE_L1) == 0 && (count % PERIOD_PER_PULSE_L1 / 2) == 0)
			{
				HAL_GPIO_WritePin(Motor_l1_PWM_GPIO_Port, Motor_l1_PWM_Pin, GPIO_PIN_SET);
				time_to_up[0] += PERIOD_PER_PULSE_L1;
				current_pos.theta_l1 += dirs[0] * DEGREE_PER_PULSE_L1;
			}			
			else if((count % PERIOD_PER_PULSE_L1) != 0 && (count % PERIOD_PER_PULSE_L1 / 2) == 0)
			{
				time_to_down[0] += PERIOD_PER_PULSE_L1;
				HAL_GPIO_WritePin(Motor_l1_PWM_GPIO_Port, Motor_l1_PWM_Pin, GPIO_PIN_RESET);
			}
		}
		//l2
		if(if_move[1])
		{
			if((count % PERIOD_PER_PULSE_L2) == 0 && (count % PERIOD_PER_PULSE_L2 / 2) == 0)
			{
				HAL_GPIO_WritePin(Motor_l2_PWM_GPIO_Port, Motor_l2_PWM_Pin, GPIO_PIN_SET);
				time_to_up[1] += PERIOD_PER_PULSE_L2;
				current_pos.theta_l2 += dirs[1] * DEGREE_PER_PULSE_L2;
			}			
			else if((count % PERIOD_PER_PULSE_L2) != 0 && (count % PERIOD_PER_PULSE_L2 / 2) == 0)
			{
				time_to_down[1] += PERIOD_PER_PULSE_L2;
				HAL_GPIO_WritePin(Motor_l2_PWM_GPIO_Port, Motor_l2_PWM_Pin, GPIO_PIN_RESET);
			}
		}
		//r1
		if(if_move[2])
		{
			if((count % PERIOD_PER_PULSE_R1) == 0 && (count % PERIOD_PER_PULSE_R1 / 2) == 0)
			{
				HAL_GPIO_WritePin(Motor_r1_PWM_GPIO_Port, Motor_r1_PWM_Pin, GPIO_PIN_SET);
				time_to_up[2] += PERIOD_PER_PULSE_R1;
				current_pos.theta_r1 += dirs[2] * DEGREE_PER_PULSE_R1;
			}			
			else if((count % PERIOD_PER_PULSE_R1) != 0 && (count % PERIOD_PER_PULSE_R1 / 2) == 0)
			{
				time_to_down[2] += PERIOD_PER_PULSE_R1;
				HAL_GPIO_WritePin(Motor_r1_PWM_GPIO_Port, Motor_r1_PWM_Pin, GPIO_PIN_RESET);
			}
		}
		//r2
		if(if_move[3])
		{
			if((count % PERIOD_PER_PULSE_R2) == 0 && (count % PERIOD_PER_PULSE_R2 / 2) == 0)
			{
				HAL_GPIO_WritePin(Motor_r2_PWM_GPIO_Port, Motor_r2_PWM_Pin, GPIO_PIN_SET);
				time_to_up[3] += PERIOD_PER_PULSE_R2;
				current_pos.theta_r2 += dirs[3] * DEGREE_PER_PULSE_R2;
			}			
			else if((count % PERIOD_PER_PULSE_R2) != 0 && (count % PERIOD_PER_PULSE_R2 / 2) == 0)
			{
				time_to_down[3] += PERIOD_PER_PULSE_R2;
				HAL_GPIO_WritePin(Motor_r2_PWM_GPIO_Port, Motor_r2_PWM_Pin, GPIO_PIN_RESET);
			}
		}
		//l
		if(if_move[4])
		{
			if((count % PERIOD_PER_PULSE_L) == 0 && (count % PERIOD_PER_PULSE_L / 2) == 0)
			{
				HAL_GPIO_WritePin(Motor_l_PWM_GPIO_Port, Motor_l_PWM_Pin, GPIO_PIN_SET);
				time_to_up[4] += PERIOD_PER_PULSE_L;
				current_pos.mm_l += dirs[4] * MM_PER_PULSE_L;
			}			
			else if((count % PERIOD_PER_PULSE_L) != 0 && (count % PERIOD_PER_PULSE_L / 2) == 0)
			{
				time_to_down[4] += PERIOD_PER_PULSE_L;
				HAL_GPIO_WritePin(Motor_l_PWM_GPIO_Port, Motor_l_PWM_Pin, GPIO_PIN_RESET);
			}
		}
		//r 
		if(if_move[5])
		{
			if((count % PERIOD_PER_PULSE_R) == 0 && (count % PERIOD_PER_PULSE_R / 2) == 0)
			{
				HAL_GPIO_WritePin(Motor_r_PWM_GPIO_Port, Motor_r_PWM_Pin, GPIO_PIN_SET);
				time_to_up[5] += PERIOD_PER_PULSE_R;
				current_pos.mm_r += dirs[5]* MM_PER_PULSE_R;
			}			
			else if((count % PERIOD_PER_PULSE_R) != 0 && (count % PERIOD_PER_PULSE_R / 2) == 0) 
			{
				time_to_down[5] += PERIOD_PER_PULSE_R;
				HAL_GPIO_WritePin(Motor_r_PWM_GPIO_Port, Motor_r_PWM_Pin, GPIO_PIN_RESET);
			}
		}
		current_pos.vel_l = latest_command.vel_l;
		current_pos.vel_r = latest_command.vel_r;
		count = (count + 1) % 65536;
	}
	else if(htim->Instance == TIM1)
	{
		//HAL_UART_Transmit(&huart2, (uint8_t*)("2222") , strlen("2222"), 100);
		send_data();
	}

}
