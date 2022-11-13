/*! @file : uard0.c
 * @author  manuel berdugo 
 * @version 1.0.0
 * @date    11/11/2022
 * @brief   Driver para 
 * @details
 *
*/
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "K32L2B31A.h"

#include "lpuart0.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/

/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Local vars
 ******************************************************************************/
static uint8_t dato_lpuart0=0;
static uint8_t flag_nuevo_dato_lpuart0=0;

/*******************************************************************************
 * Private Source Code
 ******************************************************************************/
/* LPUART0_IRQn interrupt handler */
void LPUART0_SERIAL_RX_TX_IRQHANDLER(void) {
  uint32_t intStatus;

  /* captura banderas de estado para el puerto LPUART0
   * esta lectura tambien borra las banderas de estado*/
  intStatus = LPUART_GetStatusFlags(LPUART0_PERIPHERAL);

  /* Verifica que la IRQ es por llegada de nuevo dato por Rx*/
	if ((kLPUART_RxDataRegFullFlag) & intStatus) {
		dato_lpuart0 = LPUART_ReadByte(LPUART0);
		flag_nuevo_dato_lpuart0=1;
	}

  /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
     Store immediate overlapping exception return operation might vector to incorrect interrupt. */
  #if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
  #endif
}

/*******************************************************************************
 * Public Source Code
 ******************************************************************************/
uint8_t leer_dato(void) {
	return (dato_lpuart0);
}

uint8_t leer_bandera_nuevo_dato(void) {
	return (flag_nuevo_dato_lpuart0);
}

void escribir_bandera_nuevo_dato(uint8_t nuevo_valor) {
	flag_nuevo_dato_lpuart0 = nuevo_valor;
}
