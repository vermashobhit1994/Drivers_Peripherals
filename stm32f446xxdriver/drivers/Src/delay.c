/*
 * delay.c
 *
 *  Created on: 22-Jan-2021
 *      Author: vermas
 */

#include"delay.h"



/******************** API's used by delay function ****************/

/* *********************************Documentation Section **********************************************
 * Function Name                 : TIMER6_Init
 * Brief Description             : This function initialise the Timer6
 * Return Type                   : None
 * Special Note                  : Here the Peripheral clock = 16MHz
 */

void TIMER6_Init(void)
{


	//Step1 : Enable the timer6 peripheral clock
	uint32_t *RCC_TIMER6_CLK_EN = ((uint32_t*)RCC_APB1ENR_BASE_ADDRESS);
	*RCC_TIMER6_CLK_EN |= (1 << 4);//Here OR'ng is must

	//Step2 : Set the Prescaler and ARR value
	TIMER6 ->TIM_PSC = 16-1;
	TIMER6 -> TIM_ARR = 0xFFFF;//max value of ARR i.e 65536




    /*
	TIMER_RegDef_t *TIMER  = ( (TIMER_RegDef_t*)TIMER6_BASE_ADDRESS);


	//Step2 : Configure the prescaler value
	//selecting the frequency as 1MHz for 1 us delay
	TIMER -> TIM_PSC = prescaler_value -1;//since in prescaler +1 is added

	//setting the URS bit to generate the UEV event for underflow /overflow condition only
	//TIMER -> TIM_CR1 |= (1 << 2);

	//setting the ARPE bit to store the register value in buffer
	//TIMER -> TIM_CR1 |= (1 << 7);

	//TIMER -> TIM_EGR |= (1 << 0);


    */
}


/* *********************************Documentation Section **********************************************
 * Function Name                 : delay_us
 * Brief Description             : This function generate the microseconds delay.
 * Input Parameter 1 description : The delay value in microseconds
 * Return Type                   : None
 * Special Note                  : Enable the timer only when delay is required.
 *                                 NOt working well until 8 us.
 */
void delay_us(uint16_t time_us)
{



	//enable the timer6
	TIMER6 -> TIM_CR1 |= (1 << 0);


	while(! ( (TIMER6 -> TIM_SR ) &  (1 << 0) ));

	TIMER6 -> TIM_CNT = 0;
	time_us -= 8;
	while( (TIMER6 -> TIM_CNT) < time_us);


	//disable the timer6
	TIMER6 -> TIM_CR1 &= ~(1 << 0);


}

/* *********************************Documentation Section **********************************************
 * Function Name                 : delay_ms
 * Brief Description             : This function generate the milliseconds delay.
 * Input Parameter 1 description : The delay value in milliseconds
 * Return Type                   : None
 * Special Note                  : Enable the timer only when delay is required.
 */
void delay_ms(uint32_t time_ms)
{
	/* As continued in Timer6_Init()*/
	//Step3 : Enable the timer6
	TIMER6 ->TIM_CR1 |= (1 << 0);

	//Step4 : Wait until the Register are updated by use of update flag
	//wait until the SR bit is set
	while( ! ( TIMER6 -> TIM_SR & (1 << 0) ) ) ;


	for(uint32_t i = 0;i<time_ms;i++)
	{
		//Step5 : Reset the counter
		TIMER6 -> TIM_CNT = 0;
		while(  (TIMER6 -> TIM_CNT) < 1000);
	}

	//Step7 : Turn OFF the TIMER6
	TIMER6 ->TIM_CR1 &= ~(1 << 0);




}


void mdelay(uint32_t delay)
{
	for(uint32_t i = 0;i<(delay*1000);i++);
}

void udelay(uint32_t delay)
{
	for(uint32_t i = 0;i<(delay);i++);
}




