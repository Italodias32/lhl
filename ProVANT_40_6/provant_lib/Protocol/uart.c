/*
 * uart.c
 *
 *  Created on: 4 de abr de 2019
 *      Author: arthur
 */
#include "uart.h"
#include <string.h>

//extern UART_HandleTypeDef huart4;
//extern UART_HandleTypeDef huart5;
//extern UART_HandleTypeDef huart7;
//extern UART_HandleTypeDef huart8;
//extern UART_HandleTypeDef huart1;
//extern UART_HandleTypeDef huart2;
//extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;


void usart_init()
{
	memset(usart_rb_in, 0, sizeof(usart_rb_in));
	memset(usart_rb_out, 0, sizeof(usart_rb_out));
	memset(usart_available_flag, 0, sizeof(usart_available_flag));
	memset(is_int, 0, sizeof(is_int));

	//HAL_UART_Receive_IT(&huart6,&rx_buff,1);
	//HAL_UART_Receive_IT(&huart1,&(rx_buff[0]),1);
	//HAL_UART_Receive_IT(&huart2,&(rx_buff[1]),1);
	//HAL_UART_Receive_IT(&huart3,&(rx_buff[2]),1);
	//HAL_UART_Receive_IT(&huart4,&(rx_buff[3]),1);
	//HAL_UART_Receive_IT(&huart5,&(rx_buff[4]),1);
	__HAL_UART_ENABLE_IT(&huart6, UART_IT_RXNE);
	HAL_StatusTypeDef status = HAL_UART_Receive_IT(&huart6,&(rx_buff[5]),1);
	//if(status == HAL_OK) printf("usart_init HAL_OK");
	//if(status == HAL_ERROR) printf("usart_init HAL_ERROR");
	//if(status == HAL_BUSY) printf("usart_init HAL_BUSY");
	//if(status == HAL_TIMEOUT) printf("usart_init HAL_TIMEOUT");
	//HAL_UART_Receive_IT(&huart7,&(rx_buff[6]),1);
	//HAL_UART_Receive_IT(&huart8,&(rx_buff[7]),1);
}


unsigned char usart_read(UART_HandleTypeDef* huart)
{
	uint8_t option;
	/*if(huart->Instance == huart1.Instance)	{
		option = 0;
	}
	if(huart->Instance == huart2.Instance)	{
		option = 1;
	}
	if(huart->Instance == huart3.Instance)	{
		option = 2;
	}
	if(huart->Instance == huart4.Instance)	{
		option = 3;
	}
	if(huart->Instance == huart5.Instance)	{
		option = 4;
	}*/
	if(huart->Instance == huart6.Instance)	{
		option = 5;
	}
	/*if(huart->Instance == huart7.Instance)	{
		option = 6;
	}
	if(huart->Instance == huart8.Instance)	{
		option = 7;
	}*/
	uint8_t ret = usart_recv_buffer[usart_rb_out[option]][option];
	if(usart_rb_out[option] < RECV_BUFFER_SIZE-1) usart_rb_out[option]++;
	else	usart_rb_out[option] = 0;
	if(usart_rb_in[option] == usart_rb_out[option]) usart_available_flag[option] = false;
	return ret;
}

unsigned char usart_print(UART_HandleTypeDef* huart, unsigned char* input, int size)
{
	char b;
	for(int i = 0; i < size; i++) {
		b = input[i];
		HAL_UART_Transmit(huart, (uint8_t*)&(b), 1, 50);
	}
	return 0;
}

int usart_available(UART_HandleTypeDef* huart) {
	uint8_t option = -1;
	/*if(huart->Instance == huart1.Instance)	{
		option = 0;
	}
	if(huart->Instance == huart2.Instance)	{
		option = 1;
	}
	if(huart->Instance == huart3.Instance)	{
		option = 2;
	}
	if(huart->Instance == huart4.Instance)	{
		option = 3;
	}
	if(huart->Instance == huart5.Instance)	{
		option = 4;
	}*/
	if(huart->Instance == huart6.Instance)	{
		option = 5;
	}
	/*if(huart->Instance == huart7.Instance)	{
		option = 6;
	}
	if(huart->Instance == huart8.Instance)	{
		option = 7;
	}*/
	return usart_available_flag[option];

}

void Callback(UART_HandleTypeDef *huart)
{
	//printf("Callback\n");
	uint8_t option = -1;
	/*if(huart->Instance == huart1.Instance)	{
		option = 0;
	}
	if(huart->Instance == huart2.Instance)	{
		option = 1;
	}
	if(huart->Instance == huart3.Instance)	{
		option = 2;
	}
	if(huart->Instance == huart4.Instance)	{
		option = 3;
	}
	if(huart->Instance == huart5.Instance)	{
		option = 4;
	}*/
	if(huart->Instance == huart6.Instance)	{
		option = 5;
	}
	/*if(huart->Instance == huart7.Instance)	{
		option = 6;
	}
	if(huart->Instance == huart8.Instance)	{
		option = 7;
	}*/
	if(is_int[option]!=0)
	{
		usart_available_flag[option] = 1;
		usart_recv_buffer[usart_rb_in[option]][option] = rx_buff[option];
		//HAL_UART_Transmit(&huart3, &(usart_recv_buffer[usart_rb_in[option]][option]),1,1);
		if(usart_rb_in[option] < RECV_BUFFER_SIZE-1) usart_rb_in[option]++;
		else	usart_rb_in[option] = 0;
	}
	else
	{
		is_int[option] = 1;
	}

	//__HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);

	HAL_StatusTypeDef status = HAL_UART_Receive_IT(huart,&rx_buff[option],1);
	//if(status == HAL_OK) printf("Callback HAL_OK");
	//if(status == HAL_ERROR) printf("Callback HAL_ERROR");
	//if(status == HAL_BUSY) printf("Callback HAL_BUSY");
	//if(status == HAL_TIMEOUT) printf("Callback HAL_TIMEOUT");
}
