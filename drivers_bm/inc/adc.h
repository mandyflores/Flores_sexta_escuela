#ifndef ADC_H
#define ADC_H


#include "stdint.h" //para los numeros
#include "chip.h" /* carga biblioteca de LPCOPEN */

//#define lpc4337            1
//#define mk60fx512vlq15     2


void InicializarADC (void);

uint16_t ConversionAD (void);



#endif /* #ifndef MI_NUEVO_PROYECTO_H */
