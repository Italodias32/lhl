#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "c_common_frame.h"

#define FLOAT_FRAME 1
#define STR_FRAME 0


// void print_frame(Frame frame, u8 type);
// void print_buffer(u8 *data, i32 size);
// void print_float_buffer(Frame frame);
void c_io_protocolP2P_init(UART_HandleTypeDef* huart);
Frame c_io_protocolP2P_receive(UART_HandleTypeDef* huart);
void c_io_protocolP2P_send(UART_HandleTypeDef* huart, Frame *frame);

#endif
