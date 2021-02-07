#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
/**************************************************************************************\
* Private prototypes
\**************************************************************************************/

/**
 * @brief Periodic timer initialization overflow mode
 */
void OVERFLOW_TIMER_Init();

/**
 * @brief Periodic timer initialization compare mode
 */
void COMPARE_TIMER_Init();

#endif /* TIMER_H_ */
