
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

//float contador;
//float paso;
//uint32_t periodo;
//uint32_t amplitud;
 //uint32_t umbral_max;
 //uint32_t umbral_min;
 uint16_t dato,dato_convertido;
 uint16_t dato1,resto1,dato2,resto2,daro3,resto3;


 uint8_t marca_tecla12;
 uint8_t marca_tecla34;
 float contador;
 float paso;
 float contador_amplitud; /*variable para variar amplitud */
 uint32_t periodo;
 float amplitud_max;/*ira variando el maxiMO*/
 float amplitud_min;

 uint32_t periodo_calibracion;
 uint32_t mitad_periodo;

 uint16_t dato_convertido;
 float resultado;
 float valor;

 float ganancia;
 float offset;
 float amplitud;


int main(void)

{
	uint8_t tecla;

	periodo_calibracion=10;//100ms
	ganancia=1;
	 	amplitud_max=775;
	 	amplitud_min=465;
	 	contador=0;
	 	amplitud=amplitud_max-amplitud_min;//775-465=310

	 	mitad_periodo=periodo_calibracion/2;
	 	offset=amplitud_min;


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
				amplitud=amplitud_max-amplitud_min;


						switch(tecla)
						    {
			     		  case TECLA1:/*aumenta la ganancia*/
			     			   resultado= valor*1.1;
			     			    if(amplitud=310)
			     			    {
			     			   amplitud_max=(resultado*930/3);
			     			    }

			     			    if (amplitud=0)
			     			    {
			     			    	amplitud_min=(resultado*930/3);
			     			    	offset=(resultado*930/3);
			     			    }


			     			   ganancia=ganancia*1.1;//reveer
			     			   contador=0;

							   break;

						   case TECLA2:/* atenuo la señal 0.8 */
							   resultado= valor*0.8;

							   if(amplitud=310)
							   	{
							   amplitud_max=(resultado*930/3);
							   offset=amplitud_max-amplitud;
							   	 }

							   if (amplitud=0)
							   	   {
								   amplitud_min=(resultado*930/3);
							   	   offset=(resultado*930/3);
							   			    }

			     			   ganancia=ganancia*0.8;//reveer
							   contador=0;

						        break;

					       case TECLA3:/*aumento el offset 100mv*/
					    	   resultado= valor + 0.1;
					    	   if(amplitud=310)
					    	   	  {
					    	   		amplitud_max=(resultado*930/3);
					    	   		offset=amplitud_max-amplitud
					    	   			   }

					    	   	if (amplitud=0)
					    	   			{
					    	   			    amplitud_min=(resultado*930/3);
					    	   			    offset=(resultado*930/3);
					    	   			    }
					    	    contador=0;

					    	   	 break;

					       case TECLA4:/*disminuyo offset 100mv=0.1v*/
					    	   resultado= valor - 0.1;
					    	   if(amplitud=310)
					    	   		{
					    	   		amplitud_max=(resultado*930/3);
					    	   		offset=amplitud_max-amplitud
					    	   					    }

					    	   	if (amplitud=0)
					    	   			{
					    	   			amplitud_min=(resultado*930/3);
					    	   			 offset=(resultado*930/3);
					    	   			 }
					    	   contador=0;

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




/////
	//InicializarADC ();
	//InicializarTimer ();
	//(INTERVALO);
	//InicializarLed ();

	//HabilitaInterrupcion();
	//InicializarUSART();

		//////
		void ISR_RIT(void)
		  {

			  //contador = contador+paso; /*9.3v*/
			  contador++;
			   //if (contador<amplitud_max )
			  if (contador<= mitad_periodo)
			    {
				   valor=amplitud_max;

			    }

			   if ((contador> mitad_periodo) &&(contador<periodo_calibracion))
			      {
				  valor=amplitud_min;
				   //contador=0;
				   //InvertirLed(LED_ROJO);/*al volverse el contador cero, se tiene un periodo a 100ms*/
			       }
			      else
			      {
			    	  contador=0;
			    	  InvertirLed(LED_ROJO);//al volverse el contador cero, se tiene un periodo
			       }

			   //valor=(uint32_t)contador;

			   ConversionDA (valor);/*   */
			   dato= ConversionAD ();


			   dato1=dato/1000;//primer dato a transmitir
				  TransmisionUSART(dato1+'0');
			      resto1=dato%1000;
			      dato2=resto1/100;//segundo dato a transmitir
			      TransmisionUSART(dato2+'0');
			      resto2=resto1%100;
			      dato3=resto2/10;
				  TransmisionUSART(dato3+'0');
				  resto3=resto2%10;
				  TransmisionUSART(resto3+'0');

				  TransmisionUSART(resto+'0');

				  //Convertir dato a unidades de mil, centenas, decenas y unidades


				  //transmitir cada uno de esos datos
				  //unidades=5;
			      //TransmisionUSART(unidades+'0');

			      TransmisionUSART('\n\r');






			   LimpiarBandera();

		  }











