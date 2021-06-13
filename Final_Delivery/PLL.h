#ifndef PLL_H_
#define PLL_H_
#include "microconfig.h"
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define SYSCTL_RCC2_USERCC2_MASK     0x80000000  /* USERCC2 Bit MASK */
#define SYSCTL_RCC2_BYPASS2_MASK     0x00000800  /* PLL BYPASS2 Bit MASK */
#define SYSCTL_RCC_XTAL_MASK         0x000007C0  /* XTAL Bits MASK */
#define SYSCTL_RCC_XTAL_8MHZ         0x00000380  /* 8 MHz Crystal Value */
#define SYSCTL_RCC_XTAL_16MHZ        0x00000540  /* 16 MHz Crystal Value */
#define SYSCTL_RCC2_OSCSRC2_MASK     0x00000070  /* OSCSRC2 Bits MASK */
#define SYSCTL_RCC2_OSCSRC2_MOSC     0x00000000  /* MOSC(Main Oscillator) value */
#define SYSCTL_RCC2_PWRDN2_MASK      0x00002000  /* PWRDN2  Bit MASK */
#define SYSCTL_RCC2_DIV400_MASK      0x40000000  /* DIV400  Bit MASK to Divide PLL as 400 MHz vs. 200 */
#define SYSCTL_RCC2_SYSDIV2_MASK     0x1FC00000  /* SYSDIV2 Bits MASK */
#define SYSCTL_RIS_PLLLRIS_MASK      0x00000040  /* PLLLRIS Bit MASK */
#define SYSCTL_RCC2_SYSDIV2_BIT_POS  22          /* SYSDIV2 Bits Postion start from bit number 22 */
#define SYSDIV2_VALUE                4

 /*******************************************************************************
  *                      Functions Prototypes                                   *
  *******************************************************************************/
void PLL_Init(void);
#endif /* PLL_H_ */
