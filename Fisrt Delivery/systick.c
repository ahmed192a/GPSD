#include "systick.h"
#include "stdint.h"
#include "tm4c123gh6pm.h"


static volatile void(*g_callBackPtrSystick)(void) = NULL_PTR;


/*******************************************************************************
 *                      Function Declaration                                   *
 *******************************************************************************/
/*********************************************************************************
 * Description : Function to initialize the Systick with max value (MAX in systick.h)
 * Arguments   : none
 * Return      : none
 *********************************************************************************/
void SysTick_Init(void){
    //Max Reload_value = 0x00FFFFFF --> 0.2 sec
    //Reload_value = (required_delay * sysClk(80M)) - 1
    NVIC_ST_CTRL_R = 0; // disable SysTick during setup
    NVIC_ST_RELOAD_R = MAX - 1;// 0.2 sec
    NVIC_ST_CURRENT_R = 0; //clear current register and COUNTFLAG
    //NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000; // priority 2
    // enable SysTick with core clock and interrupts
    NVIC_ST_CTRL_R = 0x05; //enable and clock source 101 = 5
}
/*********************************************************************************
 * Description : Use the systick to wait for 1 second
 * Arguments   : none
 * Return      : none
 *********************************************************************************/
void delay_s(void){
    uint8_t i;
    for(i=0; i < 5; i++){
		SysTick_Init();
        while((NVIC_ST_CTRL_R&0x10000) == 0);
    }
}
/*********************************************************************************
 * Description : Use delay_s to wait for num of seconds
 * Arguments   : (in)(num) number of seconds
 * Return      : none
 *********************************************************************************/
void wait_s(uint32_t num){
    unsigned long k;
	for(k = 0; k < num; k++){
		delay_s();
	}
}
/*********************************************************************************
 * Description : configure systick to wait for 1 ms
 * Arguments   : none
 * Return      : none
 *********************************************************************************/
void delay_ms(void){
    NVIC_ST_CTRL_R = 0;
    NVIC_ST_RELOAD_R = 80000-1; //1 msec.
    NVIC_ST_CURRENT_R = 0; //clear current register and COUNTFLAG
    NVIC_ST_CTRL_R = 5; //enable and clock source 101 = 5
    while((NVIC_ST_CTRL_R & 0x10000) == 0){}
}
/*********************************************************************************
 * Description : use delay_ms() to wait for number of ms
 * Arguments   : (in)(num) number of ms
 * Return      : none
 *********************************************************************************/
void wait_ms(uint32_t num){
    unsigned long k;
	for(k = 0; k < num; k++){
		delay_ms();
	}
}
/*********************************************************************************
 * Description : Configure Systick to wait for 5ms
 * Arguments   : none
 * Return      : none
 *********************************************************************************/
void delay_5ms(void){
    NVIC_ST_CTRL_R = 0;
    NVIC_ST_RELOAD_R = (400000) - 1; //1 msec.
    NVIC_ST_CURRENT_R = 0; //clear current register and COUNTFLAG
    NVIC_ST_CTRL_R = 5; //enable and clock source 101 = 5
    while((NVIC_ST_CTRL_R & 0x10000) == 0){}
}
/*********************************************************************************
 * Description : use delay_5ms() to wait for number of 5ms
 * Arguments   : (in)(num) number of 5ms
 * Return      : none
 *********************************************************************************/
void wait_5ms(uint32_t num){
    unsigned long k;
	for(k = 0; k < num; k++){
		delay_5ms();
	}
}

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

void SysTick_Handler(void){
    if(g_callBackPtrSystick != NULL_PTR){

        /* Call the Call Back function for Systick Interrupt */
        (*g_callBackPtrSystick)();
    }
}

void Systick_setCallBack(void(*a_ptr)(void)){
    g_callBackPtrSystick = (volatile void (*)(void))a_ptr;
}




