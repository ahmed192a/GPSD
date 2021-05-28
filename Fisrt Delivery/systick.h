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
#define NULL_PTR (void *)0
#define MAX 0x00FFFFFF      /* MAX value of the Reload Register */

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void Systick_setCallBack(void(*a_ptr)(void));
void delay_ms(void);
void delay_5ms(void);
void SysTick_Init(void);
void delay_s(void);
void wait_s(uint32_t num);
void wait_ms(uint32_t num);
void wait_5ms(uint32_t num);
#endif /* SYSTICK_H_ */
