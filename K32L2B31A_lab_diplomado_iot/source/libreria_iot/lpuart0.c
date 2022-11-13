/*! @file : lpuart0.c
 * @author  Sebastian Manotas
 * @version 1.0.0
 * @date    12/11/2022
 * @brief   Driver para 
 * @details
 *
*/
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lpuart0.h"

#include "peripherals.h"
#include "K32L2B31A.h"
#include "pin_mux.h"
#include "board.h"
#include "clock_config.h"

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
uint8_t dato_lpuart0;
uint8_t flag_nuevo_dato_lpuart0 = 0;


/*******************************************************************************
 * Private Source Code
 ******************************************************************************/
/* LPUART0_IRQn interrupt handler */
void LPUART0_SERIAL_RX_TX_IRQHANDLER(void) {
  uint32_t intStatus;
  /* Reading all interrupt flags of status registers */
  intStatus = LPUART_GetStatusFlags(LPUART0_PERIPHERAL);

  /* Flags can be cleared by reading the status register and reading/writing data registers.
    See the reference manual for details of each flag.
    The LPUART_ClearStatusFlags() function can be also used for clearing of flags in case the content of data/FIFO regsiter is not used.
    For example:
        status_t status;
        status = LPUART_ClearStatusFlags(LPUART0_PERIPHERAL, intStatus);
  */

  /* Place your code here */
  if ((kLPUART_RxDataRegFullFlag)&intStatus){
	  dato_lpuart0 = LPUART_ReadByte(LPUART0);
	  flag_nuevo_dato_lpuart0 = 1;
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
uint8_t leer_dato(void){
	 return (dato_lpuart0);
 }

uint8_t leer_bandera_dato_nuevo(void){
	 return (flag_nuevo_dato_lpuart0);
 }

 void escribir_bandera_dato_nuevo(uint8_t nuevo_valor){
 	 flag_nuevo_dato_lpuart0 = nuevo_valor;
  }
