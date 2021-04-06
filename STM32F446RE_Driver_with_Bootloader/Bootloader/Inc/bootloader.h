/*
 * bootloader.h
 *
 *  Created on: Apr 1, 2021
 *      Author: aayush
 */

#ifndef BOOTLOADER_H_
#define BOOTLOADER_H_


void bootloader_init(void);
#include<stdio.h>
#include<stdint.h>
#include"memory_map.h"
//#include"stm32f446xx.h"

#define FLASH_SECTOR1_BASE_ADDR       (0x08004000UL)
#define __STATIC_FORCEINLINE          __attribute__((always_inline)) static inline

#define     __IM     volatile const     /*! Defines 'read only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */
/**
  \brief  Structure type to access the System Control Block (SCB).
 */
typedef struct
{
  __IM  uint32_t CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  __IOM uint32_t ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  __IOM uint32_t VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  __IOM uint32_t AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  __IOM uint32_t SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
  __IOM uint32_t CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  __IOM uint8_t  SHP[12U];               /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  __IOM uint32_t SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  __IOM uint32_t CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  __IOM uint32_t HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  __IOM uint32_t DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  __IOM uint32_t MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  __IOM uint32_t BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  __IOM uint32_t AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  __IM  uint32_t PFR[2U];                /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  __IM  uint32_t DFR;                    /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  __IM  uint32_t ADR;                    /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  __IM  uint32_t MMFR[4U];               /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  __IM  uint32_t ISAR[5U];               /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
        uint32_t RESERVED0[5U];
  __IOM uint32_t CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
} SCB_Type;


#define SCB_BASE_ADDR                       0xE000ED00UL
#define SCB                 ((SCB_Type*)SCB_BASE_ADDR)   /*!< SCB configuration struct */

#define VECT_TAB_BASE_ADDRESS          (0x08000000UL)/*!< Vector Table base address field.
                                                     This value must be a multiple of 0x200. */


#define VECT_TAB_OFFSET                (0x00004000UL)     /*!< Vector Table base offset field.
                                                     This value must be a multiple of 0x200. */
void SystemInit(void);





#endif /* BOOTLOADER_H_ */
