
#include "frame_pilha.h"

Frame frameCreate()
{
	Frame frame;
	frame.size = 0;	
	return frame;	
}

void frameClear(Frame *frame)
{
	frame->size = 0;		
}

void putData(Frame *frame, u8* input, int size)
{
	memcpy(frame->buffer,input, sizeof(u8)*size);
	frame->size = size;		
}

u8* getData(Frame *frame)
{	
	return frame->buffer;		
}

int getSize(Frame *frame)
{
	return frame->size;		
}

void addFloat(Frame *frame, float num)
{
	u8 index = frame->size;
	memcpy(&(frame->buffer[index]),(void*)&num, sizeof(u8)*4);
	frame->size = frame->size + 4;
}

float getFloat(Frame *frame)
{
	if(frame->size > 0)
	{
		float out;
		frame->size = frame->size - 4;
		u8 index = frame->size;
		memcpy((void*)&out, &(frame->buffer[index]), sizeof(u8)*4);	
		return out;
	}
	else return 0;
}

void addInt(Frame *frame, int num)
{
	u8 index = frame->size;
	memcpy(&(frame->buffer[index]),(void*)&num, sizeof(u8)*4);
	frame->size = frame->size + 4;
}

int getInt(Frame *frame)
{
	if(frame->size > 0 )
	{
		int out;
		frame->size = frame->size - 4;
		u8 index = frame->size;
		memcpy((void*)&out, &(frame->buffer[index]), sizeof(u8)*4);
		return out;
	}
	else return 0;
}
