/*Actividad 9: Variación de umbral. Diseñe e implemente un Firmware sobre la EDU-CIAA que
 permita adquirir una señal analógica de excursión entre el 0 y 3.3V, presente en el pin CH1
 del conector P1 con una frecuencia de muestreo de 100Hz (empleando el RIT por interrupciones).
 El sistema debe analizar la excursión de la señal. Encendiendo el led rojo se indica que la
 señal sobrepasa un umbral máximo. Encendiendo el led verde se indica que el mínimo
 de la señal se encuentra por debajo de un umbral mínimo. Los umbrales podran ajustarse
 empleando el teclado.
 Tecla1: aumenta el valor del umbral
 Tecla2: disminuye el valor del umbral */


#include "led.h"
#include "stdint.h"
#include "timer.h"
#include "tecla.h"
#include "var_umbral.h"
#include "adc.h"
//#include "chip_lpc43xx.h"
//#include "core_cm4.h"//libreria define habilitacion de interrupcion
/*=============================================================================*/

#define INTERVALO 10 //PERIODO DE TIMER 10ms porque f=100 Hz
#define TRUE  1

/*=======================================================================================*/

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif


 uint32_t umbral_max;
 uint32_t umbral_min;
 uint16_t dato_convertido;



int main(void)
{


  uint8_t tecla;
  uint32_t topemax;
  uint32_t topemin;
  uint32_t amplitud;

 uint32_t retardo;


  topemax=1500;/*equivalente a 4.8V*/
  topemin=33;/*equivalente a 0.106 v.......(33*3V)/930 = 0.106V*/
  amplitud=1023; /*equivalente a 3.3 V*/

  umbral_max=1000;//3.22v
  umbral_min=5; //aprox 0.016v




	InicializarTimer ();
	Periodo(INTERVALO);
	InicializarLed ();

	HabilitaInterrupcion();
	InicializarTecla ();
	InicializarADC ();


	//while(TRUE);

	for(;;){


			tecla=LeerTecla();


					switch(tecla)
					    {
		     		  case TECLA1:/*aumenta el valor del umbral*/

						  if(umbral_max<topemax)/* topemax=1500*/
						      {
							  umbral_max=umbral_max+31; /* incremento en 31 el umbral es decir o,1V */
							  umbral_min=umbral_max-amplitud; /*aumento el umbral minimo */

						      }

						   break;

					   case TECLA2:/* disminuye el valor del umbral */
						   if(umbral_min>topemin)/* topemin=33 */
						   	  {
						   		umbral_min=umbral_min-31;/* disminuyo el umbral minimo */
						   		umbral_max=umbral_min+amplitud;/*disminuyo el umbral maximo*/
						   	  }

					        break;

				       case TECLA3:


				    	   			 break;

				       case TECLA4:


				    	   			  break;

					    }
					if (tecla!=0) //para el antirebote
						//retardo
					     {

						for(retardo=0;retardo<10000000;retardo++);
						/*ApagarTodos();*/

					          }
			        }
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

