#ifndef __CONTROL_H
#define __CONTROL_H

#include "main.h"
#include <stdbool.h> 



#define DRIVER_SUBDIVISION_L1               128
#define DRIVER_SUBDIVISION_L2               128
#define DRIVER_SUBDIVISION_R1               128
#define DRIVER_SUBDIVISION_R2               128
#define DRIVER_SUBDIVISION_L               128
#define DRIVER_SUBDIVISION_R               128


// 42 step motor: each step 1.8 degree
// 57 step motor: each step 
#define DEGREE_PER_PULSE_L1        ((float)(1.8 / DRIVER_SUBDIVISION_L1))
#define DEGREE_PER_PULSE_L2        ((float)(1.8 / DRIVER_SUBDIVISION_L2))
#define DEGREE_PER_PULSE_R1        ((float)(1.8 / DRIVER_SUBDIVISION_R1))
#define DEGREE_PER_PULSE_R2        ((float)(1.8 / DRIVER_SUBDIVISION_R2))
#define DEGREE_PER_PULSE_L        ((float)(1.8 / DRIVER_SUBDIVISION_L))
#define DEGREE_PER_PULSE_R        ((float)(1.8 / DRIVER_SUBDIVISION_R))
	
//#define PULSE_PER_DEGREE        ((float)(DRIVER_SUBDIVISION/1.8))

#define LINEAR_STEP_MM 5
#define MM_PER_PULSE_L ((float)(DEGREE_PER_PULSE_L / 360.0 * LINEAR_STEP)
#define MM_PER_PULSE_R ((float)(DEGREE_PER_PULSE_R / 360.0 * LINEAR_STEP)
	
// YZL suggests: remove "VEL" will improve readability
#define DEGREE_VEL_PER_SECOND_L1 ((float)(60.0))  
#define DEGREE_VEL_PER_SECOND_L2 ((float)(60.0))
#define DEGREE_VEL_PER_SECOND_R1 ((float)(60.0))
#define DEGREE_VEL_PER_SECOND_R2 ((float)(60.0))
#define DEGREE_VEL_PER_SECOND_L ((float)(60.0))
#define DEGREE_VEL_PER_SECOND_R ((float)(60.0))

#define MM_PER_SECOND_L    ((float)(LINEAR_STEP_MM * DEGREE_VEL_PER_SECOND_L / 360.0))
#define MM_PER_SECOND_R    ((float)(LINEAR_STEP_MM * DEGREE_VEL_PER_SECOND_R / 360.0))
	
//#define FREQUENCY_FOR_MOTOR_CONTROL 10000

//#define COUNT_FOR_ONE_PERIOD_L1 ((float)(FREQUENCY_FOR_MOTOR_CONTROL*DEGREE_PER_PULSE_L1/DEGREE_VEL_PER_SECOND_L1))
	

#define PERIOD_PER_SECOND_L1       10000
#define PERIOD_PER_SECOND_L2       10000
#define PERIOD_PER_SECOND_R1       10000
#define PERIOD_PER_SECOND_R2       10000
#define PERIOD_PER_SECOND_L       10000
#define PERIOD_PER_SECOND_R       10000

#define PERIOD_PER_PULSE_L1      ((float)(PERIOD_PER_SECOND_L1 * DEGREE_PER_PULSE_L1 / DEGREE_VEL_PER_SECOND_L1))
#define PERIOD_PER_PULSE_L2      ((float)(PERIOD_PER_SECOND_L2 * DEGREE_PER_PULSE_L2 / DEGREE_VEL_PER_SECOND_L2))
#define PERIOD_PER_PULSE_R1      ((float)(PERIOD_PER_SECOND_R1 * DEGREE_PER_PULSE_R1 / DEGREE_VEL_PER_SECOND_R1))
#define PERIOD_PER_PULSE_R2      ((float)(PERIOD_PER_SECOND_R2 * DEGREE_PER_PULSE_R2 / DEGREE_VEL_PER_SECOND_R2))
#define PERIOD_PER_MM_L      ((float)(PERIOD_PER_SECOND_L / MM_PER_SECOND_L))
#define PERIOD_PER_MM_R      ((float)(PERIOD_PER_SECOND_R / MM_PER_SECOND_R))

typedef struct {
	uint8_t theta_l1[4];
	uint8_t theta_l2[4];
	uint8_t theta_r1[4];
	uint8_t theta_r2[4];
	uint8_t mm_l[4];
	uint8_t mm_r[4];
	uint8_t vel_l[4];
	uint8_t vel_r[4];
} ControlFrame;

ControlFrame latest_command;

// TODO: YT stop here

//void set_dir(int32_t tar_x, int32_t tar_y);
//void motor_en(void);
//void motor_dis_en(void);
void reset_all(void);
void move(int32_t tar_x, int32_t tar_y);

#endif