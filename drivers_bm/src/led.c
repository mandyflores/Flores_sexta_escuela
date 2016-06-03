/* Copyright 2016, XXXXXXXXX  
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief Blinking Bare Metal driver led
 **
 **
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal LED Driver
 ** @{ */

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

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif
#include "led.h"
#include <stdint.h>












/*==================[macros and definitions]=================================*/
#define LED_PAQUETE 2
#define LEDOR       0
#define LEDOG       1
#define LEDOB       2
#define LED1        14
#define LED2        11
#define LED3        12
#define PORT_NUM_LED0    5
#define PORT_NUM_LED1    0
#define PORT_NUM_LED2Y3  1
#define OUT      1
//#define INPUT       0

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
 //uint8_t led;

/*==================[internal functions definition]==========================*/
 void InicializarLed (void)
 {
	 Chip_GPIO_Init(LPC_GPIO_PORT);
	 Chip_SCU_PinMux(LED_PAQUETE,LEDOR,MD_PUP,FUNC4);/*mapea P2 0 en GPIO5[0], LED0R y habilita el pull up	 */
	 Chip_SCU_PinMux(LED_PAQUETE,LEDOG,MD_PUP,FUNC4); /*mapea P2 1 en GPIO5[1], LED0G y habilita el pull up	 */
	 Chip_SCU_PinMux(LED_PAQUETE,LEDOB,MD_PUP,FUNC4); /* mapea P2 2 en GPIO5[2], LED0B y habilita el pull up	 */
	 Chip_SCU_PinMux(LED_PAQUETE,LED1,MD_PUP,FUNC0); /* remapea P2 10 en GPIO0[14], LED1 y habilita el pull up	 */
	 Chip_SCU_PinMux(LED_PAQUETE,LED2,MD_PUP,FUNC0); /*remapea P2 11 en GPIO1[11], LED2 y habilita el pull up */
	 Chip_SCU_PinMux(LED_PAQUETE,LED3,MD_PUP,FUNC0); /* remapea P2 12 en GPIO1[12], LED3 y habilita el pull up */
	 Chip_GPIO_SetDir(LPC_GPIO_PORT,  PORT_NUM_LED0, 1<<0|1<<1|1<<2, OUT);
	 Chip_GPIO_SetDir(LPC_GPIO_PORT, PORT_NUM_LED1,1<<14, OUT);
	 Chip_GPIO_SetDir(LPC_GPIO_PORT, PORT_NUM_LED2Y3,1<<11|1<<12,OUT);
 }
	 void EncenderLed(uint8_t led)
	 {
		switch(led)
		    {
		   case LED_ROJO:
			   Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,PORT_NUM_LED0,LEDOR);
		           break;
	       case LED_VERDE:
	    	   Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,PORT_NUM_LED0,LEDOG);
		         break;
	       case LED_AMARILLO:
	       	    Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,PORT_NUM_LED0,LEDOB);
	       		      break;
	       case LED_1:
	       	    	   Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,PORT_NUM_LED1,LED1);
	       		         break;
	       case LED_2:
	       	    	   Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,PORT_NUM_LED2Y3,LED2);
	       		         break;
	       case LED_3:
	       	    	   Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,PORT_NUM_LED2Y3,LED3);
	       		         break;
		    }

	 }
	 void ApagarLed (uint8_t led)
	 {
			switch(led)
			    {
			   case LED_ROJO:
				   Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PORT_NUM_LED0,LEDOR);
			           break;
		       case LED_VERDE:
		    	   Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PORT_NUM_LED0,LEDOG);
			         break;
		       case LED_AMARILLO:
		       	    Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PORT_NUM_LED0,LEDOB);
		       		      break;
		       case LED_1:
		       	    	   Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PORT_NUM_LED1,LED1);
		       		         break;
		       case LED_2:
		       	    	   Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PORT_NUM_LED2Y3,LED2);
		       		         break;
		       case LED_3:
		       	    	   Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PORT_NUM_LED2Y3,LED3);
		       		         break;
			    }

		 }
	 void ApagarTodos(void)
	 {
		 Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PORT_NUM_LED0,LEDOR);
		 Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PORT_NUM_LED0,LEDOG);
		 Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PORT_NUM_LED0,LEDOB);
		 Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PORT_NUM_LED1,LED1);
		 Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PORT_NUM_LED2Y3,LED2);
		 Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PORT_NUM_LED2Y3,LED3);
	 }









	 void InvertirLed (uint8_t led)
	 {
	 			switch(led)
	 			    {
	 			   case LED_ROJO:
	 				   Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,PORT_NUM_LED0,LEDOR);
	 			           break;
	 		       case LED_VERDE:
	 		    	  Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,PORT_NUM_LED0,LEDOG);
	 			         break;
	 		       case LED_AMARILLO:
	 		    	  Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,PORT_NUM_LED0,LEDOB);
	 		       		      break;
	 		       case LED_1:
	 		    	  Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,PORT_NUM_LED1,LED1);
	 		       		         break;
	 		       case LED_2:
	 		    	  Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,PORT_NUM_LED2Y3,LED2);
	 		       		         break;
	 		       case LED_3:
	 		    	  Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,PORT_NUM_LED2Y3,LED3);
	 		       		         break;
	 			    }

	 		 }
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





/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

