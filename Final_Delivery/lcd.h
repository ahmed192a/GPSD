#ifndef LCD_H_
#define LCD_H_
#include "microconfig.h"
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define LCDUSE 1

#define DATA_BITS_MODE 4
/* Use higher 4 bits in the data port */
#if (DATA_BITS_MODE == 4)
#define UPPER_PORT_PINS
#endif
/* LCD HW Pins */
#define RS 0x02     // RS -> PD1
#define RW 0x04     // Rw -> PD2
#define E  0x08     // E  -> PD3

/* LCD Commands */
#define CLEAR_COMMAND               0x01
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define TWO_LINE_LCD_FOUR_BIT_MODE  0x28
#define FOUR_BITS_DATA_MODE         0x02
#define CURSOR_OFF                  0x0C
#define CURSOR_ON                   0x0E
#define SET_CURSOR_LOCATION         0x80

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void LCD_sendCommand(uint8_t command);
void LCD_init(void);
void LCD_clearScreen(void);
void LCD_displayCharacter(uint8_t data);
void LCD_displayString(const char *Str);
void LCD_goToRowColumn(uint8_t row,uint8_t col);
void LCD_intgerToString(double data);
#endif /* LCD_H_ */
