/*
 * gpio.h
 */

#ifndef GPIO_H_
#define GPIO_H_
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define RED_LED     0x02           
#define BLUE_LED    0x04           
#define GREEN_LED   0x08
#define SWITCH_1    0x10  
#define PORTF       0x20
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void Led_on();                                /* LED_OFF */
void Led_off();                              /* LED_ON */
void GPIOF_Init();                          /*INITIALIZE PORTF */
void SW1_Int_Interrupt(void);              /*PORTF_Enable_Interrupt */
void GPIOF_Handler(void);                 /* Interrupt Service Routines  */



#endif /* GPIO_H_ */
