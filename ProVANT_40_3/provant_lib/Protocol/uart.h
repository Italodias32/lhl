/*
 * uart.h
 *
 *  Created on: 4 de abr de 2019
 *      Author: arthur
 */

#ifndef PROTOCOL_UART_H_
#define PROTOCOL_UART_H_

#include "stm32f7xx_hal.h"

#define RECV_BUFFER_SIZE	256
#define NUM_USART 8
#define false 0
#define true 1

uint8_t rx_buff[NUM_USART];
uint8_t usart_recv_buffer[RECV_BUFFER_SIZE][NUM_USART]; //! Ring-Buffer de recebimento.
int  usart_rb_in[NUM_USART]; //! Index do Ring-Buffer para recebimento na USART.
int  usart_rb_out[NUM_USART]; //! Index para leitura do Ring-Buffer da USART.
uint8_t  usart_available_flag[NUM_USART]; //! Flag de recebimento de USART.
uint8_t  is_int[NUM_USART]; // eliminar a primeira interrupção "vazia"

void usart_init();
unsigned char usart_read(UART_HandleTypeDef* huart);
unsigned char usart_print(UART_HandleTypeDef* huart, unsigned char* input, int size);
int usart_available(UART_HandleTypeDef* huart);
void Callback(UART_HandleTypeDef *huart);

#endif /* PROTOCOL_UART_H_ */
