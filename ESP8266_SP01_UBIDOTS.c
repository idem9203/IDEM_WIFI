#include "ESP8266_SP01_UBIDOTS.h"

////////////////////////////////////////////////////////////////////////////////
/////////////////// VARIABLES PARA TRABAJAR CON ESP8266 ////////////////////////
///////////////////          CONTROL DE DATOS           ////////////////////////
////////////////////////////////////////////////////////////////////////////////

char Lee_Trama_Server()                                                         //Funcio que retorna 1 si hay dato sino 0
{
    char dato_rx_server;

    //limpa todas las variables
    memset(trama_rx_server, 50, 0);
    demora_server = 0;
    contador_trama_server = 0;
    estado_rec = cap_l;

    //borra errores de recepcion
    PIR1bits.RCIF = 0;
    RCSTAbits.CREN = 0; //
    RCSTAbits.CREN = 1; //

    while (demora_server <= 766667)
    {
        demora_server++;
        switch (estado_rec)
        {
            case cap_l:
                if (PIR1bits.RCIF == 1)                                         //Si hay un dat recibido
                {
                    dato_rx_server = UART1_Read();                              //lee el dato
                    trama_rx_server[contador_trama_server] = dato_rx_server;
                    if (dato_rx_server != 'l') contador_trama_server = 0;       //no fue el dato que me interesa
                    else
                    {
                        contador_trama_server++;                                //incrementa contador para proximo dato
                        estado_rec = cap_u;                                     //pasa al estado de capturar la u
                    }
                    PIR1bits.RCIF = 0;                                          //limpia la bandera de recepcion par esperar otro dato
                }
            break;
        
            case cap_u:
                if (PIR1bits.RCIF == 1)                                         //si hay un dat recibido
                {
                    dato_rx_server = UART1_Read();                              //lee el dato
                    trama_rx_server[contador_trama_server] = dato_rx_server;
                    if (dato_rx_server != 'u')
                    {
                        contador_trama_server = 0;
                        estado_rec = cap_l;                                     //regresa al estado inical
                    }
                    else
                    {
                        contador_trama_server++;                                //incrementa contador para proximo dato
                        estado_rec = cap_e;                                     //pasa al estado de capturar la u
                    }
                    PIR1bits.RCIF = 0;                                          //limpia la bandera de recepcion par esperar otro dato
                }
            break;

            case cap_e:
                if (PIR1bits.RCIF == 1)                                         //si hay un dat recibido
                {
                    dato_rx_server = UART1_Read();                              //lee el dato
                    trama_rx_server[contador_trama_server] = dato_rx_server;
                    if (dato_rx_server != 'e')
                    {
                    contador_trama_server = 0;
                    estado_rec = cap_l;                                         //regresa al estado inical
                    }
                    else
                    {
                        contador_trama_server++;                                //incrementa contador para proximo dato
                        estado_rec = cap_co;                                    //pasa al estado de capturar la u
                    }
                    PIR1bits.RCIF = 0;                                          //limpia la bandera de recepcion par esperar otro dato
                }
            break;

            case cap_co:
                if (PIR1bits.RCIF == 1)                                         //si hay un dat recibido
                {
                    dato_rx_server = UART1_Read();                              //lee el dato
                    trama_rx_server[contador_trama_server] = dato_rx_server;
                    if (dato_rx_server != '\"')
                    {
                        contador_trama_server = 0;
                        estado_rec = cap_l;                                     //regresa al estado inical
                    }
                    else
                    {
                        contador_trama_server++;                                //incrementa contador para proximo dato
                        estado_rec = esp_final;                                 //pasa al estado de capturar la u
                    }
                    PIR1bits.RCIF = 0;                                          //limpia la bandera de recepcion par esperar otro dato
                }
            break;

            case esp_final:
                if (PIR1bits.RCIF == 1)                                         //si hay un dat recibido
                {
                    dato_rx_server = UART1_Read();                              //lee el dato
                    trama_rx_server[contador_trama_server] = dato_rx_server;
                    contador_trama_server++;
                    if (dato_rx_server == ',')   return(1);                     //sale del procedimiento
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
    sprintf(captu_server, "%1u", largo);                                        //Es el largo de la trama +2 por enter y fin de linea
    UART1_printf(captu_server);                                                 //Envia el largo de la trama
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
    sprintf(captu_server, "%1u", largo);                                        //Es el largo de la trama +2 por enter y fin de linea
    UART1_printf(captu_server);                                                 //Envia el largo de la trama
    UART1_printf("\r\n");
    __delay_ms(100);                                                            //retardo antes de enviar la trama
    UART1_printf(info);                                                         //manda envia solo constantes
    
}
////////////////////////////////////////////////////////////////////////////////
