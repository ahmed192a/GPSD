/*
 * systick.h
 *
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_
#include "stdint.h"
/*******************************************************************************
 *                      Preprocessor Macros & Configuration                    *
 *******************************************************************************/
#define SYSTICK_USE 1       /* Configure the main code to use systick delay or not*/
#define MAX 0x00FFFFFF      /* MAX value of the Reload Register */

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void SysTick_Init(void);
void delay_ms(void);
void delay_5ms(void);
void delay_s(void);
#endif /* SYSTICK_H_ */
