/*Diseñe e implemente un Firmware sobre la EDU-CIAA que permita adquirir una señal analógica
 * de excursión entre 0 y 3.3v,a una frecuencia de muestreo de 100Hz.
 * El sistema tendrá los siguientes requerimientos:
 * Teclas 1 y 2:Ampllificar/atenuar la señal x 0.8V y 1.1V
 * Teclas 3 y 4: Modificar el offset de la señal sumándole: +100mV,-100mV
 * Transmitir a la computadora, cada un segundo los siguientes valores: Ganancia y Offset
 * configurados; Máximo y Mínimo medido sobre la última ventana.
 * -Generar una señal de calibración cuadrada de 10 Hz, 1 Vpp y 1.5 de offset
 * Adicionalmente el Led Verde, deberá alternar su estado entre una ventana y otra
 * de transmision para indicar que el sistema se encuentra adquiriendo
 */

#include "led.h"
#include "stdint.h"
#include "timer.h"
//#include "adquisicion.h"
#include "adc.h"
#include "usart.h"
#include "tecla.h"
//#include "chip_lpc43xx.h"
//#include "core_cm4.h"//libreria define habilitacion de interrupcion

#define INTERVALO 10//PERIODO DE TIMER 10ms porque f=100 Hz
#define TRUE      1
#define TOPE_MIN   62//equivalente a 0.2V
#define TOPE_MAX   930// equivalente a 3V
#define VREF 3   //3V
#define ESCALONES_REF  930  //1023.....> 3.3V
#define DECIMALES_PRECISION  10
//#define  CUENTA_MAX 775

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


 uint16_t dato1,dato2;
 uint16_t dato;


 uint8_t contador;
 float amplitud_max;/*ira variando el maximo*/
 float amplitud_min;/*ira variando el minimo*/
 uint32_t valor;

 uint32_t periodo_calibracion;
 uint32_t mitad_periodo;

 uint8_t contador_periodo;//cuenta los periodos de la onda cuadrada


 float ganancia;
 float offset;
 float amplitud;
 float tension;
 uint16_t entero;
 uint16_t decimas;


int main(void)

{
	uint8_t tecla;
	uint32_t retardo;

    contador_periodo=0;
	periodo_calibracion=10;//100ms

	ganancia=1;//

	amplitud_max=775;//2.5V
	amplitud_min=465;//1.5V
	contador=0;
    amplitud=amplitud_max-amplitud_min;//775-465=310

   mitad_periodo=periodo_calibracion/2;
   offset=amplitud_max-amplitud;


	//Generacion de señal cuadrada

	///
	//paso=(float)(amplitud_max/periodo);
		InicializarTimer ();
		Periodo(INTERVALO);
		InicializarLed ();

		HabilitaInterrupcion();
		//InicializarTecla ();
		InicializarDAC ();
		InicializarADC ();
		InicializarUSART();

		for(;;){


				tecla=LeerTecla();
				//amplitud=amplitud_max-amplitud_min;


						switch(tecla)
						    {
			     		  case TECLA1:/*aumenta la ganancia 1.1, su  equivalente adc 341*/


			     			   ganancia=ganancia*1.1;
			     			   amplitud_max=amplitud_max*ganancia;
			     			   amplitud_min=amplitud_min*ganancia;
			     			   amplitud=amplitud_max-amplitud_min;
			     			   offset=amplitud_max-amplitud;

			     			   contador=0;
							   break;

						   case TECLA2:/* atenuo la señal 0.8 */
							   ganancia=ganancia*0.8;

							   amplitud_max=amplitud_max*ganancia;
							   amplitud_min=amplitud_min*ganancia;
							   amplitud=amplitud_max-amplitud_min;
							   offset=amplitud_max-amplitud;

							   contador=0;

						        break;

					       case TECLA3:/*aumento el offset 100mv*/

					    	   //31 es el equivalente a 0.1V=100mV
					    	   if (amplitud_max<TOPE_MAX)
					    	      {
					    	   amplitud_max=amplitud_max+31;
					    	   amplitud_min=amplitud_min+31;
					    	   amplitud=amplitud_max-amplitud_min;
					    	   offset=offset+31;
					    	    contador=0;
					    	      }

					    	   	 break;

					       case TECLA4:/*disminuyo offset 100mv=0.1v*/
					    	   //31 es el equivalente a 0.1V=100mV
					    	   if (amplitud_min>TOPE_MIN)//equivalente a 0.2V
					    	      {
					    	      amplitud_max=amplitud_max-31;
					    	      amplitud_min=amplitud_min-31;
					    	      amplitud=amplitud_max-amplitud_min;
					    	      offset=offset-31;
					    	      contador=0;
					    	      }

					    	   break;
						    }

						if (tecla!=0){  //para el antirebote
							//retardo

							for(retardo=0;retardo<10000000;retardo++);
							/*ApagarTodos();*/

						          }
				        }


		while (TRUE);
}



		void ISR_RIT(void)
		  {

			   contador++;
			  //generación de la onda cuadrada

			  if (contador<= mitad_periodo)
			    {
				   valor=(uint32_t)amplitud_max;

			    }

			   if ((contador> mitad_periodo) &&(contador<periodo_calibracion))
			      {
				  valor=(uint32_t)amplitud_min;
				   //contador=0;
				   //InvertirLed(LED_ROJO);/*al volverse el contador cero, se tiene un periodo a 100ms*/
			       }
			      else
			      {
			    	  contador=0;
			    	  //led rojo
			    	  InvertirLed(LED_2);//al volverse el contador cero, se tiene un periodo
			    	  contador_periodo++;
			       }

			   //valor=(uint32_t)contador;

			   ConversionDA (valor);/*   */
			   dato= ConversionAD ();

               if (contador_periodo==10)//cada 10T de la onda cuadrada se tiene 1seg....1T=100ms
                  {
            	     //Transmite el valor maximo
			       dato1=(uint16_t)amplitud_max;

            	   tension=(float)(dato1*VREF)/ESCALONES_REF;//obtengo el valor equivalente de tension de "dato"
            	   //se realiza una conversion de float a uint.. para quedarme primero con la parte entera

            	   	 entero=(uint16_t)tension; //convierto una variable float a uint16

            	   	 TransmisionUSART(entero+'0');//se convierte en char y se envia

            	   	  //Se escribe el punto que separa el entero de las decimas
            	   	  TransmisionUSART('.');

            	      //convierto las decimas en char y envio
            	   	  tension=(tension-(uint16_t)tension)*DECIMALES_PRECISION;
            	   	  decimas=(uint16_t)tension;
            	   	  TransmisionUSART(decimas+'0');//se convierte en char y se envia
            	   	  TransmisionUSART('\n\r');

            	   	  //Transmite el valor minimo

            	   	  dato2=(uint16_t)amplitud_min;
            	   	  tension=(float)(dato2*VREF)/ESCALONES_REF;//obtengo el valor equivalente de tension de "dato"
            	   	  //se realiza una conversion de float a uint.. para quedarme primero con la parte entera

            	   	   entero=(uint16_t)tension; //convierto una variable float a uint16

            	   	   TransmisionUSART(entero+'0');//se convierte en char y se envia

            	   	   //Se escribe el punto que separa el entero de las decimas
            	   	    TransmisionUSART('.');

            	   	   //convierto las decimas en char y envio

            	   	     tension=(tension-(uint16_t)tension)*DECIMALES_PRECISION;
            	   	     decimas=(uint16_t)tension;
            	   	     TransmisionUSART(decimas+'0');//se convierte en char y se envia
            	   	     TransmisionUSART('\n\r');

                       }
                  else
                      {
            	   contador_periodo=0;
                   /*Toglea el led verde*/
               	    InvertirLed(LED_3);

                     }


			   LimpiarBandera();

		  }











