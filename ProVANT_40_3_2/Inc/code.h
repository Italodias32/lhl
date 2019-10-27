/*
 * code.h
 *
 *  Created on: Apr 27, 2019
 *      Author: arthur
 */

#ifndef CODE_H_
#define CODE_H_

#include "main.h"
#include "cmsis_os.h"
#include "pv_typedefs.h"
#include "frame_pilha.h"
#include "uart.h"
//#include "LQR.h"
#include "LQRvel.h"
#include <stdio.h>
#include <stdlib.h>

#define MODULE_PERIOD	   24

UART_HandleTypeDef huart3;
UART_HandleTypeDef huart6;
SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi5;
DMA_HandleTypeDef hdma_usart6_rx;
PCD_HandleTypeDef hpcd_USB_OTG_FS;

uint8_t buffer[200];
__IO ITStatus UartReady = RESET;
__IO ITStatus SPIReady = RESET;
uint8_t data_get;

osThreadId defaultTaskHandle;
osThreadId ControllerTaskHandle;
osThreadId OutputTaskHandle;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART6_UART_Init(void);
static void MX_USB_OTG_FS_PCD_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI5_Init(void);
void StartDefaultTask(void const * argument);
void Controller(void const * argument);
void Output(void const * argument);

extern void initialise_monitor_handles();




#endif /* CODE_H_ */
