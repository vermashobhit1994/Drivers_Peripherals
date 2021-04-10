/*
 * stm32f446xx.h
 *
 *  Created on: Apr 1, 2021
 *      Author: aayush
 */


#ifndef INC_STM32F446XX_H_
#define INC_STM32F446XX_H_

#include<stdbool.h>
#include<stdint.h>


/****************************** Processor related Macros *******************/
/* IRQ for various INterrupts */
#define IRQ_NO_EXTI_15_10            40


#define NVIC_ISER0_BASE_ADDR                  ((volatile uint32_t*)0xE000E100)
#define NVIC_ISER1_BASE_ADDR                  ((volatile uint32_t*)0xE000E104)
#define NVIC_ISER2_BASE_ADDR                  ((volatile uint32_t*)0xE000E108)
#define NVIC_ISER3_BASE_ADDR                  ((volatile uint32_t*)0xE000E10C)

#define NVIC_ICER0_BASE_ADDR                  ((volatile uint32_t*)0xE000E180)
#define NVIC_ICER1_BASE_ADDR                  ((volatile uint32_t*)0xE000E184)
#define NVIC_ICER2_BASE_ADDR                  ((volatile uint32_t*)0xE000E188)
#define NVIC_ICER3_BASE_ADDR                  ((volatile uint32_t*)0xE000E18C)









/*@brief GPIO_Struct_Register_Declaration */
typedef struct
{
	volatile uint32_t GPIOx_MODER;
	volatile uint32_t GPIOx_OTYPER;
	volatile uint32_t GPIOx_OSPEEDR;
	volatile uint32_t GPIOx_PUPDR;
	volatile uint32_t GPIOx_IDR;
	volatile uint32_t GPIOx_ODR;
	volatile uint32_t GPIOx_BSRR;
	volatile uint32_t GPIOx_LCKR;
	volatile uint32_t GPIOx_AFRL;
	volatile uint32_t GPIOx_AFRH;

}GPIOx_RegDef_t;


#define __vo volatile

/*Generic Register Definition Structure for RCC Peripheral
 * Here the RESERVED is written just for the offset due to reserved one*/
typedef struct
{
	__vo uint32_t      RCC_CR;
	__vo uint32_t      RCC_PLLCFGR;
	__vo uint32_t      RCC_CFGR;
	__vo uint32_t      RCC_CIR;
	__vo uint32_t      RCC_AHB1RSTR;
	__vo uint32_t      RCC_AHB2RSTR;
	__vo uint32_t      RCC_AHB3RSTR;
	 uint32_t          RESERVED;
	__vo uint32_t      RCC_APB1RSTR;
	__vo uint32_t      RCC_APB2RSTR;
	uint32_t           RESERVED2[2];//for two reserved values
	__vo uint32_t      RCC_AHB1ENR;
	__vo uint32_t      RCC_AHB2ENR;
	__vo uint32_t      RCC_AHB3ENR;
	 uint32_t          RESERVED1;
	__vo uint32_t      RCC_APB1ENR;
	__vo uint32_t      RCC_APB2ENR;
	uint32_t           RESERVED3[2];
	__vo uint32_t      RCC_AHB1LPENR;
	__vo uint32_t      RCC_AHB2LPENR;
	__vo uint32_t      RCC_AHB3LPENR;
	uint32_t           RESERVED4;
	__vo uint32_t      RCC_APB1LPENR;
	__vo uint32_t      RCC_APB2LPENR;
	uint32_t           RESERVED5[2];
	__vo uint32_t      RCC_BDCR;
	__vo uint32_t      RCC_CSR;
	uint32_t           RESERVED62[2];
	__vo uint32_t      RCC_SSCGR;
	__vo uint32_t      RCC_PLLI2SCFGR;
	__vo uint32_t      RCC_PLLSAICFGR;
	__vo uint32_t      RCC_DCKCFGR;
	__vo uint32_t      RCC_CKGATENR;
	__vo uint32_t      RCC_DCKCFGR2;

}RCC_RegDef_t;


/*@brief Register Defination structure for EXTI Peripheral */
typedef struct
{
	volatile uint32_t EXIT_IMR;
	volatile uint32_t EXIT_EMR;
	volatile uint32_t EXIT_RTSR;
	volatile uint32_t EXIT_FTSR;
	volatile uint32_t EXIT_SWIER;
	volatile uint32_t EXIT_PR;
}EXTI_RegDef_t;

/*@brief Register Defination structure for SYSCFG Peripheral */
typedef struct
{
	volatile uint32_t SYSCFG_MEMRMP;
	volatile uint32_t SYSCFG_PMC;
	volatile uint32_t SYSCFG_EXTICR[4];
	         uint32_t RESERVED1;
	volatile uint32_t SYSCFG_CMPCR;
	volatile uint32_t SYSCFG_CFGR;

}SYSCFG_RegDef_t;

/*********** RCC AHB1ENR Peripheral Register Bit Definations ******************/
#define RCC_AHB1ENR_GPIOA_EN             (0x00000001U)
#define RCC_AHB1ENR_GPIOB_EN             (0x00000002U)
#define RCC_AHB1ENR_GPIOC_EN             (0x00000004U)
#define RCC_AHB1ENR_GPIOD_EN             (0x00000008U)
#define RCC_AHB1ENR_GPIOE_EN             (0x00000010U)
#define RCC_AHB1ENR_GPIOF_EN             (0x00000014U)
#define RCC_AHB1ENR_GPIOG_EN             (0x00000018U)
#define RCC_AHB1ENR_GPIOH_EN             (0x0000001CU)
#define RCC_APB2ENR_SYSCFG_EN            (0x00004000U)







/************* Base Address for High Speed and Low speed Buses*/
#define APB1_BASE_ADDR                 (0x40000000U)
#define APB2_BASE_ADDR                 (0x40010000U)
#define AHB1_BASE_ADDR                 (0x40020000U)
#define AHB2_BASE_ADDR                 (0x50000000U)
#define AHB3_BASE_ADDR                 (0x60000000U)


/*************** EXTI Peripheral Base Address            ****************/
#define EXTI_BASE_ADDR                 (APB2_BASE_ADDR + 0x3C00U)


/*************** SYSCFG Peripheral base Address connected on ABP2 bus*******************/
#define SYSCFG_BASE_ADDR                ((APB2_BASE_ADDR) + 0x3800U)


/********** Peripheral Clock Enable Macros *************************/
#define RCC_BASE_ADDR                   (0x40023800U)
#define RCC_AHB1ENR_BASE_ADDR           ( (RCC_BASE_ADDR + 0x30U) )
#define RCC                             ((RCC_RegDef_t*)RCC_BASE_ADDR)
#define GPIOC_PERI_CLK_EN()               (( RCC ->RCC_AHB1ENR )|= (RCC_AHB1ENR_GPIOC_EN) )
#define GPIOA_PERI_CLK_EN()               (( RCC ->RCC_AHB1ENR) |= (RCC_AHB1ENR_GPIOA_EN) )
#define SYSCFG_PERI_CLK_EN()              ( RCC -> RCC_APB2ENR |= (RCC_APB2ENR_SYSCFG_EN))

/************ GPIO Peripheral Base Address Macros definations ****************/
#define GPIOA_BASE_ADDR                 ((AHB1_BASE_ADDR) + 0x00000000U)
#define GPIOB_BASE_ADDR                 ((AHB1_BASE_ADDR) + 0x00000400U)
#define GPIOC_BASE_ADDR                 ((AHB1_BASE_ADDR) + 0x00000800U)
#define GPIOD_BASE_ADDR                 ((AHB1_BASE_ADDR) + 0x00000C00U)
#define GPIOE_BASE_ADDR                 ((AHB1_BASE_ADDR) + 0x00001000U)
#define GPIOF_BASE_ADDR                 ((AHB1_BASE_ADDR) + 0x00001400U)
#define GPIOG_BASE_ADDR                 ((AHB1_BASE_ADDR) + 0x00001800U)
#define GPIOH_BASE_ADDR                 ((AHB1_BASE_ADDR) + 0x00001C00U)


/******* GPIO Peripheral Macros ********************************************/
#define GPIOA                   ((GPIOx_RegDef_t*)GPIOA_BASE_ADDR)
#define GPIOB                   ((GPIOx_RegDef_t*)GPIOB_BASE_ADDR)
#define GPIOC                   ((GPIOx_RegDef_t*)GPIOC_BASE_ADDR)
#define GPIOD                   ((GPIOx_RegDef_t*)GPIOD_BASE_ADDR)
#define GPIOE                   ((GPIOx_RegDef_t*)GPIOE_BASE_ADDR)
#define GPIOF                   ((GPIOx_RegDef_t*)GPIOF_BASE_ADDR)
#define GPIOG                   ((GPIOx_RegDef_t*)GPIOG_BASE_ADDR)
#define GPIOH                   ((GPIOx_RegDef_t*)GPIOH_BASE_ADDR)

/************** EXTI Peripheral Base Address ********************/
#define EXTI                     ((EXTI_RegDef_t*)EXTI_BASE_ADDR)

/************** SYSCFG Peripheral Base Address ********************/

#define SYSCFG                     ((SYSCFG_RegDef_t*)SYSCFG_BASE_ADDR)


/* Peripheral specific header file inclusion ***************/
#include"stm32f446xx_gpio_driver.h"

#endif /* INC_STM32F446XX_H_ */
