#include "stm32f4xx.h"                  // Device header


uint16_t Read_adc(void){

	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_56Cycles);
	ADC_SoftwareStartConv(ADC1);
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);	
		return ADC_GetConversionValue(ADC1);
			
}


int main(){
  
	uint8_t adc_data;	//8 bitlik data tutulcak
	
	
	GPIO_InitTypeDef 	GPIO_InitStructure;
	ADC_InitTypeDef		ADC_InitStructure;
	ADC_CommonInitTypeDef		ADC_CommonInitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 |GPIO_Pin_14 |GPIO_Pin_15;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_0;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	ADC_CommonInitStructure.ADC_Mode= ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler= ADC_Prescaler_Div4;
	ADC_CommonInit(&ADC_CommonInitStructure);
	
	ADC_InitStructure.ADC_Resolution=ADC_Resolution_8b;
	ADC_Init(ADC1,&ADC_InitStructure);
	
	ADC_Cmd(ADC1,ENABLE);
	
	while(1){
	adc_data=Read_adc();   
	if(adc_data>0 && adc_data<50){
	GPIO_SetBits(GPIOD,GPIO_Pin_12);
	
	}else if(adc_data>50 && adc_data<100){
	GPIO_SetBits(GPIOD,GPIO_Pin_13);
	
	}else if(adc_data>100 && adc_data<150){
	GPIO_SetBits(GPIOD,GPIO_Pin_14);
	
	}else if(adc_data>150 && adc_data<200){
	GPIO_SetBits(GPIOD,GPIO_Pin_15);
	
	}else {
	GPIO_ResetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15 );	
	}
	}
	 
		
	

}
