#include "lcd.h"


/*******************************************************************************
 *                      Prototype Local Functions                              *
 *******************************************************************************/
void i_s(char str[], int k); // function that converts from integer to string

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*********************************************************************************
 * Description : Function to Initialize PORTB for Data and PORTE for control
 *               and start initializing the LCD
 * Arguments   : none
 * Return      : none
 *********************************************************************************/
void LCD_init(void){
    //port E control PE1 --> RS | PE2 --> RW | PE3 --> E
    //port B data
    SYSCTL_RCGCGPIO_R |= 0x12;              //Port D & E clock enable
    while((SYSCTL_PRGPIO_R & 0x12) == 0);   //delay until the SYSCTL is enabled
    //Control port configurations
    GPIO_PORTE_AFSEL_R &= ~(RS|RW|E);       //alternate function select
    GPIO_PORTE_PCTL_R  &= ~(RS|RW|E);       //determine the selected alternate function
    GPIO_PORTE_AMSEL_R &= ~(RS|RW|E);       // analog mode select for port D
    GPIO_PORTE_DEN_R   |= (RS|RW|E);        //digital enable
    GPIO_PORTE_DIR_R   |= (RS|RW|E);        // Configure the control pins(E,RS,RW) as output pins
    //Data port configurations
    GPIO_PORTB_AFSEL_R =0;                  //alternate function select
    GPIO_PORTB_PCTL_R  =0;                  //determine the selected alternate function
    GPIO_PORTB_AMSEL_R = 0;                 // analog mode select   for port D
    GPIO_PORTB_DEN_R = 0XFF;                //digital enable
    //Configure 8 bit mode or 4 bit mode
    #if (DATA_BITS_MODE == 4)
        #ifdef UPPER_PORT_PINS
            GPIO_PORTB_DIR_R |= 0xF0;                   //Configure the highest 4 bits of the data port as output pins
        #else
            GPIO_PORTB_DIR_R |= 0x0F;                   //Configure the lowest 4 bits of the data port as output pins
        #endif
        LCD_sendCommand(FOUR_BITS_DATA_MODE);           //initialize LCD in 4-bit mode
        LCD_sendCommand(TWO_LINE_LCD_FOUR_BIT_MODE);    //use 2-line lcd + 4-bit Data Mode + 5*7 dot display Mode
    #elif (DATA_BITS_MODE == 8)
        GPIO_PORTB_DIR_R = 0xFF;                        //Configure the data port as output port
        LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE);   //use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode
    #endif
    LCD_sendCommand(CURSOR_OFF);                        //cursor off
    LCD_sendCommand(CLEAR_COMMAND);                     //clear LCD at the beginning
}
/***********************************************************************************
 * Description : Configure the LCD to send command then send the command on PORTB
 * Arguments   : command (one of the commands in the LCD.h)
 * Return      : none
 ***********************************************************************************/
void LCD_sendCommand(uint8_t command){
    GPIO_PORTE_DATA_R &= ~RS;       // Disable RS
    GPIO_PORTE_DATA_R &= ~RW;       // Disable RW
    delay_ms();                     // wait for 1 ms
    GPIO_PORTE_DATA_R |= E;         // Enable E
    delay_ms();                     // wait for 1 ms
    #if (DATA_BITS_MODE == 4)
        /* out the highest 4 bits of the required command to the data bus D4 --> D7 */
    #ifdef  UPPER_PORT_PINS
    GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & 0x0F) | (command & 0xF0);
    #else
    GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & 0xF0) | ((command & 0xF0) >> 4);
    #endif
    delay_ms();                      // wait for 1 ms
    GPIO_PORTE_DATA_R &= ~E;         // Disable E
    delay_ms();                      // wait for 1 ms
    GPIO_PORTE_DATA_R |= E;          // Enable E
    delay_ms();                      // wait for 1 ms
    #ifdef UPPER_PORT_PINS
        GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & 0x0F) | ((command & 0x0F) << 4);
    #else
        GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & 0xF0) | (command & 0x0F);
    #endif

    delay_ms();               		/* delay for processing Tdsw = 100ns */
    GPIO_PORTE_DATA_R &= ~E;  		/* disable LCD E=0 */
    delay_ms();               		/* delay for processing Th = 13ns */
    #elif (DATA_BITS_MODE == 8)
        GPIO_PORTB_DATA_R = command; /* out the required command to the data bus D0 --> D7 */
        delay_ms();                  /* delay for processing Tdsw = 100ns */
        GPIO_PORTE_DATA_R &= ~E;     /* disable LCD E=0 */
        delay_ms();                  /* delay for processing Th = 13ns */
    #endif
}
/***********************************************************************************
 * Description : send Clear command to clear the LCD and start from the beginning
 * Arguments   : none
 * Return      : none
 ***********************************************************************************/
void LCD_clearScreen(void){
    LCD_sendCommand(CLEAR_COMMAND); //clear screen
}
