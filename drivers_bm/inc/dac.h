#ifndef DAC_H
#define DAC_H
#include "stdint.h" //para los numeros
#include "chip.h" /* carga biblioteca de LPCOPEN */

//#define lpc4337            1
//#define mk60fx512vlq15     2


void InicializarDAC (void);
void ConversionDA (uint32_t valor);
/*void LimpiarBandera(void);*/

#endif /* #ifndef MI_NUEVO_PROYECTO_H */
