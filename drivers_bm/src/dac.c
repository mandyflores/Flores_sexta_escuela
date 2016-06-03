#include "stdint.h"
#include "chip.h" /* carga biblioteca de LPCOPEN */
//#include "chip_lpc43xx.h"
//#include "core_cm4.h"//libreria define habilitacion de interrupcion


/*void InicializarTimer (void)
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
*/
void InicializarDAC (void)
   {

	 Chip_SCU_DAC_Analog_Config();/*le decimos que es salida analogica*/
	 Chip_DAC_Init(LPC_DAC);
	 Chip_DAC_ConfigDAConverterControl(LPC_DAC, DAC_DMA_ENA);
}
void ConversionDA (uint32_t valor)
{
	Chip_DAC_UpdateValue(LPC_DAC,valor);
}
