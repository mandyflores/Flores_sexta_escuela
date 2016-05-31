#include "interrup.h"
#include "led.h"
#include "stdint.h"
#include "timer.h"
//#include "chip_lpc43xx.h"
//#include "core_cm4.h"//libreria define habilitacion de interrupcion

#define INTERVALO 100 //PERIODO DE TIMER
#define TRUE  1

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif

uint8_t led;//declaro variables

int main(void)
{
	 led=ROJO;


	InicializarTimer ();

	Periodo(INTERVALO);
	HabilitaInterrupcion();
	//inicializo led
	InicializarLed ();
	while(TRUE);

}

  void ISR_RIT(void)
  {

	  //invertir led
	  InvertirLed(led);
	  if (led++ > RGB_AMARILLO )
	  {
		  led=ROJO;
	  }
	   LimpiarBandera();
	 //cambiar el led
	 //deshabilitar la interrupcion
	  //limpiar el flag
  }

