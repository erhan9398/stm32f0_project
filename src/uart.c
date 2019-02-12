#include "uart.h"

void Init_Uart()
{
    //enable USART1 clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);

    /* BaudRate = 9600
       HardwareFlowControl = None
       Mode = RX & TX
       Parity = None
       StopBit = 1
       WordLength = 8bits
    */
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);

}

void SendString_Usart(char *str)
{
    while(*str)
    {
        while(!(USART1->ISR & ((uint32_t)0x00000040)));
        USART1->TDR = (*str & (uint16_t)0x01FF);
        str++;
    }
    USART1->TDR = ('\r' & (uint16_t)0x01FF);
    USART1->TDR = ('\n' & (uint16_t)0x01FF);
}