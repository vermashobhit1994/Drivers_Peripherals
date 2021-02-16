/*
 * LCD_bsp.c
 *
 *  Created on: 29-Jan-2021
 *      Author: vermas
 */


#include"LCD_HD44780_bsp.h"

void mdelay(uint32_t cnt)
{
	for(uint32_t i = 0;i<cnt * 1000;i++);
}

void udelay(uint32_t cnt)
{
	for(uint32_t i = 0;i<cnt * 1;i++);

}

//check timing diagram on Page22 of datasheet
static void LCD_Enable()
{
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_EN, GPIO_PIN_SET);
	udelay(10);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_EN, GPIO_PIN_RESET);
	udelay(100); //must be >37 us

}


//Write 4 bit data on DB7, DB6, DB5,DB4
//Here we are extracting data from Lower 4 bits
static void Write_4_bit_data(uint8_t Value)
{
	//to make the value goes to LSB bit and then extract it
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D4, (Value >> 0 ) & 0x1);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D5, (Value >> 1 ) & 0x1);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D6, (Value >> 2 ) & 0x1);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D7, (Value >> 3 ) & 0x1);


	LCD_Enable();

}


void LCD_HD44780_bsp_Init()
{
	//1. configure the GPIO Pins which are used for LCD connections
	GPIO_Handle_t LCD_Pins;

	//select the port as given by user
	LCD_Pins.pGPIOx = LCD_GPIO_PORT;

	LCD_Pins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;

	//Configuring the Pin for RS
	LCD_Pins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OPTYPE_PUSH_PULL;
	LCD_Pins.GPIO_PinConfig.GPIO_PinPuPdCtrl = GPIO_PIN_NO_PUPD;
	LCD_Pins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM;
	LCD_Pins.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_RS;
	GPIO_Init(&LCD_Pins);

	//configure the Pin for RW
	LCD_Pins.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_RW;
	GPIO_Init(&LCD_Pins);

	//configure the pin for EN
	LCD_Pins.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_RS;
	GPIO_Init(&LCD_Pins);

	//configure the pin for D4
	LCD_Pins.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D4;
	GPIO_Init(&LCD_Pins);

	//configure the pin for D5
	LCD_Pins.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D5;
	GPIO_Init(&LCD_Pins);

	//configure the pin for D6
	LCD_Pins.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D6;
	GPIO_Init(&LCD_Pins);

	//configure the pin for D7
	LCD_Pins.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D7;
	GPIO_Init(&LCD_Pins);


	/************ Reset all the pins to 0 initially *************/
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, 0);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, 0);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_EN, 0);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D4, 0);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D5, 0);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D6, 0);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D7, 0);


	//2. LCD Initialization

		//step 2a : Initial delay of > 40ms
	    mdelay(40);

	    //step 2b : RS = 0, for LCD command
	    GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, 0);

	    //Step 2c : RnW = 0, for Write to LCD, nW for W bar
	    GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, 0);

	    //Step 2d : Write DB7 = 0, DB6 = 0, DB5 = 1, DB4 = 1
	    Write_4_bit_data(0x3);

	    //Step 2e : Wait for >4.1ms
	    mdelay(5);

	    //Step 2f : Write DB7 = 0, DB6 = 0, DB5 = 1, DB4 = 1
	    Write_4_bit_data(0x3);


	    //Step 2g : Wait for >100us
	    udelay(150);

	    //Step 2h : Write DB7 = 0, DB6 = 0, DB5 = 1, DB4 = 1
	    Write_4_bit_data(0x3);

	    //Step 2i : Write DB7 = 0, DB6 = 0, DB5 = 1, DB4 = 0
	    Write_4_bit_data(0x3);


	    //Step 2j : Function set commands
	    LCD_HD44780_bsp_Send_Cmd(LCD_CMD_4DL_2N_5X8F);

	    //Step 2k : Display ON cursor ON
	    LCD_HD44780_bsp_Send_Cmd(LCD_CMD_DISP_ON_CUR_ON);

	    //Step 2l : display clear command
	    LCD_HD44780_bsp_Clear();


	    //Step 2m : Entry mode set command
	    LCD_HD44780_bsp_Send_Cmd(LCD_CMD_IN_ADDR);

}



void LCD_HD44780_bsp_Clear()
{
	LCD_HD44780_bsp_Send_Cmd(LCD_CMD_DISP_CLR);
	mdelay(2);

}

void LCD_HD44780_bsp_Send_Cmd(uint8_t cmd)
{
	//Step1 : RS = 0
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, 0);

	//Step2 : RW = 0
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, 0);

	//first send higher nibble
	Write_4_bit_data(cmd >> 4);

	//Send lower nibble
	Write_4_bit_data(cmd & 0x0F);

	//HIgh to low transition on EN PIN
	LCD_Enable();

}

void LCD_HD44780_bsp_Send_Char(uint8_t data)
{
	//Step1 : RS = 1 for sending data
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, 1);

	//Step2 : RW = 0
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, 0);

	//first send higher nibble
	Write_4_bit_data(data >> 4);

	//Send lower nibble
	Write_4_bit_data(data & 0x0F);

	//HIgh to low transition on EN PIN
	LCD_Enable();

}





