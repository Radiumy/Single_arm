/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Motor_r_PWM_Pin GPIO_PIN_6
#define Motor_r_PWM_GPIO_Port GPIOA
#define Motor_r_DIR_Pin GPIO_PIN_7
#define Motor_r_DIR_GPIO_Port GPIOA
#define Motor_r_ENA_Pin GPIO_PIN_4
#define Motor_r_ENA_GPIO_Port GPIOC
#define Motor_l_ENA_Pin GPIO_PIN_5
#define Motor_l_ENA_GPIO_Port GPIOC
#define Motor_l_DIR_Pin GPIO_PIN_0
#define Motor_l_DIR_GPIO_Port GPIOB
#define Motor_l_PWM_Pin GPIO_PIN_1
#define Motor_l_PWM_GPIO_Port GPIOB
#define Motor_l1_DIR_Pin GPIO_PIN_10
#define Motor_l1_DIR_GPIO_Port GPIOD
#define Motor_l1_ENA_Pin GPIO_PIN_11
#define Motor_l1_ENA_GPIO_Port GPIOD
#define Motor_l1_PWM_Pin GPIO_PIN_12
#define Motor_l1_PWM_GPIO_Port GPIOD
#define Motor_l2_PWM_Pin GPIO_PIN_13
#define Motor_l2_PWM_GPIO_Port GPIOD
#define Motor_l2_ENA_Pin GPIO_PIN_14
#define Motor_l2_ENA_GPIO_Port GPIOD
#define Motor_l2_DIR_Pin GPIO_PIN_15
#define Motor_l2_DIR_GPIO_Port GPIOD
#define Motor_r1_PWM_Pin GPIO_PIN_6
#define Motor_r1_PWM_GPIO_Port GPIOC
#define Motor_r1_ENA_Pin GPIO_PIN_7
#define Motor_r1_ENA_GPIO_Port GPIOC
#define Motor_r1_DIR_Pin GPIO_PIN_8
#define Motor_r1_DIR_GPIO_Port GPIOC
#define Motor_r2_PWM_Pin GPIO_PIN_9
#define Motor_r2_PWM_GPIO_Port GPIOC
#define Motor_r2_ENA_Pin GPIO_PIN_8
#define Motor_r2_ENA_GPIO_Port GPIOA
#define Motor_r2_DIR_Pin GPIO_PIN_9
#define Motor_r2_DIR_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
