/*
 * LCD_I2C_library_test.c
 *
 *  Created on: 05-Feb-2021
 *      Author: vermas
 */

/* file that will test the I2C library of LCD HD44780*/

#include<stdio.h>
#include"stm32f44xx_gpio_driver.h"
#include"LCD_HD44780_I2C.h"
#include<pthread.h>

I2C_Handle_t I2C1Handle;

//user button connected to PC13
void GPIO_Button_Init(void)
{
	GPIO_Handle_t GPIOBtn;

	//select the GPIO Port
	GPIOBtn.pGPIOx = GPIOC;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIOBtn.GPIO_PinConfig.GPIO_PinOPType = GPIO_OPTYPE_PUSH_PULL;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdCtrl = GPIO_PIN_NO_PUPD;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;

	GPIO_Init(&GPIOBtn);


}

/* Pins mapping
 * PB6 -> I2C1_SCL
 * PB7 -> I2C1_SDA
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


    I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
    //put the values in Registers of GPIO
    GPIO_Init(&I2CPins);

}

/* To initialize the I2C1 Peripheral*/
void I2C1_Init(void)
{

	//Initialize the GPIO pins to behave as I2C1
	I2C1_GPIO_Init();

    I2C1Handle.pI2Cx = I2C1;//select the I2C1

    I2C1Handle.I2C_Config.I2C_ACKCtrl = I2C_ACK_EN;
    //I2C1Handle.I2C_Config.I2C_DeviceAddress = MYADDR;//arbitrary value of 0x61
    I2C1Handle.I2C_Config.I2C_FMDUTYCYCL= I2C_FM_DUTY2;//not using fast mode
    I2C1Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_ST_MODE;//speed is 100KHz for standard mode
    I2C_Init(&I2C1Handle);
}

void display_enemies()
{

	uint8_t enemies_position = 0x8F ;

	LCD_HD44780_Send_Cmd(enemies_position, I2C1Handle);
	LCD_HD44780_Send_Data(0x1,I2C1Handle);

}

int main(void)
{
	//Initialization of button
	GPIO_Button_Init();

	//Initialization of I2C1 peripheral
	I2C1_Init();



	//Enable the I2C1 peripheral
	I2C_PeripheralControl(I2C1, ENABLE);

	//Initialize the LCD
	LCD_HD44780_Init(I2C1Handle);

	uint8_t Man_Character[] = {0x0E, 0x0E, 0x04, 0x1F, 0x04, 0x04, 0x0A, 0x0A};
	(void)Man_Character;

	uint8_t man_still[] =  {
			  0b01100,
			  0b1100,
			  0b0000,
			  0b11110,
			  0b01100,
			  0b01100,
			  0b01100,
			  0b11110
	};
	(void)man_still;

	/*
	uint8_t man_run[] = {
	  B01100,
	  B01100,
	  B00000,
	  B01110,
	  B11100,
	  B01100,
	  B11100,
	  B10011
	};
	(void)man_run;

	uint8_t run_backward[] = {
	  B01100,
	  B01100,
	  B00000,
	  B01110,
	  B11100,
	  B01100,
	  B01100,
	  B01100
	};

	(void)run_backward;
	*/
	uint8_t enemy[] = {
			0b01010,
			0b01010,
			0b01110,
			0b00100,
			0b00000,
			0b00000,
			0b00000,
			0b00000
	};

	(void)enemy;
	uint8_t player[] = {
	  0b00000,
	  0b00000,
	  0b11100,
	  0b00110,
	  0b00111,
	  0b00110,
	  0b11100,
	  0b00000
	};


	(void)player;

	uint8_t player_clear = 254;
	/************* Player initialized in CGRAM************/
	LCD_HD44780_Send_Cmd(0x40,I2C1Handle);
	for(int i = 0;i<7;i++)
			LCD_HD44780_Send_Data(player[i],I2C1Handle);
	/*************************************************/


	/************************ Enemy initialized in CGRAM*****/
	LCD_HD44780_Send_Cmd(0x48,I2C1Handle);
	for(int i = 0;i<7;i++)
			LCD_HD44780_Send_Data(enemy[i],I2C1Handle);


	/**********************************************************/
	//setting the DDRAM address
	LCD_HD44780_Send_Cmd(0x80, I2C1Handle);
	LCD_HD44780_Send_Data(0x0, I2C1Handle);
	/***************************************/
	uint8_t player_position = 0x80;

//first tell the position using DDRAM and then specify
	//the custom character .

	while(1)
	{
		player_position = 0x80 ;
		LCD_HD44780_Send_Cmd(player_position, I2C1Handle);
		LCD_HD44780_Send_Data(0x0,I2C1Handle);
		while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13))
		{
			display_enemies();
		}


		//LCD_HD44780_Send_Cmd(player_position, I2C1Handle);
		LCD_HD44780_Send_Cmd(player_position, I2C1Handle);
		LCD_HD44780_Send_Data(player_clear,I2C1Handle);
		player_position |= 0x40 ;
		LCD_HD44780_Send_Cmd(player_position, I2C1Handle);
		LCD_HD44780_Send_Data(0x0,I2C1Handle);

		while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13))
		{
			display_enemies();
		}

		LCD_HD44780_Send_Cmd(player_position, I2C1Handle);
		LCD_HD44780_Send_Data(player_clear,I2C1Handle);



	}

	/*
	uint8_t Alarm_sign [] ={0x04 , 0x0E,0x0E,0x0E,0x0E,0x1F,0x04,0x00};
	//define the location of CGRAM
	LCD_HD44780_Send_Cmd(0x40,I2C1Handle);



	for(int i = 0;i<7;i++)
		LCD_HD44780_Send_Data(Alarm_sign[i],I2C1Handle);

	LCD_HD44780_Send_Cmd(0x48,I2C1Handle);
	for(int i = 0;i<7;i++)
		LCD_HD44780_Send_Data(Man_Character[i],I2C1Handle);


	//setting the DDRAM address
	LCD_HD44780_Send_Cmd(0x80, I2C1Handle);


	while(1)
	{
		while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13));
		//setting the DDRAM address
		LCD_HD44780_Send_Cmd(0x80, I2C1Handle);
		LCD_HD44780_Send_Data(0x0,I2C1Handle);

		//setting the DDRAM address
		LCD_HD44780_Send_Cmd(0x81, I2C1Handle);
		LCD_HD44780_Send_Data(0x1,I2C1Handle);


	}
	*/





}
