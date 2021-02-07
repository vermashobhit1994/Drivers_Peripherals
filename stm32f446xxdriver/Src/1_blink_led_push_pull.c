/*
 * 1_blink_led.c
 *
 *  Created on: 18-Jul-2020
 *      Author: vermas
 */


//Here the LED is connected to PA5 (read from schematic)
#include"stm32f446xx.h"
#include<time.h>
#include<stdio.h>
#define ACTIVATE
#ifdef ACTIVATE

void delay_ms(uint32_t value )
{
	clock_t time = 1000;
	printf("%ld",time);
}
int main(void)
{

	GPIO_Handle_t gpio_led;
	gpio_led.pGPIOx = GPIOA;
	gpio_led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	gpio_led.GPIO_PinConfig.GPIO_PinMode =  GPIO_MODE_OUT;

	gpio_led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM ;
	gpio_led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OPTYPE_PUSH_PULL;
	gpio_led.GPIO_PinConfig.GPIO_PinPuPdCtrl = GPIO_PIN_NO_PUPD;

	GPIO_PeriClock_Ctrl(GPIOA,ENABLE);
	GPIO_Init(&gpio_led);
	while (1)
	{

		GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
		delay_ms(660000);
	}


}
#endif



