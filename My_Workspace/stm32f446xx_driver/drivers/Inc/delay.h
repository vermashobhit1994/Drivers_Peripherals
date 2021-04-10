/*
 * delay.h
 *
 *  Created on: 22-Jan-2021
 *      Author: vermas
 */

#ifndef INC_DELAY_H_
#define INC_DELAY_H_

#include"stdint.h"

/* Base addresses */
#define RCC_BASE_ADDRESS            (0x40023800U)
#define RCC_APB1ENR_OFFSET         0x40U
#define RCC_APB1ENR_BASE_ADDRESS   (RCC_BASE_ADDRESS + RCC_APB1ENR_OFFSET)


/* Register Defination structure for Timer6 and Timer7*/
//timer6 or timer7 generic register defination
typedef struct
{
	volatile uint32_t TIM_CR1;
	volatile uint32_t TIM_CR2;
	         uint32_t RESERVED1;
	volatile uint32_t TIM_DIER;
	volatile uint32_t TIM_SR;
	volatile uint32_t TIM_EGR;
	         uint32_t RESERVED2[3];
	volatile uint32_t TIM_CNT;
	volatile uint32_t TIM_PSC;
	volatile uint32_t TIM_ARR;
}TIMER_RegDef_t;


#define TIMER6_BASE_ADDRESS         (0x40001000U)
#define TIMER6                      ( (TIMER_RegDef_t *)TIMER6_BASE_ADDRESS)

/**** Function Prototypes ******/
void TIMER6_Init(void);
void delay_us(uint16_t time_us);
void delay_ms(uint32_t time_ms);
void mdelay(uint32_t delay);
void udelay(uint32_t delay);




#endif /* INC_DELAY_H_ */
