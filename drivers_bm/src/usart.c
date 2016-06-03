#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif
#include "led.h"
#include"adc.h"
#include "usart.h"

#include "stdint.h"
#include "chip.h" /* carga biblioteca de LPCOPEN */
//#include "chip_lpc43xx.h"
//#include "core_cm4.h"//libreria define habilitacion de interrupcion
#define PUERTO_TX     7
#define PIN_TX        1
//#define MODO_TX      MD_PDN //modo pulldown
//#define FUNCION_TX   Func6

#define PUERTO_RX     7
#define PIN_RX        2
//#define MODO_RX      MD_PLN|MD_EZI //modo pulldown
//#define FUNCION_RX   Func6

void InicializarUSART(void)
 {
	//configura la unidad de sistema de control


	Chip_SCU_PinMux(PUERTO_TX,PIN_TX, MD_PDN,FUNC6); /*	UART2 RXD*/
	Chip_SCU_PinMux(PUERTO_RX,PIN_RX, MD_PLN|MD_EZI,FUNC6); /*	UART2 RXD*/

	//Configuracion del periferico

	Chip_UART_Init(LPC_USART2);//direccion base de la direccion de memoria del periferico
	Chip_UART_SetBaud(LPC_USART2,115200);//baude rate
	Chip_UART_SetupFIFOS(LPC_USART2, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0);//envia datos,habilita bandera
   //fuerza el trigger creo..recibe un solo caracter y lo pasa
	Chip_UART_TXEnable(LPC_USART2);
	}





void TransmisionUSART (uint8_t dato)
  {

	Chip_UART_SendByte(LPC_USART2,dato);//transmite
  }

uint8_t RecepcionUSART ()
  {
	uint8_t dato;
	dato=Chip_UART_ReadByte(LPC_USART2); //recibe
	return dato;

	//while (datos==0)

  }




