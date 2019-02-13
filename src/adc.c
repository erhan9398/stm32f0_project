#include "adc.h"

void Init_Adc()
{
    //enable clock for adc
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    ADC_InitTypeDef ADC_InitStrcuture;

    ADC_DeInit(ADC1);
    ADC_StructInit(&ADC_InitStrcuture);

    //configure ADC1
    ADC_InitStrcuture.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStrcuture.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStrcuture.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStrcuture.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStrcuture.ADC_ScanDirection = ADC_ScanDirection_Upward;
    ADC_Init(ADC1, &ADC_InitStrcuture);

    //ADC_ChannelConfig(ADC1, ADC_Channel_0, ADC_SampleTime_7_5Cycles);
    //ADC_ChannelConfig(ADC1, ADC_Channel_10, ADC_SampleTime_7_5Cycles);
    //ADC_ChannelConfig(ADC1, ADC_Channel_11, ADC_SampleTime_7_5Cycles);

    ADC_Cmd(ADC1, ENABLE);
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY));
    //ADC_StartOfConversion(ADC1);
    //ADC_ITConfig(ADC1, ADC_IT_EOC, DISABLE);

}

uint16_t Read_AdcResult()
{   
    float temp1 = 0.0f;
    float temp2 = 0.0f;
    float temp3 = 0.0f;
    
    ADC_StopOfConversion(ADC1);
    ADC1->CHSELR &= 0x00;
    ADC1->CHSELR |= 0x01;
    ADC_StartOfConversion(ADC1);
    temp1 = ADC_GetConversionValue(ADC1);
    ADC_StopOfConversion(ADC1);
    temp1 *= (0.0008056640625);

    ADC_StopOfConversion(ADC1);
    ADC1->CHSELR &= 0x00;
    ADC1->CHSELR |= 0x0400;
    ADC_StartOfConversion(ADC1);
    temp2 = ADC_GetConversionValue(ADC1);
    ADC_StopOfConversion(ADC1);
    temp2 *= (0.0008056640625);

    ADC_StopOfConversion(ADC1);
    ADC1->CHSELR &= 0x00;
    ADC1->CHSELR |= 0x0800;
    ADC_StartOfConversion(ADC1);
    temp3 = ADC_GetConversionValue(ADC1);
    ADC_StopOfConversion(ADC1);
    temp3 *= (0.0008056640625);

    return temp1;
}