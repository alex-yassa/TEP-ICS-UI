/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32h7xx_hal.h"

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
#define MCO1_Pin GPIO_PIN_8
#define MCO1_GPIO_Port GPIOA
#define OSC_IN_Pin GPIO_PIN_0
#define OSC_IN_GPIO_Port GPIOH

/* USER CODE BEGIN Private defines */
/* I2C1 / CTP Touchscreen GPIO pins */
#define I2C1_SCL_CTP_HAPTIC_Pin       GPIO_PIN_6
#define I2C1_SCL_CTP_HAPTIC_GPIO_Port GPIOB
#define I2C1_SDA_CTP_HAPTIC_Pin       GPIO_PIN_7
#define I2C1_SDA_CTP_HAPTIC_GPIO_Port GPIOB
#define CTP_RST_Pin                   GPIO_PIN_14
#define CTP_RST_GPIO_Port             GPIOC
#define CTP_INT_Pin                   GPIO_PIN_3
#define CTP_INT_GPIO_Port             GPIOH
#define CTP_INT_EXTI_IRQn             EXTI3_IRQn

/* Pin mappings for the physical HMI buttons (20-Button 5x4 Matrix Keypad) */
/* Rows (Active Low scan outputs) */
#define KEYPAD_ROW0_PORT                  GPIOA
#define KEYPAD_ROW0_PIN                   GPIO_PIN_5  // PA5  -> ROW0 (P8 Pin 5)
#define KEYPAD_ROW1_PORT                  GPIOE
#define KEYPAD_ROW1_PIN                   GPIO_PIN_4  // PE4  -> ROW1 (P8 Pin 9)
#define KEYPAD_ROW2_PORT                  GPIOK
#define KEYPAD_ROW2_PIN                   GPIO_PIN_1  // PK1  -> ROW2 (P8 Pin 11)
#define KEYPAD_ROW3_PORT                  GPIOD
#define KEYPAD_ROW3_PIN                   GPIO_PIN_12 // PD12 -> ROW3 (P8 Pin 13)
#define KEYPAD_ROW4_PORT                  GPIOD
#define KEYPAD_ROW4_PIN                   GPIO_PIN_13 // PD13 -> ROW4 (P8 Pin 15)

/* Columns (Inputs with internal Pull-up) */
#define KEYPAD_COL0_PORT                  GPIOA
#define KEYPAD_COL0_PIN                   GPIO_PIN_4  // PA4  -> COL0 (P8 Pin 8 - Nav Cluster)
#define KEYPAD_COL1_PORT                  GPIOD
#define KEYPAD_COL1_PIN                   GPIO_PIN_11 // PD11 -> COL1 (P8 Pin 10 - Vertical Strip)
#define KEYPAD_COL2_PORT                  GPIOB
#define KEYPAD_COL2_PIN                   GPIO_PIN_10 // PB10 -> COL2 (P8 Pin 12 - Horiz Board 1)
#define KEYPAD_COL3_PORT                  GPIOC
#define KEYPAD_COL3_PIN                   GPIO_PIN_7  // PC7  -> COL3 (P8 Pin 14 - Horiz Board 2)
/* USER CODE END Private defines */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void MX_I2C1_Init(void);
void MX_DMA2D_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
