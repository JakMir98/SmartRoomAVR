#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

/**************************************************************************************\
* Private definitions
\**************************************************************************************/
#define HUMIDITY_SENSOR_PIN 3
#define TEMPERATURE_SENSOR_PIN 2

#define ADC_SAMPLES 5
/**************************************************************************************\
* Private prototypes
\**************************************************************************************/

/**
 * @brief Analog to digital converter initialization
 */
void ADC_Init();

/**
 * @brief Read ADC value from selected channel
 */
uint16_t ADC_Read(uint8_t ADCchannel);

/**
 * @brief Read ADC few values from selected channel and avr them
 */
uint16_t ADC_AverageRead(uint8_t ADCchannel);

#endif /* ADC_H_ */