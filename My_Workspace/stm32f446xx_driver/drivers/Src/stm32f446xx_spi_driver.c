/*
 * stm32f446xx_spi_driver.c
 *
 *  Created on: 19-Aug-2020
 *      Author: vermas
 */
//The below file must be included in every specific driver*/
#include"stm32f446xx.h"//include the driver specific header file


/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_PeriClock_Ctrl
 * @brief                        : Function to Control the peripheral clock of SPI.
 * @param[in]                    : Base address of the SPI Register structure .
 * @param[in]                    : Bit to enable or disable.
 * @return                       : None
 * Special Note                  : None
 */
void SPI_PeriClock_Ctrl(SPI_RegDef_t *pSPIx,uint8_t ENOrDI)//enable and disable the peripheral clock
{
	//enable the clock for SPI1, SPI2, SPI3 and SPI4
		if(ENOrDI == ENABLE)
		{
			if(pSPIx == SPI1)
				SPI1_PERI_CLK_EN();
			else if(pSPIx == SPI2)
				SPI2_PERI_CLK_EN();
			else if(pSPIx == SPI3)
				SPI3_PERI_CLK_EN();
			else if(pSPIx == SPI4)
				SPI4_PERI_CLK_EN();
		}
		//disable the clock SPI1, SPI2, SPI3 and SPI4
		else
		{
			if(pSPIx == SPI1)
				SPI1_PERI_CLK_DI();
			else if(pSPIx == SPI2)
				SPI2_PERI_CLK_DI();
			else if(pSPIx == SPI3)
				SPI3_PERI_CLK_DI();
			else if(pSPIx == SPI4)
				SPI4_PERI_CLK_DI();
		}

}

/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_Init
 * @brief                        : Configure the user specfic details in SPI Register.
 * @param[in]                    : Base address of the SPI handle structure
 * @return                       : None
 * Special Note                  : None
 */

void SPI_Init(SPI_Handle_t *pSPIHandle) //initialize the SPI CR1 Register
{
	//enable the SPI Peripheral Clock so no need to configure in user app.
	SPI_PeriClock_Ctrl(pSPIHandle -> pSPIx, ENABLE);

    /****************** Configure the SPI_CR1 Register ****************************************/

	uint32_t tempreg = 0;// temporary register to store the configure items and then put to SPI_CR1 Register.

	/*Configure the device Mode. This is to be done at 3rd LSB bit*/
	tempreg |= pSPIHandle -> SPI_Config.SPI_DeviceMode << SPI_CR1_MSTR;

	/* configure the bus config.*/
	if(pSPIHandle -> SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_FULLDUPLEX)
	{
		//clear the BIDIMODE (15th) bit of SPI_CR1 Register to enable the full duplex.
		tempreg &= ~(1<<SPI_CR1_BIDIMODE);
	}
	else if(pSPIHandle -> SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_HALFDUPLEX)
	{
		//set the BIDIMODE bit of SPI_CR1 Register to enable the half duplex.
		tempreg |= (1<<SPI_CR1_BIDIMODE);
	}
	else if(pSPIHandle -> SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RX_ONLY)
	{
		//clear the BIDIMODE bit of SPI_CR1 Register to enable the unidirectional two lines.
		tempreg &= ~(1<<SPI_CR1_BIDIMODE);
		//set the RXONLY bit of SPI_CR1 Register to enable the simplex .
		tempreg |= (1<<SPI_CR1_RXONLY);

	}

	/* Configure the SPI Clock Speed
	 *put the value in BR bit of SPI_CR1 Register
	 */
	tempreg |= (pSPIHandle -> SPI_Config.SPI_SclkSpeed <<SPI_CR1_BR);

	/*
	 * Configure the SPI Data Frame Format
	 * put the value in DFF bit of SPI_CR1 Register
	 */
	tempreg |= (pSPIHandle -> SPI_Config.SPI_DFF <<SPI_CR1_DFF);

	/*
	 * Configure the SPI Clock Polarity
	 * put the value in CPOL bit of SPI_CR1 Register
	*/
	tempreg |= (pSPIHandle -> SPI_Config.SPI_CPOL <<SPI_CR1_CPOL);

	/*
	 * Configure the SPI Clock Phase
	 * put the value in CPHA bit of SPI_CR1 Register
	*/
	tempreg |= (pSPIHandle -> SPI_Config.SPI_CPHA <<SPI_CR1_CPHA);

	/* Configure the SSM
	 * put the value in SSM bit of SPI_CR1 Register
	 */
	tempreg |= (pSPIHandle -> SPI_Config.SPI_SSM <<SPI_CR1_SSM);

	//put the value in the SPI_CR1 Register from tempreg
	pSPIHandle -> pSPIx -> SPI_CR[0] = tempreg;//directly putting instead of bitwise OR since freshly assign values.

}

/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_DeInit
 * @brief                        : Deinitialize all the user configurable items.
 * @param[in]                    : Base address of the SPI peripheral
 * @return                       : None
 * Special Note                  : None
 */
void SPI_DeInit(SPI_Handle_t *pSPIHandle) //initialize the GPIO Port and Pin
{
	if(pSPIHandle -> pSPIx == SPI1)
		SPI1_REG_RESET();
	else if(pSPIHandle -> pSPIx == SPI2)
		SPI2_REG_RESET();
	else if(pSPIHandle -> pSPIx == SPI3)
		SPI3_REG_RESET();
	else if(pSPIHandle -> pSPIx == SPI4)
		SPI4_REG_RESET();

}

/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_GetFlagStatus
 * @brief                        : Get the status of flag in SPI_SR Register.
 * @param[in]                    : Base address of the SPI Register Structure
 * @param[in]                    : Flag Value either True or False
 * @return                       : true or false i.e whether the flag is set or reset.
 * Special Note                  : None
 */
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx,uint32_t FlagName)
{
	/*test the FlagName  in SR Register.
	If the value is set return 1(FLAG_SET) */
	if(pSPIx -> SPI_SR & FlagName)
		return SPI_FLAG_SET;
    //else return 0(FLAG_RESET)
	return SPI_FLAG_RESET;
}

/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_SendData
 * @brief                        : Send the data to external world.
 * @param[in]                    : Base address of the SPI Register Structure
 * @param[in]                    : Pointer to Transmit buffer.
 * @param[in]                    : No of bytes to send. Here it is decrement when 1 byte of data is transmitted.
 * @return                       : None
 * Special Note                  : This is blocking api since it waits until all the bytes is transmitted.
 */

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer,uint32_t len)
{
	while(len > 0)
	{
		//wait until the TXE bit is 1 in SPI_SR Register
		//while( !(pSPIX -> SPI_SR & (1<<SPI_SR_TXE) )); -> commented since implemented by function
		/* If the return Value of function is 0 then wait here otherwise proceed .*/
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == SPI_FLAG_RESET);

		/* Checking the DFF bit in SPI_CR1.
		 * If the Tx buffer is empty i.e TXE bit is 1 then check the DFF bit of SPI_CR1 Register
		*/
		if( (pSPIx -> SPI_CR[0])  & (1<<SPI_CR1_DFF))//if the DFF bit is set i.e for 16 bit data/receive
		{

			/*STEP 1: Load data in DR Register. Here typecast to (uint16_t) since we want to access 16 bit data via
			user defined buffer pointer but our pointer is of 8 bit size.*/
			pSPIx ->SPI_DR = *( (uint16_t*)pTxBuffer);



			// STEP 2: Decrement len value twice.
			len--;len--;//decrement twice since we're sending 2 bytes of data
			//STEP 3: increment the pointer so as to point to next 16 bit data. Here typecast to (uint16_t) since 16 bit data transfer
			(uint16_t*)pTxBuffer++;
		}
		else//8 bit data for transmit /receive.
		{

			pSPIx ->SPI_DR = *pTxBuffer;//put the value in DR Register from user defined pointer.
			//printf("Read data : %lu\n",pSPIx -> SPI_DR);



			len--;//decrement once since 1 byte of data
			pTxBuffer++;//increment the user defined buffer pointer to point to next 8 bit data.
		}

	}
}

/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_ReceiveData
 * @brief                        : Receive the data from external slave.
 * @param[in]                    : Base address of the SPI Register Structure
 * @param[in]                    : Pointer to Receive buffer.
 * @param[in]                    : No of bytes to receive. Here it is decrement when 1 byte of data is Received.
 * @return                       : None
 * Special Note                  : This is blocking api since it waits until all the bytes is transmitted.
 */

void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer,uint32_t len)
{
	while(len > 0)
	{
		//wait until the RXNE bit is 1 in SPI_SR Register
		//while( !(pSPIX -> SPI_SR & (1<<SPI_SR_RXNE) )); -> commented since implemented by function
		/* If the return Value of function is 0 then wait here otherwise proceed .*/
		while(SPI_GetFlagStatus(pSPIx, SPI_RXNE_FLAG) == SPI_FLAG_RESET)
			;

		/* Checking the DFF bit in SPI_CR1.
		 * If the Rx buffer is empty i.e RXNE bit is 1 then check the DFF bit of SPI_CR1 Register
		*/
		if( (pSPIx -> SPI_CR[0])  & (1<<SPI_CR1_DFF))//if the DFF bit is set i.e for 16 bit data/receive
		{

			/*STEP 1: Load data from DR Register. Here typecast to (uint16_t) since we want to access 16 bit data via
			user defined buffer pointer but our pointer is of 8 bit size.*/
			 *( (uint16_t*)pRxBuffer)  = pSPIx ->SPI_DR ;

			// STEP 2: Decrement len value twice.
			len--;len--;//decrement twice since we're sending 2 bytes of data
			//STEP 3: increment the pointer so as to point to next 16 bit data. Here typecast to (uint16_t) since 16 bit data transfer
			(uint16_t*)pRxBuffer++;
		}
		else//8 bit data for transmit /receive.
		{

			 *pRxBuffer = pSPIx ->SPI_DR ;//put the value from DR Register into user defined pointer buffer.
			len--;//decrement once since 1 byte of data
			pRxBuffer++;//increment the user defined buffer pointer to point to next 8 bit data.
		}

	}
}



/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_PeriControl
 * @brief                        : To enable the SPI Peripheral
 * @param[in]                    : Base address of the SPI Register Structure
 * @param[in]                    : Enable or disable
 * @return                       : None
 * Special Note                  :
 */
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx,uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)//enable the SPI Peripheral
	{
		pSPIx -> SPI_CR[0] |= (1<<SPI_CR1_SPE);//enable the SPE bit of SPI_CR1 Register

	}
	else//disable the SPI Peripheral.
		pSPIx -> SPI_CR[0] &= ~(1<<SPI_CR1_SPE);//disables the SPE bit of SPI_CR1 Register
}

/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_SSIConfig
 * @brief                        : Function to remain the NSS pin high internally when using the SSM = 1
 * @param[in]                    : Base address of the SPI Register Structure
 * @param[in]                    : 8 bit data enable or disable.
 * @return                       : None
 * Special Note                  :
 */

void SPI_SSIConfig(SPI_RegDef_t *pSPIx,uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)//enable the SPI Peripheral
		{
			pSPIx -> SPI_CR[0] |= (1<<SPI_CR1_SSI);//enable the SSI bit of SPI_CR1 Register

		}
		else//disable the SPI Peripheral.
			pSPIx -> SPI_CR[0] &= ~(1<<SPI_CR1_SSI);//disables the SSI bit of SPI_CR1 Register

}



/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_SSOEConfig
 * @brief                        : Enable the NSS bit with master mode.
 * @param[in]                    : Base address of the SPI Register Structure
 * @param[in]                    : 8 bit data enable or disable.
 * @return                       : None
 * Special Note                  :
 */

void SPI_SSOEConfig(SPI_RegDef_t *pSPIx,uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)//enable the SPI Peripheral
		{
			pSPIx -> SPI_CR[1] |= (1<<SPI_CR2_SSOE);//enable the SSOE bit of SPI_CR2 Register

		}
		else//disable the SPI Peripheral.
			pSPIx -> SPI_CR[1] &= ~(1<<SPI_CR2_SSOE);//disables the SSOE bit of SPI_CR2 Register

}

/******************** Interrupt related API's *******************/

/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_IRQInterruptConfig
 * @brief                        : To set the IRQ Number in MCU specific NVIC Register
 * @param[in]                    : IRQ Number
 * @param[in]                    : 8 bit data enable or disable.
 * @return                       : None
 * Special Note                  :
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t ENOrDI)
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
 * @fn                           : SPI_IRQPriorityConfig
 * @brief                        : To configure the priority for Nested Interrupt.
 * @param[in]                    : IRQ Number.
 * @param[in]                    : 8 bit data enable or disable.
 * @return                       : None
 * Special Note                  :
 */
void SPI_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority)
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
uint8_t SPI_SendData_Interrupt(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer,uint32_t len)
{
	//checking the state first
	uint8_t txstate = pSPIHandle -> TxState;

	//modify the length and txbuffer only when the state isn't transmission
	//i.e the state is other than transmission.
	if(txstate != SPI_BUSY_IN_TX)
	{
		//Step 1 : Modify the handle structure to store the global variables from user define buffer and length.
		//check the handle structure.
		pSPIHandle -> pTxBuffer = pTxBuffer;
		pSPIHandle -> TxLen = len;

		//Step 2 : Mark the SPI state as BUSY during transmission so that
		//so that no other code can get execute until the transmission gets over.
		pSPIHandle -> TxState = SPI_BUSY_IN_TX;

		//Step 3 : Enable the TXEIE bit in SPI control register2 to
		//enable the interrupt
		pSPIHandle -> pSPIx -> SPI_CR[1] |= ( 1 << SPI_CR2_TXEIE);

		//Step 4 : Transmit the data .
		//To be handled by ISR

	}
	return txstate;
}



/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_SendData_Interrupt
 * @brief                        : To send data via the interrupt.
 * @param[in]                    : IRQ Number.
 * @param[in]                    : 8 bit data enable or disable.
 * @return                       :
 * Special Note                  :
 */

uint8_t SPI_ReceiveData_Interrupt(SPI_Handle_t *pSPIHandle,uint8_t *pRxBuffer,uint32_t len)
{
	//checking the state first
	uint8_t rxstate = pSPIHandle -> RxState;

	//modify the length and txbuffer only when the state is transmission
	if(rxstate != SPI_BUSY_IN_RX)
	{
		//Step 1 : Modify the handle structure to store the global variables
		//check the handle structure.
		pSPIHandle -> pRxBuffer = pRxBuffer;
		pSPIHandle -> RxLen = len;

		//Step 2 : Mark the SPI state as BUSY during transmission so that
		//so that no other code can get execute until the transmission gets over.
		pSPIHandle -> RxState = SPI_BUSY_IN_RX;

		//Step 3 : Enable the RXNEIE bit in SPI control register2 to
		//enable the interrupt
		pSPIHandle -> pSPIx -> SPI_CR[1] |= ( 1 << SPI_CR2_RXNEIE);

		//Step 4 : Transmit the data .
		//To be handled by ISR

	}
	return rxstate;

}

/* Prototypes for Interrupt Helper functions ****/
/******* Private functions for Interrupt handling ***/
static void SPI_TXE_Interrupt_Handle(SPI_Handle_t *pSPIHandle);
static void SPI_RXNE_Interrupt_Handle(SPI_Handle_t *pSPIHandle);
static void SPI_OVF_ERR_Interrupt_Handle(SPI_Handle_t *pSPIHandle);


/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_IRQHandling
 * @brief                        :
 * @param[in]                    :
 * @param[in]                    :
 * @return                       :
 * Special Note                  :
 */
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle)//the actual function that gets called on Interrupt or Interrupt handler
{
	//check the interrupt in status flag
	uint8_t temp1 = pSPIHandle -> pSPIx -> SPI_SR & ( 1 << SPI_SR_TXE);
	//check only if interrupt is enabled for transmission
	uint8_t temp2 = pSPIHandle -> pSPIx -> SPI_CR[2] & ( 1 << SPI_CR2_TXEIE);

	//if TX interrupt is enabled and Txbuffer is empty then handle the tx interrupt
	if( temp1 & temp2)
	{
		//Handle the TXE
		SPI_TXE_Interrupt_Handle(pSPIHandle);
	}



	//Step2 : Check for RXNE flag
	temp1 = pSPIHandle -> pSPIx -> SPI_SR & ( 1 << SPI_SR_RXNE);
	//check only if interrupt is enabled for receive
	temp2 = pSPIHandle -> pSPIx -> SPI_CR[2] & ( 1 << SPI_CR2_RXNEIE);

	if( temp1 & temp2)
	{
		//Handle the RXNE
		SPI_RXNE_Interrupt_Handle(pSPIHandle);
	}


	//Step3 : Check the OVR flag
	temp1 = pSPIHandle -> pSPIx -> SPI_SR & ( 1 << SPI_SR_OVR);
	//check only if interrupt is enabled for OVF error
	temp2 = pSPIHandle -> pSPIx -> SPI_CR[2] & ( 1 << SPI_CR2_ERRIE);

	if( temp1 & temp2)
	{
		//Handle the OVR error
		SPI_OVF_ERR_Interrupt_Handle(pSPIHandle);
	}



}
/****************** Helper function implementation for interrupt *********************************************/

/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_TXE_Interrupt_Handle
 * @brief                        :
 * @param[in]                    : Pointer to handle structure
 * @return                       :
 * Special Note                  : Here we are using via handle structure to access global variables.
 */
static void SPI_TXE_Interrupt_Handle(SPI_Handle_t *pSPIHandle)
{


	//if the DFF bit is set i.e for 16 bit data transfer
	if( (pSPIHandle -> pSPIx -> SPI_CR[0])  & (1<<SPI_CR1_DFF))
	{

		/*STEP 1: Load data in DR Register. Here typecast to (uint16_t) since we want to access 16 bit data via
		user defined buffer pointer but our pointer is of 8 bit size.*/
		pSPIHandle -> pSPIx ->SPI_DR = *( (uint16_t*)pSPIHandle -> pTxBuffer);

		// STEP 2: Decrement len value twice.
		(pSPIHandle -> TxLen)--;(pSPIHandle -> TxLen)--;//decrement twice since we're sending 2 bytes of data
		//STEP 3: increment the pointer so as to point to next 16 bit data. Here typecast to (uint16_t) since 16 bit data transfer
		(uint16_t*)( (pSPIHandle ->pTxBuffer)++);
	}
	else//8 bit data for transmit /receive.
	{

		/*STEP 1: Load data in DR Register.*/
		pSPIHandle -> pSPIx ->SPI_DR = *( (uint16_t*)pSPIHandle -> pTxBuffer);

		// STEP 2: Decrement len value .
		(pSPIHandle -> TxLen)--;//decrement once since sending 1 byte data
		//STEP 3: increment the pointer so as to point to next 8 bit data.
		(pSPIHandle ->pTxBuffer)++;


	}

	//if length is zero then close SPI communication
	//Also tell the application that transmission is over
	if(! pSPIHandle ->TxLen)
	{
		//Step 1 : Reset the TXEIE bit
		//this is done so as to prevent interrupt from TXE flag
		pSPIHandle -> pSPIx -> SPI_CR[1] &= ~( 1 << SPI_CR2_TXEIE);

		//Step 2 : Reset the buffer
		pSPIHandle -> pTxBuffer = NULL;

		//Step 3: Set the buffer size to 0
		pSPIHandle -> TxLen = 0;

		//Step 4 : change the state from busy to ready state so as to start the new transmission
		pSPIHandle -> TxState = SPI_READY;

		/******* NOte from step 1 to 4 you can use below api to abruptly close the ongoing transmission.
		 *  SPI_CloseTransmission(SPI_Handle_t *pSPIHandle);
		 */
		//Step 5 : call the event application callback function
		//The below function is implemented by application.
		//values of events from @SPI_APP_EVENTS in device specific header file.
		SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_TX_COMPLETE  );
	}


}


/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_IRQHandling
 * @brief                        :
 * @param[in]                    :
 * @param[in]                    :
 * @return                       :
 * Special Note                  :
 */
static void SPI_RXNE_Interrupt_Handle(SPI_Handle_t *pSPIHandle)
{
	//if the DFF bit is set i.e for 16 bit data receive
	if( (pSPIHandle -> pSPIx -> SPI_CR[0])  & (1<<SPI_CR1_DFF))
	{

		/*STEP 1: Load data from DR Register. Here typecast to (uint16_t) since we want to access 16 bit data via
		user defined buffer pointer but our pointer is of 8 bit size.*/
		*( (uint16_t*)pSPIHandle -> pRxBuffer) = pSPIHandle -> pSPIx ->SPI_DR ;

		// STEP 2: Decrement len value twice.
		(pSPIHandle -> RxLen)--;(pSPIHandle -> RxLen)--;//decrement twice since we're sending 2 bytes of data
		//STEP 3: increment the pointer so as to point to next 16 bit data. Here typecast to (uint16_t) since 16 bit data transfer
		(uint16_t*)( (pSPIHandle ->pRxBuffer)++);
	}
	else//8 bit data for transmit /receive.
	{

		/*STEP 1: Load data in Rx buffer from DR. Here typecast to (uint16_t) since we want to access 16 bit data via
		user defined buffer pointer but our pointer is of 8 bit size.*/
		*( (uint16_t*)pSPIHandle -> pRxBuffer) = pSPIHandle -> pSPIx ->SPI_DR  ;

		// STEP 2: Decrement len value twice.
		(pSPIHandle -> RxLen)--;//decrement once since sending 1 byte data
		//STEP 3: increment the pointer so as to point to next 16 bit data. Here typecast to (uint16_t) since 16 bit data transfer
		(pSPIHandle ->pRxBuffer)++;


	}

	//if length is zero then close SPI communication
	//Also tell the application that receive  is over
	if(! pSPIHandle ->RxLen)
	{
		//Step 1 : Reset the RXNEIE bit
		//this is done so as to prevent interrupt from TXE flag
		pSPIHandle -> pSPIx-> SPI_CR[1] &= ~( 1 << SPI_CR2_RXNEIE);

		//Step 2 : Reset the buffer
		pSPIHandle -> pRxBuffer = NULL;

		//Step 3: Set the buffer size to 0
		pSPIHandle -> RxLen = 0;

		//Step 4 : change the state from busy to ready state so as to start the new transmission
		pSPIHandle -> RxState = SPI_READY;

		/******* NOte from step 1 to 4 you can use below api to abruptly stop ongoing reception
		 *  SPI_CloseReception(SPI_Handle_t *pSPIHandle);
		 */

		//Step 5 : call the event application callback function
		//The below function is implemented by application.
		//values of events from @SPI_APP_EVENTS in device specific header file.
		SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_RX_COMPLETE  );


	}


}


/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_IRQHandling
 * @brief                        :
 * @param[in]                    :
 * @param[in]                    :
 * @return                       :
 * Special Note                  : Private function
 */
static void SPI_OVF_ERR_Interrupt_Handle(SPI_Handle_t *pSPIHandle)
{
	uint8_t temp =0;

	//Step 1 : clear the OVR flag
	//Taken from reference manual page 864
	//read DR Register only if state of Tx/Rx is ready state i.e transmission/receive isn't ongoing
	//below condition wouldn't get execute when OVR error occur when transmission is ongoing.
	if (pSPIHandle -> TxState != SPI_BUSY_IN_TX)
	{
		temp = pSPIHandle ->pSPIx -> SPI_DR;
		temp = pSPIHandle -> pSPIx -> SPI_SR;
	}
	(void)temp;//typecast to void so as to prevent unused variable warning
	//Step 2 : Inform to application of OVR error
	SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_OVR_ERR  );

	//Step 3: Clear the OVR flag as done by application in condition
	//when OVR error occurs while SPI peripheral is busy in transmission


}

/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_IRQHandling
 * @brief                        :
 * @param[in]                    :
 * @param[in]                    :
 * @return                       :
 * Special Note                  :
 */

void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle)
{
	//Step 1 : Reset the TXEIE bit
	//this is done so as to prevent interrupt from TXE flag
	pSPIHandle -> pSPIx -> SPI_CR[1] &= ~( 1 << SPI_CR2_TXEIE);

	//Step 2 : Reset the buffer
	pSPIHandle -> pTxBuffer = NULL;

	//Step 3: Set the buffer size to 0
	pSPIHandle -> TxLen = 0;

	//Step 4 : change the state from busy to ready state so as to start the new transmission
	pSPIHandle -> TxState = SPI_READY;


}



/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_IRQHandling
 * @brief                        :
 * @param[in]                    :
 * @param[in]                    :
 * @return                       :
 * Special Note                  :
 */

void SPI_CloseReception(SPI_Handle_t *pSPIHandle)
{
	//Step 1 : Reset the RXNEIE bit
	//this is done so as to prevent interrupt from TXE flag
	pSPIHandle -> pSPIx -> SPI_CR[1] &= ~( 1 << SPI_CR2_RXNEIE);

	//Step 2 : Reset the buffer
	pSPIHandle -> pRxBuffer = NULL;

	//Step 3: Set the buffer size to 0
	pSPIHandle -> RxLen = 0;

	//Step 4 : change the state from busy to ready state so as to start the new transmission
	pSPIHandle -> RxState = SPI_READY;
}


/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_ClearOVRFlag
 * @brief                        :
 * @param[in]                    :
 * @param[in]                    :
 * @return                       :
 * Special Note                  :
 */

void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx)
{
	uint8_t temp = 0;
	temp = pSPIx -> SPI_DR;
	temp = pSPIx -> SPI_DR;
	(void)temp;//to avoid the unused variable warning
}

/* *********************************Documentation Section **********************************************
 * @fn                           : SPI_ApplicationEventCallback
 * @brief                        :
 * @param[in]                    :
 * @param[in]                    :
 * @return                       :
 * Special Note                  : Implemented as weak so that can be implemented by user application.
 */
__weak void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle,uint8_t AppEvent  )
{

}

/*****************************************************************************************/









