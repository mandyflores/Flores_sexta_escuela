#ifndef TIMER_H
#define TIMER_H
#include "stdint.h" //para los numeros
#include "chip.h" /* carga biblioteca de LPCOPEN */
//#define lpc4337            1
//#define mk60fx512vlq15     2


void InicializarTimer (void);
void HabilitaInterrupcion(void);
void Periodo(uint32_t intervalo);
void LimpiarBandera(void);

#endif /* #ifndef MI_NUEVO_PROYECTO_H */
