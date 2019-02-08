#ifndef TIME1_H_
#define TIME1_H_

#include "stm32f0xx_tim.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx.h"

void Init_Timer1(void);
void Init_PWM(void);
void Init_GpioForPWM(void);
void Set_PWM(uint32_t *pwm);

#endif