#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h> // include processor files - each processor file is guarded.
#include <pic18f25j50.h>
#include "Config.h"
#include "CONFIG_CONNECT_ESP8266_SP01.h"
#include "UART1.h"

void ESP8266_CONFIG_CONNECT(char SSID[20], char password[30]) 
{
    
    UART1_printf("ATE0\r\n");                                                   //SIN ECO
    __delay_ms(200);

    UART1_printf("AT+CWMODE=1\r\n");                                            //se CONECTA A RED EXISTENTE
    __delay_ms(200);

    //Para Colocar Una Ip Al modulo
    UART1_printf("AT+CWDHCP=1,0\r\n");                                          //Deshabilita DHCP  para Ip manual
    __delay_ms(300);
    //Configura IP IP,Gateway,Mascara   en forma Manual

    UART1_printf("AT+CIPSTA=\"192.168.1.117\",\"192.168.1.254\",\"255.255.255.0\"\r\n");
    __delay_ms(300);


//    UART1_printf("AT+CWJAP=\"RED_APTO\",\"2NB112100448\"\r\n");                 //se conecta a una red WIFI
    UART1_printf("AT+CWJAP=\"");                                                //se conecta a una red WIFI 
    UART1_printf(SSID);                                                          //si no funciona utilizaar la de arriba
    UART1_printf("\",\"");
    UART1_printf(password);
    UART1_printf("\"\r\n");

    __delay_ms(3000);
    __delay_ms(3000);
    UART1_printf("AT+CIPMUX=1\r\n");                                            //acepta mulriples conexiones
    __delay_ms(200);

    UART1_printf("AT+CIFSR\r\n");                                               //mira que ip tiene el modulo
    __delay_ms(1000);

    //se conecta a ubidots
    UART1_printf("AT+CIPMUX=1\r\n");;
    __delay_ms(300);
    UART1_printf("AT+CIPSTART=4,\"TCP\",\"things.ubidots.com\",80\r\n");
    __delay_ms(3000);
}
