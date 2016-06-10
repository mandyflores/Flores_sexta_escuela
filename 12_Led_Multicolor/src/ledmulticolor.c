/* Actividad 6: Diseñe un driver (timer.c y timer.h), que le permita
  * a la aplicación acceder a los temporizadores del micro.

  * - Programe una aplicación que emplee los drivers led.c ; teclas.c; timer.c
  *con el siguiente comportamiento:

  * -Al energizar la placa debe parpadear alternadamente los leds rojo y verde, 250 ms
  *   encendido cada led.
  * - Al presionar la TECLA 1, se debe variar el color del led RGB, en al menos 16
  *    colores diferentes.

  * - La temporización de los leds se debe realizar a través del RIT Timer
  *  (ver temporización e interrupciones)*/

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "ledmulticolor.h"       /* <= own header */
#include "colores.h"
#include "tecla.h"
#include "led.h"
#include "timer.h"

/*==================[macros and definitions]=================================*/
#define TRUE  1
#define INTERVALO 1 //PERIODO DE TIMER 1ms-cada ms se produce la interrupcion
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */
uint8_t tecla;
uint8_t led;
uint32_t contador; //variable para variar periodo
uint32_t contador_rojo,contador_verde,contador_amarillo;
uint32_t combinacion;//combinacion de gama de colores


int main(void)
   {
   /* perform the needed initialization here */
    uint32_t retardo;
    contador=0; /*inicializo variable */
    combinacion=0;


	InicializarTimer();
	Periodo(INTERVALO);
	HabilitaInterrupcion();
	InicializarTecla ();

	InicializarLed ( );


	for(;;){

	tecla=LeerTecla();
	        switch(tecla)
	          {
	           case TECLA1:
				      if(combinacion<19)
				       {
					    combinacion++;//combinacion de gama de colores
					    contador=0;

					     break;
				        }
				    if (combinacion>=19)
				         {
					     combinacion=0;
					     contador=0;

					     break;
				          }

	           case TECLA2:
	        	       break;

	          case TECLA3:
	        	      break;

	          case TECLA4:
	        	      break;

	             }


			if (tecla!=0)  //para el antirebote
				//retardo
			 {

				for(retardo=0;retardo<10000000;retardo++);

			   }

           }

   }

void ISR_RIT(void)

   {
      contador++; /*incremento contador que me define el periodo de los leds rojo y verde que no son RGB*/

          if(contador==250)//contador=250ms
             {
        	  ApagarLed(LED_2);    //led rojo
		       EncenderLed(LED_3);//led verde

             }

         if(contador==500)   //contador=500ms...la interrupcion se produce cada ms
             {
           	 contador=0;
        	 ApagarLed(LED_3); //led verde
        	 EncenderLed(LED_2);//led rojo

             }
    //seleccion de gama de colores

       multicolor(combinacion);

        if (contador==0)

       {
       EncenderLed(LED_ROJO);
       EncenderLed(LED_VERDE);
       EncenderLed(LED_AMARILLO);
       }

         if (contador==contador_rojo)
                {
                  contador_rojo=0;
             	 ApagarLed(LED_ROJO);


                }
         if (contador==contador_verde)
            {
        	   contador_verde=0;
        	   ApagarLed(LED_VERDE);


              }
         if (contador==contador_amarillo)
              {
               contador_amarillo=0;
               ApagarLed(LED_AMARILLO);
              }

	   LimpiarBandera();
   }



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

