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
#include "tecla.h"
#include "stdint.h""












/*==================[macros and definitions]=================================*/
#define TECLA_PAQUETE 1
#define TEC1_PIN       0
#define TEC2_PIN       1
#define TEC3_PIN       2
#define TEC4_PIN        6
#define TEC1_BIT      4
#define TEC2_BIT      8
#define TEC3_BIT      9
#define TEC4_BIT      9
//
//#define LED3        12
//#define PORT_NUM_LED0    5
#define PORT_NUM_TEC12Y3    0 /*Numero de puerto de la tecla 1, tecla 2, tecla3*/
#define PORT_NUM_TEC4  1      /*Numero de puerto de la tecla 4 */

//#define OUT      1
 #define INPUT       0


/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
 //uint8_t led;

/*==================[internal functions definition]==========================*/
 void InicializarTecla(void)
 {
	 Chip_GPIO_Init(LPC_GPIO_PORT);
	 //Chip_SCU_PinMux(TECLA_PAQUETE,TEC1_PIN,MD_PUP,FUNC0);/*mapea P2 0 en GPIO5[0], LED0R y habilita el pull up	 */
	 //Chip_SCU_PinMux(TECLA_PAQUETE,TEC2_PIN,MD_PUP,FUNC0); /*mapea P2 1 en GPIO5[1], LED0G y habilita el pull up	 */
	 //Chip_SCU_PinMux(TECLA_PAQUETE,TEC3_PIN,MD_PUP,FUNC0); /* mapea P2 2 en GPIO5[2], LED0B y habilita el pull up	 */
	 //Chip_SCU_PinMux(TECLA_PAQUETE,TEC4_PIN,MD_PUP,FUNC0); /* remapea P2 10 en GPIO0[14], LED1 y habilita el pull up	 */

	 Chip_SCU_PinMux(TECLA_PAQUETE,TEC1_PIN,MD_PUP|MD_EZI|MD_ZI,FUNC0);/* mapea P1 0 en GPIO 0[4], SW1 */
	 Chip_SCU_PinMux(TECLA_PAQUETE,TEC2_PIN,MD_PUP|MD_EZI|MD_ZI,FUNC0);/* mapea P1 1 en GPIO 0[8], SW2 */
	 Chip_SCU_PinMux(TECLA_PAQUETE,TEC3_PIN,MD_PUP|MD_EZI|MD_ZI,FUNC0);/* mapea P1 2 en GPIO 0[9], SW3 */
	 Chip_SCU_PinMux(TECLA_PAQUETE,TEC4_PIN,MD_PUP|MD_EZI|MD_ZI,FUNC0);/* mapea P1 6 en GPIO 1[9], SW4 */

	 Chip_GPIO_SetDir(LPC_GPIO_PORT,  PORT_NUM_TEC12Y3, 1<<4|1<<8|1<<9, INPUT);/* bit*/
	 Chip_GPIO_SetDir(LPC_GPIO_PORT, PORT_NUM_TEC4,1<<9, INPUT);

 }

 uint8_t LeerTecla(void)
  {

  /* testeo de tecla pulsada */

	  if (Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,PORT_NUM_TEC12Y3, TEC1_BIT )==0)//ver argumento en LPCOpen Platform
	  {

		  return TECLA1;


	  }

	  if (Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,PORT_NUM_TEC12Y3, TEC2_BIT )==0)//ver argumento en LPCOpen Platform
	  	  {

		  return TECLA2;
	  	  }
	  if (Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,PORT_NUM_TEC12Y3,  TEC3_BIT )==0)//ver argumento en LPCOpen Platform
	  	  {

		  return TECLA3;
	  	  }
	  if (Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,PORT_NUM_TEC4,  TEC4_BIT )==0)//ver argumento en LPCOpen Platform
	  	  {

		  return TECLA4;
	  	  }
       return 0;
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

