/*
 * spi.h
 *
 */
#ifndef _spi_h
#define _spi_h

#include "microconfig.h"

 /*******************************************************************************
  *                      Functions Prototypes                                   *
  *******************************************************************************/

void SPI_EnableChipSelect(void); 
void SPI_DisableChipSelect(void) ; 
void init_SSI0(void) ; 
uint8_t SSI_Write(uint8_t data) ; 
uint8_t SSI_Read(void) ; 


#endif 

