/*
 * gpio.c
 */
#include "gpio.h"

/*******************************************************************************
 *                       Global variable                                       *
 *******************************************************************************/
volatile unsigned char g_Interrupt_Flag = 0;

/*******************************************************************************
 *                       Function Declaration                                  *
 *******************************************************************************/

 /******************************************************************************
  * Description : Initialize Port F
  * Arguments   : none
  * Return      : none
  *****************************************************************************/
void GPIOF_Init()
{
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;             /* activate port F */
    /* delay until the SYSCTL is enabled */
	while ((SYSCTL_PRGPIO_R & SYSCTL_RCGC2_GPIOF) == 0);
    GPIO_PORTF_CR_R     |= BLUE_LED;                  /* commit register*/
    GPIO_PORTF_AFSEL_R  &=~BLUE_LED;                  /* alternate function select*/
    GPIO_PORTF_PCTL_R   &=~BLUE_LED;                  /* determine the selected alternate function*/
    GPIO_PORTF_AMSEL_R  &=~BLUE_LED;                  /* analog mode select for port D*/
    GPIO_PORTF_DIR_R    |= BLUE_LED;                  /* Configure the control pin BLUE_LED (0x04) as output pin*/
    GPIO_PORTF_DEN_R    |= BLUE_LED;                  /* digital enable*/
}

 /******************************************************************************
  * Description : LED_ON
  * Arguments   : none
  * Return      : none
  *****************************************************************************/
void Led_on()
{
    GPIO_PORTF_DATA_R |= BLUE_LED;                   /*open blue led*/
}
/******************************************************************************
 * Description : LED_OFF
 * Arguments   : none
 * Return      : none
 *****************************************************************************/
void Led_off()
{
    GPIO_PORTF_DATA_R &=~ BLUE_LED;                 /*close blue led*/
}
/******************************************************************************
 * Description : PORTF_Enable_Interrupt 
 * Arguments   : none
 * Return      : none
 *****************************************************************************/
void SW1_Int_Interrupt(void)    
{
/******************** Enable Switch on PF4 **********************************/
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;           /* activate port F */
    /* delay until the SYSCTL is enabled */
	while ((SYSCTL_PRGPIO_R & SYSCTL_RCGC2_GPIOF) == 0);
    GPIO_PORTF_CR_R     |=  SWITCH_1;               /* commit register*/
    GPIO_PORTF_AFSEL_R  &=~ SWITCH_1;               /* alternate function select*/
    GPIO_PORTF_PCTL_R   &=~ SWITCH_1;               /* determine the selected alternate function*/
    GPIO_PORTF_AMSEL_R  &=~ SWITCH_1;               /* analog mode select for port D*/
    GPIO_PORTF_DIR_R    &=~ SWITCH_1;               /* Configure the control pin SWITCH_1 0x10  as input pin*/
    GPIO_PORTF_DEN_R    |=  SWITCH_1;               /* digital enable*/
    GPIO_PORTF_PUR_R    |=  SWITCH_1;               /* pull up resistor*/

/************************** Enable External interrupt on PF4 **************************/
    GPIO_PORTF_IS_R  &=~ SWITCH_1;                  /* Edge sensitive */
    GPIO_PORTF_IBE_R &=~ SWITCH_1;                  /* not both edges */
    GPIO_PORTF_IEV_R &=~ SWITCH_1;                  /* falling edge */
    GPIO_PORTF_ICR_R |=  SWITCH_1;                  /* clear the interrupt flag */
    GPIO_PORTF_IM_R  |=  SWITCH_1;                  /* pin_num */
/********************************** NVIC_IP_PRIORITY *********************************/
    NVIC_PRI7_R |= (3<<NVIC_PRI7_INT30_S);           /* set priority 3*/
    NVIC_EN0_R  |= NVIC_EN0_PORTF_M;                 /* set Interrupt */
}
/******************************************************************************
  * Description : Interrupt Service Routines 
  * Arguments   : none
  * Return      : none
 *****************************************************************************/
void GPIOF_Handler(void)
{
	GPIO_PORTF_ICR_R |= SWITCH_1;                   /* clear the interrupt flag */
    g_Interrupt_Flag ^= 0x1;                        /* toggle Interrupt_Flag */
    if(g_Interrupt_Flag){
        LCD_clearScreen();
        LCD_goToRowColumn(0, 0);
        LCD_displayString("APP Started ..");
        LCD_goToRowColumn(1, 0);
        LCD_displayString("waiting for gps");
    }
    else{
        LCD_clearScreen();
        LCD_goToRowColumn(0, 0);
        LCD_displayString("pause the app");

    }
    delay_ms();
}


