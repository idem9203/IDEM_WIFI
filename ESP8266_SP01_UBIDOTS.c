#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h> // include processor files - each processor file is guarded.
#include <pic18f25j50.h>
#include "Config.h"
#include "UART1.h"
#include "UART2.h"
#include "ESP8266_SP01_UBIDOTS.h"
#include "CONFIG_CONNECT_ESP8266_SP01.h"

////////////////////////////////////////////////////////////////////////////////
/////////////////// VARIABLES PARA TRABAJAR CON ESP8266 ////////////////////////
///////////////////          CONTROL DE DATOS           ////////////////////////
////////////////////////////////////////////////////////////////////////////////

char lee_trama()                                                                //Funcio que retorna 1 si hay dato sino 0
{
    char dato_rx;

    //limpa todas las variables
    memset(trama_rx, 50, 0);
    demora = 0;
    contador_trama = 0;
    estado_rec = cap_l;

    //borra errores de recepcion
    PIR1bits.RCIF = 0;
    RCSTAbits.CREN = 0; //
    RCSTAbits.CREN = 1; //

    while (demora <= 766667)
    {
        demora++;
        switch (estado_rec)
        {
            case cap_l:
                if (PIR1bits.RCIF == 1)                                         //Si hay un dat recibido
                {
                    dato_rx = UART1_Read();                                     //lee el dato
                    trama_rx[contador_trama] = dato_rx;
                    if (dato_rx != 'l') contador_trama = 0;                     //no fue el dato que me interesa
                    else
                    {
                        contador_trama++;                                       //incrementa contador para proximo dato
                        estado_rec = cap_u;                                     //pasa al estado de capturar la u
                    }
                    PIR1bits.RCIF = 0;                                          //limpia la bandera de recepcion par esperar otro dato
                }
            break;
        
            case cap_u:
                if (PIR1bits.RCIF == 1)                                         //si hay un dat recibido
                {
                    dato_rx = UART1_Read();                                     //lee el dato
                    trama_rx[contador_trama] = dato_rx;
                    if (dato_rx != 'u')
                    {
                        contador_trama = 0;
                        estado_rec = cap_l;                                     //regresa al estado inical
                    }
                    else
                    {
                        contador_trama++;                                       //incrementa contador para proximo dato
                        estado_rec = cap_e;                                     //pasa al estado de capturar la u
                    }
                    PIR1bits.RCIF = 0;                                          //limpia la bandera de recepcion par esperar otro dato
                }
            break;

            case cap_e:
                if (PIR1bits.RCIF == 1)                                         //si hay un dat recibido
                {
                    dato_rx = UART1_Read();                                     //lee el dato
                    trama_rx[contador_trama] = dato_rx;
                    if (dato_rx != 'e')
                    {
                    contador_trama = 0;
                    estado_rec = cap_l;                                         //regresa al estado inical
                    }
                    else
                    {
                        contador_trama++;                                       //incrementa contador para proximo dato
                        estado_rec = cap_co;                                    //pasa al estado de capturar la u
                    }
                    PIR1bits.RCIF = 0;                                          //limpia la bandera de recepcion par esperar otro dato
                }
            break;

            case cap_co:
                if (PIR1bits.RCIF == 1)                                         //si hay un dat recibido
                {
                    dato_rx = UART1_Read();                                     //lee el dato
                    trama_rx[contador_trama] = dato_rx;
                    if (dato_rx != '\"')
                    {
                        contador_trama = 0;
                        estado_rec = cap_l;                                     //regresa al estado inical
                    }
                    else
                    {
                        contador_trama++;                                       //incrementa contador para proximo dato
                        estado_rec = esp_final;                                 //pasa al estado de capturar la u
                    }
                    PIR1bits.RCIF = 0;                                          //limpia la bandera de recepcion par esperar otro dato
                }
            break;

            case esp_final:
                if (PIR1bits.RCIF == 1)                                         //si hay un dat recibido
                {
                    dato_rx = UART1_Read();                                     //lee el dato
                    trama_rx[contador_trama] = dato_rx;
                    contador_trama++;
                    if (dato_rx == ',')   return(1);                            //sale del procedimiento
                    PIR1bits.RCIF = 0;                                          //limpia la bandera de recepcion
                }
            break;
       
        }//fin del switch
    }//fin del while demora
    return(0); 
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/////////////////// VARIABLES PARA TRABAJAR CON ESP8266 ////////////////////////
///////////////////       VISUALIZACION DE DATOS        ////////////////////////
////////////////////////////////////////////////////////////////////////////////


//FUNCION PARA DETECTAR EL LARGO DE UNA CADENA CONSTANTE
unsigned long strlen_const(const char *const_pun)
{
 unsigned int cuen_const=0;

 while (*const_pun++!=0) cuen_const++;
 return (cuen_const);

}

void manda_esp8266_const(const char *info)
{
    unsigned int largo;
    UART1_printf("AT+CIPSEND=");                                                //Envia solo constantes
    UART1_printf("4");                                                          //Manda el socket el cual se conecto
    UART1_printf(",");
    largo = strlen_const(info);                                                 //Calcula el largo de la cadena a enviar
    sprintf(captu, "%1u", largo);                                               //Es el largo de la trama +2 por enter y fin de linea
    UART1_printf(captu);                                                        //Envia el largo de la trama
    UART1_printf("\r\n");
    __delay_ms(100);                                                            //retardo antes de enviar la trama
    UART1_printf(info);                                                         //manda envia solo constantes
    
}

void manda_esp8266(char *info)
{
    unsigned int largo;
    UART1_printf("AT+CIPSEND=");                                                //Envia solo constantes
    UART1_printf("4");                                                          //Manda el socket el cual se conecto
    UART1_printf(",");
    largo = strlen(info);                                                       //Calcula el largo de la cadena a enviar
    sprintf(captu, "%1u", largo);                                               //Es el largo de la trama +2 por enter y fin de linea
    UART1_printf(captu);                                                        //Envia el largo de la trama
    UART1_printf("\r\n");
    __delay_ms(100);                                                            //retardo antes de enviar la trama
    UART1_printf(info);                                                         //manda envia solo constantes
    
}
////////////////////////////////////////////////////////////////////////////////
