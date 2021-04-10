/*
 * LCD_HD44780.c
 *
 *  Created on: 20-Jan-2021
 *      Author: vermas
 */

#include "LCD_HD44780_I2C.h"
#include"delay.h"//for delay_ms



void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer,uint32_t len,uint8_t SlaveAddr);



void LCD_HD44780_Send_Data(uint8_t value,I2C_Handle_t I2C1Handle)
{
	//Variables to store the lower and higher nibble
	int8_t data_MSB =0,data_LSB = 0;

	//To store the RS, RW and EN values
	uint8_t data_init[4] = {0};

	data_MSB = value & 0xF0;
	//move the LSB nibble to MSB nibble
	data_LSB = (value << 4)& 0xF0;

	//putting upper 4 bits then lower 4 bits in array data_init
	//Here high to low pulse on EN bit to send the command
	//RS = 0 to send the command.
	data_init[0] = data_MSB | 0x0D;//EN = 1, RS = 1
	data_init[1] = data_MSB | 0x09;//EN = 0, RS = 1
	data_init[2] = data_LSB | 0x0D;//EN = 1, RS = 0
	data_init[3] = data_LSB | 0x09;//EN = 0, RS = 0

	uint8_t slaveaddr = 0x27;
	//Send the whole array to LCD
	I2C_MasterSendData(&I2C1Handle, data_init, sizeof(data_init),slaveaddr);



}

/* Send the MSB 4 bit data then 4 lower bit data*/
void LCD_HD44780_Send_Cmd(uint8_t cmd,I2C_Handle_t I2C1Handle)
{
	//Variables to store the lower and higher nibble
	uint8_t data_MSB =0,data_LSB = 0;


	//To store the RS, RW and EN values
	uint8_t data_init[4] = {0};

	data_MSB = cmd & 0xF0;
	//move the LSB nibble to MSB nibble
	data_LSB = (cmd << 4)& 0xF0;

	//putting upper 4 bits then lower 4 bits in array data_init
	//Here high to low pulse on EN bit to send the command
	//RS = 0 to send the command.
	data_init[0] = data_MSB | 0x0C;//EN = 1, RS = 0 and LCD backlight = ON
	data_init[1] = data_MSB | 0x08;//EN = 0, RS = 0 and LCD backlight = ON
	data_init[2] = data_LSB | 0x0C;//EN = 1, RS = 0 and LCD backlight = ON
	data_init[3] = data_LSB | 0x08;//EN = 0, RS = 0 and LCD backlight = ON

	volatile uint8_t slaveaddr = 0x27;
	//Send the whole array to LCD
	I2C_MasterSendData(&I2C1Handle, data_init, sizeof(data_init),slaveaddr);



}

//function that will do the Init at reset of LCD
//see the page 46 of datasheet
void LCD_HD44780_Init(I2C_Handle_t I2CHandle)
{
	TIMER6_Init();

	uint8_t slaveaddr = 0x27;
	uint8_t txbuffer = 0;

	delay_ms(40);

	txbuffer = 0x03 ;
	//LCD_Send_Cmd(txbuffer,I2CHandle);
	I2C_MasterSendData(&I2CHandle, &txbuffer, sizeof(txbuffer),slaveaddr);


	delay_ms(5);

	txbuffer = 0x03 ;//initialize for 8 bit data length with EN = 1
	//LCD_Send_Cmd(txbuffer,I2CHandle);
	I2C_MasterSendData(&I2CHandle, &txbuffer, sizeof(txbuffer),slaveaddr);

	delay_us(150);

	txbuffer = 0x03 ;//initialize for 8 bit data length with EN = 1
	//LCD_Send_Cmd(txbuffer,I2CHandle);
	I2C_MasterSendData(&I2CHandle, &txbuffer, sizeof(txbuffer),slaveaddr);


	/******* Step2 : Set the data length as 4 bit **********/
	txbuffer = 0x20 ;//initialize for 4  bit data length with 2 display lines and 5x8 dots.
	LCD_HD44780_Send_Cmd(txbuffer,I2CHandle);

	//no of lines = 2,5x8 display, 4 bit data length
	txbuffer = 0x28;
	LCD_HD44780_Send_Cmd(txbuffer,I2CHandle);

	//display OFF
	txbuffer = 0x08;
	LCD_HD44780_Send_Cmd(txbuffer,I2CHandle);

	//clear the display
	txbuffer = 0x01;
	LCD_HD44780_Send_Cmd(txbuffer,I2CHandle);
	delay_ms(3);




	//Set cursor position as increment with display ON
	txbuffer = 0x06;
	LCD_HD44780_Send_Cmd(txbuffer,I2CHandle);

	//Set cursor position as increment
	//display ON
	txbuffer = 0x0C;
	LCD_HD44780_Send_Cmd(txbuffer,I2CHandle);


}

/*
void  LCD_HD44780_Init(I2C_Handle_t *I2C1Handle)
{
    //function to initialize the functionality for 4 bit mode when LCD is reset.
	LCD_Reset_Init(I2C1Handle);


	//set the data length = 4bit , No of lines = 2, Font = 5*8
	delay_ms(2);
	LCD_Send_Cmd(0x28,I2C1Handle);


	//turn off display and also clear the display
	delay_ms(3);
	LCD_Send_Cmd(0x08,I2C1Handle);//turn off display
	delay_ms(3);
	LCD_Send_Cmd(0x01,I2C1Handle);//clear the display



	//display ON with cursor blinking
	delay_ms(2);
	LCD_Send_Cmd(0x0F,I2C1Handle);


	//setting the entry mode with cursor shift to right
	delay_ms(2);
	LCD_Send_Cmd(0x06,I2C1Handle);




}
*/



















