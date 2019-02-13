#ifndef UART_H_
#define UART_H_

#include "stm32f0xx_usart.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"

void Init_Uart(void);
void SendString_Usart(uint8_t *s);

#endif