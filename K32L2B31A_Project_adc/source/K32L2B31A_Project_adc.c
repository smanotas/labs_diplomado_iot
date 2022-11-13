/*
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    K32L2B31A_Project_adc.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "K32L2B31A.h"


/// fls ////////////////////
#include "fsl_debug_console.h"
#include "fsl_adc16.h"


//// personales ///////////////

#include "lpuart0.h"


/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 *
 *
 *
 */

#define ADC16_BASE          ADC0
#define ADC16_CHANNEL_GROUP 0U
#define ADC16_USER_CHANNEL  3U

#define BOARD_LED_GPIO1     BOARD_LED_GREEN_GPIO
#define BOARD_LED_GPIO_PIN1 BOARD_LED_GREEN_GPIO_PIN

#define BOARD_LED_GPIO2     BOARD_LED_RED_GPIO
#define BOARD_LED_GPIO_PIN2 BOARD_LED_RED_GPIO_PIN


volatile uint32_t g_systickCounter;


///////////////////// funciones ////////////////////////
///////////////////////////////////////////////////////

void led_encendidos();

void SysTick_Handler(void)
{
    if (g_systickCounter != 0U)
    {
        g_systickCounter--;
    }
}

void SysTick_DelayTicks(uint32_t n)
{
    g_systickCounter = n;
    while (g_systickCounter != 0U)
    {
    }
}

////////////////// definition /////////////////////////////7

typedef struct _iot_nodo_data{
	uint32_t preamble;
	uint16_t frame_sync;
	//------------------------------------
	uint32_t end_divice_ID;
	uint16_t payload;
	uint16_t auth;
	//------------------------------------
	uint16_t FCS;
	//------------------------------------
} iot_nodo_data_t;

/*******************************************************************************
 * Private Source Code
 ******************************************************************************/
void ec25_print_data_raw(uint8_t *data_ptr, uint32_t data_size) {
	for (uint32_t i = 0; i < data_size; i++) {
		PRINTF("%c", *(data_ptr + i));
	}
}


int main(void) {

uint8_t	aux_recepcion = "H";

iot_nodo_data_t nuevo_formato;

nuevo_formato.preamble = 60;
nuevo_formato.frame_sync = 30;
nuevo_formato.end_divice_ID = 56;
nuevo_formato.payload = 89;
nuevo_formato.auth = 123;
nuevo_formato.FCS = 83;



    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_InitLEDsPins();


#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();


#endif



    if (SysTick_Config(SystemCoreClock / 1000U))
    {
        while (1)
        {
        }
    }


/*
     int adc_dato = 0;
     float vout ;
     float valor_muestra = 0;
     float lux_valor;



    ADC16_SetChannelConfig(ADC16_BASE, ADC16_CHANNEL_GROUP, &ADC0_channelsConfig[0]);
    while (0U == (kADC16_ChannelConversionDoneFlag &
                          ADC16_GetChannelStatusFlags(ADC16_BASE, ADC16_CHANNEL_GROUP)))
            {
            }*/


    while(1) {
    	if(leer_bandera_nuevo_dato()!=0){
    	escribir_bandera_nuevo_dato(0);

    	aux_recepcion = leer_dato();
    	PRINTF("%c",aux_recepcion);

    	if(aux_recepcion == 83){
    		ec25_print_data_raw((uint8_t *)(&nuevo_formato),sizeof(nuevo_formato));
    		PRINTF("\n\r");
    	}

    	if (aux_recepcion == 71){
    	  GPIO_PortToggle(BOARD_LED_GPIO1, 1u << BOARD_LED_GPIO_PIN1);
    	}

    	if (aux_recepcion == 82){
    	  GPIO_PortToggle(BOARD_LED_GPIO2, 1u << BOARD_LED_GPIO_PIN2);
    	}



       }




/*
        ADC16_SetChannelConfig(ADC16_BASE, ADC16_CHANNEL_GROUP, &ADC0_channelsConfig[0]);
            while (0U == (kADC16_ChannelConversionDoneFlag &
                                  ADC16_GetChannelStatusFlags(ADC16_BASE, ADC16_CHANNEL_GROUP)))
                    {
                    }

            adc_dato = ADC16_GetChannelConversionValue(ADC16_BASE,ADC16_CHANNEL_GROUP);
            vout = (adc_dato * 0.00080566406f);
            valor_muestra = (10000.0f * (3.3f - vout))/vout;
            lux_valor = (adc_dato /1.48231511254f);


            PRINTF("dato adc  %d \n\r",adc_dato);
            PRINTF("voltaje %f\n\r",vout);
            PRINTF("corriente %f\n\r",valor_muestra);
            PRINTF("lux : %f\n\r",lux_valor);
          SysTick_DelayTicks(2000U);*/



        __asm volatile ("nop");
        //PRINTF("%u\n\r ",i);
    }
    return 0 ;
}


void led_encendidos(){


}
