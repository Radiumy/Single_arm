#include "control.h"
#include "math.h"
#include "tim.h"
#include "stdio.h"
#include "usart.h"
#include <stdlib.h>
#include <string.h>
/* TIM8对应Motor1,TIM4对应Motor2*/

int32_t l1_min_degree = -90, l1_max_degree = 90;
int32_t l2_min_degree = -30, l2_max_degree = 30;
int32_t r1_min_degree = -90, r1_max_degree = 90;
int32_t r2_min_degree = -30, r2_max_degree = 30;
int32_t l_min_mm = 0, l_max_mm = 100;
int32_t r_min_mm = 0, r_max_mm = 100;


// 默认复位角度
int32_t cur_theta_l1=0;
int32_t cur_theta_l2=90;
int32_t cur_theta_r1=0;
int32_t cur_theta_r2=90;
int32_t cur_mm_l=0;
int32_t cur_mm_r=90;

//bool x_is_running=false;
//bool y_is_running=false;

// cw: low, ccw: high,  
int8_t dir_theta_l1 = 0, dir_theta_l2 = 0;
int8_t dir_theta_r1 = 0, dir_theta_r2 = 0;
int8_t dir_l = 0, dir_r = 0;


// move to tim callback
//uint32_t count_1 = 0, count_2 = 0;


// move to usart callback
//uint32_t pulse1=0, pulse2=0;

// to pc
//int32_t degree_x = 0, degree_y = 0;

// ?
//int32_t used_tar_x, used_tar_y;


uint8_t data_frame_head[2] = {0xAA, 0x0A}; 


//uint8_t flag[1] = {0x00};

//uint8_t empty_frame[24] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//													 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

uint8_t frame_foot = 0xBB; 

//void motor_en(void)
//{
//	HAL_GPIO_WritePin(Motor_l1_ENA_GPIO_Port, Motor_l1_ENA_Pin, GPIO_PIN_SET);
//  HAL_GPIO_WritePin(Motor_l2_ENA_GPIO_Port, Motor_l2_ENA_Pin, GPIO_PIN_SET);
//}

//void motor_dis_en(void)
//{
//	HAL_GPIO_WritePin(Motor_l1_ENA_GPIO_Port, Motor_l1_ENA_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(Motor_l2_ENA_GPIO_Port, Motor_l2_ENA_Pin, GPIO_PIN_RESET);
//}

void set_dir(bool dir_l1, bool dir_l2, bool dir_r1, bool dir_r2, bool l, bool r)
//void set_dir(int32_t tar_x, int32_t tar_y)
{
	// true: cw, false: ccw
	
//	if(tar_x > tar_x_last)
	if(dir_l1)
	{
//		dir_x = 1;
		HAL_GPIO_WritePin(Motor_l1_DIR_GPIO_Port, Motor_l1_DIR_Pin, GPIO_PIN_RESET);	// 顺时针
	}
	else
//   else if(tar_x < tar_x_last)
	{
//		dir_x = -1;
		HAL_GPIO_WritePin(Motor_l1_DIR_GPIO_Port, Motor_l1_DIR_Pin, GPIO_PIN_SET);
	}

	if(dir_l2)
//   if(tar_y > tar_y_last)
	{
//		dir_y = 1;
		HAL_GPIO_WritePin(Motor_l2_DIR_GPIO_Port, Motor_l2_DIR_Pin, GPIO_PIN_RESET);		// 逆时针
	}
//    else if(tar_y < tar_y_last)
	else
	{
//		dir_y = -1;
		HAL_GPIO_WritePin(Motor_l2_DIR_GPIO_Port, Motor_l2_DIR_Pin, GPIO_PIN_SET);
	}
	
	if(dir_r1)
	{
		HAL_GPIO_WritePin(Motor_r1_DIR_GPIO_Port, Motor_r1_DIR_Pin, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(Motor_r1_DIR_GPIO_Port, Motor_r1_DIR_Pin, GPIO_PIN_SET);
	}

	if(dir_r2)
	{
		HAL_GPIO_WritePin(Motor_r2_DIR_GPIO_Port, Motor_r2_DIR_Pin, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(Motor_r2_DIR_GPIO_Port, Motor_r2_DIR_Pin, GPIO_PIN_SET);
	}

	if(dir_l)
	{
		HAL_GPIO_WritePin(Motor_l_DIR_GPIO_Port, Motor_l_DIR_Pin, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(Motor_l_DIR_GPIO_Port, Motor_l_DIR_Pin, GPIO_PIN_SET);
	}

	if(dir_r)
	{
		HAL_GPIO_WritePin(Motor_r_DIR_GPIO_Port, Motor_r_DIR_Pin, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(Motor_r_DIR_GPIO_Port, Motor_r_DIR_Pin, GPIO_PIN_SET);
	}
	
	
	
	
}

void move(int32_t tar_x, int32_t tar_y)
{
 	//printf("tar_x_last:%f,tar_y_last:%f\r\n",tar_x_last,tar_y_last);
	//printf("tar_x:%d, tar_y:%d\r\n", tar_x, tar_y);
	used_tar_x = tar_x;
	used_tar_y = tar_y;
	
	pulse1 = 0;
	pulse2 = 0;
	set_dir(tar_x, tar_y);
	if ((tar_x - tar_x_last != 0) && !x_is_running)
	{
		if(tar_x > tar_x_last)
		{
			pulse1 = (tar_x - tar_x_last) / DEGREE_PER_PULSE;
		}
		else
		{
			pulse1 = (tar_x_last - tar_x) / DEGREE_PER_PULSE;
		}
		HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);  /* 开启TIM4发送PWM脉冲 */
		HAL_TIM_Base_Start_IT(&htim4);
		//printf("pulse1:%d",pulse1);
		x_is_running = true;
		flag[0] = 0x00;
	}
	if ((tar_y - tar_y_last != 0) && !y_is_running)
	{
		if(tar_y > tar_y_last)
		{
			pulse2 = (tar_y - tar_y_last) / DEGREE_PER_PULSE;
		}
		else
		{
			pulse2 = (tar_y_last - tar_y) / DEGREE_PER_PULSE;
		}
		HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);  /* 开启TIM4发送PWM脉冲 */
		HAL_TIM_Base_Start_IT(&htim4);
		y_is_running = true;
		flag[0] = 0x00;
	}
}
void send_data(int32_t x, int32_t y)
{
	uint8_t angle_frame[35]={0};
	memcpy(angle_frame, data_frame_head, 2);

	uint8_t data[8];

	data[0] = (uint8_t)(x >> 24);
	data[1] = (uint8_t)(x >> 16);
	data[2] = (uint8_t)(x >> 8);
	data[3] = (uint8_t)(x);
	data[4] = (uint8_t)(y >> 24);
	data[5] = (uint8_t)(y >> 16);
	data[6] = (uint8_t)(y >> 8);
	data[7] = (uint8_t)(y);
	memcpy(angle_frame+2, data, 8);
	memcpy(angle_frame+10, empty_frame, 24);
	memcpy(angle_frame+34, frame_foot, 1);
	//printf( "frame:");
	//for( uint8_t i=0;i<35;i++)
	//{
		//printf("%02X ", angle_frame[i]);
	//}
	//printf("\r\n");
	HAL_UART_Transmit(&huart2, angle_frame , 35, 100);
}
void reset_all()
{
	tar_x_last=0;
  tar_y_last=90;

  x_is_running=false;
  y_is_running=false;

  dir_x = 0, dir_y = 0;
  count_1 = 0, count_2 = 0;
  pulse1=0, pulse2=0;
  degree_x = 0, degree_y = 0;
}

//void send_flag(uint8_t flag)
//{
//	uint8_t frame[5];
//	memcpy(frame, flag_frame_head, 3);
//	memcpy(frame+3, &flag, 1);
//	memcpy(frame+4, frame_foot, 1);
//	HAL_UART_Transmit(&huart2, frame , 5,50);
//}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{  
//	if(htim->Instance == TIM4)// l1 & l2
//	{
//		count_1 += 1;
//		count_2 += 1;
//		degree_x = tar_x_last + dir_x * (count_1 / PULSE_PER_DEGREE);
//		degree_y = tar_y_last + dir_y * (count_2 / PULSE_PER_DEGREE);
//		if(count_1 == pulse1)
//		{
//			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
//			//HAL_TIM_Base_Stop_IT(&htim8);
//			x_is_running = false;
//			tar_x_last = used_tar_x;
//			count_1 = 0;
//		}
//		if(count_2 == pulse2)
//		{
//			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
//			HAL_TIM_Base_Stop_IT(&htim4);
//			tar_y_last = used_tar_y;
//			y_is_running = false;
//			count_2 = 0;
//		}
//		//if(!x_is_running && !y_is_running)
//		//{
//			//flag[0] = 0x01;
//			//printf("degree_x:%d",degree_x);
//			//send_data(degree_x, degree_y);
////			send_flag(flag[0]);
////		}
//	}

	if(htim->Instance == TIM8) // r1 & r2
	{
		static int count = 0;
		static int step_motor_rise[6] = {0, 0, 0, 0, 0, 0};

		// The number of count that the pin of motor should switch
		static int step_motor_period[6];
		if((count % (int)(PERIOD_PER_PULSE_L1 / 2)) == 0)
		{
			HAL_GPIO_TogglePin(Motor_l1_PWM_GPIO_Port, Motor_l1_PWM_Pin);
		}
		if((count % (int)(PERIOD_PER_PULSE_L2 / 2)) == 0)
		{
			HAL_GPIO_TogglePin(Motor_l2_PWM_GPIO_Port, Motor_l2_PWM_Pin);
		}
		if((count % (int)(PERIOD_PER_PULSE_R1 / 2)) == 0)
		{
			HAL_GPIO_TogglePin(Motor_r1_PWM_GPIO_Port, Motor_r1_PWM_Pin);
		}
		if((count % (int)(PERIOD_PER_PULSE_R2 / 2)) == 0)
		{
			HAL_GPIO_TogglePin(Motor_r2_PWM_GPIO_Port, Motor_r2_PWM_Pin);
		}
		if((count % (int)(PERIOD_PER_MM_L / 2)) == 0)
		{
			HAL_GPIO_TogglePin(Motor_l1_PWM_GPIO_Port, Motor_l1_PWM_Pin);
		}
		if((count % (int)(PERIOD_PER_MM_R / 2)) == 0)
		{
			HAL_GPIO_TogglePin(Motor_l1_PWM_GPIO_Port, Motor_l1_PWM_Pin);
		}
		count++;
		
		
		
		
//		if((count % (PERIOD_PER_PULSE_L1 / 2)) == 0 && (count % PERIOD_PER_PULSE_L1）!= 0))
//		{
//			HAL_GPIO_WritePin(Motor_l1_PWM_GPIO_Port, Motor_l1_PWM_Pin, GPIO_PIN_SET);
//		}			
//		if((count % PERIOD_PER_PULSE_L1)== 0)
//		{
//			HAL_GPIO_WritePin(Motor_l1_PWM_GPIO_Port, Motor_l1_PWM_Pin, GPIO_PIN_RESET);
//		}
//		
//		
//		if((count % (PERIOD_PER_PULSE_L2 / 2)) == 0 && (count % PERIOD_PER_PULSE_L2）!= 0))
//		{
//			HAL_GPIO_WritePin(Motor_l2_PWM_GPIO_Port, Motor_l2_PWM_Pin, GPIO_PIN_SET);
//		}			
//		if((count % PERIOD_PER_PULSE_L2)== 0)
//		{
//			HAL_GPIO_WritePin(Motor_l2_PWM_GPIO_Port, Motor_l2_PWM_Pin, GPIO_PIN_RESET);
//		}
//		
//		if((count % (PERIOD_PER_PULSE_R1 / 2)) == 0 && (count % PERIOD_PER_PULSE_R1）!= 0))
//		{
//			HAL_GPIO_WritePin(Motor_r1_PWM_GPIO_Port, Motor_r1_PWM_Pin, GPIO_PIN_SET);
//		}			
//		if((count % PERIOD_PER_PULSE_R1)== 0)
//		{
//			HAL_GPIO_WritePin(Motor_r1_PWM_GPIO_Port, Motor_r1_PWM_Pin, GPIO_PIN_RESET);
//		}
//		
//		if((count % (PERIOD_PER_PULSE_R2 / 2)) == 0 && (count % PERIOD_PER_PULSE_R2）!= 0))
//		{
//			HAL_GPIO_WritePin(Motor_r2_PWM_GPIO_Port, Motor_r2_PWM_Pin, GPIO_PIN_SET);
//		}			
//		if((count % PERIOD_PER_PULSE_R2)== 0)
//		{
//			HAL_GPIO_WritePin(Motor_r2_PWM_GPIO_Port, Motor_r2_PWM_Pin, GPIO_PIN_RESET);
//		}
//		if(!x_is_running && !y_is_running)
//		{
//			flag[0] = 0x01;
//			//send_data(degree_x, degree_y);
//			send_flag(flag[0]);
//		}
	}
	else if(htim->Instance == TIM1)
	{
//		send_data(degree_x, degree_y);
//		if(!x_is_running && !y_is_running)
//		{
//			flag[0] = 0x01;
//			send_flag(flag[0]);
//		}
	}


}
