
#ifndef INC_STM32F446XX_GPIO_H_
#define INC_STM32F446XX_GPIO_H_

bool GPIO_Read_Input_Pin(GPIOx_RegDef_t *pGPIOx, uint8_t GPIOPinNumber);
void GPIO_Write_Output_Pin(GPIOx_RegDef_t *pGPIOx, uint8_t Value,uint8_t PinNumber);
/******************* GPIO Pin No Definations ********************/
typedef const enum
{
	GPIO_PIN_NO_0,
	GPIO_PIN_NO_1 ,
	GPIO_PIN_NO_2,
	GPIO_PIN_NO_3,
	GPIO_PIN_NO_4,
	GPIO_PIN_NO_5,
	GPIO_PIN_NO_6,
	GPIO_PIN_NO_7,
	GPIO_PIN_NO_8,
	GPIO_PIN_NO_9,
	GPIO_PIN_NO_10,
	GPIO_PIN_NO_11,
	GPIO_PIN_NO_12,
	GPIO_PIN_NO_13,
	GPIO_PIN_NO_14,
	GPIO_PIN_NO_15
}GPIO_PIN_NO;

#endif
