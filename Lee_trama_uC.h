/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LEE_TRAMA_UC_H
#define	LEE_TRAMA_UC_H

#include <xc.h> // include processor files - each processor file is guarded.
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <pic18f26j50.h>
#include "Config.h"
#include "UART1.h"
#include "UART2.h"  

////////////////////////////////////////////////////////////////////////////////
/////////////////// VARIABLES PARA TRABAJAR CON ESP8266 ////////////////////////
///////////////////          CONTROL DE DATOS           ////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Lo que se va a capturar se toma desde lue=   value*: 0.0}
// Estados de la recepcion de variables
enum estados_uC {cap_l_uC, cap_u_uC, cap_e_uC, cap_co_uC, esp_final_uC};
//Estado inicial
char estado_rec_uC = cap_l_uC;

//Lo que se va a capturar se toma desde lue=   value": 0.0}
float valor_rx_uC;                                                              //Captura valor de lavariables
char trama_rx_uC[50];
char contador_trama_uC = 0;
unsigned long demora_uC = 0;                                                    //Usado para alir de la lectura de datos


char Lee_Trama_uC();                                                            //Funcio que retorna 1 si hay dato sino 0

////////////////////////////////////////////////////////////////////////////////


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

