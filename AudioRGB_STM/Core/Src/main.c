/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "config.h"
#include "functions.h"
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// left audio channel
//uint16_t *buffArrL = (uint16_t *)malloc(BUFFER_SIZE_AUX * sizeof(uint16_t));
size_t buffIndL = 0;
uint16_t auxValL = 0, auxFilterL = 0;

// right audio channel
//uint16_t *buffArrR = (uint16_t *)malloc(BUFFER_SIZE_AUX * sizeof(uint16_t));
size_t buffIndR = 0;
uint16_t auxValR = 0, auxFilterR = 0;

// rgb led (uint8_t doesn't work)
//uint16_t *rgbArr = (uint16_t *)malloc(CHANNEL_COUNT_RGB * sizeof(uint16_t));
size_t colSel = 0, colSelPrev = 0;
uint16_t colVal = COLOR_HALF, colValPrev = COLOR_HALF;

// nanokernel tick counter
uint32_t ticks = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	// left audio channel
	uint16_t *buffArrL = (uint16_t *)malloc(BUFFER_SIZE_AUX * sizeof(uint16_t));
	emptyArray(buffArrL, BUFFER_SIZE_AUX);

	// right audio channel
	uint16_t *buffArrR = (uint16_t *)malloc(BUFFER_SIZE_AUX * sizeof(uint16_t));
	emptyArray(buffArrR, BUFFER_SIZE_AUX);

	// rgb led (uint8_t doesn't work)
	uint16_t *rgbArr = (uint16_t *)malloc(CHANNEL_COUNT_RGB * sizeof(uint16_t));
	emptyArray(rgbArr, CHANNEL_COUNT_RGB);
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	// setup rgb led
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	writeRGB(COLOR_HALF, COLOR_HALF, COLOR_HALF);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
		// get left audio channel from adc
		ADC_Select_CH1();
		HAL_ADC_Start(&hadc1);
		if (HAL_ADC_PollForConversion(&hadc1, TIMEOUT_ADC) == HAL_OK)
		{
			auxValL = HAL_ADC_GetValue(&hadc1);
			HAL_ADC_Stop(&hadc1);
			// write buffer and apply filter
			bufferAppend(auxValL, buffArrL, &buffIndL);
			auxFilterL = bufferFilter(buffArrL, &buffIndL);
		}

		// get right audio channel from adc
		ADC_Select_CH4();
		HAL_ADC_Start(&hadc1);
		if (HAL_ADC_PollForConversion(&hadc1, TIMEOUT_ADC) == HAL_OK)
		{
			auxValR = HAL_ADC_GetValue(&hadc1);
			HAL_ADC_Stop(&hadc1);
			// write buffer and apply filter
			bufferAppend(auxValR, buffArrR, &buffIndR);
			auxFilterR = bufferFilter(buffArrR, &buffIndR);
		}

		// generate color and write rgb
		writeRGB(
			generator(auxFilterL),
			5,
			generator(auxFilterR)
		);

		// update nanokernel tick and wait
		ticks++;
		HAL_Delay(DELAY);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

