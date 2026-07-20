/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "mdma.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "app_hardware.h"
#include "dma2d.h"
#include "i2c.h"
#include "lvgl/lvgl.h"
#include "lvgl_port_touch.h"
#include "porting/lv_port_disp.h"
#include "porting/lv_port_indev.h"
#include "ui.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
static void MX_GPIO_Init(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* USER CODE BEGIN Boot_Mode_Sequence_1 */
  /*HW semaphore Clock enable*/
  __HAL_RCC_HSEM_CLK_ENABLE();
  /* Activate HSEM notification for Cortex-M4*/
  HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));
  /*
  Domain D2 goes to STOP mode (Cortex-M4 in deep-sleep) waiting for Cortex-M7 to
  perform system initialization (system clock config, external memory
  configuration.. )
  */
  HAL_PWREx_ClearPendingEvent();
  HAL_PWREx_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFE,
                          PWR_D2_DOMAIN);
  /* Clear HSEM flag */
  __HAL_HSEM_CLEAR_FLAG(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));

  /* USER CODE END Boot_Mode_Sequence_1 */
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick.
   */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_MDMA_Init();
  /* USER CODE BEGIN 2 */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_DMA2D_Init();

  /* initialize LVGL framework */
  lv_init();

  /* initialize display and touchscreen */
  lv_port_disp_init();
  // lvgl_touchscreen_init(); //there is no touchscreen on this device !!!
  lv_port_indev_init();

  /* Initialize EEZ-generated UI */
  ui_init();
  app_ui_init();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {
    /* Let LVGL process timer-driven widget rendering & interactions */
    lv_timer_handler();

    /* Let EEZ UI process ticks and logical flows */
    ui_tick();

    /* Increment the tick counter by 5ms */
    lv_tick_inc(5);

    /* Delay for 5ms to maintain visual update frequency and limit bus
     * contention */
    HAL_Delay(5);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/* USER CODE BEGIN 4 */
static void MX_GPIO_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Enable GPIO Clocks for keypad (GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOK) */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOK_CLK_ENABLE();

  /* Configure Column Inputs (COL0..COL3) with internal Pull-up resistors */
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  GPIO_InitStruct.Pin = KEYPAD_COL0_PIN;
  HAL_GPIO_Init(KEYPAD_COL0_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = KEYPAD_COL1_PIN;
  HAL_GPIO_Init(KEYPAD_COL1_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = KEYPAD_COL2_PIN;
  HAL_GPIO_Init(KEYPAD_COL2_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = KEYPAD_COL3_PIN;
  HAL_GPIO_Init(KEYPAD_COL3_PORT, &GPIO_InitStruct);

  /* Configure Row Pins (ROW0..ROW4) as Open-Drain Outputs initialized to HIGH */
  HAL_GPIO_WritePin(KEYPAD_ROW0_PORT, KEYPAD_ROW0_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin(KEYPAD_ROW1_PORT, KEYPAD_ROW1_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin(KEYPAD_ROW2_PORT, KEYPAD_ROW2_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin(KEYPAD_ROW3_PORT, KEYPAD_ROW3_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin(KEYPAD_ROW4_PORT, KEYPAD_ROW4_PIN, GPIO_PIN_SET);

  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  GPIO_InitStruct.Pin = KEYPAD_ROW0_PIN;
  HAL_GPIO_Init(KEYPAD_ROW0_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = KEYPAD_ROW1_PIN;
  HAL_GPIO_Init(KEYPAD_ROW1_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = KEYPAD_ROW2_PIN;
  HAL_GPIO_Init(KEYPAD_ROW2_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = KEYPAD_ROW3_PIN;
  HAL_GPIO_Init(KEYPAD_ROW3_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = KEYPAD_ROW4_PIN;
  HAL_GPIO_Init(KEYPAD_ROW4_PORT, &GPIO_InitStruct);
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1) {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line) {
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line
     number, ex: printf("Wrong parameters value: file %s on line %d\r\n", file,
     line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
