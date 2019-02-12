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

    ADC_ChannelConfig(ADC1, ADC_Channel_0, ADC_SampleTime_7_5Cycles);
    //ADC_ChannelConfig(ADC1, ADC_Channel_10, ADC_SampleTime_7_5Cycles);
    //ADC_ChannelConfig(ADC1, ADC_Channel_11, ADC_SampleTime_7_5Cycles);

    ADC_Cmd(ADC1, ENABLE);
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY));
    ADC_StartOfConversion(ADC1);
    ADC_ITConfig(ADC1, ADC_IT_EOC, DISABLE);

}

void Read_AdcResult(uint16_t *result)
{
    result[0] = ADC_GetConversionValue(ADC1);
    
}