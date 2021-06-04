/*
 * main.c
 */

#include "microconfig.h"

/*******************************************************************************
 *                      Global Variables                                  *
 *******************************************************************************/
extern char latitudeResult[];
extern char longitudeResult[];
extern char AltitudeResult[];
extern double r_distance;
extern volatile unsigned char g_Interrupt_Flag ;

/*******************************************************************************
 *                      Main Function                                          *
 *******************************************************************************/

void main(void){

    uint16_t arrived = 0;        /*local variable clear arrived flag if reach the distenation (100 m)*/
  
 /******************************** INITIALIZATION ******************************/

      PLL_Init();           /* Set the internal frequency to 80MHz */

  /************ configuration of uart 0 for pc communication ******************/
    UART_ConfigType uart0={EIGHT_BITS,DISABLED,ONE_STOP_BIT,u0,9600};
    UART_init(&uart0);

  /************ onfiguration of uart 1 port C for gps ************************/
    UART_ConfigType uart1={EIGHT_BITS,DISABLED,ONE_STOP_BIT,u1_C,9600};
    UART_init(&uart1);

    GPIOF_Init();                 /**  Initialize the GPIO of PF2 BLUE LED **/
    SW1_Int_Interrupt();          /*Enable Interrupt on PF4 Switch 1 */

  /*********************** Enable if we use lcd or not ******************************/
#if LCDUSE
    LCD_init();                                   /*Initialize lcd*/
    LCD_clearScreen();                            /*clear lcd before printing*/
    LCD_displayString("Welcome to ..");           /*First, Print Welcome sentence*/
#endif

    while(1){
        if(g_Interrupt_Flag==1 && arrived == 0){
#if SYSTICK_USE
            delay_s();                            /*delay 1sec*/
#endif
            //readGPSs();
            readGPSa();                           /* Call read GPS Function */
            if( r_distance >= 100 )               /*check if reach the distenation (100 m)*/
			{ 
                Led_on();                         /*Led_on*/
                arrived = 1;                      /* set arrived flag equal 1 if reach the distenation (100 m)*/
                g_Interrupt_Flag = 0;             /*clear Interrupt_Flag*/
            }
        }
    }
}
