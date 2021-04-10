/*
 * LCD_HD44780.h
 *
 *  Created on: 20-Jan-2021
 *      Author: vermas
 */

#ifndef INC_LCD_HD44780_H_
#define INC_LCD_HD44780_H_

#include"stm32f446xx.h"

void LCD_HD44780_Send_Data(uint8_t value,I2C_Handle_t I2C1Handle);
void LCD_HD44780_Send_Cmd(uint8_t cmd,I2C_Handle_t I2C1Handle);
void LCD_HD44780_Init(I2C_Handle_t I2C1Handle);

#endif /* INC_LCD_HD44780_H_ */
