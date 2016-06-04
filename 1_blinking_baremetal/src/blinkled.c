/*Actividad2: Blinkin_baremetal....Blinking con driver
 * enciende,toglea(invierte),apaga a los leds de la placa
 */


#include "led.h"
#include "stdint.h"
#include "blinkled.h"
//#include "chip_lpc43xx.h"
//#include "core_cm4.h"//libreria define habilitacion de interrupcion

//#define TRUE 1

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif


int main(void)
{
	uint8_t led;//declaro variables
	uint32_t retardo;

	led=ROJO;

	InicializarLed ();

	/*ROJO 0
     VERDE 1
     AMARILLO 2
     RGB_ROJO 3
     RGB_VERDE 4
     RGB_AMARILLO 5
     */

	for(led=ROJO;led<6;led++)
	   {
		EncenderLed(led);
		for(retardo=0;retardo<10000000;retardo++);
		 ApagarLed(led);
		 for(retardo=0;retardo<10000000;retardo++);
		InvertirLed(led);
		for(retardo=0;retardo<10000000;retardo++);
	   }
	ApagarTodos();
}

