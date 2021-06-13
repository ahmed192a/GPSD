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
extern volatile unsigned char g_Interrupt_Flag;
extern uint16_t arrived ;
#if SDCARDUSE
extern uint8_t returnStatus,sdcardType;
extern fileConfig_st *srcFilePtr;
#endif
#if CSV
extern fileConfig_st *srcFilePtr_C;
#endif

/*******************************************************************************
 *                      Local functions prototypes                             *
 *******************************************************************************/
void init_peripheral();

/*******************************************************************************
 *                      Main Function                                          *
 *******************************************************************************/
void main(void){
    /******************************** INITIALIZATION ******************************/
    init_peripheral();

    while(1){
        if(g_Interrupt_Flag==1 && arrived == 0){
            delay_s();                            /*delay 1sec*/
            readGPSa();                           /* Call read GPS Function */
            if(r_distance<100){
#if SDCARDUSE
                Insert_data();
#endif
            }
            else if( r_distance >= 100 )               /*check if reach the distenation (100 m)*/
            {
                Led_on();                         /*Led_on*/
                arrived = 1;                      /* set arrived flag equal 1 if reach the distenation (100 m)*/
                g_Interrupt_Flag = 0;             /*clear Interrupt_Flag*/
                close_files();
#if LCDUSE
                LCD_clearScreen();
                LCD_goToRowColumn(1, 0);
                LCD_displayString("reached 100 m");
#endif
            }
        }
    }
}

/*********************************************************************************
 * Description : Initialize main peripheral needed
 * Arguments   : none
 * Return      : none
 *********************************************************************************/
void init_peripheral(){

    PLL_Init();           /* Set the internal frequency to 80MHz */

    /************ configuration of uart 0 for pc communication ******************/
    UART_ConfigType uart0={EIGHT_BITS,DISABLED,ONE_STOP_BIT,u0,9600};
    UART_init(&uart0);

    /************ configuration of uart 1 port C for gps ************************/
    UART_ConfigType uart1={EIGHT_BITS,DISABLED,ONE_STOP_BIT,u1_C,9600};
    UART_init(&uart1);

    GPIOF_Init();                 /*  Initialize the GPIO of PF2 BLUE LED **/

    SW1_Int_Interrupt();          /*Enable Interrupt on PF4 Switch 1 */

    /*********************** Enable if we use lcd or not ******************************/
#if LCDUSE
    LCD_init();                                   /*Initialize lcd*/
    LCD_clearScreen();                            /*clear lcd before printing*/
    LCD_displayString("Finish initializing");           /*First, Print Welcome sentence*/
    LCD_goToRowColumn(1, 0);
    LCD_displayString("Set up files..");           /*First, Print Welcome sentence*/
    delay_s();
#endif

#if SDCARDUSE
    /**************** Initialize SD card module  *******************************/
    /* wait till SD card detected and initialized */
    init_SD_Card();
    Create_files();
#endif

#if LCDUSE
    LCD_clearScreen();                            /*clear lcd before printing*/
    LCD_goToRowColumn(0, 0);
    LCD_displayString("To start the app");           /*First, Print Welcome sentence*/
    LCD_goToRowColumn(1, 0);
    LCD_displayString("press the button");           /*First, Print Welcome sentence*/
#endif
}
