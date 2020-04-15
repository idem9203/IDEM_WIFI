/*
 * File:   main.c
 * Author: Ivan D Echeverry M
 *
 * Created on April 8, 2020, 10:41 PM
 */

#include "Config.h"
#include "UART1.h"
#include "UART2.h"
#include "ESP8266_SP01_UBIDOTS.h"
#include "Remapeo_Pines.h"
#include "CONFIG_CONNECT_ESP8266_SP01.h"

float iA1;
float A1, A2;

//VARIABLES PARA CAPTURAR LA TRAMA
char trama_rx2[30];
char procesa[30];

char dato_rx2;

void main(void) {
    
    Remap_PIN();
    
    //HABILITAR COMUNICACION SERIAL
    UART1_Init(115200);
//    UART2_Init(115200);
    
    __delay_ms(200);
    
//    UART2_printf("PROBANDO");
    
//    ESP8266_CONFIG_CONNECT("RED_APTO","2NB112100448");                          //Los parametros son SSID y Password, siempre entre comillas
    
    //DAMOS UN TIEMPO PARA QUE INCIE EL BUCLE DE OPERACION
    
    while(1)
    {
        
        lee_trama();
        
        strcpy(captu, strtok(trama_rx, ":"));                                   //Inicia captura de tokens desde el =
        strcpy(captu, strtok(0, ","));                                          //Captura hasta el /
        
        //Pasa la cadena a  numero
        valor_rx = atof(captu);
        
        UART1_printf(captu);
        
        UART1_printf("Esperando...\r\n");
        
        __delay_ms(500);
        //LIMPIA LAS TRAMAS
//        memset(trama_largo,20,0);
//        memset(trama,150,0);
//        
//        //ARMAMOS TRAMA DE VARIABLES
//        sprintf(trama,"{\"corriente\": %5.2f,\"inputdigital0\": %c,\"inputdigital1\": %c,\"analog1\": %5.2f,\"analog2\": %5.2f}\n",iA1,d0_string,d1_string,A1,A2);
//        
//        var_largo = strlen(trama)-1;                                            //Calcula el largo de la trama de variables
//        
//        sprintf(trama_largo,"%u\n\n",var_largo);                                //La pasa a cadena y le agrega dos fin de lineas
//        
//        ////////////////////////////////////////////////////////////////////////
//        ////////////////////// ENVIOS DE DATOS A UBIDOTS ///////////////////////
//        // El device en este caso es idem_v1-5                                //
//        // y el token BBFF-cdocy3PYE8Iu2wocqEY6pMuZAiAN6G                     //
//        // se debe colocar los de la inteface                                 //
//        ////////////////////////////////////////////////////////////////////////
//        
//        //MANDA EL LARGO DE LA TRAMA
//        manda_esp8266_const("POST /api/v1.6/devices/idem_v1-5/?token=BBFF-cdocy3PYE8Iu2wocqEY6pMuZAiAN6G HTTP/1.1\nHost: things.ubidots.com\nContent-Type: application/json\nContent-Length: ");
//        __delay_ms(700);       
//        
//        manda_esp8266(trama_largo);                                             //Manda el largo de la trama
//        __delay_ms(500);
//        
//        manda_esp8266(trama);                                                   //Manda la info con las variables
//        __delay_ms(500);
//        
//        //PREGUNTA POR VARIABLES DESEADAS (R1)
//        manda_esp8266_const("GET /api/v1.6/devices/idem_v1-5/r1-ac/values?page_size=1&token=BBFF-cdocy3PYE8Iu2wocqEY6pMuZAiAN6G HTTP/1.1\nHost: things.ubidots.com\n\n");
//        
//        lee_trama();                                                            //Lee la respuesta
//        
//        //Captura el valor de la variables        value": 0.0}
//        strcpy(captu, strtok(trama_rx, ":"));                                   //Inicia captura de tokens desde el :
//        strcpy(captu, strtok(0, ","));                                          //Captura hasta la coma ,
//        
//        //Pasa la cadena a  numero
//        valor_rx = atof(captu);
//        if (valor_rx == 1.0) RELE1 = 1; else RELE1 = 0;                         //Aplica la salida al led
//        __delay_ms(200);
//        
//        
//        //PREGUNTA POR VARIABLES DESEADAS (R2)
//        manda_esp8266_const("GET /api/v1.6/devices/idem_v1-5/r2-ac/values?page_size=1&token=BBFF-cdocy3PYE8Iu2wocqEY6pMuZAiAN6G HTTP/1.1\nHost: things.ubidots.com\n\n");
//        
//        lee_trama();                                                            //Lee la respuesta
//        
//        //Captura el valor de la variables        value": 0.0}
//        strcpy(captu, strtok(trama_rx, ":"));                                   //Inicia captura de tokens desde el =
//        strcpy(captu, strtok(0, ","));                                          //Captura hasta el /
//        
//        //Pasa la cadena a  numero
//        valor_rx = atof(captu);
//        if (valor_rx == 1.0) RELE2 = 1; else RELE2 = 0;                         //Aplica la salida al led
//        __delay_ms(200);
//        
//        reconect++;
//        if (reconect >= 7)
//        {
//            reconect = 0;
//            //se conecta a ubidots
//            printf1("AT+CIPSTART=4,\"TCP\",\"things.ubidots.com\",80\r\n");
//            __delay_ms(300); 
//        }
    }
    return;
}
