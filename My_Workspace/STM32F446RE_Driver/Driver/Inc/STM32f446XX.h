/*
 * STM32f446XX.h
 *
 *  Created on: Mar 29, 2021
 *      Author: aayush
 */

#ifndef INC_STM32F446XX_H_
#define INC_STM32F446XX_H_

//To prevent the change of symbol name when compiled on c++ compiler
#ifdef __cplusplus
extern "C"{
#endif


/**************************** @ref Peri_RegDef*********************************************
 * Peripheral_registers_structures for various peripherals
 *******************************************************************************************/


/*@brief RCC_struct_Register_Declaration
 * Reset and Clock Control */
typedef struct
{
	volatile uint32_t RCC_CR;
	volatile uint32_t RCC_PLLCFGR;
	volatile uint32_t RCC_CFGR;
	volatile uint32_t RCC_CIR;
	volatile uint32_t RCC_AHB1RSTR;
	volatile uint32_t RCC_AHB2RSTR;
	volatile uint32_t RCC_AHB3RSTR;
	         uint32_t RESERVED1;
	volatile uint32_t RCC_APB1RSTR[2];
	         uint32_t RESERVED2;
	         uint32_t RESERVED3;
	volatile uint32_t RCC_AHB1ENR;
	volatile uint32_t RCC_AHB2ENR;
	volatile uint32_t RCC_AHB3ENR;
	volatile uint32_t RCC_APB1ENR;
	volatile uint32_t RCC_APB2ENR;
	         uint32_t RESERVED4;
	         uint32_t RESERVED5;
	volatile uint32_t RCC_AHB1LPENR;
	volatile uint32_t RCC_AHB2LPENR;
	volatile uint32_t RCC_AHB3LPENR;
	         uint32_t RESERVED6;
	volatile uint32_t RCC_APB1LPENR;
	volatile uint32_t RCC_APB2LPENR;
	         uint32_t RESERVED7[2];
	volatile uint32_t RCC_BDCR;
	volatile uint32_t RCC_CSR;
	         uint32_t RESERVED8[2];
	volatile uint32_t RCC_SSCGR;
	volatile uint32_t RCC_PLL2SCFGR;
	volatile uint32_t RCC_PLLSAICFGR;
	volatile uint32_t RCC_DCKCFGR;
	volatile uint32_t RCC_CKGATENR;
	volatile uint32_t RCC_DCKCFGR2;


}RCC_RegDef_t;

/*@brief GPIO_Struct_Register_Declaration */
typedef struct
{
	volatile uin32_t GPIOx_MODER;
	volatile uin32_t GPIOx_OTYPER;
	volatile uin32_t GPIOx_OSPEEDR;
	volatile uin32_t GPIOx_PUPDR;
	volatile uin32_t GPIOx_IDR;
	volatile uin32_t GPIOx_ODR;
	volatile uin32_t GPIOx_BSRR;
	volatile uin32_t GPIOx_LCKR;
	volatile uin32_t GPIOx_AFRL;
	volatile uin32_t GPIOx_AFRH;

}GPIOx_RegDef_t;


/* ********************************* @ref Peripheral_memory_map ***********************
 * ********************Base Address for various peripherals  *************************
 *************************************************************************************/

/* Getting the details from page 57 of stm32f446re reference manual. */
#define PERIPH_BASE_ADDR               ((uint32_t)0x40000000U)
#define APB1_BASE_ADDR                 PERIPH_BASE_ADDR
#define APB2_BASE_ADDR                 (PERIPH_BASE_ADDR + 0x00010000U)
#define AHB1_BASE_ADDR                 (PERIPH_BASE_ADDR + 0x00020000U)
#define AHB2_BASE_ADDR                 (PERIPH_BASE_ADDR + 0x10000000U)
#define AHB3_BASE_ADDR                 (PERIPH_BASE_ADDR + 0x20000000U)

/*RCC Peripheral Base Address
 * Get the details from Table1 on Page 58*/
#define RCC_BASE_ADDR                  (AHB1_BASE_ADDR + 0x3800U)


/* GPIO's Peripheral Base Address
 * Get the details from Table1 on Page 58
 */
#define GPIOA_BASE_ADDR                (AHB1_BASE_ADDR + 0x00000000U)
#define GPIOB_BASE_ADDR                (AHB1_BASE_ADDR + 0x00000400U)
#define GPIOC_BASE_ADDR                (AHB1_BASE_ADDR + 0x00000800U)
#define GPIOD_BASE_ADDR                (AHB1_BASE_ADDR + 0x00000C00U)
#define GPIOE_BASE_ADDR                (AHB1_BASE_ADDR + 0x00001000U)
#define GPIOF_BASE_ADDR                (AHB1_BASE_ADDR + 0x00001400U)
#define GPIOG_BASE_ADDR                (AHB1_BASE_ADDR + 0x00001800U)
#define GPIOH_BASE_ADDR                (AHB1_BASE_ADDR + 0x00001C00U)


/* ********************************* @ref Peripheral_declaration ***********************
 * ******************** Macro for Various Peripheral Declaration  *************************
 *************************************************************************************/
/*@Note: Here the macro is typecast to struct Address to make it a pointer */

/*@brief Register and clock control */
#define RCC                            ((RCC_RegDef_t*)RCC_BASE_ADDR)

/*@brief GPIO_Base_Address */
#define GPIOA                          ((GPIOx_RegDef_t*)GPIOA_BASE_ADDR)
#define GPIOB                          ((GPIOx_RegDef_t*)GPIOB_BASE_ADDR)
#define GPIOC                          ((GPIOx_RegDef_t*)GPIOC_BASE_ADDR)
#define GPIOD                          ((GPIOx_RegDef_t*)GPIOD_BASE_ADDR)
#define GPIOE                          ((GPIOx_RegDef_t*)GPIOE_BASE_ADDR)
#define GPIOF                          ((GPIOx_RegDef_t*)GPIOF_BASE_ADDR)
#define GPIOG                          ((GPIOx_RegDef_t*)GPIOG_BASE_ADDR)
#define GPIOH                          ((GPIOx_RegDef_t*)GPIOH_BASE_ADDR)


/*********************************** @ref Clock_en ***************************************
 * **************** Macros for enabling the clock for various peripherals ****************
 *****************************************************************************************/

/*@brief GPIO_CLOCK_EN */
#define GPIOA_CLK_EN                   (RCC -> RCC_AHB1ENR)




/******************************** @ref Peripheral Registers_Bits_Definition *************
 */

/*for RCC_AHB1  Peripheral */
#define RCC_AHB1ENR_GPIOAEN             ((uint32_t*)0x00000000)
#define RCC_AHB1ENR_GPIOBEN             ((uint32_t*)0x00000002)
#define RCC_AHB1ENR_GPIOCEN             ((uint32_t*)0x00000004)
#define RCC_AHB1ENR_GPIODEN             ((uint32_t*)0x00000008)
#define RCC_AHB1ENR_GPIOEEN             ((uint32_t*)0x00000010)
#define RCC_AHB1ENR_GPIOFEN             ((uint32_t*)0x00000014)
#define RCC_AHB1ENR_GPIOGEN             ((uint32_t*)0x00000018)
#define RCC_AHB1ENR_GPIOHEN             ((uint32_t*)0x0000001C)
#define RCC_AHB1ENR_CRCEN               ((uint32_t*)0x)


#ifdef __cplusplus
}
#endif


#endif /* INC_STM32F446XX_H_ */
