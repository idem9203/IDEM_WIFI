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
#include "Lee_trama_uC.h"

float iA1;
float A1, A2;
int digital_Input_0, digital_Input_1, rele_1, rele_2;

char mensaje[10];
char *token;
char dig0[10];
char gid1[10];
char ana1[10];
char nal2[10];
char tcm1[10];
char rel1[10];
char ler2[10];

void main(void) {
    
    Remap_PIN();
    
    //HABILITAR COMUNICACION SERIAL
//    UART1_Init(9600);
    UART2_Init(9600);
    
    __delay_ms(200);
    
//    ESP8266_CONFIG_CONNECT("RED_APTO","2NB112100448");                          //Los parametros son SSID y Password, siempre entre comillas
    
    //DAMOS UN TIEMPO PARA QUE INCIE EL BUCLE DE OPERACION
    
    while(1)
    {
        
//        Lee_Trama_Server();
//        
//        token = strtok(trama_rx_server, "/");
//        strcpy(mensaje, token);
//        
//        token = strtok(NULL, "/");
//        digital_Input_0 = atoi (token);
//        sprintf(dig0, "%i", digital_Input_0);
//        
//        token = strtok(NULL, "/");
//        digital_Input_1 = atoi (token);
//        sprintf(gid1, "%i", digital_Input_1);
//        
//        token = strtok(NULL, "/");
//        A1 = atof (token);
//        sprintf(ana1, "%5.2f", A1);
//        
//        token = strtok(NULL, "/");
//        A2 = atof (token);
//        sprintf(nal2, "%5.2f", A2);
//        
//        token = strtok(NULL, "/");
//        iA1 = atof (token);
//        sprintf(tcm1, "%5.2f", iA1);
//        
//        token = strtok(NULL, "/");
//        rele_1 = atoi (token);
//        sprintf(rel1, "%i", rele_1);
//        
//        token = strtok(NULL, "/");
//        rele_2 = atoi (token);
//        sprintf(ler2, "%i", rele_2);
//        
//        UART1_printf(mensaje);
//        UART1_printf("/");
//        UART1_printf(dig0);
//        UART1_printf("/");
//        UART1_printf(gid1);
//        UART1_printf("/");
//        UART1_printf(ana1);
//        UART1_printf("/");
//        UART1_printf(nal2);
//        UART1_printf("/");
//        UART1_printf(tcm1);
//        UART1_printf("/");
//        UART1_printf(rel1);
//        UART1_printf("/");
//        UART1_printf(ler2);
//        UART1_printf("\r\n");
        
        Lee_Trama_uC();
        
        token = strtok(trama_rx_uC, "/");
        strcpy(mensaje, token);
        
        token = strtok(NULL, "/");
        digital_Input_0 = atoi (token);
        sprintf(dig0, "%i", digital_Input_0);
              
        token = strtok(NULL, "/");
        digital_Input_1 = atoi (token);
        sprintf(gid1, "%i", digital_Input_1);
               
        token = strtok(NULL, "/");
        A1 = atof (token);
        sprintf(ana1, "%5.2f", A1);
               
        token = strtok(NULL, "/");
        A2 = atof (token);
        sprintf(nal2, "%5.2f", A2);
               
        token = strtok(NULL, "/");
        iA1 = atof (token);
        sprintf(tcm1, "%5.2f", iA1);
               
        token = strtok(NULL, "/");
        rele_1 = atoi (token);
        sprintf(rel1, "%i", rele_1);
               
        token = strtok(NULL, "/");
        rele_2 = atoi (token);
        sprintf(ler2, "%i", rele_2);
               
        UART2_printf(mensaje);
        UART2_printf("/");
        UART2_printf(dig0);
        UART2_printf("/");
        UART2_printf(gid1);
        UART2_printf("/");
        UART2_printf(ana1);
        UART2_printf("/");
        UART2_printf(nal2);
        UART2_printf("/");
        UART2_printf(tcm1);
        UART2_printf("/");
        UART2_printf(rel1);
        UART2_printf("/");
        UART2_printf(ler2);
        UART2_printf("/");
        UART2_printf("\r\n");
        
        //Pasa la cadena a  numero
//        valor_rx_server = atof(captu_server);
        
//        UART1_printf("Esperando...\r\n");
        UART2_printf("Probando UART2\r\n");
        
        __delay_ms(500);
        //LIMPIA LAS TRAMAS
//        memset(trama_largo_server,20,0);
//        memset(trama_server,150,0);
//        
//        //ARMAMOS TRAMA DE VARIABLES
//        sprintf(trama_server,"{\"corriente\": %5.2f,\"inputdigital0\": %i,\"inputdigital1\": %i,\"analog1\": %5.2f,\"analog2\": %5.2f}\n",iA1,digital_Input_0,digital_Input_1,A1,A2);
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
