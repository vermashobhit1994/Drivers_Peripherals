/*
 * lcd_receive_data_i2c.c
 *
 *  Created on: 25-Sep-2020
 *      Author: vermas
 */
#include"stm32f446xx.h"
#include<time.h>

#define SLAVE_ADDR       0x27//default address of LCD
#define MYADDR           0x00

I2C_Handle_t I2C1Handle;
/* Pins mapping
 * PB6 -> I2C1_SCL
 * PB7 -> I2C1_SDA
 */
/**************************** NOTE : Here P3 of PCF8574 is always high******************************/
void delay_us(uint32_t microseconds)//generate 1us delay
{
	long pause;
	clock_t now,then;

	pause = microseconds*(CLOCKS_PER_SEC/16000000);
	now = then = clock();
	while( (now-then) < pause )
	    now = clock();
}

void lcd_send_cmd (char cmd)
{
  uint8_t data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1,r/w=0,rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0,r/w=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0,r/w=0
	data_t[3] = data_l|0x08;  //en=0, rs=0,r/w=0
	I2C_MasterSendData(&I2C1Handle, data_t, sizeof(data_t), SLAVE_ADDR);
	//I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=1
	data_t[1] = data_u|0x09;  //en=0, rs=1
	data_t[2] = data_l|0x0D;  //en=1, rs=1
	data_t[3] = data_l|0x09;  //en=0, rs=1
	I2C_MasterSendData(&I2C1Handle, data_t, sizeof(data_t), SLAVE_ADDR);

	//HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}


void lcd_init (void)
{
	// 4 bit initialisation



	    delay_us(50000);//wait for 1ms

	lcd_send_cmd (0x31);//8 bit one line 5*8 dots
	delay_us(1000);//wait for 1ms

	lcd_send_cmd (0x20);//8 bit one line 5*8 dots
	delay_us(10000);//wait for 1ms

	lcd_send_cmd (0x28);//8 bit one line 5*8 dots
	delay_us(1000);//wait for 1ms



	lcd_send_cmd (0x01);//8 bit one line 5*8 dots
	delay_us(2000);//wait for 2ms

	lcd_send_cmd (0x06);//8 bit one line 5*8 dots
	delay_us(1000);//wait for 1ms

	lcd_send_cmd (0x0C);//8 bit one line 5*8 dots

}


void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
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

    I2C1Handle.pI2Cx = I2C1;//select the I2C1

    I2C1Handle.I2C_Config.I2C_ACKCtrl = I2C_ACK_EN;
    //I2C1Handle.I2C_Config.I2C_DeviceAddress = MYADDR;//arbitrary value of 0x61
    I2C1Handle.I2C_Config.I2C_FMDUTYCYCL= I2C_FM_DUTY2;//not using fast mode
    I2C1Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_ST_MODE;//speed is 100KHz for standard mode
    I2C_Init(&I2C1Handle);
}


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


int main()
{

	GPIO_Button_Init();//initialize the button
	//to make gpio pins behave as i2c
	I2C1_GPIO_Init();
	I2C1_Init();
	I2C_PeripheralControl(I2C1, ENABLE);


	{
		while(!GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_NO_13));
		delay_us(2000);
		lcd_init();

		lcd_send_data('S');

	}while(1);


}
