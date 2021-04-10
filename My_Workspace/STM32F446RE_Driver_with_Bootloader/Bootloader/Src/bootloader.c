/*
 * bootloader.c
 *
 *  Created on: Apr 1, 2021
 *      Author: aayush
 */
//File used to implement bootloader in c


#include"bootloader.h"

#include"stm32f446xx.h"
//#define __DEBUG__

/* @func : bootloader_jump_to_user_app
 * @desc : Function that will jump to user application and it is stored at
 *         adddress Sector1(0x08004000) of flash.
 */


/**
  * @brief  Setup the microcontroller system
  *         Initialize the FPU setting, vector table location and External memory
  *         configuration.
  * @param  None
  * @retval None
  */


/*
void SystemInit(void)
{
	//SCB->VTOR = ( (VECT_TAB_BASE_ADDRESS | VECT_TAB_OFFSET) << 8) & (~0xC00001FF) ;
	SCB->VTOR =  (VECT_TAB_BASE_ADDRESS | VECT_TAB_OFFSET);
}
*/

#define LED_PIN_NO         5
#define BUTTON_PIN_NO      13



/**
  @brief   Set Main Stack Pointer
  \details Assigns the given value to the Main Stack Pointer (MSP).
  \param [in]    topOfMainStack  Main Stack Pointer value to set
 */
__STATIC_FORCEINLINE void __set_MSP(uint32_t topOfMainStack)
{
   __asm volatile ("MSR msp, %0" : : "r" (topOfMainStack) : );
}


static void bootloader_jump_to_user_app(void)
{


#ifdef __DEBUG__
	//print the statement for debugging
	printf("Bootloader is jumping to user application\n");
#endif
	/*Configure the MSP that earlier is pointing to Bootloader start address and
	 * now configuring it to user application start address */
const int FLASH_SECTOR0_BASE_ADDR = 0x08000000;
	uint32_t msp_value = *(volatile uint32_t*)FLASH_SECTOR0_BASE_ADDR;

#ifdef __DEBUG__
	//printing the msp value for debugging purpose
	printf("mspvalue = %lu\n",msp_value);
#endif


	//Set the MSP to user application start address
	__set_MSP(msp_value);

	//Step2 : configure the user application reset handler address to function pointer.
	//First getting the address of reset handler and then assign it to function pointer.
	uint32_t user_app_reset_addr = *(volatile uint32_t*)(FLASH_SECTOR1_BASE_ADDR+4);

	//Function pointer declaration that store User application Reset Handler address.
	void (*app_reset_handler) (void);
	app_reset_handler = (void*)user_app_reset_addr;


#ifdef __DEBUG__
	printf("App reset handler is %lu\n",(uint32_t)app_reset_handler);
#endif

	//Step3 : Jump to reset handler of user application
	app_reset_handler();




}


void Button_Init()
{
	//Enable the peripheral clock for GPIOC
	GPIOC_PERI_CLK_EN();

	//configure the mode as input mode
	GPIOC -> GPIOx_MODER &= ~(0x3 << (2 * BUTTON_PIN_NO));

	//Turn ON Pull up
	GPIOC -> GPIOx_PUPDR |= (1 << (2*BUTTON_PIN_NO));


}

void LED_Init()
{
	//Enable the Peripheral clock for GPIOA
	GPIOA_PERI_CLK_EN();

	//Setting the mode for PA5 as output mode
	GPIOA -> GPIOx_MODER |= (1 << (2 * LED_PIN_NO));

}






/*main function for bootloader */
int main(void)
{

	Button_Init();


	LED_Init();


	for(int i = 0;i<500000;i++)
		;


	/* If button is pressed then only jumps to bootloader which can happen when
	 * Falling edge trigger is done on button.
	 */
	if( !(GPIOC -> GPIOx_IDR & (1 << BUTTON_PIN_NO )) )
	{
		printf("Going to Bootloder mode since button is pressed\n");



		while(1)
			GPIOA -> GPIOx_ODR |= (1 << LED_PIN_NO);


	}
	else
	{
		printf("Going to Application mode\n");
		bootloader_jump_to_user_app();

		//the below statement should never gets executed if user application has started
		while(1);

	}

}
