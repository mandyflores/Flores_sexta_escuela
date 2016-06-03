#include "stdint.h"
#include "chip.h" /* carga biblioteca de LPCOPEN */
//#include "chip_lpc43xx.h"
//#include "core_cm4.h"//libreria define habilitacion de interrupcion


void InicializarTimer (void)
{
	Chip_RIT_Init(LPC_RITIMER);//inicializa el temporizador RTI direccion base del periferico
}
void HabilitaInterrupcion(void)
{
	NVIC_EnableIRQ(RITIMER_IRQn);	//funcion que habilita la interrupcion
}

void Periodo(intervalo)
{
 Chip_RIT_SetTimerInterval(LPC_RITIMER, intervalo);
}

void LimpiarBandera(void)
{
	Chip_RIT_ClearInt(LPC_RITIMER);//borra el flag
}
