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
float valor_rx;                                                                 //Captura valor de lavariables
char trama_rx[50];
char contador_trama = 0;
unsigned long demora = 0;                                                       //Usado para alir de la lectura de datos

int reconect = 0;                                                               //Variable para reconectar con Ubidots.com

char lee_trama();                                                               //Funcio que retorna 1 si hay dato sino 0

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/////////////////// VARIABLES PARA TRABAJAR CON ESP8266 ////////////////////////
///////////////////       VISUALIZACION DE DATOS        ////////////////////////
////////////////////////////////////////////////////////////////////////////////
char trama[150];                                                                //Enviar informacion al ESP8266
char trama_largo[20];                                                           //Para calcular el largo de la trama de las variables a enviar
char captu[30];                                                                 //Para capturar informacion de la trama

int var_largo;                                                                  //Largo de la trama en entero
char d0_string, d1_string;

unsigned long strlen_const(const char *const_pun);
void manda_esp8266_const(const char *info);
void manda_esp8266(char *info);


////////////////////////////////////////////////////////////////////////////////


#endif	/* XC_HEADER_TEMPLATE_H */

