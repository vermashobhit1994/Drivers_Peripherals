/*
 * LCD_bsp.c
 *
 *  Created on: 29-Jan-2021
 *      Author: vermas
 */

#ifndef INC_LCD_BSP_C_
#define INC_LCD_BSP_C_

/************ Driver Dependencies *****************
 *
 *stm32f446xx.h
 *stm32f44xx_gpio_driver.h
 */
#include"stm32f446xx.h"
//#include"stm32f44xx_gpio_driver.h"

/* BSP (board support package ) exposed API's
 *
 */

//Initialize the LCD
void LCD_HD44780_bsp_Init();
//send the command
void LCD_HD44780_bsp_Send_Cmd(uint8_t cmd);

void LCD_HD44780_bsp_Send_Char(uint8_t cmd);
void LCD_HD44780_bsp_Clear();



/*******************************************************************************
 * For override the configuration items
 * #define __LCD_CONFIG__
 * #define LCD_GPIO_PORT           GPIOB//default port for LCD
 * #define LCD_GPIO_RS              GPIO_PIN_NO_0
	#define LCD_GPIO_RW              GPIO_PIN_NO_1
	#define LCD_GPIO_EN              GPIO_PIN_NO_2
	#define LCD_GPIO_D4              GPIO_PIN_NO_3
	#define LCD_GPIO_D5              GPIO_PIN_NO_4
	#define LCD_GPIO_D6              GPIO_PIN_NO_5
	#define LCD_GPIO_D7              GPIO_PIN_NO_6
 *
 */

/* Application Configurable Items ****/
//Default configurations
#ifndef __LCD_CONFIG__
#define __LCD_CONFIG__
#define LCD_GPIO_PORT            GPIOB
#define LCD_GPIO_RS              GPIO_PIN_NO_0
#define LCD_GPIO_RW              GPIO_PIN_NO_1
#define LCD_GPIO_EN              GPIO_PIN_NO_2
#define LCD_GPIO_D4              GPIO_PIN_NO_3
#define LCD_GPIO_D5              GPIO_PIN_NO_4
#define LCD_GPIO_D6              GPIO_PIN_NO_5
#define LCD_GPIO_D7              GPIO_PIN_NO_6
#endif

//LCD Command codes
#define LCD_CMD_4DL_2N_5X8F      0x28
#define LCD_CMD_DISP_ON_CUR_ON   0x0E
#define LCD_CMD_IN_ADDR          0x06
#define LCD_CMD_DISP_CLR         0x01
#define LCD_CMD_DISP_RET_HOME    0x02





#endif /* INC_LCD_BSP_C_ */
