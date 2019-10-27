/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "pv_typedefs.h"
#include "c_common_frame.h"
#include "uart.h"
#include "LQR4.h"
#include <stdio.h>
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MODULE_PERIOD	   10

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi5;
DMA_HandleTypeDef hdma_spi1_rx;

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart6;
DMA_HandleTypeDef hdma_uart4_rx;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart6_rx;

PCD_HandleTypeDef hpcd_USB_OTG_FS;

osThreadId defaultTaskHandle;
osThreadId ControllerTaskHandle;
/* USER CODE BEGIN PV */
uint8_t data_get_uart4;
unsigned char usart4_recv_buffer[RECV_BUFFER_SIZE]; //! Ring-Buffer de recebimento de USART6.
int usart4_rb_in  = 0; //! Index do Ring-Buffer para recebimento na USART6.
int usart4_rb_out = 0; //! Index para leitura do Ring-Buffer da USART6.
int usart4_available_flag = 0; //! Flag de recebimento de USART6.

uint8_t data_get_uart6;
unsigned char usart6_recv_buffer[RECV_BUFFER_SIZE]; //! Ring-Buffer de recebimento de USART6.
int usart6_rb_in  = 0; //! Index do Ring-Buffer para recebimento na USART6.
int usart6_rb_out = 0; //! Index para leitura do Ring-Buffer da USART6.
int usart6_available_flag = 0; //! Flag de recebimento de USART6.

int num = 0;
int num2 = 0;
int num3[100];
float low = 0.0; // variável cque define o nivel de embarcado que executa lei de controle (1 = baixo nivel, 0 = alto nivel)
int boss = 0; // indica se a placa será a placa primária

Frame c_io_protocolP2P_receive6();
Frame c_io_protocolP2P_receive4();
int c_common_usart_available6();
int c_common_usart_available4();
unsigned char c_common_usart_read6();
unsigned char c_common_usart_read4();

pv_msg_controlOutput ControlOutputData;
pv_msg_controlOutput ControlOutputData2;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART6_UART_Init(void);
static void MX_USB_OTG_FS_PCD_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI5_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_UART4_Init(void);
void StartDefaultTask(void const * argument);
void Controller(void const * argument);

/* USER CODE BEGIN PFP */
void HAL_SPI_RxCpltCallback (SPI_HandleTypeDef *hspi);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//extern void initialise_monitor_handles();
uint8_t buffer[200];
__IO ITStatus UartReady = RESET;
__IO ITStatus SPIReady = RESET;
uint8_t data_get;
int fault = 0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	//initialise_monitor_handles();
	//printf("Começou programa!\n");
    //DWT->CTRL |= (1 << 0); // Enable CYCCNT in DWN_CTRL
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
  MX_DMA_Init();
  MX_USART6_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  MX_USART3_UART_Init();
  MX_SPI1_Init();
  MX_SPI5_Init();
  MX_USART2_UART_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */
  //HAL_UART_Receive_DMA(&huart4, &data_get_uart4, 1);
  //HAL_UART_Receive_DMA(&huart6, &data_get_uart6, 1);
  HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_SET);
  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  //osThreadDef(defaultTask, StartDefaultTask, osPriorityLow, 0, 128);
  //defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of ControllerTask */
  osThreadDef(ControllerTask, Controller, osPriorityNormal, 0, 512);
  ControllerTaskHandle = osThreadCreate(osThread(ControllerTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  //c_io_protocolP2P_init(&huart6);

  while (1)
  {

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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure LSE Drive Capability 
  */
  HAL_PWR_EnableBkUpAccess();
  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode 
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_USART3
                              |RCC_PERIPHCLK_USART6|RCC_PERIPHCLK_UART4
                              |RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInitStruct.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  PeriphClkInitStruct.Uart4ClockSelection = RCC_UART4CLKSOURCE_PCLK1;
  PeriphClkInitStruct.Usart6ClockSelection = RCC_USART6CLKSOURCE_PCLK2;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
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
  hspi1.Init.Mode = SPI_MODE_SLAVE;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES_RXONLY;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_HARD_INPUT;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI5_Init(void)
{

  /* USER CODE BEGIN SPI5_Init 0 */

  /* USER CODE END SPI5_Init 0 */

  /* USER CODE BEGIN SPI5_Init 1 */

  /* USER CODE END SPI5_Init 1 */
  /* SPI5 parameter configuration*/
  hspi5.Instance = SPI5;
  hspi5.Init.Mode = SPI_MODE_MASTER;
  hspi5.Init.Direction = SPI_DIRECTION_2LINES;
  hspi5.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi5.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi5.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi5.Init.NSS = SPI_NSS_SOFT;
  hspi5.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi5.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi5.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi5.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi5.Init.CRCPolynomial = 7;
  hspi5.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi5.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi5) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI5_Init 2 */

  /* USER CODE END SPI5_Init 2 */

}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  //huart4.Init.BaudRate = 921600;
  huart4.Init.BaudRate = 460800;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 921600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 921600;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  huart6.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart6.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

/**
  * @brief USB_OTG_FS Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_OTG_FS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_FS_Init 0 */

  /* USER CODE END USB_OTG_FS_Init 0 */

  /* USER CODE BEGIN USB_OTG_FS_Init 1 */

  /* USER CODE END USB_OTG_FS_Init 1 */
  hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints = 6;
  hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.Sof_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.vbus_sensing_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_OTG_FS_Init 2 */

  /* USER CODE END USB_OTG_FS_Init 2 */

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream2_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream2_IRQn);
  /* DMA1_Stream5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
  /* DMA2_Stream1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);

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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(RESET_OTHER_GPIO_Port, RESET_OTHER_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PE3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : USER_Btn_Pin */
  GPIO_InitStruct.Pin = USER_Btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RMII_MDC_Pin RMII_RXD0_Pin RMII_RXD1_Pin */
  GPIO_InitStruct.Pin = RMII_MDC_Pin|RMII_RXD0_Pin|RMII_RXD1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : RMII_REF_CLK_Pin RMII_MDIO_Pin */
  GPIO_InitStruct.Pin = RMII_REF_CLK_Pin|RMII_MDIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : RESET_OTHER_Pin LD3_Pin LD2_Pin */
  GPIO_InitStruct.Pin = RESET_OTHER_Pin|LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : RMII_TXD1_Pin */
  GPIO_InitStruct.Pin = RMII_TXD1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(RMII_TXD1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RMII_TX_EN_Pin RMII_TXD0_Pin */
  GPIO_InitStruct.Pin = RMII_TX_EN_Pin|RMII_TXD0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == huart6.Instance){
		usart6_available_flag = 1;
		usart6_recv_buffer[usart6_rb_in] = data_get_uart6;
		if(usart6_rb_in < RECV_BUFFER_SIZE-1) usart6_rb_in++;
		else	usart6_rb_in = 0;
		HAL_UART_Receive_DMA(&huart6, &data_get_uart6, 1);

		}
	if (huart->Instance == huart4.Instance){
			usart4_available_flag = 1;
			usart4_recv_buffer[usart4_rb_in] = data_get_uart4;
			if(usart4_rb_in < RECV_BUFFER_SIZE-1) usart4_rb_in++;
			else	usart4_rb_in = 0;
			HAL_UART_Receive_DMA(&huart4, &data_get_uart4, 1);
			}
}

unsigned char c_common_usart_read6() {
		uint8_t ret = usart6_recv_buffer[usart6_rb_out];
		if(usart6_rb_out < RECV_BUFFER_SIZE-1) usart6_rb_out++;
		else	usart6_rb_out = 0;
		if(usart6_rb_in == usart6_rb_out) usart6_available_flag = false;
		return ret;
}

unsigned char c_common_usart_read4() {
		uint8_t ret = usart4_recv_buffer[usart4_rb_out];
		if(usart4_rb_out < RECV_BUFFER_SIZE-1) usart4_rb_out++;
		else	usart4_rb_out = 0;
		if(usart4_rb_in == usart4_rb_out) usart4_available_flag = false;
		return ret;
}


int c_common_usart_available6() {
	return usart6_available_flag;
}

int c_common_usart_available4() {
	return usart4_available_flag;
}

Frame c_io_protocolP2P_receive4()
{
	Frame frame = frame_create();
	u8 header = frame.header;
	u8 end = frame.end;
	i32  status = 0;
	u8 last = 'a';
	int fim  = 0;
	int finst = 0;

	while(!fim)
	{
		// timeout = 2 periodos de amostragem
		while(!c_common_usart_available4())
		{
			int i  = HAL_GetTick();
			int sub = i - num;
			if(sub > 1*MODULE_PERIOD)
			{
				//printf("Falha!\n");
				fault++;
				finst = 1;
				if(fault > 2){
					//printf("Falha total!\n");
					low = 3.0;
				}
				break;
			}
		 }
		 //if(low==1) break;
		 if(finst==1)
		 {
			 finst = 0;
			 break;
		 }

		if(c_common_usart_available4())
		{
			fault=0;

			char b[1];
			b[0] = c_common_usart_read4();

			switch(status)
			{
				case 1:
					if (b[0] == last && last == header && header == end)
						break;
					if (b[0] != end) frame_addByte(&frame,b[0]);
					if (b[0] == end)
					{
							frame_addEnd(&frame);
							status = 0;
							fim = 1;
					}
					break;
				case 0:
					if (b[0] == header)
					{
						frame_addHeader(&frame);
						status = 1;
					}
					break;
			}
			last = b[0];
		}
	}

	return frame;
}

Frame c_io_protocolP2P_receive6()
{
	Frame frame = frame_create();
	u8 header = frame.header;
	u8 end = frame.end;
	i32  status = 0;
	u8 last = 'a';
	int fim  = 0;

	while(!fim)
	{
		if(c_common_usart_available6())
		{
			char b[1];
			b[0] = c_common_usart_read6();

			switch(status)
			{
				case 1:
					if (b[0] == last && last == header && header == end)
						break;
					if (b[0] != end) frame_addByte(&frame,b[0]);
					if (b[0] == end)
					{
							frame_addEnd(&frame);
							status = 0;
							fim = 1;
					}
					break;
				case 0:
					if (b[0] == header)
					{
						frame_addHeader(&frame);
						status = 1;
					}
					break;
			}
			last = b[0];
		}
	}
	return frame;
}


void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if (hspi->Instance == hspi1.Instance){
		SPIReady = SET;

		HAL_SPI_Receive_IT(&hspi1, &data_get, 4);
	}
}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
    
    
    
    

  /* USER CODE BEGIN 5 */

  /* Infinite loop */
  for(;;)
  {


  }
  /* USER CODE END 5 */ 
}

/* USER CODE BEGIN Header_Controller */
/**
* @brief Function implementing the ControllerTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Controller */
void Controller(void const * argument)
{
  /* USER CODE BEGIN Controller */
		int sample=0;

		pv_msg_input InputData;
		portTickType lastWakeTime;
		c_control_lqr4_init();

		HAL_SPI_Receive_IT(&hspi1, &data_get, 4);


		// tempo para garantir que as placas estão de comunicando
		HAL_Delay(50);
	  /* Infinite loop */
		int cont = 0;
		int p;
		for(;;)
	  {
			if(cont%500==0)
			{
				if(p==0)
				{
					InputData.position_reference.x = 0;
					InputData.position_reference.y = 0;
					InputData.position_reference.z = 2;
					InputData.position_reference.dotX = 0;
					InputData.position_reference.dotY = 0;
					InputData.position_reference.dotZ = 0;
					InputData.attitude_reference.roll = 0;
					InputData.attitude_reference.pitch = -0.578;
					InputData.attitude_reference.yaw = 0;
					InputData.attitude_reference.dotRoll = 0;
					InputData.attitude_reference.dotPitch = 0;
					InputData.attitude_reference.dotYaw = 0;
					p = 1;
				}
				else
				{
					InputData.position_reference.x = 0;
					InputData.position_reference.y = 0;
					InputData.position_reference.z = 2.2;
					InputData.position_reference.dotX = 0;
					InputData.position_reference.dotY = 0;
					InputData.position_reference.dotZ = 0;
					InputData.attitude_reference.roll = 0;
					InputData.attitude_reference.pitch = -0.578;
					InputData.attitude_reference.yaw = 0;
					InputData.attitude_reference.dotRoll = 0;
					InputData.attitude_reference.dotPitch = 0;
					InputData.attitude_reference.dotYaw = 0;
					p = 0;
				}
			}

		  lastWakeTime = xTaskGetTickCount();

		  if(low > 0.0) HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_SET);
		  else HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_RESET);
		  if(boss == 1)HAL_GPIO_WritePin(GPIOB, LD3_Pin, GPIO_PIN_SET);
		  else HAL_GPIO_WritePin(GPIOB, LD3_Pin, GPIO_PIN_RESET);

			if(boss==0)
			{
				if(SPIReady==SET)
				{
					SPIReady = RESET;
					sample = 0;
				}
				else sample++;

				if(sample > 2)
				{
					sample = 0;
					// comando para virar o boss

					GPIO_InitTypeDef GPIO_InitStruct;
					GPIO_InitStruct.Pin = GPIO_PIN_6;
					GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
					GPIO_InitStruct.Pull = GPIO_NOPULL;
					GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
					GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
					HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
					HAL_UART_Receive_DMA(&huart6, &data_get_uart6, 1);

					GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
					GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
					GPIO_InitStruct.Pull = GPIO_NOPULL;
					GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
					GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
					HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
					HAL_UART_Receive_DMA(&huart4, &data_get_uart4, 1);

					boss = 1;

					HAL_GPIO_WritePin(RESET_OTHER_GPIO_Port, RESET_OTHER_Pin, GPIO_PIN_RESET);
					HAL_Delay(10);
					HAL_GPIO_WritePin(RESET_OTHER_GPIO_Port, RESET_OTHER_Pin, GPIO_PIN_SET);
					// modo escrita no canal UART
				}
			}
			else
			{
				num = HAL_GetTick();

		  	  // código para solicitar informações
			  	Frame frameSend = frame_create();
			  	frame_addFloat(&frameSend, 1);
			  	frame_addFloat(&frameSend, 0);
			  	frame_addFloat(&frameSend, 0);
			  	frame_addFloat(&frameSend, 0);
			  	frame_addFloat(&frameSend, 0);
			  	frame_addFloat(&frameSend, low);

			  	frame_build(&frameSend);
			  	usart_print(&huart6,frameSend.buffer,frameSend.buffer_size);


			  	Frame frameRecv;
			  	frameRecv = c_io_protocolP2P_receive6();
			  	if(frame_unbuild(&frameRecv))
			  	{
			  		InputData.position.x  = frame_getFloat(&frameRecv);
			  		InputData.position.y  = frame_getFloat(&frameRecv);
			  		InputData.position.z  = frame_getFloat(&frameRecv);
			  		InputData.attitude.roll  = frame_getFloat(&frameRecv);
			  		InputData.attitude.pitch  = frame_getFloat(&frameRecv);
			  		InputData.attitude.yaw  = frame_getFloat(&frameRecv);
			  		InputData.servosOutput.servo.alphar = frame_getFloat(&frameRecv);
			  		InputData.servosOutput.servo.alphal = frame_getFloat(&frameRecv);
			  		InputData.position.dotX  = frame_getFloat(&frameRecv);
			  		InputData.position.dotY  = frame_getFloat(&frameRecv);
			  		InputData.position.dotZ  = frame_getFloat(&frameRecv);
			  		InputData.attitude.dotRoll  = frame_getFloat(&frameRecv);
			  		InputData.attitude.dotPitch  = frame_getFloat(&frameRecv);
			  		InputData.attitude.dotYaw  = frame_getFloat(&frameRecv);
			  		InputData.servosOutput.servo.dotAlphar = frame_getFloat(&frameRecv);
			  	    InputData.servosOutput.servo.dotAlphal = frame_getFloat(&frameRecv);


			  		if(low == 0.0)
			  		{
			  			Frame frameSend = frame_create();
			  			frame_addFloat(&frameSend, InputData.position.x);
			  			frame_addFloat(&frameSend, InputData.position.y);
			  			frame_addFloat(&frameSend, InputData.position.z);
			  			frame_addFloat(&frameSend, InputData.attitude.roll);
			  			frame_addFloat(&frameSend, InputData.attitude.pitch);
			  			frame_addFloat(&frameSend, InputData.attitude.yaw);
			  			frame_addFloat(&frameSend, InputData.servosOutput.servo.alphar);
			  			frame_addFloat(&frameSend, InputData.servosOutput.servo.alphal);
			  			frame_addFloat(&frameSend, InputData.position.dotX);
			  			frame_addFloat(&frameSend, InputData.position.dotY);
			  			frame_addFloat(&frameSend, InputData.position.dotZ);
			  			frame_addFloat(&frameSend, InputData.attitude.dotRoll);
			  			frame_addFloat(&frameSend, InputData.attitude.dotPitch);
			  			frame_addFloat(&frameSend, InputData.attitude.dotYaw);
			  			frame_addFloat(&frameSend, InputData.servosOutput.servo.dotAlphar);
			  			frame_addFloat(&frameSend, InputData.servosOutput.servo.dotAlphal);
			  			frame_addFloat(&frameSend, InputData.position_reference.x);
			  			frame_addFloat(&frameSend, InputData.position_reference.y);
			  			frame_addFloat(&frameSend, InputData.position_reference.z);
			  			/*frame_addFloat(&frameSend, InputData.position_reference.dotX);
			  			frame_addFloat(&frameSend, InputData.position_reference.dotY);
			  			frame_addFloat(&frameSend, InputData.position_reference.dotZ);
			  			frame_addFloat(&frameSend, InputData.attitude_reference.roll);
			  			frame_addFloat(&frameSend, InputData.attitude_reference.pitch);
			  			frame_addFloat(&frameSend, InputData.attitude_reference.yaw);
			  			frame_addFloat(&frameSend, InputData.attitude_reference.dotRoll);
			  			frame_addFloat(&frameSend, InputData.attitude_reference.dotPitch);
			  			frame_addFloat(&frameSend, InputData.attitude_reference.dotYaw);*/
			  			frame_build(&frameSend);
			  			usart_print(&huart4,frameSend.buffer,frameSend.buffer_size);
			  		}


			  	  // neste espaço será efetuado a detecção de malha do backup

			  	    	// enviar bytes de Watchdog
			  	    	uint8_t data_send[4];
			  	  		data_send[0] = 0;
			  	  		data_send[1] = 0;
			  	  		data_send[2] = 0;
			  	  		data_send[3] = 0;

			  	  		HAL_Delay(1);
			  	  		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET); // habilitar
			  	  		HAL_SPI_Transmit(&hspi5, data_send, 4, 1000);
			  	  		while(HAL_SPI_GetState(&hspi5)!= HAL_SPI_STATE_READY);
			  	  		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET); // desabilitar

			  	  // fim espaço

			  	 if(low == 0.0)
			  	 {
			  		 Frame frameRecv2;
			  		 frameRecv2 = c_io_protocolP2P_receive4();

			  		 if(fault == 0)
			  		 {
			  			 if(low == 0.0)
			  			 {

			  				 if(frame_unbuild(&frameRecv2))
			  				 {
			  					 ControlOutputData.actuation.escRightNewtons = frame_getFloat(&frameRecv2);
			  					 ControlOutputData.actuation.escLeftNewtons = frame_getFloat(&frameRecv2);
			  					 ControlOutputData.actuation.servoRight = frame_getFloat(&frameRecv2);
			  					 ControlOutputData.actuation.servoLeft = frame_getFloat(&frameRecv2);
			  				 }
			  				 else
			  				 {
			  					 low = 1.0;
			  				 }
			  			 }
			  		 }
			  	 }

			  	ControlOutputData2.actuation = c_control_lqr4_controller(InputData);

			  	if(low == 0.0)
			  	{
			  		if(ControlOutputData.actuation.escRightNewtons > 5 + ControlOutputData2.actuation.escRightNewtons || ControlOutputData.actuation.escRightNewtons < -5 + ControlOutputData2.actuation.escRightNewtons)
			  		{
			  			low  = 2.0;
			  		}
			  	}

			  	if (low==0.0)
			  	{
		   		 	  Frame frame = frame_create();
		   			  frame_addFloat(&frame, 0);
		   			  frame_addFloat(&frame, ControlOutputData.actuation.escRightNewtons);
		   			  frame_addFloat(&frame, ControlOutputData.actuation.escLeftNewtons);
		   			  frame_addFloat(&frame, ControlOutputData.actuation.servoRight);
		   			  frame_addFloat(&frame, ControlOutputData.actuation.servoLeft);
		   			  frame_addFloat(&frame, low);
		   			  frame_build(&frame);
		   			  usart_print(&huart6,frame.buffer,frame.buffer_size);
			  	}
			  	else
			  	{
			  		Frame frame = frame_create();
			  		frame_addFloat(&frame, 0);
			  		frame_addFloat(&frame, ControlOutputData2.actuation.escRightNewtons);
			  		frame_addFloat(&frame, ControlOutputData2.actuation.escLeftNewtons);
			  		frame_addFloat(&frame, ControlOutputData2.actuation.servoRight);
			  		frame_addFloat(&frame, ControlOutputData2.actuation.servoLeft);
			  		frame_addFloat(&frame, low);
			  		frame_build(&frame);
			  		usart_print(&huart6,frame.buffer,frame.buffer_size);
			  	}
			  	}
			}
			cont++;
			cont = cont%500;
		  vTaskDelayUntil( &lastWakeTime, (MODULE_PERIOD / portTICK_RATE_MS));
	  }
  /* USER CODE END Controller */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
