#ifndef USART_H
#define USART_H


#include "stdint.h" //para los numeros
#include "chip.h" /* carga biblioteca de LPCOPEN */

//#define lpc4337            1
//#define mk60fx512vlq15     2


void InicializarUSART(void);

void TransmisionUSART (uint8_t datos);

uint8_t RecepcionUSART (void);



#endif /* #ifndef MI_NUEVO_PROYECTO_H */
