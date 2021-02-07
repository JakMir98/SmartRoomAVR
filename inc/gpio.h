#ifndef gpio_h
#define gpio_h

#include <avr/io.h>
#include <avr/interrupt.h>
/**************************************************************************************\
* Global macros
\**************************************************************************************/
#define SET_PIN_AS_INPUT_PULLUP(dirReg, portReg, pinNum) ({dirReg &= ~(1 << pinNum); portReg |= (1 << pinNum);})
#define SET_PIN_AS_OUTPUT(portReg, pinNum) (portReg |= (1 << pinNum))

#define SET_BIT(portReg, pinNum) (portReg |= (1 << pinNum))
#define RESET_BIT(portReg, pinNum) (portReg &= ~(1 << pinNum))
#define TOOGLE_BIT(portReg, pinNum) (portReg ^= (1 << pinNum))
#define IS_BIT_SET(portReg, pinNum) (portReg & (1 << pinNum))

/**************************************************************************************\
* Private definitions
\**************************************************************************************/
// GPIOB
#define RELAY4_PIN 0
#define PUMP_PIN 1
#define PUSH_BUTTON_PIN 2
// GPIOD
#define TEST_LED_PIN 4
#define RELAY1_PIN 5
#define RELAY2_PIN 6
#define RELAY3_PIN 7


/**************************************************************************************\
* Private prototypes
\**************************************************************************************/

/**
 * @brief All GPIO initialization
 */
void GPIO_Init(void);

#endif
