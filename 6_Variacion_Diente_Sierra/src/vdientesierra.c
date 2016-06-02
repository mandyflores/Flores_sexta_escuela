
#include "led.h"
#include "stdint.h"
#include "tecla.h"
#include "timer.h"
#include "vdientesierra.h"
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
uint8_t marca_tecla12;
uint8_t marca_tecla34;
float contador;
float paso;
float contador_amplitud; /*variable para variar amplitud */
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

	//float amplitud;

	contador_amplitud=0; /*inicializo variable */
    periodo=100;
    amplitud_max=93; /*equivalente a 0.3v */
    topemax=1000;
    topemin=93;


    contador=0;
    //contador_max=periodo;/*100ms...es el periodo del diente de sierra..para inicializar*/
    periodo_min=20;
    periodo_max=500;
    //amplitud=930;


    marca_tecla12=0;
    marca_tecla34=0;

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
						  contador_amplitud=0;
						  marca_tecla12=1;

					    }

					   break;

				   case TECLA2:/* disminuyo la amplitud de la señal */
					   if(amplitud_max>topemin)/* topemin=93 */
					   	  {
					   		amplitud_max=amplitud_max-10;/* decremento en 10 la amplitud */
					   		paso=(float)(amplitud_max/periodo);
					   		contador_amplitud=0;
					   		marca_tecla12=1;
					   		}
				        break;

			       case TECLA3:/*aumenta el periodo de la señal*/

			    	   if (periodo < periodo_max)/*500*1ms=500ms tope maximo*/
			    	   	    {
			    	   		 periodo=periodo+10;
			    	   		paso=(float)(amplitud_max/periodo);
			    	   		  contador=0;/*reseteo para que no se tilde la tecla*/
			    	   		  marca_tecla34=1;
			    	   	    }

			    	   			 break;

			       case TECLA4:/*disminuye el periodo de la señal*/
			    	   if (periodo > periodo_min )//20*1ms=20ms tope minimo*/
			    	   			  {
			    	   			    periodo=periodo-10;
			    	   			 paso=(float)(amplitud_max/periodo);
			    	   			   contador=0;/*reseteo para que no se tilde la tecla*/
			    	   			   marca_tecla34=1;
			    	   			    	 }

			    	   			    break;

				    }
				if (tecla!=0){  //para el antirebote
					//retardo

					for(retardo=0;retardo<10000000;retardo++);
					/*ApagarTodos();*/

				          }
		        }
   }




	//while(TRUE);



  void ISR_RIT(void)
  {
	  uint32_t valor;

	  if (marca_tecla12==1)
	    {
	 	  contador_amplitud = contador_amplitud + paso; /* */
	 	   if (contador_amplitud>amplitud_max )
	 	    {
	 		   contador_amplitud=0;
	 		   InvertirLed(LED_ROJO);/*al volverse el contador cero, se tiene un periodo a 100ms*/
	 	    }
	 	   valor=(uint32_t)contador_amplitud;
	 	   ConversionDA (valor);/*   */
	    }

	  if (marca_tecla34==1)
	     {
		  contador = contador + paso; /*9.3v*/
		  	   if (contador>amplitud_max )
		  	    {
		  		   contador=0;
		  		   InvertirLed(LED_ROJO);/*al volverse el contador cero, se tiene un periodo a 100ms*/
		  	    }
		  	   valor=(uint32_t)contador;
		  	   ConversionDA (valor);/*   */

	     }

	 	   LimpiarBandera();

  }

