/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ST7735.h"
#include "GFX_FUNCTIONS.h"
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
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int brickRowCount = 5;
int brickColumnCount = 11;
int brickWidth = 10;
int brickHeight = 10;
int brickPadding = 1;
int brickOffsetTop = 1;
int brickOffsetLeft = 1;

int ball_radius = 4;
int ball_x = 50;
int ball_y = 90;
int ball_x_speed = 2;
int ball_y_speed = 2;

struct Brick {
	int x;
	int y;
	int status;
};

struct Brick Brick_Field[15][15];

void collisionDetection(){
	for (int row=0; row<brickRowCount; row++)
	{
		for (int col=0; col<brickColumnCount; col++)
		{
			struct Brick b = Brick_Field[row][col];
			if (b.status == 1)
			{
//				if (ball_x+ball_radius>=b.x && ball_x-ball_radius<=b.x+brickWidth && ball_y+ball_radius>=b.y && ball_y-ball_radius<=b.y+brickHeight)
//				{
//					ball_y_speed = -ball_y_speed;
//					Brick_Field[row][col].status = 0;
//					fillRect(Brick_Field[row][col].x, Brick_Field[row][col].y, brickWidth, brickHeight, BLACK);
//				}
				//left -> right side
				if(ball_x+ball_radius>=b.x && ball_x+ball_radius<=b.x+brickWidth && ball_y>b.y && ball_y<b.y+brickHeight)
				{
					ball_x_speed = -ball_x_speed;
					Brick_Field[row][col].status = 0;
					fillRect(Brick_Field[row][col].x, Brick_Field[row][col].y, brickWidth, brickHeight, BLACK);
				}
				//right -> left side
				else if (ball_x-ball_radius>=b.x && ball_x-ball_radius<=b.x+brickWidth && ball_y>b.y && ball_y<b.y+brickHeight)
				{
					ball_x_speed = -ball_x_speed;
					Brick_Field[row][col].status = 0;
					fillRect(Brick_Field[row][col].x, Brick_Field[row][col].y, brickWidth, brickHeight, BLACK);
				}
				//up -> down side
				else if (ball_y+ball_radius>=b.y && ball_y+ball_radius<=b.y+brickHeight && ball_x>b.x && ball_x<b.x+brickWidth)
				{

					ball_y_speed = -ball_y_speed;
					Brick_Field[row][col].status = 0;
					fillRect(Brick_Field[row][col].x, Brick_Field[row][col].y, brickWidth, brickHeight, BLACK);
				}
				//down -> up side
				else if (ball_y-ball_radius>=b.y && ball_y-ball_radius<=b.y+brickHeight && ball_x>b.x && ball_x<b.x+brickWidth)
				{

					ball_y_speed = -ball_y_speed;
					Brick_Field[row][col].status = 0;
					fillRect(Brick_Field[row][col].x, Brick_Field[row][col].y, brickWidth, brickHeight, BLACK);
				}
			}
		}
	}
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  ST7735_Init(0);
  fillScreen(BLACK);

  /* construct block field */


  for(int row=0; row<brickRowCount; row++)
  {
	  for(int col=0; col<brickColumnCount; col++)
	  {
		  Brick_Field[row][col].x = (col*(brickWidth+brickPadding))+brickOffsetLeft + 4;
		  Brick_Field[row][col].y = (row*(brickHeight+brickPadding))+brickOffsetTop;
		  Brick_Field[row][col].status = 1;
		  fillRect(Brick_Field[row][col].x, Brick_Field[row][col].y, brickWidth, brickHeight, YELLOW);
	  }
  }



//  int w = 10;
//    for(int y=0; y+w<=60; y=y+w+1)
//    {
//		for(int x=4; x+w<=128; x=x+w+1)
//		{
//			fillRect(x, y, w, w, YELLOW);
//		}
//    }

//    fillCircle(50, 90, 4, MAGENTA);
//    fillRect(60, 120, 30, 5, GREEN);
//    fillRect(60, 120, 30, 5, BLACK);
//    fillRect(55, 120, 30, 5, GREEN);
//    fillRect(55, 120, 30, 5, BLACK);
//    fillRect(50, 120, 30, 5, GREEN);
//    fillRect(50, 120, 30, 5, BLACK);
//    fillRect(45, 120, 30, 5, GREEN);
//    fillRect(45, 120, 30, 5, BLACK);
//    fillRect(40, 120, 30, 5, GREEN);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int x=60;
  int y=120;
  int direct = 0;
  fillRect(60, 120, 30, 5, GREEN);
  drawCircle(50, 90, 4, CYAN);


  while (1)
  {
	  collisionDetection();
	  drawCircle(ball_x, ball_y, 4, BLACK);
	  if(ball_y >= 124) ball_y_speed = -ball_y_speed;
	  if(ball_x == 4 || ball_x == 124) ball_x_speed = -ball_x_speed;
	  ball_x += ball_x_speed;
	  ball_y += ball_y_speed;
	  drawCircle(ball_x, ball_y, 4, CYAN);

	  if(direct==0 && x>=0 && x<=98)
	  {
		  fillRect(x+1, 120, 30, 5, GREEN);
		  fillRect(x, 120, 1, 5, BLACK);
		  x++;
	  }
	  if(direct==1 && x>=0 && x<=98)
	  {
		  fillRect(x-1, 120, 30, 5, GREEN);
		  fillRect(x+29, 120, 1, 5, BLACK);
		  x--;
	  }
	  if(x<=10)
	  {
		  direct=0;
	  }
	  else if(x>=90)
	  {
		  direct=1;
	  }
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA9 */
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
