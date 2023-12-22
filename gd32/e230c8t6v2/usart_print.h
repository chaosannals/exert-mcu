#ifndef USART_PRINT_H
#define USART_PRINT_H
#include <stdint.h>

void InitUSART0(void);
void SendUSART0(char c);
void SendUSART0Ui16(uint16_t i16);
void PrintUSART0(char *t);

#endif
