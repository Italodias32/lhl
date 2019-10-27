#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef	uint8_t	u8;

typedef struct _frame {
	u8 buffer[100]; // estrutura de dados do tipo pilha -> ultimo a entrar será o primeiro a sair
	int size;
} Frame;

Frame frameCreate();
void frameClear(Frame *frame);
void putData(Frame *frame, u8* input, int size);
u8* getData(Frame *frame);
int getSize(Frame *frame);
void addFloat(Frame *frame,float num);
float getFloat(Frame *frame);
void addInt(Frame *frame, int num);
int getInt(Frame *frame);

