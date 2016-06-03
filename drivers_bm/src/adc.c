#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif
#include "led.h"
#include"adc.h"

#include "stdint.h"
#include "chip.h" /* carga biblioteca de LPCOPEN */
//#include "chip_lpc43xx.h"
//#include "core_cm4.h"//libreria define habilitacion de interrupcion




#define ADC_ID   0



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
void InicializarADC (void)
   {
	 LPC_ADC_T ADCSetup;//estructura
	 //Chip_SCU_DAC_Analog_Config();/*le decimos que es salida analogica*/
	 Chip_SCU_ADC_Channel_Config(ADC_ID, ADC_CH1);
	 Chip_ADC_Init(LPC_ADC0,&ADCSetup );
	 Chip_ADC_EnableChannel(LPC_ADC0, ADC_CH1, ENABLE);
	 //Chip_DAC_Init(LPC_DAC);
	 //Chip_DAC_ConfigDAConverterControl(LPC_DAC, DAC_DMA_ENA);
}
uint16_t ConversionAD (void)
{
	uint16_t dato_convertido;
	//start A/D conversion);
	Chip_ADC_SetStartMode(LPC_ADC0, ADC_START_NOW ,ADC_TRIGGERMODE_RISING);
	//waiting for A/D conversion complete
	while (Chip_ADC_ReadStatus(LPC_ADC0, ADC_CH1, ADC_DR_DONE_STAT)!=SET) {}
	//ESTA permanentemente leyendo el estatus


	//Read ADC value
	Chip_ADC_ReadValue(LPC_ADC0, ADC_CH1,&dato_convertido); 	//te devuelve un valor de 16
	 return dato_convertido;
}
