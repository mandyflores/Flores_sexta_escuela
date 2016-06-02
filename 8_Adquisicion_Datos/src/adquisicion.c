
#include "led.h"
#include "stdint.h"
#include "timer.h"
#include "adquisicion.h"
#include "adc.h"
//#include "chip_lpc43xx.h"
//#include "core_cm4.h"//libreria define habilitacion de interrupcion

#define INTERVALO 10 //PERIODO DE TIMER 10ms porque f=100 Hz
#define TRUE  1

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

//float contador;
//float paso;
//uint32_t periodo;
//uint32_t amplitud;
 uint32_t umbral_max;
 uint32_t umbral_min;
 uint16_t dato_convertido;



int main(void)
{
  umbral_max=1000;//3.3v
  umbral_min=5; //aprox 0v



	InicializarTimer ();
	Periodo(INTERVALO);
	InicializarLed ();

	HabilitaInterrupcion();

	InicializarADC ();



	while(TRUE);

}

  void ISR_RIT(void)
  {
	  dato_convertido= ConversionAD ();

	   if (dato_convertido > umbral_max )
	    {

		   EncenderLed(LED_ROJO);
	    }
		   else
		   {
		   ApagarLed(LED_ROJO);

	       }
	   if (dato_convertido < umbral_min )
	   	    {

	   		   EncenderLed(LED_VERDE);
	   	    }
	   		   else
	   		   {
	   			ApagarLed(LED_VERDE);
	   	       }


	   LimpiarBandera();

    }

