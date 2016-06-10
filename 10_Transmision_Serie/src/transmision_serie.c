
/*Actividad 10: Diseñe e implemente un Firmware sobre la EDU-CIAA que permita adquirir una
 * señal analógica de excursión entre 0 y 3,3V presente en el CH1. El sistema debe enviar
 * por el puerto serie una cadena de caracteres con el valor en decimal del dato convertido */


/*==============================================================================*/

#include "led.h"
#include "stdint.h"
#include "timer.h"
#include "adc.h"
#include "usart.h"
//#include "chip_lpc43xx.h"
//#include "core_cm4.h"//libreria define habilitacion de interrupcion

#define INTERVALO 300 //PERIODO DE TIMER
#define TRUE  1

/*===========================================================================*/

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif
/*============================================================================*/

 uint8_t dato_convertido;
 uint16_t dato,dato1,resto1,resto2,dato2,dato3,resto3;



int main(void)
{
  //umbral_max=1000;//3.3v
  //umbral_min=5; //aprox 0v


	InicializarADC ();
	InicializarTimer ();
	Periodo(INTERVALO);
	InicializarLed ();

	HabilitaInterrupcion();
	InicializarUSART();


	while (1)
	        {
		    dato_convertido = RecepcionUSART();

	         switch (dato_convertido){
	         case 'r':
	              /*Toggle Red Led*/
	        	 InvertirLed(LED_2);

	            break;
	         case 'v':
	              /*Toggle Green Led*/
	        	 InvertirLed(LED_3);

	            break;
	         case 'a':
	              /*Toggle Yellow Led*/
	        	 InvertirLed(LED_1);

	            break;
	         default:
	            dato_convertido= 0;
	              }
	        }


}

  void ISR_RIT(void)
  {
	  dato= ConversionAD ();//leo el valor convertido
      //se convierte el dato leido del adc a 4 bytes separados
	  //luego a char y se lo envía por la uart

	  dato1=dato/1000;//primer byte a transmitir
	  TransmisionUSART(dato1+'0');//se convierte en char y se envia
      resto1=dato%1000;

      dato2=resto1/100;//segundo byte a transmitir
      TransmisionUSART(dato2+'0');
      resto2=resto1%100;

      dato3=resto2/10; //tercer byte a transmitir
	  TransmisionUSART(dato3+'0');

	  resto3=resto2%10;//cuarto byte a transmitir
	  TransmisionUSART(resto3+'0');


	  TransmisionUSART('\n\r');

	   LimpiarBandera();

    }

