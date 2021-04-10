/*
 * stm32f446xx_i2c_driver.c
 *
 *  Created on: 18-Sep-2020
 *      Author: vermas
 */







/*******************************************************************************************
 ****************************API's definitions supported by this driver*********************************/

/* *********************************Documentation Section **********************************************
 * @fn                           : I2C_PeriClock_Ctrl
 * @brief                        : Function to Control the peripheral clock of I2C.
 * @param[in]                    : Base address of the I2C Register structure .
 * @param[in]                    : Bit to enable or disable.
 * @return                       : None
 * Special Note                  : None
 */

#include"stm32f446xx.h"
void I2C_PeriClock_Ctrl(I2C_RegDef_t *pI2Cx,uint8_t ENOrDI)//enable and disable the peripheral clock
{
	//enable the clock for I2C1, I2C2, I2C3
			if(ENOrDI == ENABLE)
			{
				if(pI2Cx == I2C1)
					I2C1_PERI_CLK_EN();
				else if(pI2Cx == I2C2)
					I2C2_PERI_CLK_EN();
				else if(pI2Cx == I2C3)
					I2C3_PERI_CLK_EN();

			}
			//disable the clock I2C1, I2C2, I2C3
			else
			{
				if(pI2Cx == I2C1)
					I2C1_PERI_CLK_DI();
				else if(pI2Cx == I2C2)
					I2C2_PERI_CLK_DI();
				else if(pI2Cx == I2C3)
					I2C3_PERI_CLK_DI();

			}
}

/* *********************************Documentation Section **********************************************
 * @fn                           :  RCC_GetPLLOutputClk
 * @brief                        : Function to get the PLL clock source value.
 * @return                       : 8 bit clock source value.
 * Special Note                  : Not implemented.
 */

static uint8_t RCC_GetPLLOutputClk(void)
{
	return 1;
}


/* array to hold the prescaler division factor for AHB Prescaler.*/
uint16_t AHB_Prescaler_array [] = {2,4,8,16,64,128,256,512};

/*array to hold the prescaler division factor for APB1 Prescaler*/
uint8_t APB1_Prescaler_array [4] = {2,4,8,16};


/* *********************************Documentation Section **********************************************
 * @fn                           : RCC_GetPCLK1Value
 * @brief                        : Function to get the clock value for APB1 bus.
 * @return                       : 32 bit clock value.
 * Special Note                  : Taken from clock tree.
 */

uint32_t RCC_GetPCLK1Value(void)
{
	uint32_t Pclk1,SystemClk;//variable to store the APB1 clock value.
    uint8_t temp,clksrc,APB1_Prescaler_Value,AHB_Prescaler_Value;

	/* ************** STEP 1 : to find the current clock source value from  HSE,HSI,PLLCLK,PLLR************
	 * Done by two bits of SWS in RCC_CFGR Register.
	 * Here our clock source is HSI i.e 16MHz.*/
	clksrc =(  (RCC -> RCC_CFGR >> 2) & 3);//varible to hold current clock source by reading value.

	/*select HSI i.e High Speed Internal clock as clock source.*/
	if(clksrc == 0)
	{
		SystemClk = 16000000;//i.e 16 MHz Internal Clock
	}
	/* Select the HSE as system clock. In Nucleo f446re there is no external oscillator*/
	else if (clksrc == 1)
		SystemClk = 8000000;//external clock of 8 MHz
	/* PLL_P is the system Clock */
	else if (clksrc == 2)
		SystemClk = RCC_GetPLLOutputClk();//not implemented Here

	/* ***************** step2 : find out the AHB prescaler value**************************************
	 * Done by reading the HPRE Bit of RCC_CFGR Register.*/
	temp = ( (RCC -> RCC_CFGR >> 4) & 0xF);
	if(temp < 8)//no prescaler
		AHB_Prescaler_Value = 1;
	//select the prescaler value from array
	else
		AHB_Prescaler_Value = AHB_Prescaler_array[temp - 8];//extract prescaler value from array.


	/*** Step 3 : find the APB1 Prescaler value*/
	temp = ( (RCC -> RCC_CFGR >> 10) & 0x7);
	if(temp < 4)//no prescaler
		APB1_Prescaler_Value = 1;
	else
		APB1_Prescaler_Value = APB1_Prescaler_array[temp - 4];//extract value from array.

	/* ************* Step 4: Put value in Pclk1 calculated ****************************************************/
	//first find systemclk then divide by AHB1 prescaler value then by APB1 prescaler value.
	Pclk1 = (SystemClk / AHB_Prescaler_Value)/APB1_Prescaler_Value;

	return Pclk1;

}





/* *********************************Documentation Section **********************************************
 * @fn                           : I2C_Init
 * @brief                        : Function to initialize the parameters given by user.
 * @param[in]                    : Base address of the I2C Handle structure .
 * @return                       : None
 * Special Note                  : None
 */
void I2C_Init(I2C_Handle_t *pI2CHandle)
{
	uint32_t tempreg = 0;//temporary register to store the data

	//enable the I2C Peripheral Clock
	I2C_PeriClock_Ctrl(pI2CHandle -> pI2Cx,ENABLE);

	/******************* step 1: enable the ACK***************************************/
		tempreg = 0;
		tempreg |=( (pI2CHandle -> I2C_Config.I2C_ACKCtrl) << I2C_CR1_ACK);
	    (pI2CHandle ->pI2Cx->I2C_CR[0]) |= tempreg;//put the value in I2C_CR1 Ack field.
         //(*(pI2CHandle ->pI2Cx->I2C_CR[0])) |= tempreg;

	/*****************Step 2: configure the FREQ fields of I2C_CR2 Register to get the value of APB1 bus clock.********/
	tempreg = 0;
	tempreg |= RCC_GetPCLK1Value()/1000000U;//to get only 16 instead of 16000000
	//to check only 5 LSB Bits and store value in I2C_CR2 Register.
	pI2CHandle -> pI2Cx -> I2C_CR[1] |= (tempreg & 0x3F);






	/******************* Step3 : Select the slave address if device is slave ***********************************/
	tempreg = 0;
	//getting the slave address as entered by user.
	tempreg |= pI2CHandle -> I2C_Config.I2C_DeviceAddress << 1;//for excluding the ADD0 bit
	tempreg |= (1<<14);//As specified by reference Manual

	//copy the value in ADD field of I2C_OAR1 Register
	//putting the 1 in 14th bit of I2C_OAR1 Register i.e reserved bit.
	pI2CHandle ->pI2Cx->I2C_OAR[0] = tempreg;

	/******************* Step4 : Select the CCR Value according to mode ***********************************/
    /* This is used to produce the clock of I2C peripheral */
	//CCR Calculations
	uint16_t ccr_value = 0;//I2C_CCR Register is of 16 bit
	tempreg = 0;

	//Step a : configure CCR value for the standard mode i.e 100 KHz
	if(pI2CHandle -> I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_ST_MODE)
	{
		//get the ccr value using the pclk1 and i2cscl clock.
		ccr_value = RCC_GetPCLK1Value() / (2 * pI2CHandle -> I2C_Config.I2C_SCLSpeed);
		tempreg |= (ccr_value & 0xFFF);//check only LSB 12 bits and store in tempreg.
	}

	//Step b: configure CCR value for the fast mode i.e > 100KHz
	else
	{
		//step 1. select the mode as fast .
		tempreg |= (1 << I2C_CCR_F_S);

		//step2 select duty cycle as entered by user.
		tempreg |= ( (pI2CHandle -> I2C_Config.I2C_FMDUTYCYCL) << I2C_CCR_DUTY);

		//check the duty cycle value = 0 i.e 2
		if(pI2CHandle -> I2C_Config.I2C_FMDUTYCYCL == I2C_FM_DUTY2)
			ccr_value = RCC_GetPCLK1Value()/ (3 * pI2CHandle -> I2C_Config.I2C_SCLSpeed);
		else
			ccr_value = RCC_GetPCLK1Value()/ (25 * pI2CHandle -> I2C_Config.I2C_SCLSpeed);

		//put the value from ccr_value in tempreg where only 12 bits are taken.
		tempreg |= ccr_value & 0xFFF;

	}
	//put the value in I2C_CCR Register from tempreg
	pI2CHandle -> pI2Cx -> I2C_CCR |= tempreg;


	/************ Step5: Configure the Rise time i.e I2C_TRISE Register******************/
	//to store the rise time for both standard and fast mode
	uint8_t Trise;

	//if mode is standard mode that means the Trise max = 1000ns
	if(pI2CHandle -> I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_ST_MODE)
	{

		Trise = (RCC_GetPCLK1Value() / 1000000U) + 1;

	}
	//if mode is fast mode
	else
	{
		Trise = ( (RCC_GetPCLK1Value() * 300) / 1000000000U ) + 1;
	}
    //put the value in I2C_TRISE Register.
	pI2CHandle -> pI2Cx ->I2C_TRISE |= (Trise & 0x3F);//masking i.e filtering  the 5 lowest bits only.


}




/* *********************************Documentation Section **********************************************
 * @fn                           : I2C_DeInit
 * @brief                        : Function to deinitialize peripheral clock of I2C.
 * @param[in]                    : Base address of the I2C Handle structure .
 * @return                       : None
 * Special Note                  : None
 */
void I2C_DeInit(I2C_Handle_t *pI2CHandle) //Deinitialize the I2C
{
	if(pI2CHandle -> pI2Cx == I2C1)
		I2C1_REG_RESET();
	else if(pI2CHandle -> pI2Cx == I2C2)
		I2C2_REG_RESET();
	else if(pI2CHandle -> pI2Cx == I2C3)
		I2C3_REG_RESET();

}

/* *********************************Documentation Section **********************************************
 * @fn                           : I2C_GenerateStartCondition
 * @brief                        : Function to generate repeated start condition I2C.
 * @param[in]                    : Base address of the I2C Register structure .
 * @return                       : None
 * Special Note                  : This is private to this file.
 */

static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx)
{
	pI2Cx -> I2C_CR[0] |= ( 1 << I2C_CR1_START);//set the START Bit of I2C_CR1 to activate repeated start.
}

/* *********************************Documentation Section **********************************************
 * @fn                           : I2C_ExecuteAddressPhase
 * @brief                        : Function to send 7 bit slave address + read/write bit.
 * @param[in]                    : Base address of the I2C Register structure .
 * @return                       : None
 * Special Note                  : Here the slave address is first left shfited to add the R/W bit
 */
static void I2C_ExecuteAddressPhase(I2C_RegDef_t  *pI2Cx,volatile uint8_t SlaveAddr,uint8_t R_W_Bit)
{
	//SlaveAddr = 0x27;
	SlaveAddr <<= 1;//make space for r/w bit.

	//if the Master wants to write/Transmit Data then put the LSB = 0
	if(R_W_Bit == 0)
		//clear the 0th bit
		SlaveAddr &= ~(1);
	//else set the last bit to read/receive data by master
	else
		SlaveAddr |= 1;//slave address is slaveaddr+r/w(1)


	//put the value in DR Register
	pI2Cx ->I2C_DR = SlaveAddr;
}

/* *********************************Documentation Section **********************************************
 * @fn                           : I2C_GetFlagStatus
 * @brief                        : Function to
 * @param[in]                    : Base address of the I2C Handle structure .
 * @return                       : None
 * Special Note                  : None
 */
static void I2C_ClearADDRFlag(I2C_RegDef_t  *pI2Cx)
{
	//read the dummy data from I2C_SR1
	uint16_t dummyRead = pI2Cx -> I2C_SR[0];//read SR1 register
	dummyRead = pI2Cx -> I2C_SR[1];//read SR2 Register
	(void )dummyRead;//avoid warning of unused variable
}

/* *********************************Documentation Section **********************************************
 * @fn                           : I2C_GetFlagStatus
 * @brief                        : Function to
 * @param[in]                    : Base address of the I2C Handle structure .
 * @return                       : None
 * Special Note                  : None
 */
static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx)
{
	pI2Cx -> I2C_CR[0] |= ( 1 << I2C_CR1_STOP);//set the STOP Bit of I2C_SR1 Register.
}
/* *********************************Documentation Section **********************************************
 * @fn                           : I2C_GetFlagStatus
 * @brief                        : Function to Read the bit of I2C_SR1 Register.
 * @param[in]                    : Base address of the I2C Handle structure .
 *  @param[in]                   : Flag of status register.
 * @return                       : None
 * Special Note                  : None
 */

uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx,uint32_t FlagName)
{
	/*test the FlagName  in I2C_SR1 Register.
	If the value is set return 1(FLAG_SET) */
	if((pI2Cx -> I2C_SR[0]) & FlagName)
		return I2C_FLAG_SET;
	   //else return 0(FLAG_RESET)
	return I2C_FLAG_RESET;
}

void Initialise_SlaveAddr(I2C_Handle_t *pI2CHandle,uint8_t SlaveAddr)
{
	//step1. Generate the start condition
		//api private to driver.
		I2C_GenerateStartCondition(pI2CHandle -> pI2Cx);

		/******** After Step 2 and step 3 the SB bit is cleared *******/
		//step 2. Confirm that start condition is generated or not by checking the SB bit of I2C_SR1 Register.
		//SCL will be low until SB = 1 condition isn't met .
		//SB bit is 1 when start condition is generated successfully.
		while(!I2C_GetFlagStatus(pI2CHandle -> pI2Cx, I2C_FLAG_SB));

		//step 3: send address of slave with read/write bit = 0 (to write)
		I2C_ExecuteAddressPhase(pI2CHandle -> pI2Cx,SlaveAddr,0);

	/********************************** SB Bit in I2C_SR1 Register is cleared ************************/

		//step 4: check the ADDR bit in I2C_SR1 Register to confirm address phase completed or not.
		while(!I2C_GetFlagStatus(pI2CHandle -> pI2Cx, I2C_FLAG_ADDR)  );//wait until it return 1

		//step 5: clear the ADDR bit in I2C_SR1 Register
		//until this is cleared SCL will be low.
	     I2C_ClearADDRFlag(pI2CHandle -> pI2Cx);
	   /************************** After this the ADDR bit is cleared ********/
}

void Deinitialize_SlaveAddr(I2C_Handle_t *pI2CHandle)
{
	//step 7: Wait until BTF and TXE is set in I2C_SR1 Register.
	     //when both BTF and TXE is set i.e both SR and DR is empty so next transmission should begin.
	     //when BTF = 1 SCL is low.
	     while( !I2C_GetFlagStatus(pI2CHandle -> pI2Cx, I2C_FLAG_TXE));//wait until TXE is set
	    // while( I2C_GetFlagStatus(pI2CHandle -> pI2Cx, I2C_FLAG_BTF));

	     //step 8: Generate stop condition.
	     //clear the BTF flag automatically
	     I2C_GenerateStopCondition(pI2CHandle -> pI2Cx);

}

/* *********************************Documentation Section **********************************************
 * @fn                           : I2C_MasterSendData
 * @brief                        : Function to send the data to slave byte by byte.
 * @param[in]                    : Base address of the I2C Handle structure .
 * @param[in]                    : Pointer to user buffer.
 * @param[in]                    : length of user buffer.
 * @param[in]                    : 7 bit slave address.
 * @return                       : None
 * Special Note                  : None
 */
void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer,uint32_t len,volatile uint8_t SlaveAddr)
{

	Initialise_SlaveAddr(pI2CHandle,SlaveAddr);

    //step 6: Send the data 1 byte at a time to DR register.
     while(len > 0)
     {
    	 while( !I2C_GetFlagStatus(pI2CHandle -> pI2Cx, I2C_FLAG_TXE));//wait until TXE becomes zero

    	 //putting the data from user pointer in I2C_DR Register
    	 pI2CHandle -> pI2Cx ->I2C_DR =  *pTxBuffer;
    	 pTxBuffer++;//to point to next byte data.
    	 len--;
     }
     Deinitialize_SlaveAddr(pI2CHandle);



}

/* *********************************Documentation Section **********************************************
 * @fn                           : I2C_MasterReceiveData
 * @brief                        : Function to receive the data via the I2C.
 * @param[in]                    : Base address of the I2C Handle structure .
 *@param[in]                     :
 *@param[in]                     : No of bytes of user buffer.
 *@param[in]                     : SlaveAddress.
 * @return                       : None
 * Special Note                  : Received Data stored in pRxBuffer
 */
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer,uint32_t maxlen,uint8_t SlaveAddr)
{
	//step1. Generate the start condition
	//api private to driver.
	I2C_GenerateStartCondition(pI2CHandle -> pI2Cx);

	/******** After Step 2 and step 3 the SB bit is cleared *******/
		//step 2. Confirm that start condition is generated or not by checking the SB bit of I2C_SR1 Register.
		//SCL will be low until SB = 1 condition isn't met .
		//SB bit is 1 when start condition is generated successfully.
		while(!I2C_GetFlagStatus(pI2CHandle -> pI2Cx, I2C_FLAG_SB));

		//step 3: send address of slave with read/write bit = 0 (to write)
		I2C_ExecuteAddressPhase(pI2CHandle -> pI2Cx,SlaveAddr,1);

	/********************************** SB Bit in I2C_SR1 Register is cleared ************************/

	//step 4: check the ADDR bit in I2C_SR1 Register to confirm address phase completed or not.
	while(!I2C_GetFlagStatus(pI2CHandle -> pI2Cx, I2C_FLAG_ADDR)  )//wait until it return 1
		;
	//step 5 : Read the data

		//step 5a: Reading 1 byte of data
		if(maxlen == 1)
		{
			//Step 5a1 : disable the ACK
	    	(pI2CHandle -> pI2Cx ->I2C_CR[0]) &= ~(1 << I2C_CR1_ACK);

	    	//Step 5a2 : Clear the ADDR flag(as seen in timing diagram)
	    	I2C_ClearADDRFlag(pI2CHandle -> pI2Cx);

	    	//Step 5a3 : Wait until RxNE becomes 1 so as to confirm data has been received or not.
	    	while( !I2C_GetFlagStatus(pI2CHandle -> pI2Cx, I2C_FLAG_RxNE));

	    	//Step 5a4 : Generate stop condition
	    	I2C_GenerateStopCondition(pI2CHandle -> pI2Cx);

	    	//Step 5a5 : Read the 1 byte data
			 //putting the data from user pointer in I2C_DR Register
	    	 *pRxBuffer = pI2CHandle -> pI2Cx ->I2C_DR ;



		}

		//Step 5b: Read >1 byte of data
		else
		{
			//Step 5b1 : clear the ADDR flag
			I2C_ClearADDRFlag(pI2CHandle -> pI2Cx);

			//Step 5b2 : Read the data until the len becomes 0
			for(uint32_t i = maxlen;i>=0;i--)
			{
				//Step 5b3 : Wait until the RxNE becomes 1
				while( !I2C_GetFlagStatus(pI2CHandle -> pI2Cx, I2C_FLAG_RxNE))
					;

				//Step 5b3 : if last 2 bytes are remaining
				if(i == 2)
				{
					//clear the ACK bit
					(pI2CHandle -> pI2Cx ->I2C_CR[0]) &= ~(1 << I2C_CR1_ACK);

					//generate STOP condition
					I2C_GenerateStopCondition(pI2CHandle -> pI2Cx);


				}

				//Step 5b4 : Read the data from data register into user buffer
				*pRxBuffer = pI2CHandle -> pI2Cx ->I2C_DR ;
				//Step 5b5 : Increment the buffer address
				pRxBuffer++;
			}
		}






}






/* *********************************Documentation Section **********************************************
 * @fn                           : I2C_PeripheralControl
 * @brief                        : Function to enable the I2C Peripheral.
 * @param[in]                    : Base address of the I2C Register structure .
 *@param[in]                     : Enable or Disable .
 * @return                       : None
 * Special Note                  : None
 */
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx,uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)//enable the I2C Peripheral
	{
		pI2Cx -> I2C_CR[0] |= (1<<I2C_CR1_PE);//enable the PE bit of I2C_CR1 Register

	}
		else//disable the SPI Peripheral.
			pI2Cx -> I2C_CR[0] &= ~(1<<I2C_CR1_PE);//disables the I2C bit of I2C_CR1 Register
}




