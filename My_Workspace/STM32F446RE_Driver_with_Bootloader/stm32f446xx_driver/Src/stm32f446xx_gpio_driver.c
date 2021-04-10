


#include"stm32f446xx.h"


bool GPIO_Read_Input_Pin(GPIOx_RegDef_t *pGPIOx, uint8_t GPIOPinNumber)
{
	uint8_t value = ( (pGPIOx -> GPIOx_IDR) & (1 << (GPIOPinNumber) )) ;
	return value;
}

void GPIO_Write_Output_Pin(GPIOx_RegDef_t *pGPIOx, uint8_t Value,uint8_t PinNumber)
{

	//GPIO Pin configured for output type as push pull

	if(Value == 1 || Value == 0)
		pGPIOx -> GPIOx_ODR = (Value << PinNumber);

}

