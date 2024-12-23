#ifndef __CONTROL_H
#define __CONTROL_H

#include "main.h"
#include <stdbool.h> 



//#define DRIVER_SUBDIVISION_L1               128
//#define DRIVER_SUBDIVISION_L2               128
//#define DRIVER_SUBDIVISION_R1               128
//#define DRIVER_SUBDIVISION_R2               128
//#define DRIVER_SUBDIVISION_L               	128
//#define DRIVER_SUBDIVISION_R               	128

// 0.01 degree per pulse
#define DRIVER_SUBDIVISION_L1               128
#define DRIVER_SUBDIVISION_L2               128
#define DRIVER_SUBDIVISION_R1               128
#define DRIVER_SUBDIVISION_R2               128
#define DRIVER_SUBDIVISION_L               	16 
#define DRIVER_SUBDIVISION_R               	16


// 42 step motor: each step 1.8 degree
// 57 step motor: each step 
#define DEGREE_PER_PULSE_L1        ((float)(1.8 / DRIVER_SUBDIVISION_L1))
#define DEGREE_PER_PULSE_L2        ((float)(1.8 / DRIVER_SUBDIVISION_L2))
#define DEGREE_PER_PULSE_R1        ((float)(1.8 / DRIVER_SUBDIVISION_R1))
#define DEGREE_PER_PULSE_R2        ((float)(1.8 / DRIVER_SUBDIVISION_R2))
	
//0.1125
#define DEGREE_PER_PULSE_L         ((float)(1.8 / DRIVER_SUBDIVISION_L))
#define DEGREE_PER_PULSE_R         ((float)(1.8 / DRIVER_SUBDIVISION_R))
	
//#define PULSE_PER_DEGREE        ((float)(DRIVER_SUBDIVISION/1.8))

#define LINEAR_STEP_MM 5
//0.0015625
#define MM_PER_PULSE_L ((float)(DEGREE_PER_PULSE_L / 360.0 * LINEAR_STEP_MM))
#define MM_PER_PULSE_R ((float)(DEGREE_PER_PULSE_R / 360.0 * LINEAR_STEP_MM))
	//max:70 ---->  2 period per pulse  
#define DEGREE_VEL_PER_SECOND_L1 ((float)(14.0))   
#define DEGREE_VEL_PER_SECOND_L2 ((float)(14.0))
#define DEGREE_VEL_PER_SECOND_R1 ((float)(14.0))
#define DEGREE_VEL_PER_SECOND_R2 ((float)(14.0))
	//max:562.5
#define DEGREE_VEL_PER_SECOND_L ((float)(562.5))
#define DEGREE_VEL_PER_SECOND_R ((float)(562.5))

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

#define PERIOD_PER_PULSE_L1      ((int)(PERIOD_PER_SECOND_L1 * DEGREE_PER_PULSE_L1 / DEGREE_VEL_PER_SECOND_L1))
#define PERIOD_PER_PULSE_L2      ((int)(PERIOD_PER_SECOND_L2 * DEGREE_PER_PULSE_L2 / DEGREE_VEL_PER_SECOND_L2))
#define PERIOD_PER_PULSE_R1      ((int)(PERIOD_PER_SECOND_R1 * DEGREE_PER_PULSE_R1 / DEGREE_VEL_PER_SECOND_R1))
#define PERIOD_PER_PULSE_R2      ((int)(PERIOD_PER_SECOND_R2 * DEGREE_PER_PULSE_R2 / DEGREE_VEL_PER_SECOND_R2))
#define PERIOD_PER_PULSE_L      ((int)(PERIOD_PER_SECOND_L * DEGREE_PER_PULSE_L / DEGREE_VEL_PER_SECOND_L))
#define PERIOD_PER_PULSE_R      ((int)(PERIOD_PER_SECOND_R * DEGREE_PER_PULSE_R / DEGREE_VEL_PER_SECOND_R))
//#define PERIOD_PER_PULSE_L1      ((float)(PERIOD_PER_SECOND_L1 * DEGREE_PER_PULSE_L1 / DEGREE_VEL_PER_SECOND_L1))
//#define PERIOD_PER_PULSE_L2      ((float)(PERIOD_PER_SECOND_L2 * DEGREE_PER_PULSE_L2 / DEGREE_VEL_PER_SECOND_L2))
//#define PERIOD_PER_PULSE_R1      ((float)(PERIOD_PER_SECOND_R1 * DEGREE_PER_PULSE_R1 / DEGREE_VEL_PER_SECOND_R1))
//#define PERIOD_PER_PULSE_R2      ((float)(PERIOD_PER_SECOND_R2 * DEGREE_PER_PULSE_R2 / DEGREE_VEL_PER_SECOND_R2))
//#define PERIOD_PER_MM_L      ((float)(PERIOD_PER_SECOND_L / MM_PER_SECOND_L))
//#define PERIOD_PER_MM_R      ((float)(PERIOD_PER_SECOND_R / MM_PER_SECOND_R))

//typedef struct {
//	uint8_t theta_l1[4];
//	uint8_t theta_l2[4];
//	uint8_t theta_r1[4];
//	uint8_t theta_r2[4];
//	uint8_t mm_l[4];
//	uint8_t mm_r[4];
//	uint8_t vel_l[4];
//	uint8_t vel_r[4];
//} ControlFrame;

// TODO: YT stop here
typedef struct {
	float theta_l1;
	float theta_l2;
	float theta_r1;
	float theta_r2;
	float mm_l;
	float mm_r;
	float vel_l;
	float vel_r;
	bool cam_l;
	bool cam_m;
	bool cam_r;
} ControlFrame;



extern ControlFrame latest_command;
extern ControlFrame current_pos;


static bool if_move[6]={0,0,0,0,0,0};
static int8_t dirs[6] = {0,0,0,0,0,0};
static int time_to_up[6]={0,0,0,0,0,0};
static int time_to_down[6]= { PERIOD_PER_PULSE_L1 / 2,
															PERIOD_PER_PULSE_L2 / 2,
															PERIOD_PER_PULSE_R1 / 2,
															PERIOD_PER_PULSE_R2 / 2,
															PERIOD_PER_PULSE_L / 2,
															PERIOD_PER_PULSE_R / 2 };

void reset_all(void);
void Calculate_dirs();
void set_dirs(int8_t *dirs);

#endif