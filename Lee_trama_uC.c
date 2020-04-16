#include "Lee_trama_uC.h"


char Lee_Trama_uC()
{
    char dato_rx_uC;

    //limpa todas las variables
    memset(trama_rx_uC, 50, 0);
    demora_uC = 0;
    contador_trama_uC = 0;
    estado_rec_uC = cap_l_uC;

    //borra errores de recepcion
    PIR3bits.RC2IF = 0;
    RCSTA2bits.CREN2 = 0; //
    RCSTA2bits.CREN2 = 1; //

    while (demora_uC <= 766667)
    {
        demora_uC++;
        switch (estado_rec_uC)
        {
            case cap_l_uC:
                if (PIR3bits.RC2IF == 1)                                         //Si hay un dat recibido
                {
                    dato_rx_uC = UART2_Read();                              //lee el dato
                    trama_rx_uC[contador_trama_uC] = dato_rx_uC;
                    if (dato_rx_uC != 'l') contador_trama_uC = 0;       //no fue el dato que me interesa
                    else
                    {
                        contador_trama_uC++;                                //incrementa contador para proximo dato
                        estado_rec_uC = cap_u_uC;                                     //pasa al estado de capturar la u
                    }
                    PIR3bits.RC2IF = 0;                                          //limpia la bandera de recepcion par esperar otro dato
                }
            break;
        
            case cap_u_uC:
                if (PIR3bits.RC2IF == 1)                                         //si hay un dat recibido
                {
                    dato_rx_uC = UART2_Read();                              //lee el dato
                    trama_rx_uC[contador_trama_uC] = dato_rx_uC;
                    if (dato_rx_uC != 'u')
                    {
                        contador_trama_uC = 0;
                        estado_rec_uC = cap_l_uC;                                     //regresa al estado inical
                    }
                    else
                    {
                        contador_trama_uC++;                                //incrementa contador para proximo dato
                        estado_rec_uC = cap_e_uC;                                     //pasa al estado de capturar la u
                    }
                    PIR3bits.RC2IF = 0;                                          //limpia la bandera de recepcion par esperar otro dato
                }
            break;

            case cap_e_uC:
                if (PIR3bits.RC2IF == 1)                                         //si hay un dat recibido
                {
                    dato_rx_uC = UART2_Read();                              //lee el dato
                    trama_rx_uC[contador_trama_uC] = dato_rx_uC;
                    if (dato_rx_uC != 'e')
                    {
                    contador_trama_uC = 0;
                    estado_rec_uC = cap_l_uC;                                         //regresa al estado inical
                    }
                    else
                    {
                        contador_trama_uC++;                                //incrementa contador para proximo dato
                        estado_rec_uC = cap_co_uC;                                    //pasa al estado de capturar la u
                    }
                    PIR3bits.RC2IF = 0;                                          //limpia la bandera de recepcion par esperar otro dato
                }
            break;

            case cap_co_uC:
                if (PIR3bits.RC2IF == 1)                                         //si hay un dat recibido
                {
                    dato_rx_uC = UART2_Read();                              //lee el dato
                    trama_rx_uC[contador_trama_uC] = dato_rx_uC;
                    if (dato_rx_uC != '\"')
                    {
                        contador_trama_uC = 0;
                        estado_rec_uC = cap_l_uC;                                     //regresa al estado inical
                    }
                    else
                    {
                        contador_trama_uC++;                                //incrementa contador para proximo dato
                        estado_rec_uC = esp_final_uC;                                 //pasa al estado de capturar la u
                    }
                    PIR3bits.RC2IF = 0;                                          //limpia la bandera de recepcion par esperar otro dato
                }
            break;

            case esp_final_uC:
                if (PIR3bits.RC2IF == 1)                                         //si hay un dat recibido
                {
                    dato_rx_uC = UART2_Read();                              //lee el dato
                    trama_rx_uC[contador_trama_uC] = dato_rx_uC;
                    contador_trama_uC++;
                    if (dato_rx_uC == ',')   return(1);                     //sale del procedimiento
                    PIR3bits.RC2IF = 0;                                          //limpia la bandera de recepcion
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
unsigned long strlen_const_uC(const char *const_pun)
{
 unsigned int cuen_const=0;

 while (*const_pun++!=0) cuen_const++;
 return (cuen_const);

}

void manda_uC_const(const char *info_uC)
{
    unsigned int largo_uC;
    UART2_printf("AT+CIPSEND=");                                                //Envia solo constantes
    UART2_printf("4");                                                          //Manda el socket el cual se conecto
    UART2_printf(",");
    largo_uC = strlen_const_uC(info_uC);                                                 //Calcula el largo de la cadena a enviar
    sprintf(captu_uC, "%1u", largo_uC);                                        //Es el largo de la trama +2 por enter y fin de linea
    UART2_printf(captu_uC);                                                 //Envia el largo de la trama
    UART2_printf("\r\n");
    __delay_ms(100);                                                            //retardo antes de enviar la trama
    UART2_printf(info_uC);                                                         //manda envia solo constantes
    
}

void manda_uC(char *info_uC)
{
    unsigned int largo_uC;
    UART2_printf("AT+CIPSEND=");                                                //Envia solo constantes
    UART2_printf("4");                                                          //Manda el socket el cual se conecto
    UART2_printf(",");
    largo_uC = strlen(info_uC);                                                       //Calcula el largo de la cadena a enviar
    sprintf(captu_uC, "%1u", largo_uC);                                        //Es el largo de la trama +2 por enter y fin de linea
    UART2_printf(captu_uC);                                                 //Envia el largo de la trama
    UART2_printf("\r\n");
    __delay_ms(100);                                                            //retardo antes de enviar la trama
    UART2_printf(info_uC);                                                         //manda envia solo constantes
    
}
////////////////////////////////////////////////////////////////////////////////

