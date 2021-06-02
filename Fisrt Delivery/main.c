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
	char c;
	LCD_init();
    GPIOF_Init();                 /**  Initialize the GPIO of PF2 BLUE LED **/
    SW1_Int_Interrupt();          /*Enable Interrupt on PF4 Switch 1 */
	  /************ configuration of uart 0 for pc communication ******************/
    UART_ConfigType uart0={EIGHT_BITS,DISABLED,ONE_STOP_BIT,u0,9600};
    UART_init(&uart0);

  /************ onfiguration of uart 1 port C for gps ************************/
    UART_ConfigType uart1={EIGHT_BITS,DISABLED,ONE_STOP_BIT,u1_C,9600};
    UART_init(&uart1);

	LCD_clearScreen();
	LCD_displayString("welcome to ..");
    while(1){
        if(g_Interrupt_Flag==1){
			Led_on(); 
        }
		else{
			Led_off();
		}
    }
}
