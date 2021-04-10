/*
 * I2C_Testing.c
 *
 *  Created on: 20-Sep-2020
 *      Author: vermas
 */

/**************** Here we are sending data to LCD ***************/

//#include<string.h>
//#include<time.h>
//#include"LCD_HD44780.h"
#include<stdio.h>
#include"delay.h"


#define MYADDR           0x61
#define SLAVE_ADDR       0x27//default address of LCD


I2C_Handle_t I2C1Handle;//used by I2C1_Init() and I2C_Peripheral_Control()
GPIO_Handle_t GPIOBtn,GPIOLed;

/* Not used here
void delay(uint32_t microseconds)//generate 1us delay
{
	long pause;
	clock_t now,then;

	pause = microseconds*(CLOCKS_PER_SEC);
	now = then = clock();
	while( (now-then) < pause )
	    now = clock();
}
*/


/* Here PB6 -> I2C1_SCL
 *      PB7 -> I2C1_SDA
 */

void I2C1_GPIO_Init(void)
{
    GPIO_Handle_t I2CPins;
    //select the gpio port
    I2CPins.pGPIOx = GPIOB;

    //select the mode
    I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4;//choose the AF4
    I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFUN;
    I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OPTYPE_OPEN_DRAIN;//due to I2C
    I2CPins.GPIO_PinConfig.GPIO_PinPuPdCtrl = GPIO_PIN_PULL_UP;//use the INternal pull up for SDA and SCL
    I2CPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM;//choose any arbitrary value

    //configure for SCL
    I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
    //put the values in Registers of GPIO
    GPIO_Init(&I2CPins);


    //Configure for SDA
    I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
    //put the values in Registers of GPIO
    GPIO_Init(&I2CPins);

}

/* To initialize the I2C1 Peripheral*/
void I2C1_Init(void)
{

    I2C1Handle.pI2Cx = I2C1;

    I2C1Handle.I2C_Config.I2C_ACKCtrl = I2C_ACK_EN;
    //see the reserved address first.
    I2C1Handle.I2C_Config.I2C_DeviceAddress = MYADDR;//arbitrary value of 0x61
    I2C1Handle.I2C_Config.I2C_FMDUTYCYCL= I2C_FM_DUTY2;//not using fast mode and using the standard mode only.
    I2C1Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_ST_MODE;//speed is 100KHz for standard mode
    I2C_Init(&I2C1Handle);
}


//user button connected to PC13
//Configure the user button.
void GPIO_Button_Init(void)
{


	//select the GPIO Port
	GPIOBtn.pGPIOx = GPIOC;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIOBtn.GPIO_PinConfig.GPIO_PinOPType = GPIO_OPTYPE_PUSH_PULL;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdCtrl = GPIO_PIN_NO_PUPD;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;

	GPIO_Init(&GPIOBtn);


}

//taken PB8 as  LED
void LED_Init()
{

	GPIOLed.pGPIOx = GPIOB;
	GPIOLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8;
	GPIOLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OPTYPE_PUSH_PULL;
	GPIOLed.GPIO_PinConfig.GPIO_PinPuPdCtrl = GPIO_PIN_NO_PUPD;
	GPIOLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM;

	GPIO_Init(&GPIOLed);


}




void LCD_Write_Data(uint8_t *string)
{

	while( (*string) != '\0')
	{
		LCD_Send_Data(*string,I2C1Handle);
		string++;
	}
}

void LCD_Data_Write_btn_press(uint8_t *string)
{
	//Turn ON LED to indicate to press switch.
	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_8, 1);

	while(GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_NO_13) )
	;
	delay_ms(1);


	//Turn OFF the led to indicate switch is pressed
	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_8, 0);


	LCD_Send_Cmd(0x01,I2C1Handle);
	delay_ms(2);
	LCD_Send_Cmd(0x02,I2C1Handle);
	delay_ms(2);




	LCD_Write_Data(string);
	delay_ms(10);

}


void scroll_text_horizontal(uint8_t text)
{
	//Turn ON LED to indicate to press switch.
	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_8, 1);

	//while(GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_NO_13) )
	//;
	delay_ms(500);
	//Turn OFF the led to indicate switch is pressed
	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_8, 0);


	//shift the character to right
	LCD_Send_Cmd(0x1C,I2C1Handle );
	delay_ms(50);


}

int main(void)
{
	GPIO_Button_Init();//initialize the button

	LED_Init();

	//enable the timer6
	TIMER6_Init();



	//to make gpio pins behave as i2c
	I2C1_GPIO_Init();

	//done by driver itself
	//I2C_PeriClock_Ctrl(I2C1,ENABLE);//enable the clock for I2C1

	//I2C1 Peripheral configuration
	I2C1_Init();



	//enable the I2C peripheral. This must be done after initialization of I2C data.
	I2C_PeripheralControl(I2C1, ENABLE);


	/*********** NOTE :          *********************************************/
	//enable the I2C1 Peripheral
	//I2C Peripheral Configuration.

	//Turn ON LED to indicate to press switch.
	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_8, 1);

	while(GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_NO_13));

	//Turn OFF the led to indicate switch is pressed
	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_8, 0);

	LCD_Init(I2C1Handle);


	uint8_t string []= "India is great";
	while(1)
	{
		LCD_Data_Write_btn_press(string);
		delay_ms(1000);


		/******** Scroll the text only when switch is pressed ****/
		//Turn ON LED to indicate to press switch.
		GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_8, 1);
		while(GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_NO_13) );
		delay_ms(1);
		//Turn OFF the led to indicate switch is pressed
		GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_8, 0);



		uint8_t i = 0;
		while(i < 16 )
		{
			scroll_text_horizontal(string[i]);
			i++;

		}




	}



}
