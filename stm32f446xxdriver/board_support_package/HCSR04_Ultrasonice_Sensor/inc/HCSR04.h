/*
 * HCSR04.h
 *
 *  Created on: 12-Feb-2021
 *      Author: vermas
 */

/*********************** Documentation ***************
 * Range - 2cm to 400cm or 1”to 13 feet.
 * Trigger I/P Pulse Width = 10 us.
 * Operating frequency - 40KHz
 * ECHO Pin Pulse width = distance measured.
 */

#ifndef HCSR04_ULTRASONICE_SENSOR_INC_HCSR04_H_
#define HCSR04_ULTRASONICE_SENSOR_INC_HCSR04_H_

#include"stm32f44xx_gpio_driver.h"
#include"delay.h"

/* Default Pins and Port for ECHO and TRIG */
#ifndef __HCSR04_CONFIG__
#define __HCSR04_CONFIG__
#define HCSR04_TRIG_PORT       GPIOC
#define HCSR04_ECHO_PORT       GPIOC
#define HCSR04_TRIG_PIN        GPIO_PIN_NO_2
#define HCSR04_ECHO_PIN        GPIO_PIN_NO_4
#endif

#ifndef __HCSR04_TIMEOUT__
#define __HCSR04_TIMEOUT__
#define HCSR04_TIMEOUT          1000000//Timeout = 1 us
#endif

//Default temperature value
#ifndef DEFAULT_TEMP_VALUE
#define DEFAULT_TEMP_VALUE      20
#endif



uint8_t HCSR04_Init();
double HCSR04_Sensor_Read();




#endif /* HCSR04_ULTRASONICE_SENSOR_INC_HCSR04_H_ */
