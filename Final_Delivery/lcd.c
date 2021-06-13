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
    /* port E control PE1 --> RS | PE2 --> RW | PE3 --> E */
    /* port B data */

    /* Port B & E clock enable */
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOB | SYSCTL_RCGC2_GPIOE;
    /* delay until the SYSCTL is enabled */
    while((SYSCTL_PRGPIO_R & (SYSCTL_RCGC2_GPIOB | SYSCTL_RCGC2_GPIOE)) == 0);

    //Control port configurations
    GPIO_PORTE_AFSEL_R &= ~(RS|RW|E);       // alternate function select
    GPIO_PORTE_PCTL_R  &= ~(RS|RW|E);       // determine the selected alternate function
    GPIO_PORTE_AMSEL_R &= ~(RS|RW|E);       // analog mode select for port E
    GPIO_PORTE_DEN_R   |= (RS|RW|E);        // digital enable
    GPIO_PORTE_DIR_R   |= (RS|RW|E);        // Configure the control pins(E,RS,RW) as output pins
    //Data port configurations
    GPIO_PORTB_AFSEL_R = 0;                 // alternate function select
    GPIO_PORTB_PCTL_R  = 0;                 // determine the selected alternate function
    GPIO_PORTB_AMSEL_R = 0;                 // analog mode select for port B
    GPIO_PORTB_DEN_R = 0XFF;                // digital enable
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

    delay_ms();               /* delay for processing Tdsw = 100ns */
    GPIO_PORTE_DATA_R &= ~E;  /* disable LCD E=0 */
    delay_ms();               /* delay for processing Th = 13ns */
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
/***********************************************************************************
 * Description : Configure the LCD to send character then send the data on PORTB
 * Arguments   : character
 * Return      : none
 ***********************************************************************************/
void LCD_displayCharacter(uint8_t data){
    GPIO_PORTE_DATA_R |= RS;    //Data Mode RS=1
    GPIO_PORTE_DATA_R &= ~RW;   //write data to LCD so RW=0
    delay_ms();                 //delay for processing Tas = 50ns
    GPIO_PORTE_DATA_R |= E;     //Enable LCD E=1
    delay_ms();                 //delay for processing Tpw - Tdws = 190ns
    //Configure 8 bit mode or 4 bit mode
    #if (DATA_BITS_MODE == 4)
        // out the highest 4 bits of the required data to the data bus B4 --> B7
    #ifdef UPPER_PORT_PINS
        GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & 0x0F) | (data & 0xF0);
    #else
        GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & 0xF0) | ((data & 0xF0) >> 4);
    #endif
    delay_ms();                 //delay for processing Tdsw = 100ns
    GPIO_PORTE_DATA_R &= ~E;    //disable LCD E=0
    delay_ms();                 //delay for processing Th = 13ns
    GPIO_PORTE_DATA_R |= E;     //Enable LCD E=1
    delay_ms();                 //delay for processing Tpw - Tdws = 190ns
    //out the lowest 4 bits of the required data to the data bus B4 --> B7
    #ifdef UPPER_PORT_PINS
        GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & 0x0F) | ((data & 0x0F) << 4);
    #else
        GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & 0xF0) | (data & 0x0F);
    #endif

        delay_ms();                 /* delay for processing Tdsw = 100ns */
        GPIO_PORTE_DATA_R &= ~E;    /* disable LCD E=0 */
        delay_ms();                 /* delay for processing Th = 13ns */
    #elif (DATA_BITS_MODE == 8)
        GPIO_PORTB_DATA_R = data;   /* out the required command to the data bus D0 --> D7 */
        delay_ms();                 /* delay for processing Tdsw = 100ns */
        GPIO_PORTE_DATA_R &= ~E;    /* disable LCD E=0 */
        delay_ms();                 /* delay for processing Th = 13ns */
    #endif
}
/***********************************************************************************
 * Description : Send Multiple character(string) to the LCD
 * Arguments   : string
 * Return      : none
 ***********************************************************************************/
void LCD_displayString(const char *Str){
    uint8_t i = 0;
    while(Str[i] != '\0')
    {
        LCD_displayCharacter(Str[i]);
        i++;
    }
}
/***********************************************************************************
 * Description : change the position  of the cursor
 * Arguments   : (row) position in the row, (col) postion in the column
 * Return      : none
 ***********************************************************************************/
void LCD_goToRowColumn(uint8_t row,uint8_t col)
{
    uint8_t Address;
    //Calculate the required address
    switch(row)
    {
        case 0:
                Address=col;
                break;
        case 1:
                Address=col+0x40;
                break;
        case 2:
                Address=col+0x10;
                break;
        case 3:
                Address=col+0x50;
                break;
    }
    //to write in a specific address in the LCD
    //we need to send the corresponding command 0b10000000 + Address
    LCD_sendCommand(Address | SET_CURSOR_LOCATION);
}
/***********************************************************************************
 * Description : Prints double number on the LCD, converts the double number to
 *               string and then call function LCD_displayString(..)
 * Arguments   : (data) the number to be displayed on the screen
 * Return      : none
 ***********************************************************************************/
void LCD_intgerToString(double data)
{
    char buff[16];  //String to hold the ascii result
    sprintf(buff, "%f", data);
    //i_s( buff, (int)data);
    //itoa(data,buff,10);  //10 for decimal

    LCD_displayString(buff);
}
/***********************************************************************************
 * Description : Converts the integer number to string
 * Arguments   : (in/out)(str[]) pointer to the buffer to save the converted number in,
 *               (in)(k) number to be converted
 * Return      : none
 ***********************************************************************************/
void i_s(char str[], int k){
    uint8_t c=0, i=0;
    char tmp[20];
    while(k!=0){
        c=k%10;
        k=k/10;
        switch(c){
        case 0:
            c='0';
            break;
        case 1:
            c='1';
            break;
        case 2:
            c='2';
            break;
        case 3:
            c='3';
            break;
        case 4:
            c='4';
            break;
        case 5:
            c='5';
            break;
        case 6:
            c='6';
            break;
        case 7:
            c='7';
            break;
        case 8:
            c='8';
            break;
        case 9:
            c='9';
            break;
        }
        tmp[i]=c;
        i++;
    }
    tmp[i]='\0';
    for(c=0;c<i;c++){
        str[c]=tmp[i-c-1];
    }

    str[c]='\0';
}
