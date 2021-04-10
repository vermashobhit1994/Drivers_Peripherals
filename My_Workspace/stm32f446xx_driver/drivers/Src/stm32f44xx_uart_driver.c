/*
 * stm32f44xx_uart_driver.c
 *
 *  Created on: 30-Jan-2021
 *      Author: vermas
 */


#include"stm32f446xx.h"




/*******************************************************************************************
 ****************************API's definitions supported by this driver*********************************/


/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_SendData_Interrupt
 * @brief                        : To send data to slave via the interrupt.
 *  @param[in]                   : Pointer to handle structure
 * @param[in]                    : Pointer to user buffer.
 * @param[in]                    : length of user buffer.
 * @return                       : Current State of SPI TX
 * Special Note                  : Save the data in global variable and enable the TXEIE bit to enable the Interrupt.
 */

void USART_PeriClockCtrl(USART_RegDef_t *pUSARTx, uint8_t ENOrDI)
{
	//enable the clock for USART1, USART2, USART3, UART4, UART5
		if(ENOrDI == ENABLE)
		{
			if(pUSARTx == USART1)
				USART1_PERI_CLK_EN();
			else if(pUSARTx == USART2)
				USART2_PERI_CLK_EN();
			else if(pUSARTx == USART3)
				USART3_PERI_CLK_EN();
			else if (pUSARTx == UART4)
				UART4_PERI_CLK_EN();
			else if (pUSARTx == UART5)
				UART5_PERI_CLK_DI();


		}
		//disable the clock USART1, USART2, USART3, UART4, UART5
		else
		{
			if(pUSARTx == USART1)
				USART1_PERI_CLK_DI();
			else if(pUSARTx == USART2)
				USART2_PERI_CLK_DI();
			else if(pUSARTx == USART3)
				USART3_PERI_CLK_DI();
			else if (pUSARTx == UART4)
				UART4_PERI_CLK_EN();
			else if (pUSARTx == UART5)
				UART5_PERI_CLK_DI();


		}

}

/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_SendData_Interrupt
 * @brief                        : To send data to slave via the interrupt.
 *  @param[in]                   : Pointer to handle structure
 * @param[in]                    : Pointer to user buffer.
 * @param[in]                    : length of user buffer.
 * @return                       : Current State of SPI TX
 * Special Note                  : Save the data in global variable and enable the TXEIE bit to enable the Interrupt.
 */

void USART_PeripheralControl(I2C_RegDef_t *pUSARTx,uint8_t ENOrDI)
{
	if(ENOrDI == ENABLE)
		pUSARTx -> I2C_CR[0] |= (1 << USART_CR1_UE);
	else
		pUSARTx -> I2C_CR[0] &= ~(1 << USART_CR1_UE);
}

/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_SendData_Interrupt
 * @brief                        : To send data to slave via the interrupt.
 *  @param[in]                   : Pointer to handle structure
 * @param[in]                    : Pointer to user buffer.
 * @param[in]                    : length of user buffer.
 * @return                       : Current State of SPI TX
 * Special Note                  : Save the data in global variable and enable the TXEIE bit to enable the Interrupt.
 */

void USART_ClearFlag(USART_RegDef_t *pUSARTx,uint32_t FlagName)
{
	if((pUSARTx -> USART_SR) & FlagName)
		pUSARTx -> USART_SR &= ~(FlagName)	;

}

/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_SendData_Interrupt
 * @brief                        : To send data to slave via the interrupt.
 *  @param[in]                   : Pointer to handle structure
 * @param[in]                    : Pointer to user buffer.
 * @param[in]                    : length of user buffer.
 * @return                       : Current State of SPI TX
 * Special Note                  : Save the data in global variable and enable the TXEIE bit to enable the Interrupt.
 */

uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx,uint32_t FlagName)
{
	/*test the FlagName  in I2C_SR1 Register.
		If the value is set return 1(FLAG_SET) */
		if((pUSARTx -> USART_SR) & FlagName)
			return USART_FLAG_SET;
		   //else return 0(FLAG_RESET)
		return USART_FLAG_RESET;
}

/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_SendData_Interrupt
 * @brief                        : To send data to slave via the interrupt.
 *  @param[in]                   : Pointer to handle structure
 * @param[in]                    : Pointer to user buffer.
 * @param[in]                    : length of user buffer.
 * @return                       : Current State of SPI TX
 * Special Note                  : Save the data in global variable and enable the TXEIE bit to enable the Interrupt.
 */

//to configure the Interrupt i.e IRQ no of USART
void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t ENOrDI)
{
	/* Configurations for the Interrupt Set Enable Register(ISER)*/
		if(ENOrDI == ENABLE)//if the Interrupt is enable
		{
			//select the IRQ No range
			if(IRQNumber <= 31)//since each register is of 32 bit size
			{
				//code for ISER0 Register
				//putting the IRQNumber in NVIC_ISER0 Register
				(*NVIC_ISER0_BASE_ADDR) |= (1<<IRQNumber);
			}
			else if(IRQNumber > 31 && IRQNumber <64)//for getting the next IRQNumber add 32.
			{
				//code for ISER1Register
				/*putting the IRQNumber in NVIC_ISER0 Register.
				 * Since to select the particular register we modulus(%) by 32 since each register is of 32 bit size*/
				(*NVIC_ISER1_BASE_ADDR) |= (1<<(IRQNumber % 32) );
			}
			else if(IRQNumber >= 64 && IRQNumber <96)//for getting the next IRQNumber add 32
			{
				//code for ISER2 Register
				//putting the IRQNumber in NVIC_ISER0 Register
				(*NVIC_ISER2_BASE_ADDR) |= (1<<(IRQNumber  % 64));
			}
		}

		else //configurations for the ICER(Interrupt Clear Enable Register) Register to disable the interrupt
		{
				//select the IRQ No range
				if(IRQNumber <= 31)//since each register is of 32 bit size
				{
					//code for ICER0 Register
					//putting the IRQNumber in NVIC_ISER0 Register
					*NVIC_ICER0_BASE_ADDR |= (1<<(IRQNumber ));
				}
				else if(IRQNumber > 31 && IRQNumber <64)//for getting the next IRQNumber add 32.
				{
					//code for ICER1Register
					//putting the IRQNumber in NVIC_ISER0 Register
					(*NVIC_ICER1_BASE_ADDR) |= (1<<(IRQNumber % 32) );
				}
				else if(IRQNumber >= 64 && IRQNumber <96)//for getting the next IRQNumber add 32
				{
					//code for ICER2 Register
					//putting the IRQNumber in NVIC_ISER0 Register
					(*NVIC_ICER2_BASE_ADDR) |= (1<<(IRQNumber % 64));
				}

		}

}

/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_SendData_Interrupt
 * @brief                        : To send data to slave via the interrupt.
 *  @param[in]                   : Pointer to handle structure
 * @param[in]                    : Pointer to user buffer.
 * @param[in]                    : length of user buffer.
 * @return                       : Current State of SPI TX
 * Special Note                  : Save the data in global variable and enable the TXEIE bit to enable the Interrupt.
 */

//to configure the priority of I2C
void USART_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority)
{
	//Step 1. Select the IPRx Register
	uint8_t iprx = IRQNumber / 4;
	//select the section from a particular iprx register
	uint8_t iprx_section = IRQNumber % 4;
	/*Here *4 since to shift the iprx register base address by 4
	 * Here *8 to access that particular bit in iprx register
	 * NO_OF_PRIORITY_BITS_IMPLEMENTED is depend on processor and 8- for select the high 4 bits in priority
	 * since the lower bits aren't implemented in each priority field	*/
	uint8_t shift_amt = (8 * iprx_section) + (8 - NO_OF_PRIORITY_BITS_IMPLEMENTED);
	//NOTE: In NVIC Register lower 8 bits isn't implemented so max value is 15
	*(NVIC_PR_BASE_ADDR + (iprx  )) |= (IRQPriority <<  shift_amt);


}


/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_SendData_Interrupt
 * @brief                        : To send data to slave via the interrupt.
 *  @param[in]                   : Pointer to handle structure
 * @param[in]                    : Pointer to user buffer.
 * @param[in]                    : length of user buffer.
 * @return                       : Current State of SPI TX
 * Special Note                  : Save the data in global variable and enable the TXEIE bit to enable the Interrupt.
 */

void USART_DeInit(USART_RegDef_t *pUSARTx)
{
	if(pUSARTx  == USART1)
		USART1_REG_RESET();
	else if(pUSARTx  == USART2)
		USART2_REG_RESET();
	else if(pUSARTx  == USART3)
			USART3_REG_RESET();
	else if(pUSARTx  == UART4)
			UART4_REG_RESET();
	else if(pUSARTx  == UART5)
			UART5_REG_RESET();
	else if(pUSARTx  == USART6)
		USART6_REG_RESET();





}





