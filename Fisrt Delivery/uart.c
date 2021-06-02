#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "tm4c123gh6pm.h"
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
    double uart_clk = 80000000 / (16 * Config_Ptr->baudrate);

    if(Config_Ptr->uart_num == u0) /* UART0 -> portA */
    {
        SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0;       /* Enable UART0 clock */
        SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;       /* Enable PORTA clock */

        UART0_CTL_R &= ~(1<<0);                     /* Disable UART0 enable */

        /* Adjust baudrate */
        UART0_IBRD_R = (uint32_t)uart_clk;
        UART0_FBRD_R = (uint32_t)((uart_clk - (uint32_t)uart_clk) *64 + 0.5) ;

        /* Adjust BIT_Data number (number of bits to be sent or received)*/
        if(Config_Ptr->bit_data == FIVE_BITS)
        {
            UART0_LCRH_R = 0;
        }
        else if(Config_Ptr->bit_data == SIXTH_BITS)
        {
            UART0_LCRH_R |= (1<<5);
            UART0_LCRH_R &= ~(1<<6);
        }
        else if(Config_Ptr->bit_data == SEVEN_BITS)
        {
            UART0_LCRH_R &= ~(1<<5);
            UART0_LCRH_R |= (1<<6);
        }
        else if(Config_Ptr->bit_data == EIGHT_BITS)
        {
            UART0_LCRH_R |= (1<<5);
            UART0_LCRH_R |= (1<<6);
        }

        /* Enable the FIFO */
        UART0_LCRH_R |= 0X10;

        /* Enable RXE, TXE, UARTEN */
        UART0_CTL_R |= (1<<0) | (1<<8) | (1<<9);

        GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011;/* put ones on pin 0, 1 to work as UART0 */
        GPIO_PORTA_AFSEL_R |= (1<<0) | (1<<1);                        /* Enable the alternate functions on pin 0, 1 */
        GPIO_PORTA_DEN_R |= (1<<0) | (1<<1);                          /* Enable Digital on pins 0, 1 */
        GPIO_PORTA_AMSEL_R &= (~(1<<0)) &(~(1<<1));                   /* Disable Analog on pins 0, 1 */
    }

    else if(Config_Ptr -> uart_num == u1_B)/* UART1 -> portB */
    {
        SYSCTL_RCGCUART_R |= (1<<1); /* activate UART1 */
        SYSCTL_RCGCGPIO_R |= (1<<1); /* activate PORTB */

        UART1_CTL_R &= ~(1<<0);      /* Disable UART1 enable */

        /* Adjust baudrate */
        UART1_IBRD_R = (uint32_t)uart_clk;
        UART1_FBRD_R = (uint32_t)((uart_clk - (uint32_t)uart_clk) * 64 + 0.5) ;

        /* Adjust BIT_Data number (number of bits to be sent or received)*/
        if(Config_Ptr->bit_data == FIVE_BITS)
        {
            UART1_LCRH_R = 0;
        }
        else if(Config_Ptr->bit_data == SIXTH_BITS)
        {
            UART1_LCRH_R |= (1<<5);
            UART1_LCRH_R &= ~(1<<6);
        }
        else if(Config_Ptr->bit_data == SEVEN_BITS)
        {
            UART1_LCRH_R &= ~(1<<5);
            UART1_LCRH_R |= (1<<6);
        }
        else if(Config_Ptr->bit_data == EIGHT_BITS)
        {
            UART1_LCRH_R |= (1<<5);
            UART1_LCRH_R |= (1<<6);
        }

        /* Enable the FIFO */
        UART1_LCRH_R |= 0X10;

        /* Enable RXE, TXE, UARTEN */
        UART1_CTL_R |= (1<<0) | (1<<8) | (1<<9);


        GPIO_PORTB_AFSEL_R |= (1<<0) | (1<<1);                         /* Enable the alternate functions on pin 0, 1 */
        GPIO_PORTB_DEN_R |= (1<<0) | (1<<1);                           /* Enable Digital on pins 0, 1 */
        GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFFFF00)+0x00000011; /* put ones on pin 0, 1 to work as UART1 */
        GPIO_PORTB_AMSEL_R &= (~(1<<0)) & (~(1<<1));                   /* Disable Analog on pins 0, 1 */
    }

    else if(Config_Ptr -> uart_num == u1_C)/* UART1 -> portC */
    {
        SYSCTL_RCGCUART_R |= (1<<1); /* activate UART1 */
        SYSCTL_RCGCGPIO_R |= (1<<2); /* activate PORTC */

        UART1_CTL_R &= ~(1<<0);      /* Disable UART1 enable */

        /* Adjust baudrate */
        UART1_IBRD_R = (uint32_t)uart_clk;
        UART1_FBRD_R = (uint32_t)((uart_clk - (uint32_t)uart_clk) * 64 + 0.5) ;

        /* Adjust BIT_Data number (number of bits to be sent or received)*/
        if(Config_Ptr->bit_data == FIVE_BITS)
        {
            UART1_LCRH_R = 0;
        }
        else if(Config_Ptr->bit_data == SIXTH_BITS)
        {
            UART1_LCRH_R |= (1<<5);
            UART1_LCRH_R &= ~(1<<6);
        }
        else if(Config_Ptr->bit_data == SEVEN_BITS)
        {
            UART1_LCRH_R &= ~(1<<5);
            UART1_LCRH_R |= (1<<6);
        }
        else if(Config_Ptr->bit_data == EIGHT_BITS)
        {
            UART1_LCRH_R |= (1<<5);
            UART1_LCRH_R |= (1<<6);
        }

        /* Enable the FIFO */
        UART1_LCRH_R |= 0X10;

        /* Enable RXE, TXE, UARTEN */
        UART1_CTL_R |= (1<<0) | (1<<8) | (1<<9);


        GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF)+0x00220000;/* put 2 on pin 4, 5 to work as UART1 */
        GPIO_PORTC_AFSEL_R |= (1<<4) | (1<<5);                        /* Enable the alternate functions on pin 4, 5 */
        GPIO_PORTC_DEN_R |= (1<<4) | (1<<5);                          /* Enable Digital on pins 4, 5 */
        GPIO_PORTC_AMSEL_R &= (~(1<<4)) & (~(1<<5));                  /* Disable Analog on pins 4, 5 */
    }
    else if(Config_Ptr -> uart_num == u3)/* UART3 -> portC */
    {
        SYSCTL_RCGCUART_R |= (1<<3); /* activate UART3 */
        SYSCTL_RCGCGPIO_R |= (1<<2); /* activate PORTC */

        UART3_CTL_R &= ~(1<<0);      /* Disable UART3 enable */

        /* Adjust baudrate */
        UART3_IBRD_R = (uint32_t)uart_clk;
        UART3_FBRD_R = (uint32_t)((uart_clk - (uint32_t)uart_clk) * 64 + 0.5) ;

        /* Adjust BIT_Data number (number of bits to be sent or received)*/
        if(Config_Ptr->bit_data == FIVE_BITS)
        {
            UART3_LCRH_R = 0;
        }
        else if(Config_Ptr->bit_data == SIXTH_BITS)
        {
            UART3_LCRH_R |= (1<<5);
            UART3_LCRH_R &= ~(1<<6);
        }
        else if(Config_Ptr->bit_data == SEVEN_BITS)
        {
            UART3_LCRH_R &= ~(1<<5);
            UART3_LCRH_R |= (1<<6);
        }
        else if(Config_Ptr->bit_data == EIGHT_BITS)
        {
            UART3_LCRH_R |= (1<<5);
            UART3_LCRH_R |= (1<<6);
        }

        /* Enable the FIFO */
        UART3_LCRH_R |= 0X10;

        /* Enable RXE, TXE, UARTEN */
        UART3_CTL_R |= (1<<0) | (1<<8) | (1<<9);


        GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0x00FFFFFF)+0x11000000;/* put 1 on pin 6, 7 to work as UART3 */
        GPIO_PORTC_AFSEL_R |= (1<<6) | (1<<7);                        /* Enable the alternate functions on pin 6, 7 */
        GPIO_PORTC_DEN_R |= (1<<6) | (1<<7);                          /* Enable Digital on pins 6, 7 */
        GPIO_PORTC_AMSEL_R &= (~(1<<6)) & (~(1<<7));                  /* Disable Analog on pins 6, 7 */
    }

    else if(Config_Ptr -> uart_num == u4)/* UART4 -> portC */
    {
        SYSCTL_RCGCUART_R |= (1<<4); /* activate UART4 */
        SYSCTL_RCGCGPIO_R |= (1<<2); /* activate PORTC */

        UART4_CTL_R &= ~(1<<0);      /* Disable UART4 enable */

        /* Adjust baudrate */
        UART4_IBRD_R = (uint32_t)uart_clk;
        UART4_FBRD_R = (uint32_t)((uart_clk - (uint32_t)uart_clk) * 64 + 0.5) ;

        /* Adjust BIT_Data number (number of bits to be sent or received)*/
        if(Config_Ptr->bit_data == FIVE_BITS)
        {
            UART4_LCRH_R = 0;
        }
        else if(Config_Ptr->bit_data == SIXTH_BITS)
        {
            UART4_LCRH_R |= (1<<5);
            UART4_LCRH_R &= ~(1<<6);
        }
        else if(Config_Ptr->bit_data == SEVEN_BITS)
        {
            UART4_LCRH_R &= ~(1<<5);
            UART4_LCRH_R |= (1<<6);
        }
        else if(Config_Ptr->bit_data == EIGHT_BITS)
        {
            UART4_LCRH_R |= (1<<5);
            UART4_LCRH_R |= (1<<6);
        }

        /* Enable the FIFO */
        UART4_LCRH_R |= 0X10;

        /* Enable RXE, TXE, UARTEN */
        UART4_CTL_R |= (1<<0) | (1<<8) | (1<<9);


        GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF)+0x00110000;/* put 1 on pin 4, 5 to work as UART4 */
        GPIO_PORTC_AFSEL_R |= (1<<4) | (1<<5);                        /* Enable the alternate functions on pin 4, 5 */
        GPIO_PORTC_DEN_R |= (1<<4) | (1<<5);                          /* Enable Digital on pins 4, 5 */
        GPIO_PORTC_AMSEL_R &= (~(1<<4)) & (~(1<<5));                  /* Disable Analog on pins 4, 5 */
    }

    else if(Config_Ptr -> uart_num == u5)/* UART5 -> portE */
    {
        SYSCTL_RCGCUART_R |= (1<<5); /* activate UART5 */
        SYSCTL_RCGCGPIO_R |= (1<<4); /* activate PORTE */

        UART5_CTL_R &= ~(1<<0);      /* Disable UART5 enable */

        /* Adjust baudrate */
        UART5_IBRD_R = (uint32_t)uart_clk;
        UART5_FBRD_R = (uint32_t)((uart_clk - (uint32_t)uart_clk) *64 + 0.5) ;

        /* Adjust BIT_Data number (number of bits to be sent or received)*/
        if(Config_Ptr->bit_data == FIVE_BITS)
        {
            UART5_LCRH_R = 0;
        }
        else if(Config_Ptr->bit_data == SIXTH_BITS)
        {
            UART5_LCRH_R |= (1<<5);
            UART5_LCRH_R &= ~(1<<6);
        }
        else if(Config_Ptr->bit_data == SEVEN_BITS)
        {
            UART5_LCRH_R &= ~(1<<5);
            UART5_LCRH_R |= (1<<6);
        }
        else if(Config_Ptr->bit_data == EIGHT_BITS)
        {
            UART5_LCRH_R |= (1<<5);
            UART5_LCRH_R |= (1<<6);
        }

        /* Enable the FIFO */
        UART5_LCRH_R |= 0X10;

        /* Enable RXE, TXE, UARTEN */
        UART5_CTL_R |= (1<<0) | (1<<8) | (1<<9);


        GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R&0xFF00FFFF)+0x00110000;/* put 1 on pin 4, 5 to work as UART5 */
        GPIO_PORTE_AFSEL_R |= (1<<5) | (1<<4);                        /* Enable the alternate functions on pin 4, 5 */
        GPIO_PORTE_DEN_R |= (1<<5) | (1<<4);                          /* Enable Digital on pins 4, 5 */
        GPIO_PORTE_AMSEL_R &= (~(1<<5)) & (~(1<<4));                  /* Disable Analog on pins 4, 5 */
    }

    else if(Config_Ptr -> uart_num == u6)/* UART6 -> portD */
    {
        SYSCTL_RCGCUART_R |= (1<<6); /* activate UART6 */
        SYSCTL_RCGCGPIO_R |= (1<<3); /* activate PORTD */

        UART6_CTL_R &= ~(1<<0);      /* Disable UART6 enable */

        /* Adjust baudrate */
        UART6_IBRD_R = (uint32_t)uart_clk;
        UART6_FBRD_R = (uint32_t)((uart_clk - (uint32_t)uart_clk) *64 + 0.5) ;

        /* Adjust BIT_Data number (number of bits to be sent or received)*/
        if(Config_Ptr->bit_data == FIVE_BITS)
        {
            UART6_LCRH_R = 0;
        }
        else if(Config_Ptr->bit_data == SIXTH_BITS)
        {
            UART6_LCRH_R |= (1<<5);
            UART6_LCRH_R &= ~(1<<6);
        }
        else if(Config_Ptr->bit_data == SEVEN_BITS)
        {
            UART6_LCRH_R &= ~(1<<5);
            UART6_LCRH_R |= (1<<6);
        }
        else if(Config_Ptr->bit_data == EIGHT_BITS)
        {
            UART6_LCRH_R |= (1<<5);
            UART6_LCRH_R |= (1<<6);
        }

        /* Enable the FIFO */
        UART6_LCRH_R |= 0X10;

        /* Enable RXE, TXE, UARTEN */
        UART6_CTL_R |= (1<<0) | (1<<8) | (1<<9);


        GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R&0xFF00FFFF)+0x00110000;/* put 1 on pin 4, 5 to work as UART6 */
        GPIO_PORTD_AFSEL_R |= (1<<5) | (1<<4);                        /* Enable the alternate functions on pin 4, 5 */
        GPIO_PORTD_DEN_R |= (1<<5) | (1<<4);                          /* Enable Digital on pins 4, 5 */
        GPIO_PORTD_AMSEL_R &= (~(1<<5)) & (~(1<<4));                  /* Disable Analog on pins 4, 5 */
    }
    else/* UART7 -> portE */
    {
        SYSCTL_RCGCUART_R |= (1<<7); /* activate UART7 */
        SYSCTL_RCGCGPIO_R |= (1<<4); /* activate PORTE */

        UART7_CTL_R &= ~(1<<0);      /* Disable UART7 enable */

        /* Adjust baudrate */
        UART7_IBRD_R = (uint32_t)uart_clk;
        UART7_FBRD_R = (uint32_t)((uart_clk - (uint32_t)uart_clk) *64 + 0.5) ;

        /* Adjust BIT_Data number (number of bits to be sent or received)*/
        if(Config_Ptr->bit_data == FIVE_BITS)
        {
            UART7_LCRH_R = 0;
        }
        else if(Config_Ptr->bit_data == SIXTH_BITS)
        {
            UART7_LCRH_R |= (1<<5);
            UART7_LCRH_R &= ~(1<<6);
        }
        else if(Config_Ptr->bit_data == SEVEN_BITS)
        {
            UART7_LCRH_R &= ~(1<<5);
            UART7_LCRH_R |= (1<<6);
        }
        else if(Config_Ptr->bit_data == EIGHT_BITS)
        {
            UART7_LCRH_R |= (1<<5);
            UART7_LCRH_R |= (1<<6);
        }

        /* Enable the FIFO */
        UART7_LCRH_R |= 0X10;

        /* Enable RXE, TXE, UARTEN */
        UART7_CTL_R |= (1<<0) | (1<<8) | (1<<9);


        GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R&0xFFFFFF00)+0x00000011;/* put 1 on pin 0, 1 to work as UART6 */
        GPIO_PORTE_AFSEL_R |= (1<<1) | (1<<0);                        /* Enable the alternate functions on pin 0, 1 */
        GPIO_PORTE_DEN_R |= (1<<1) | (1<<0);                          /* Enable Digital on pins 0, 1 */
        GPIO_PORTE_AMSEL_R &= (~(1<<1)) & (~(1<<0));                  /* Disable Analog on pins 0, 1 */
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
        while((UART0_FR_R &0x0020) != 0);   /* wait until fifo is not full, 0-> not full*/
        UART0_DR_R = data;
    }
    else if(num == u1_B)
    {
        while((UART1_FR_R &0x0020) != 0);   /* wait until fifo is not full, 0-> not full*/
        UART1_DR_R = data;
    }
    else if(num == u1_C)
    {
        while((UART1_FR_R &0x0020) != 0);   /* wait until fifo is not full, 0-> not full*/
        UART1_DR_R = data;
    }
    else if(num == u3)
    {
        while((UART3_FR_R &0x0020) != 0);   /* wait until fifo is not full, 0-> not full*/
        UART3_DR_R = data;
    }
    else if(num == u4)
    {
        while((UART4_FR_R &0x0020) != 0);   /* wait until fifo is not full, 0-> not full*/
        UART4_DR_R = data;
    }
    else if(num == u5)
    {
        while((UART5_FR_R &0x0020) != 0);   /* wait until fifo is not full, 0-> not full*/
        UART5_DR_R = data;
    }
    else if(num == u6)
    {
        while((UART6_FR_R &0x0020) != 0);   /* wait until fifo is not full, 0-> not full*/
        UART6_DR_R = data;
    }
    else
    {
        while((UART7_FR_R &0x0020) != 0);   /* wait until fifo is not full, 0-> not full*/
        UART7_DR_R = data;
    }

}
