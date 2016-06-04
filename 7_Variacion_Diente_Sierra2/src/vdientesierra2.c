/*Actividad7: Diente de Sierra/Teclado
   Diseñe e implemente un firmware sobre la EDU-CIAA que genera una señal tipo diente
   de sierra de periodo 100ms y excursion de 0 a 3v de parámetros, amplitud y frec variables
   Tecla1: Aumente la amplitud de la señal
   Tecla2: Disminuye la amplitud de la señal
   Tecla3: Aumenta el periodo de la señal
   Tecla4: Disminuy el periodo de la señal
 */
#include "led.h"
#include "stdint.h"
#include "tecla.h"
#include "timer.h"
#include "vdientesierra2.h"
#include "dac.h"/*declaracion de driver del dac */
//#include "chip_lpc43xx.h"
//#include "core_cm4.h"//libreria define habilitacion de interrupcion

#define INTERVALO 1 //PERIODO DE TIMER 1ms
#define TRUE  1



#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif



//periodo=100;/*aqui se declaran las variables globlales */
//

float contador;
float paso;
uint32_t periodo;
uint32_t amplitud_max;/*ira variando el maxiMO*/

int main(void)

{

	uint8_t tecla;
	uint32_t topemax;
	uint32_t topemin;
	uint32_t periodo_min;
	uint32_t periodo_max;

	uint32_t retardo;

    periodo=100;/*100ms*/
    amplitud_max=310; /*equivalente a 1v */
    topemax=1000;/*equivalente a 3.22V*/
    topemin=93;/*equivalente a 0.3 v*/


    contador=0;
    periodo_min=20;/*20ms*/
    periodo_max=500;/*500 ms*/
    //amplitud=930;

	paso=(float)(amplitud_max/periodo);
	InicializarTimer ();
	Periodo(INTERVALO);
	InicializarLed ();

	HabilitaInterrupcion();
	InicializarTecla ();
	InicializarDAC ();


	for(;;){


		tecla=LeerTecla();


				switch(tecla)
				    {
	     		  case TECLA1:/*aumenta la amplitud de la señal si pulso Tecla1*/

					  if(amplitud_max<topemax)/* topemax=1000*/
					    {
						  amplitud_max=amplitud_max+10;/* incremento en 10 la amplitud */
						  paso=(float)(amplitud_max/periodo);
						  //contador_amplitud=0;
						  //marca_tecla12=1;
						  contador=0;

					    }

					   break;

				   case TECLA2:/* disminuyo la amplitud de la señal */
					   if(amplitud_max>topemin)/* topemin=93 */
					   	  {
					   		amplitud_max=amplitud_max-10;/* decremento en 10 la amplitud */
					   		paso=(float)(amplitud_max/periodo);
					   		//contador_amplitud=0;
					   		contador=0;
					   		//marca_tecla12=1;
					   		}
				        break;

			       case TECLA3:/*aumenta el periodo de la señal*/

			    	   if (periodo < periodo_max)/*500*1ms=500ms tope maximo*/
			    	   	    {
			    	   		 periodo=periodo+10;
			    	   		paso=(float)(amplitud_max/periodo);
			    	   		  contador=0;/*reseteo para que no se tilde la tecla*/

			    	   	    }

			    	   			 break;

			       case TECLA4:/*disminuye el periodo de la señal*/
			    	   if (periodo > periodo_min )//20*1ms=20ms tope minimo*/
			    	   			  {
			    	   			    periodo=periodo-10;
			    	   			 paso=(float)(amplitud_max/periodo);
			    	   			   contador=0;/*reseteo para que no se tilde la tecla*/

			    	   			    	 }

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

/*rutina de interrupcion*/

  void ISR_RIT(void)
  {


	  uint32_t valor;
	  	  contador = contador+paso; /* amplitud del escaloncito*/
	  	   if (contador>amplitud_max )
	  	    {
	  		   contador=0;
	  		   InvertirLed(LED_ROJO);/*al volverse el contador cero, se tiene un periodo a 100ms*/

	  	    }
	  	   valor=(uint32_t)contador;
	  	   ConversionDA (valor);/*   */

	  	   LimpiarBandera();

  }

