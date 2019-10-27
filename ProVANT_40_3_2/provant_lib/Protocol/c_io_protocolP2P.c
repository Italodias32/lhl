#include "uart.h"
#include "c_io_protocolP2P.h"


//#define BAUDRATE 921600//576000
#define TRUE 1
#define FALSE 0


void c_io_protocolP2P_init(UART_HandleTypeDef* huart)
{
	usart_init();
}

Frame c_io_protocolP2P_receive(UART_HandleTypeDef* huart)
{
	Frame frame = frame_create();
	u8 header = frame.header;
	u8 end = frame.end;
	i32  status = 0;
	u8 last = 'a';
	int fim  = FALSE;
	//unsigned long now = 0, timeOut;
	//now = c_common_utils_millis();
	//timeOut = 3 + now;
	while(!fim /*&& (long)(now - timeOut) <= 0*/)
	{
		//now = c_common_utils_millis();
		if(usart_available(huart))
		{
			char b[1];
			b[0] = usart_read(huart);
			switch(status)
			{
				case 1:
					if (b[0] == last && last == header && header == end)
					{
						//printf("Alguma coisa\n");
						break;
					}
					if (b[0] != end){
						//printf("Meio de pacote\n");
						frame_addByte(&frame,b[0]);
					}
					if (b[0] == end)
					{
							//printf("Fim de pacote\n");
							frame_addEnd(&frame);
							status = 0;
							fim = TRUE;
					}
					break;
				case 0:
					if (b[0] == header)
					{
						//printf("Inicio de pacote\n");
						frame_addHeader(&frame);
						status = 1;
					}
					break;
			}
			last = b[0];
		}
	}
	//if((long)(now - timeOut) <= 0)	frame.complete = 0;
	return frame;
}


void c_io_protocolP2P_send(UART_HandleTypeDef* huart, Frame *frame)
{
	usart_print(huart, frame->buffer, frame->buffer_size);
}

