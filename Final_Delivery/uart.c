#include "uart.h"


/*******************************************************************************
 *                      Function Declaration                                   *
 *******************************************************************************/
/************************************************************************************************
 * Description : Function to initialize the UART
 * Arguments   : Pointer to a struct contains (no. of data bits, parity mode, UART num, baudrate)
 * Return      : none
 ************************************************************************************************/
void UART_init(const UART_ConfigType *Config_Ptr)
{
    double uart_clk = F_CPU / (16 * Config_Ptr->baudrate);

    if(Config_Ptr->uart_num == u0) /* UART0 -> portA */
    {
        SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;       /* Enable UART0 clock */
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;       /* Enable PORTA clock */

        UART0_CTL_R &= ~UART_CTL_UARTEN;            /* Disable UART0 enable */

        /* Adjust baudrate */
        UART0_IBRD_R = (uint32_t)uart_clk;
        UART0_FBRD_R = (uint32_t)((uart_clk - (uint32_t)uart_clk) *64 + 0.5) ;

        /* Adjust BIT_Data number (number of bits to be sent or received)*/
        if(Config_Ptr->bit_data == FIVE_BITS)
        {
            UART0_LCRH_R = (UART0_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_5;
        }
        else if(Config_Ptr->bit_data == SIXTH_BITS)
        {
            UART0_LCRH_R = (UART0_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_6;
        }
        else if(Config_Ptr->bit_data == SEVEN_BITS)
        {
            UART0_LCRH_R = (UART0_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_7;
        }
        else if(Config_Ptr->bit_data == EIGHT_BITS)
        {
            UART0_LCRH_R = (UART0_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_8;
        }

        /* Enable the FIFO */
        UART0_LCRH_R |= UART_LCRH_FEN;

        /* Enable RXE, TXE, UARTEN */
        UART0_CTL_R |= UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE;

        /* Enable PA0, PA1 as U0RX, U0TX  */
        GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&(~(GPIO_PCTL_PA0_M|GPIO_PCTL_PA1_M)))+(GPIO_PCTL_PA0_U0RX|GPIO_PCTL_PA1_U0TX);
        GPIO_PORTA_AFSEL_R |= P0 | P1;                          /* Enable the alternate functions on pin 0, 1 */
        GPIO_PORTA_DEN_R   |= P0 | P1;                          /* Enable Digital on pins 0, 1 */
        GPIO_PORTA_AMSEL_R &= (~P0) & (~P1);                    /* Disable Analog on pins 0, 1 */
    }

    else if(Config_Ptr -> uart_num == u1_B)/* UART1 -> portB */
    {
        SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1; /* activate UART1 */
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1; /* activate PORTB */

        UART1_CTL_R &= ~UART_CTL_UARTEN;      /* Disable UART1 enable */

        /* Adjust baudrate */
        UART1_IBRD_R = (uint32_t)uart_clk;
        UART1_FBRD_R = (uint32_t)((uart_clk - (uint32_t)uart_clk) * 64 + 0.5) ;

        /* Adjust BIT_Data number (number of bits to be sent or received)*/
        if(Config_Ptr->bit_data == FIVE_BITS)
        {
            UART1_LCRH_R = (UART1_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_5;
        }
        else if(Config_Ptr->bit_data == SIXTH_BITS)
        {
            UART1_LCRH_R |= (UART1_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_6;
        }
        else if(Config_Ptr->bit_data == SEVEN_BITS)
        {
            UART1_LCRH_R |= (UART1_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_7;
        }
        else if(Config_Ptr->bit_data == EIGHT_BITS)
        {
            UART1_LCRH_R |= (UART1_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_8;
        }

        /* Enable the FIFO */
        UART1_LCRH_R |= UART_LCRH_FEN;

        /* Enable RXE, TXE, UARTEN */
        UART1_CTL_R |= UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE;

        GPIO_PORTB_AFSEL_R |= P0 | P1;                         /* Enable the alternate functions on pin 0, 1 */
        GPIO_PORTB_DEN_R   |= P0 | P1;                           /* Enable Digital on pins 0, 1 */
        GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&(~(GPIO_PCTL_PB0_M|GPIO_PCTL_PB1_M)))+(GPIO_PCTL_PB1_U1TX|GPIO_PCTL_PB0_U1RX); /* put ones on pin 0, 1 to work as UART1 */
        GPIO_PORTB_AMSEL_R &= (~P0) & (~P1);                   /* Disable Analog on pins 0, 1 */
    }

    else if(Config_Ptr -> uart_num == u1_C)/* UART1 -> portC */
    {
        SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1; /* activate UART1 */
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2; /* activate PORTC */

        UART1_CTL_R &= ~UART_CTL_UARTEN;      /* Disable UART1 enable */

        /* Adjust baudrate */
        UART1_IBRD_R = (uint32_t)uart_clk;
        UART1_FBRD_R = (uint32_t)((uart_clk - (uint32_t)uart_clk) * 64 + 0.5) ;

        /* Adjust BIT_Data number (number of bits to be sent or received)*/
        if(Config_Ptr->bit_data == FIVE_BITS)
        {
	    UART1_LCRH_R = (UART1_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_5;
        }
        else if(Config_Ptr->bit_data == SIXTH_BITS)
        {
            UART1_LCRH_R |= (UART1_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_6;
        }
        else if(Config_Ptr->bit_data == SEVEN_BITS)
        {
            UART1_LCRH_R |= (UART1_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_7;
        }
        else if(Config_Ptr->bit_data == EIGHT_BITS)
        {
	    UART1_LCRH_R |= (UART1_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_8;
        }

        /* Enable the FIFO */
        UART1_LCRH_R |= UART_LCRH_FEN;

        /* Enable RXE, TXE, UARTEN */
        UART1_CTL_R |= UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE;


        GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF)+0x00220000;/* put 2 on pin 4, 5 to work as UART1 */
        GPIO_PORTC_AFSEL_R |= P4 | P5;                        /* Enable the alternate functions on pin 4, 5 */
        GPIO_PORTC_DEN_R |= P4 | P5;                          /* Enable Digital on pins 4, 5 */
        GPIO_PORTC_AMSEL_R &= (~P4) & (~P5);                  /* Disable Analog on pins 4, 5 */
    }
    else if(Config_Ptr -> uart_num == u3)/* UART3 -> portC */
    {
        SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R3; /* activate UART3 */
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2; /* activate PORTC */

        UART3_CTL_R &= ~UART_CTL_UARTEN;      /* Disable UART3 enable */

        /* Adjust baudrate */
        UART3_IBRD_R = (uint32_t)uart_clk;
        UART3_FBRD_R = (uint32_t)((uart_clk - (uint32_t)uart_clk) * 64 + 0.5) ;

        /* Adjust BIT_Data number (number of bits to be sent or received)*/
        if(Config_Ptr->bit_data == FIVE_BITS)
        {
	    UART3_LCRH_R = (UART3_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_5;
        }
        else if(Config_Ptr->bit_data == SIXTH_BITS)
        {
	    UART3_LCRH_R = (UART3_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_6;
        }
        else if(Config_Ptr->bit_data == SEVEN_BITS)
        {
	    UART3_LCRH_R |= (UART3_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_7;
        }
        else if(Config_Ptr->bit_data == EIGHT_BITS)
        {
	    UART3_LCRH_R |= (UART3_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_8;
        }

        /* Enable the FIFO */
        UART3_LCRH_R |= UART_LCRH_FEN;

        /* Enable RXE, TXE, UARTEN */
        UART3_CTL_R |= UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE;


        GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0x00FFFFFF)+0x11000000;/* put 1 on pin 6, 7 to work as UART3 */
        GPIO_PORTC_AFSEL_R |= P6 | P7;                        /* Enable the alternate functions on pin 6, 7 */
        GPIO_PORTC_DEN_R   |= P6 | P7;                        /* Enable Digital on pins 6, 7 */
        GPIO_PORTC_AMSEL_R &= (~P6) & (~P7);                  /* Disable Analog on pins 6, 7 */
    }

    else if(Config_Ptr -> uart_num == u4)/* UART4 -> portC */
    {
        SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R4; /* activate UART4 */
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2; /* activate PORTC */

        UART4_CTL_R &= ~UART_CTL_UARTEN;      /* Disable UART4 enable */

        /* Adjust baudrate */
        UART4_IBRD_R = (uint32_t)uart_clk;
        UART4_FBRD_R = (uint32_t)((uart_clk - (uint32_t)uart_clk) * 64 + 0.5) ;

        /* Adjust BIT_Data number (number of bits to be sent or received)*/
        if(Config_Ptr->bit_data == FIVE_BITS)
        {
	    UART4_LCRH_R = (UART4_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_5;
        }
        else if(Config_Ptr->bit_data == SIXTH_BITS)
        {
            UART4_LCRH_R = (UART4_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_6;
        }
        else if(Config_Ptr->bit_data == SEVEN_BITS)
        {
            UART4_LCRH_R = (UART4_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_7;
        }
        else if(Config_Ptr->bit_data == EIGHT_BITS)
        {
            UART4_LCRH_R = (UART4_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_8;
        }

        /* Enable the FIFO */
        UART4_LCRH_R |= UART_LCRH_FEN;

        /* Enable RXE, TXE, UARTEN */
        UART4_CTL_R |= UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE;


        GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF)+0x00110000;/* put 1 on pin 4, 5 to work as UART4 */
        GPIO_PORTC_AFSEL_R |= P4 | P5;                        /* Enable the alternate functions on pin 4, 5 */
        GPIO_PORTC_DEN_R |= P4 | P5;                          /* Enable Digital on pins 4, 5 */
        GPIO_PORTC_AMSEL_R &= (~P4) & (~P5);                  /* Disable Analog on pins 4, 5 */
    }

    else if(Config_Ptr -> uart_num == u5)/* UART5 -> portE */
    {
        SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R5; /* activate UART5 */
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4; /* activate PORTE */

        UART5_CTL_R &= ~UART_CTL_UARTEN;      /* Disable UART5 enable */

        /* Adjust baudrate */
        UART5_IBRD_R = (uint32_t)uart_clk;
        UART5_FBRD_R = (uint32_t)((uart_clk - (uint32_t)uart_clk) *64 + 0.5) ;

        /* Adjust BIT_Data number (number of bits to be sent or received)*/
        if(Config_Ptr->bit_data == FIVE_BITS)
        {
            UART5_LCRH_R = (UART5_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_5;
        }
        else if(Config_Ptr->bit_data == SIXTH_BITS)
        {
            UART5_LCRH_R = (UART5_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_6;
        }
        else if(Config_Ptr->bit_data == SEVEN_BITS)
        {
            UART5_LCRH_R = (UART5_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_7;
        }
        else if(Config_Ptr->bit_data == EIGHT_BITS)
        {
            UART5_LCRH_R = (UART5_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_8;
        }

        /* Enable the FIFO */
        UART5_LCRH_R |= UART_LCRH_FEN;

        /* Enable RXE, TXE, UARTEN */
        UART5_CTL_R |= UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE;


        GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R&0xFF00FFFF)+0x00110000;/* put 1 on pin 4, 5 to work as UART5 */
        GPIO_PORTE_AFSEL_R |= P5 | P4;                        /* Enable the alternate functions on pin 4, 5 */
        GPIO_PORTE_DEN_R |= P5 | P4;                          /* Enable Digital on pins 4, 5 */
        GPIO_PORTE_AMSEL_R &= (~P5) & (~P4);                  /* Disable Analog on pins 4, 5 */
    }

    else if(Config_Ptr -> uart_num == u6)/* UART6 -> portD */
    {
        SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R6; /* activate UART6 */
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3; /* activate PORTD */

        UART6_CTL_R &= ~UART_CTL_UARTEN;      /* Disable UART6 enable */

        /* Adjust baudrate */
        UART6_IBRD_R = (uint32_t)uart_clk;
        UART6_FBRD_R = (uint32_t)((uart_clk - (uint32_t)uart_clk) *64 + 0.5) ;

        /* Adjust BIT_Data number (number of bits to be sent or received)*/
        if(Config_Ptr->bit_data == FIVE_BITS)
        {
            UART6_LCRH_R = (UART6_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_5;
        }
        else if(Config_Ptr->bit_data == SIXTH_BITS)
        {
            UART6_LCRH_R = (UART6_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_6;
        }
        else if(Config_Ptr->bit_data == SEVEN_BITS)
        {
            UART6_LCRH_R = (UART6_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_7;
        }
        else if(Config_Ptr->bit_data == EIGHT_BITS)
        {
            UART6_LCRH_R = (UART6_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_8;
        }

        /* Enable the FIFO */
        UART6_LCRH_R |= UART_LCRH_FEN;

        /* Enable RXE, TXE, UARTEN */
        UART6_CTL_R |= UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE;


        GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R&0xFF00FFFF)+0x00110000;/* put 1 on pin 4, 5 to work as UART6 */
        GPIO_PORTD_AFSEL_R |= P5 | P4;                        /* Enable the alternate functions on pin 4, 5 */
        GPIO_PORTD_DEN_R |= P5 | P4;                          /* Enable Digital on pins 4, 5 */
        GPIO_PORTD_AMSEL_R &= (~P5) & (~P4);                  /* Disable Analog on pins 4, 5 */
    }
    else/* UART7 -> portE */
    {
        SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R7; /* activate UART7 */
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4; /* activate PORTE */

        UART7_CTL_R &= ~UART_CTL_UARTEN;      /* Disable UART7 enable */

        /* Adjust baudrate */
        UART7_IBRD_R = (uint32_t)uart_clk;
        UART7_FBRD_R = (uint32_t)((uart_clk - (uint32_t)uart_clk) *64 + 0.5) ;

        /* Adjust BIT_Data number (number of bits to be sent or received)*/
        if(Config_Ptr->bit_data == FIVE_BITS)
        {
	    UART7_LCRH_R = (UART7_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_5;
        }
        else if(Config_Ptr->bit_data == SIXTH_BITS)
        {
            UART7_LCRH_R = (UART7_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_6;
        }
        else if(Config_Ptr->bit_data == SEVEN_BITS)
        {
            UART7_LCRH_R = (UART7_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_7;
        }
        else if(Config_Ptr->bit_data == EIGHT_BITS)
        {
            UART7_LCRH_R = (UART7_LCRH_R & UART_LCRH_WLEN_M )| UART_LCRH_WLEN_8;
        }

        /* Enable the FIFO */
        UART7_LCRH_R |= UART_LCRH_FEN;

        /* Enable RXE, TXE, UARTEN */
        UART7_CTL_R |= UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE;


        GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R&0xFFFFFF00)+0x00000011;/* put 1 on pin 0, 1 to work as UART6 */
        GPIO_PORTE_AFSEL_R |= P1 | P0;                        /* Enable the alternate functions on pin 0, 1 */
        GPIO_PORTE_DEN_R   |= P1 | P0;                        /* Enable Digital on pins 0, 1 */
        GPIO_PORTE_AMSEL_R &= (~P1) & (~P0);                  /* Disable Analog on pins 0, 1 */
    }
}


/************************************************************************************************
 * Description : Function to send a data to another device (max 1 byte)
 * Arguments   : data to be sent, the UART number
 * Return      : none
 ************************************************************************************************/
void UART_sendByte(const uint8_t data, UART_NUMBER num)
{
    if(num == u0)
    {
        while((UART0_FR_R &UART_FR_TXFF) != 0);   /* wait until fifo is not full, 0-> not full*/
        UART0_DR_R = data;
    }
    else if(num == u1_B)
    {
        while((UART1_FR_R &UART_FR_TXFF) != 0);   /* wait until fifo is not full, 0-> not full*/
        UART1_DR_R = data;
    }
    else if(num == u1_C)
    {
        while((UART1_FR_R &UART_FR_TXFF) != 0);   /* wait until fifo is not full, 0-> not full*/
        UART1_DR_R = data;
    }
    else if(num == u3)
    {
        while((UART3_FR_R &UART_FR_TXFF) != 0);   /* wait until fifo is not full, 0-> not full*/
        UART3_DR_R = data;
    }
    else if(num == u4)
    {
        while((UART4_FR_R &UART_FR_TXFF) != 0);   /* wait until fifo is not full, 0-> not full*/
        UART4_DR_R = data;
    }
    else if(num == u5)
    {
        while((UART5_FR_R &UART_FR_TXFF) != 0);   /* wait until fifo is not full, 0-> not full*/
        UART5_DR_R = data;
    }
    else if(num == u6)
    {
        while((UART6_FR_R &UART_FR_TXFF) != 0);   /* wait until fifo is not full, 0-> not full*/
        UART6_DR_R = data;
    }
    else
    {
        while((UART7_FR_R &UART_FR_TXFF) != 0);   /* wait until fifo is not full, 0-> not full*/
        UART7_DR_R = data;
    }

}


/************************************************************************************************
 * Description : Function to receive a data from another device
 * Arguments   : the UART number
 * Return      : the received data
 ************************************************************************************************/
uint8_t UART_recieveByte(UART_NUMBER num)
{
    if(num == u0)
    {
        while((UART0_FR_R&UART_FR_RXFE) != 0);      // wait until RXFE is 0
        return((char)(UART0_DR_R&UART_DR_DATA_M));
    }
    else if(num == u1_B)
    {
        while((UART1_FR_R&UART_FR_RXFE) != 0);      // wait until RXFE is 0
        return((char)(UART1_DR_R&UART_DR_DATA_M));
    }
    else if(num == u1_C)
    {
        while((UART1_FR_R&UART_FR_RXFE) != 0);      // wait until RXFE is 0
        return((char)(UART1_DR_R&UART_DR_DATA_M));
    }
    else if(num == u3)
    {
        while((UART3_FR_R&UART_FR_RXFE) != 0);      // wait until RXFE is 0
        return((char)(UART3_DR_R&UART_DR_DATA_M));
    }
    else if(num == u4)
    {
        while((UART4_FR_R&UART_FR_RXFE) != 0);      // wait until RXFE is 0
        return((char)(UART4_DR_R&UART_DR_DATA_M));
    }
    else if(num == u5)
    {
        while((UART5_FR_R&UART_FR_RXFE) != 0);      // wait until RXFE is 0
        return((char)(UART5_DR_R&UART_DR_DATA_M));
    }
    else if(num == u6)
    {
        while((UART6_FR_R&UART_FR_RXFE) != 0);      // wait until RXFE is 0
        return((char)(UART6_DR_R&UART_DR_DATA_M));
    }
    else
    {
        while((UART7_FR_R&UART_FR_RXFE) != 0);      // wait until RXFE is 0
        return((char)(UART7_DR_R&UART_DR_DATA_M));
    }
}

/************************************************************************************************
 * Description : Function to send a data (of type string) to another device
 * Arguments   : string to be sent, the UART number
 * Return      : none
 ************************************************************************************************/
void UART_sendString(char * string, UART_NUMBER uart_num)
{
    while(*string)
    {
        UART_sendByte(*(string++), uart_num);
    }
}



/************************************************************************************************
 * Description : Function to receive a data (of type string) from another device
 * Arguments   : string to be save the received data in, the UART number
 * Return      : length of the string
 ************************************************************************************************/
uint8_t UART_receiveString(char *ptr_string , UART_NUMBER uart_num)
{
    char ch;
    uint8_t len = 0;
    while(1)
    {
        ch = UART_recieveByte(uart_num);
        //UART_sendByte(ch,uart_num);
        if((ch=='\r') || (ch=='\n') || (ch==0)) // Read till enter key is pressed
        {
            if(len!=0)                          // Wait till atleast 1 char is received
            {
                ptr_string[len]=0;              // once enter key is pressed null terminate the string and break the loop
                break;
            }
        }
        else if((ch=='\b') && (len!=0))
        {
            len--;                              // If backspace is pressed then decrement the index to remove the old char
        }
        else
        {
            ptr_string[len]=ch;               //copy the char into string and increment the index
            len++;
        }
    }
    return len;
}
