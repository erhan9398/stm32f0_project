#include "main.h"

uint32_t pwm[3] = {0};
uint32_t i = 0;

int main(void)
{	
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
    Init_Timer2();

	while(1)
	{   
        i++;
        if(99 < i)
        {
            i = 0;
        }

		if(flag)
		{	  
            GPIO_SetBits(GPIOA, GPIO_Pin_5);
            Delay_MilliSec(50);
            GPIO_ResetBits(GPIOA, GPIO_Pin_5);
            Delay_MilliSec(50);
		}
        
		else
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		}
        
	}

}

void EXTI4_15_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line13) != RESET)
	{
		flag = !(flag);
	}
	EXTI_ClearFlag(EXTI_Line13);
}

void TIM2_IRQHandler()
{
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)    
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        pwm[0] = 99-i;
        pwm[1] = i;
        pwm[2] = i;
        Set_PWM(pwm);
}
