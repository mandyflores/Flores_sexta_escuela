
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

#define INTERVALO 300 //PERIODO DE TIMER...300ms
#define TRUE  1
#define VREF 3   //3V
#define ESCALONES_REF  930  //1023.....> 3.3V
#define DECIMALES_PRECISION  10
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
 uint16_t dato;
 //uint16_t dato,dato1,resto1,resto2,dato2,dato3,resto3;
 float tension;
 uint16_t entero;
 uint16_t decimas;
 //char tens;


int main(void)
{
  //umbral_max=1000;//3.3v
  //umbral_min=5; //aprox 0v

    InicializarUSART();
	InicializarADC ();
	InicializarTimer ();
	Periodo(INTERVALO);
	InicializarLed ();

	HabilitaInterrupcion();
	//InicializarUSART();


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

	              }//end del switch
	        }//end del while


}

  void ISR_RIT(void)
  {
	  dato= ConversionAD ();//leo el valor convertido

	  //convierto el valor leido por el conversor en tension dentro de una variable float

	  tension=(float)(dato*VREF)/ESCALONES_REF;//obtengo el valor equivalente de tension de "dato"
	  //se realiza una conversion de float a uint.. para quedarme primero con la parte entera

	  entero=(uint16_t)tension; //convierto una variable float a uint16

	  //printf("  \n %d ",entero);

	  TransmisionUSART(entero+'0');//se convierte en char y se envia

	  //Se escribe el punto que separa el entero de las decimas
	  TransmisionUSART('.');

       //convierto las decimas en char y envio

	  tension=(tension-(uint16_t)tension)*DECIMALES_PRECISION;
	  decimas=(uint16_t)tension;
	  TransmisionUSART(decimas+'0');//se convierte en char y se envia



	  TransmisionUSART('\r\n');

	   LimpiarBandera();

    }

