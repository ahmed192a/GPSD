#ifndef MICROCONFIG_H_
#define MICROCONFIG_H_
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include <string.h>
#include "math.h"
#include "tm4c123gh6pm.h"
#include "gpio.h"
#include "systick.h"
#include "lcd.h"
#include "uart.h"
#include "PLL.h"
#include "gps.h"
#include "APP.h"
#include "FAT32.h"
#include "spi.h"
#include "SD.h"

#define F_CPU 80000000 /* Internal frequency 80 MHz */
#define CSV 1

/* Enable IRQ Interrupts by clearing the I bit in the PRIMASK */
#define Enable_Interrupts()  __asm("CPSIE I")
/* Disable IRQ Interrupts by setting the I bit in the PRIMASK */
#define Disable_Interrupts() __asm("CPSID I")


#endif /* MICROCONFIG_H_ */
