/* 
 * File: ESP8266 ESP01
 * Author: Ivan D. Echeverry M.
 * Comments: Libreria para trabajar conjuntamente con el modulo ESP8266
 * Revision history: 12/04/2020
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ESP8266_SP01_UBIDOTS_H
#define	ESP8266_SP01_UBIDOTS_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <pic18f25j50.h>
#include "Config.h"
#include "UART1.h"
#include "UART2.h"
#include "CONFIG_CONNECT_ESP8266_SP01.h"

////////////////////////////////////////////////////////////////////////////////
/////////////////// VARIABLES PARA TRABAJAR CON ESP8266 ////////////////////////
///////////////////          CONTROL DE DATOS           ////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Lo que se va a capturar se toma desde lue=   value*: 0.0}
// Estados de la recepcion de variables
enum estados_ {cap_l, cap_u, cap_e, cap_co, esp_final};
//Estado inicial
char estado_rec = cap_l;

//Lo que se va a capturar se toma desde lue=   value": 0.0}
float valor_rx_server;                                                          //Captura valor de lavariables
char trama_rx_server[50];
char contador_trama_server = 0;
unsigned long demora_server = 0;                                                //Usado para alir de la lectura de datos

int reconect = 0;                                                               //Variable para reconectar con Ubidots.com

char Lee_Trama_Server();                                                        //Funcio que retorna 1 si hay dato sino 0

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/////////////////// VARIABLES PARA TRABAJAR CON ESP8266 ////////////////////////
///////////////////       VISUALIZACION DE DATOS        ////////////////////////
////////////////////////////////////////////////////////////////////////////////
char trama_server[150];                                                         //Enviar informacion al ESP8266
char trama_largo_server[20];                                                    //Para calcular el largo de la trama de las variables a enviar
char captu_server[30];                                                          //Para capturar informacion de la trama

int var_largo_server;                                                           //Largo de la trama en entero

unsigned long strlen_const(const char *const_pun);
void manda_esp8266_const(const char *info);
void manda_esp8266(char *info);


////////////////////////////////////////////////////////////////////////////////


#endif	/* XC_HEADER_TEMPLATE_H */

