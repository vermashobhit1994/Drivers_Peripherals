/*
 * HCSR04.c
 *
 *  Created on: 12-Feb-2021
 *      Author: vermas
 */

#include"HCSR04.h"

uint8_t HCSR04_Init()
{

	//Initialize the GPIO Port and Pins for TRIGGER and ECHO
	GPIO_Handle_t HCSR04Config ;
	(void)HCSR04Config;
	//Initialize the TRIG Pin
	HCSR04Config.pGPIOx = HCSR04_TRIG_PORT;
	HCSR04Config.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	HCSR04Config.GPIO_PinConfig.GPIO_PinOPType = GPIO_OPTYPE_PUSH_PULL;
	//Why selected as Pull down?
	HCSR04Config.GPIO_PinConfig.GPIO_PinPuPdCtrl = GPIO_PIN_PULL_DOWN;
	HCSR04Config.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM;
	HCSR04Config.GPIO_PinConfig.GPIO_PinNumber = HCSR04_TRIG_PIN;
	GPIO_Init(&HCSR04Config);


	//Initialize the ECHO Pin as Input Pin
	GPIO_Handle_t HCSR04Configecho;
	HCSR04Configecho.pGPIOx = HCSR04_ECHO_PORT;
	HCSR04Configecho.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	HCSR04Configecho.GPIO_PinConfig.GPIO_PinOPType = GPIO_OPTYPE_PUSH_PULL;
	//Why selected as Pull down?
	HCSR04Configecho.GPIO_PinConfig.GPIO_PinPuPdCtrl = GPIO_PIN_PULL_DOWN;
	HCSR04Configecho.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM;
	HCSR04Configecho.GPIO_PinConfig.GPIO_PinNumber = HCSR04_ECHO_PIN;
	GPIO_Init(&HCSR04Configecho);

	//Setting the TRIG to low by default
	GPIO_WriteToOutputPin(HCSR04_TRIG_PORT, HCSR04_TRIG_PIN, 0);

	//Read the dummy data
	if(HCSR04_Sensor_Read() >= 0)
		return 1;
	else
		return 0;

}


double HCSR04_Sensor_Read()
{
	//Initialize the Timer6 i.e enable the peripheral clock.
	TIMER6_Init();

	//Initialize the TRIG Pin
	GPIO_WriteToOutputPin(HCSR04_TRIG_PORT, HCSR04_TRIG_PIN, 0);
	delay_us(2);

	//Start sending the pulse
	GPIO_WriteToOutputPin(HCSR04_TRIG_PORT, HCSR04_TRIG_PIN, 1);
	delay_us(10);
	GPIO_WriteToOutputPin(HCSR04_TRIG_PORT, HCSR04_TRIG_PIN, 0);

	//wait until the ECHO Pin becomes HIGH
	//If ECHO Pin doesn't becomes High it means timeout occurs.
	uint32_t timeout = HCSR04_TIMEOUT;
	while(!GPIO_ReadFromInputPin(HCSR04_ECHO_PORT, HCSR04_ECHO_PIN))
	{
		if(timeout == 0x00)
			return -1.0;
		timeout--;
	}

	//Measure the time by checking the ECHO Pin until it remains HIGH
	unsigned long timeinMicroseconds =0;

	TIMER6_START();
	while(GPIO_ReadFromInputPin(HCSR04_ECHO_PORT, HCSR04_ECHO_PIN))
	{
		timeinMicroseconds++;
		delay_us(1);
	}

	TIMER6_STOP();
	//Convert time into distance
	//Calculate the speed of sound in Centimeter Per microseconds
	//where it depends on temperature.
	float temperature = DEFAULT_TEMP_VALUE;//default value of temperature
	//double SpeedSoundInCmPerMicroseconds = (((double)331.3*100)/1000000) + (((double)0.606 * 100)/1000000)*temperature;
	double SpeedSoundInCmPerMicroseconds = 0.03313 + 0.0000606 * temperature;
	//divided by 2 so as to get the half journey time.
	double DistanceInCm = SpeedSoundInCmPerMicroseconds * (double)timeinMicroseconds/2.0   ;


	//If the calculated distance isn't in range then return -1.0
	if(DistanceInCm == 0 || DistanceInCm == 400)
	{
		return -1.0;
	}

	else

		return DistanceInCm;
}
