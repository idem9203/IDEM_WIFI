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
int digitalInput_1, digital_Input_2, rele_1, rele_2;

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
        
        Lee_Trama_Server();
        
        strcpy(captu_server, strtok(trama_rx_server, ":"));                     //Inicia captura de tokens desde el :
        strcpy(captu_server, strtok(0, ","));                                   //Captura hasta la coma ,
        
        //Pasa la cadena a  numero
        valor_rx_server = atof(captu_server);
        
        UART1_printf(captu_server);
        
        UART1_printf("Esperando...\r\n");
        
        __delay_ms(500);
        //LIMPIA LAS TRAMAS
//        memset(trama_largo_server,20,0);
//        memset(trama_server,150,0);
//        
//        //ARMAMOS TRAMA DE VARIABLES
//        sprintf(trama_server,"{\"corriente\": %5.2f,\"inputdigital0\": %c,\"inputdigital1\": %c,\"analog1\": %5.2f,\"analog2\": %5.2f}\n",iA1,d0_string,d1_string,A1,A2);
//        
//        var_largo_server = strlen(trama_server)-1;                              //Calcula el largo de la trama de variables
//        
//        sprintf(trama_largo_server,"%u\n\n",var_largo_server);                  //La pasa a cadena y le agrega dos fin de lineas
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
//        manda_esp8266(trama_largo_server);                                      //Manda el largo de la trama
//        __delay_ms(500);
//        
//        manda_esp8266(trama_server);                                            //Manda la info con las variables
//        __delay_ms(500);
//        
//        //PREGUNTA POR VARIABLES DESEADAS (R1)
//        manda_esp8266_const("GET /api/v1.6/devices/idem_v1-5/r1-ac/values?page_size=1&token=BBFF-cdocy3PYE8Iu2wocqEY6pMuZAiAN6G HTTP/1.1\nHost: things.ubidots.com\n\n");
//        
//        Lee_Trama_Server();                                                     //Lee la respuesta
//        
//        //Captura el valor de la variables        value": 0.0}
//        strcpy(captu_server, strtok(trama_rx_server, ":"));                     //Inicia captura de tokens desde el :
//        strcpy(captu_server, strtok(0, ","));                                   //Captura hasta la coma ,
//        
//        //Pasa la cadena a  numero
//        valor_rx_server = atof(captu_server);
//        if (valor_rx_server == 1.0) rele_1 = 1; else rele_1 = 0;                  //Aplica la salida al led
//        __delay_ms(200);
//        
//        
//        //PREGUNTA POR VARIABLES DESEADAS (R2)
//        manda_esp8266_const("GET /api/v1.6/devices/idem_v1-5/r2-ac/values?page_size=1&token=BBFF-cdocy3PYE8Iu2wocqEY6pMuZAiAN6G HTTP/1.1\nHost: things.ubidots.com\n\n");
//        
//        Lee_Trama_Server();                                                     //Lee la respuesta
//        
//        //Captura el valor de la variables        value": 0.0}
//        strcpy(captu_server, strtok(trama_rx_server, ":"));                     //Inicia captura de tokens desde el =
//        strcpy(captu_server, strtok(0, ","));                                   //Captura hasta el /
//        
//        //Pasa la cadena a  numero
//        valor_rx_server = atof(captu_server);
//        if (valor_rx_server == 1.0) rele_2 = 1; else rele_2 = 0;                  //Aplica la salida al led
//        __delay_ms(200);
//        
//        reconect++;
//        if (reconect >= 7)
//        {
//            reconect = 0;
//            //se conecta a ubidots
//            UART1_printf("AT+CIPSTART=4,\"TCP\",\"things.ubidots.com\",80\r\n");
//            __delay_ms(300); 
//        }
    }
    return;
}
