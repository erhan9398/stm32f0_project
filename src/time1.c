
#include "time1.h"

void Init_Timer1()
{   
    TIM_DeInit(TIM1);
    //enable TIM1 clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    //system freq 48MHz--TIM1 freq = (48MHz/20) = 2.4 MHz
    TIM_TimeBaseInitStructure.TIM_Prescaler = 17;
    //PWM freq = 2.4MHz / (Period + 1) = 24kHz
    TIM_TimeBaseInitStructure.TIM_Period = 99;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;

    //initialize TIM1
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

    //start TIM1
    TIM_Cmd(TIM1, ENABLE);

}

void Init_PWM()
{
    // PWM initialization struct
	TIM_OCInitTypeDef TIM_OCInitStructure;

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);
    TIM_OC2Init(TIM1, &TIM_OCInitStructure);
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);
    //TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
    //TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
    //TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
    //set pwm out as active high
    TIM1->CCER &=  0xFDDD;
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

void Set_PWM(uint32_t *pwm)
{   
    TIM1->CCR1 = pwm[0];
    TIM1->CCR2 = pwm[1];
    TIM1->CCR3 = pwm[2];
}