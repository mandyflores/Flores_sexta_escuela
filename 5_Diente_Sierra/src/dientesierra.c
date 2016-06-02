
#include "led.h"
#include "stdint.h"
#include "timer.h"
#include "dientesierra.h"
#include "dac.h"
//#include "chip_lpc43xx.h"
//#include "core_cm4.h"//libreria define habilitacion de interrupcion

#define INTERVALO 1 //PERIODO DE TIMER 1ms
#define TRUE  1
#define  CUENTA_MAX 930
//#define PERIODO    100  /* PERIODO=100 ms*/
//#define AMPLITUD   930  /* equivalente*/

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif

float contador;
float paso;
uint32_t periodo;
uint32_t amplitud;


int main(void)
{





	periodo=100;
	amplitud=930;
	contador=0;


	paso=(float)(amplitud/periodo);//convertir a flotante la division
	InicializarTimer ();
	Periodo(INTERVALO);
	InicializarLed ();

	HabilitaInterrupcion();

	InicializarDAC ();


	while(TRUE);

}

  void ISR_RIT(void)
  {
	  uint32_t valor;
	  contador = contador+paso; /*9.3v*/
	   if (contador>amplitud )
	    {
		   contador=0;
		   InvertirLed(LED_ROJO);/*al volverse el contador cero, se tiene un periodo a 100ms*/
	    }
	   valor=(uint32_t)contador;
	   ConversionDA (valor);/*   */

	   LimpiarBandera();

  }

