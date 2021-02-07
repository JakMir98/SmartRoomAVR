#include "/Projekty/AVR projects/SmartRoom/SmartRoom/inc/adc.h"

void ADC_Init()
{
	// Select Vref=AVcc
	ADMUX |= (1<<REFS0);
	// Set prescaller to 128 and enable ADC
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}

uint16_t ADC_Read(uint8_t ADCchannel)
{
	//select ADC channel with safety mask
	ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
	//single conversion mode
	ADCSRA |= (1<<ADSC);
	// wait until ADC conversion is complete
	while(!(ADCSRA & (1 << ADIF)));
	ADCSRA |= (1 << ADIF); //reset as required  
	
	return ADC;
}

uint16_t ADC_AverageRead(uint8_t ADCchannel)
{
	uint16_t adcVal = 0;
	uint16_t adcValTotal = 0;
	ADC_Read(ADCchannel); //first throw-away read
	//read n sample values from the ADC and average them out
	for(int i = 0; i < ADC_SAMPLES; ++i)
		adcValTotal += ADC_Read(ADCchannel);

	adcVal = adcValTotal / ADC_SAMPLES;
	return adcVal;
}

