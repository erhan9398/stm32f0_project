#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_exti.h"
#include "stm32f0xx_syscfg.h"

#define USART1_RX       GPIO_Pin_10
#define USART1_TX       GPIO_Pin_9
#define LED2_Pin        GPIO_Pin_5
#define BUTTON1_Pin     GPIO_Pin_13
#define HBridgeEnA      GPIO_Pin_10
#define HBridgeEnB      GPIO_Pin_11
#define HBridgeEnC      GPIO_Pin_12
#define MDriverEn       GPIO_Pin_6
#define LED2Port        GPIOA
#define HBridgeEnPort   GPIOC

void Init_Gpio(void);


#endif