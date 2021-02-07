/*
 * stm32f44xx_spi_driver.h
 *
 *  Created on: 19-Aug-2020
 *      Author: vermas
 */

#ifndef INC_STM32F44XX_SPI_DRIVER_H_
#define INC_STM32F44XX_SPI_DRIVER_H_

#include"stm32f446xx.h"

#define __weak  __attribute__((weak))

/* SPI User Configuration Structure*/
typedef struct
{
	uint8_t SPI_DeviceMode;/* Device Mode i.e either the master or slave. Possible values from @SPIModes*/
	uint8_t SPI_BusConfig;/* Bus configuration i.e simplex, half-duplex , full-duplex.Possible values from @SPI_BusConfig*/
	uint8_t SPI_SclkSpeed;/* Clock Speed as decided by prescaler.Possible values from @SPI_SclkSpeed*/
	uint8_t SPI_DFF;/*Data Frame format i.e 8bit or 16 bit for shift register. Possible values from @SPI_DFF*/
	uint8_t SPI_CPOL;/*Clock Polarity. Possible values from @SPI_CPOL*/
	uint8_t SPI_CPHA;/* Clock Phase. Possible values from @SPI_CPHA*/
	uint8_t SPI_SSM;/* Software Slave Management. Possible values from @SPI_SSM*/

}SPI_Config_t;

/* Handle Structure for SPI Peripheral*/
typedef struct
{
	SPI_Config_t SPI_Config;//Configuration Structurex
	SPI_RegDef_t *pSPIx;//Pointer storing Base Address of SPI Peripheral register.


	/*** Adding Global variables used by ISR while handling SPI Interrupt ******/
	/* These values are taken from User defined parameters to driver ***/
	uint8_t *pTxBuffer;  //Pointer to store the user defined Tx buffer address.
	uint8_t *pRxBuffer;//Pointer to store the user defined Rx buffer address.
	uint32_t TxLen ;  //To store the user defined buffer Tx length .
	uint32_t RxLen; //To store the user defined buffer Rx length.
	uint8_t TxState ;//To store the user defined buffer Tx state.
	//To store the user defined buffer Rx state.
	uint8_t RxState ; //Possible values from @SPI_STATES

}SPI_Handle_t;

/* User defined Application States Macros for SPI */
/*@SPI_STATES*/
#define SPI_READY                           0
#define SPI_BUSY_IN_RX                      1
#define SPI_BUSY_IN_TX                      2


//Possible SPI Application events
//@SPI_APP_EVENTS
#define SPI_EVENT_TX_COMPLETE               1
#define SPI_EVENT_RX_COMPLETE               2
#define SPI_EVENT_OVR_ERR                   3
#define SPI_EVENT_CRC_ERR                   4

/**************************************************************************************************************
 * SPI Peripheral related Macros
 */

/* Possible values get from  Control Register1 MSTR field of SPI Peripheral
 * @SPIModes
 */
#define SPI_DEVICE_MODE_MASTER                   1
#define SPI_DEVICE_MODE_SLAVE                    0

/*Possible values For Duplex and Half-Duplex get from  Control Register1 BIDIMODE(bidirectional mode i.e Full Duplex)
 *  and BIDIOE field of SPI Peripheral.
 *  BIDIMODE = 0 -> full duplex, BIDIMODE = 1 -> Half Duplex.
 *  BIDIOE = 0 -> Device is Rx only in half duplex , BIDIMODE = 1 -> Device is Tx only in half duplex.
 *Possible values For Simplex  get from  Control Register1 RXONLY  field of SPI Peripheral with Rx Only capability
 *Possible . Here the BIDIMODE = 0 for two way lines.
 * RXONLY = 1 -> Simplex with Rx only and force to produce the serial clock when the MOSI is disabled .
 * @SPI_BusConfig
 */
#define SPI_BUS_CONFIG_FULLDUPLEX                1
#define SPI_BUS_CONFIG_HALFDUPLEX                2
//#define SPI_BUS_CONFIG_SIMPLEX_TX_ONLY           3 -> Removed since simplex with Tx is full duplex
#define SPI_BUS_CONFIG_SIMPLEX_RX_ONLY           3

/*Possible values get from  Control Register1 BR(Baud Rate) field of SPI Peripheral.
 * Here the default prescaler is 2. So if the RC oscillator clock is 16 MHz then the clock is 8 MHz.
 * @SPI_SclkSpeed
 */
#define SPI_SclkSpeed_DIV2                       0
#define SPI_SclkSpeed_DIV4                       1
#define SPI_SclkSpeed_DIV8                       2
#define SPI_SclkSpeed_DIV16                      3
#define SPI_SclkSpeed_DIV32                      4
#define SPI_SclkSpeed_DIV64                      5
#define SPI_SclkSpeed_DIV128                     6
#define SPI_SclkSpeed_DIV256                     7

/*Possible values get from  Control Register1 DFF field of SPI Peripheral
 * @SPI_DFF
 */
#define SPI_DFF_8_BITS                           0
#define SPI_DFF_16_BITS                          1

/*Possible values get from  Control Register1 CPOL field of SPI Peripheral
 * @SPI_CPOL
 */
#define SPI_CPOL_LOW                              0
#define SPI_CPOL_HIGH                             1

/*Possible values get from  Control Register1 CPHA field of SPI Peripheral
 * @SPI_CPHA
 */
#define SPI_CPHA_LOW                              0
#define SPI_CPHA_HIGH                             1

/*Possible values get from  Control Register1 SSM field of SPI Peripheral
 * @SPI_SSM
 */
#define SPI_SSM_DI                                0
#define SPI_SSM_EN                                1

/*Status flag Defination Macro*/
#define SPI_TXE_FLAG                              (1 << SPI_SR_TXE)//Masking the TXE flag of SPI_SR Register
#define SPI_RXNE_FLAG                             (1<< SPI_SR_RXNE)//masking the RXNE flag of SPI_SR Register.
#define SPI_BUSY_FLAG                             (1 << SPI_SR_BSY)//masking the BUSY flag of SPI_SR Register.


/**************************************************************************************************************/


/********************************************************************************************************************
 *                                          API's Supported by this driver
 *
 */
/* Peripheral Clock  */
void SPI_PeriClock_Ctrl(SPI_RegDef_t *pSPIx,uint8_t ENOrDI);//enable and disable the peripheral clock

/*Init and Deinit*/
void SPI_Init(SPI_Handle_t *pSPIHandle); //initialize the GPIO Port and Pin
void SPI_DEInit(SPI_RegDef_t *pSPIx);//deinitialize the GPIO Port i.e reset state

/* DAta Send andReceive*/
/* Polling or Non-Interrupt based Send and Receive*/
/* First parameter is name of SPI i.e SPI1,SPI2,SPI3,SPI4.
 * Second Parameter is the pointer to TxBuffer i.e user provided input buffer. 8 bit size of data is transmitted.
 * Third Parameter is the no of bytes to be transmitted where the length is of type uint32_t as standard.
 */
void SPI_SendData(SPI_RegDef_t *pSPIX, uint8_t *pTxBuffer,uint32_t len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx,uint8_t *pRxBuffer,uint32_t len);

/************************************/
/*IRQ Configuration and ISR Handling*/
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t ENOrDI);//to configure the Interrupt i.e IRQ no of SPI
void SPI_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority);//to configure the priority of SPI
void SPI_IRQHandling(SPI_Handle_t *pHandle);//the actual function that gets called on Interrupt or Interrupt handler

/************************************/

/**************** Sending and receiving Interrupt based API's ***/
uint8_t SPI_SendData_Interrupt(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer,uint32_t len);
uint8_t SPI_ReceiveData_Interrupt(SPI_Handle_t *pSPIHandle,uint8_t *pRxBuffer,uint32_t len);




/*
 * Other Peripheral Control API's
 */
//enable or Disable the SPI Peripheral. This must be done after the configurations in SPI_CR1 is done.
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx,uint8_t EnOrDi);


//configure the SSI bit to enable NSS pin to high when using the SSM = 1 i.e software slave management
void SPI_SSIConfig(SPI_RegDef_t *pSPIx,uint8_t EnOrDi);

//configure the SSOE bit to enable or disable the NSS
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx,uint8_t EnOrDi);

//checking if SPI Communication ends or not
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx,uint32_t FlagName);

//Clear the OVR flag only if OVR error occurs
void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx);

//Abruptly stop the SPI communication by application
void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle);
void SPI_CloseReception(SPI_Handle_t *pSPIHandle);

//Application callback function for various events and implement by application
//Weak implementation and application can override the below function
void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle,uint8_t AppEvent  );



#endif /* INC_STM32F44XX_SPI_DRIVER_H_ */



