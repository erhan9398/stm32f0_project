#include "main.h"

uint32_t pwm[3] = {0};
uint32_t i = 0;
uint8_t MyText[16];
uint8_t *FloatToString(uint16_t nmbr);

int main(void)
{	
    uint16_t ADC_Res = 0;
    Init_Gpio();
	Init_Delay();
    Init_Timer1();
    Init_PWM();
    //TODO: Init uart rx-tx as PA3-PA2
    //Init_Uart();   
    Init_Adc();
    //Init_Timer2();
    
    while(1)
	{   
        
		//GPIO_SetBits(GPIOA, MDriverEn);
        if(flag)
		{	  
            GPIO_SetBits(LED2Port, LED2_Pin);
            
            GPIO_SetBits(HBridgeEnPort, HBridgeEnA);
            pwm[0] = 40;
            pwm[1] = 0;
            pwm[2] = 0;
            Set_PWM(pwm);
            Delay_MilliSec(20);
            GPIO_ResetBits(HBridgeEnPort, HBridgeEnA);
            
            GPIO_SetBits(HBridgeEnPort, HBridgeEnB);
            pwm[0] = 0;
            pwm[1] = 40;
            pwm[2] = 0;
            Set_PWM(pwm);
            Delay_MilliSec(20);
            GPIO_ResetBits(HBridgeEnPort, HBridgeEnB);
            
            GPIO_SetBits(HBridgeEnPort, HBridgeEnC);
            pwm[0] = 0;
            pwm[1] = 0;
            pwm[2] = 40;
            Set_PWM(pwm);
            GPIO_ResetBits(LED2Port, LED2_Pin);
            Delay_MilliSec(20);
            GPIO_ResetBits(HBridgeEnPort, HBridgeEnC);
            //ADC_Res = Read_AdcResult();
		}
        
		else
		{
            GPIO_ResetBits(HBridgeEnPort, HBridgeEnA | HBridgeEnB | HBridgeEnC);
		    GPIO_ResetBits(LED2Port, LED2_Pin);
            //FloatToString(ADC_Res);
            //SendString_Usart(MyText);
            //Delay_MilliSec(50);
		}
        
	}

}

//Button B1 interrupt Falling Edge
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
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

    }
    
}

uint8_t *FloatToString(uint16_t nmbr)
{
    sprintf(MyText, "%d Volt", nmbr);
    return (MyText);
}