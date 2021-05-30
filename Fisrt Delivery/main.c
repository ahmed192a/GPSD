/*
 * main.c
 */

#include "microconfig.h"

/*******************************************************************************
 *                      Global Variables                                  *
 *******************************************************************************/

extern volatile unsigned char g_Interrupt_Flag ;

/*******************************************************************************
 *                      Main Function                                          *
 *******************************************************************************/

void main(void){

	LCD_init();
    GPIOF_Init();                 /**  Initialize the GPIO of PF2 BLUE LED **/
    SW1_Int_Interrupt();          /*Enable Interrupt on PF4 Switch 1 */

	LCD_clearScreen();
	LCD_displayString("Welcome to ..");

    while(1){
        if(g_Interrupt_Flag==1){
			Led_on(); 
        }
		else{
			Led_off();
		}
    }
}
