#include "stm32f0xx_conf.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_exti.h"
#include "stm32f0xx_syscfg.h"
#include "uart.h"
#include "delay.h"
#include "time1.h"

uint8_t flag = 1;

void Init_Gpio(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC | RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Set pin as input */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
    
    /* Tell system that you will use PC13 for EXTI_Line13 */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13);
    
    /* PC13 is connected to EXTI_Line13 */
    EXTI_InitStruct.EXTI_Line = EXTI_Line13;
    /* Enable interrupt */
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    /* Interrupt mode */
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    /* Triggers on rising and falling edge */
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    /* Add to EXTI */
    EXTI_Init(&EXTI_InitStruct);
 
    /* Add IRQ vector to NVIC */
    /* PC13 is connected to EXTI4_15_IRQn, which has EXTI4_15_IRQn vector */
    NVIC_InitStruct.NVIC_IRQChannel = EXTI4_15_IRQn;
    /* Set priority */
    NVIC_InitStruct.NVIC_IRQChannelPriority = 0x00;
    /* Enable interrupt */
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    /* Add to NVIC */
    NVIC_Init(&NVIC_InitStruct);



}

int main(void)
{	
    uint32_t pwm[3] = {0};
    uint32_t i = 0;
	Init_Gpio();
		
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

    Init_Delay();
    Init_GpioForPWM();
    Init_Timer1();
    Init_PWM();

    

	while(1)
	{
		if(flag)
		{	i = 0;
            do
            {   
                pwm[0] = 99-i;
                pwm[1] = i;
                pwm[2] = i;
                GPIO_SetBits(GPIOA, GPIO_Pin_5);
                Delay_MilliSec(5);
                GPIO_ResetBits(GPIOA, GPIO_Pin_5);
                Set_PWM(pwm);
                Delay_MilliSec(5);
                Set_Pwms();
                i++;
            }while(i <= 99 & flag);
		}
		else
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		}
	}

}

void EXTI4_15_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line13) != RESET)
	{
		flag = !(flag);
	}
	EXTI_ClearFlag(EXTI_Line13);
}
