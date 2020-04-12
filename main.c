/*
 * File:   main.c
 * Author: Ivan D Echeverry M
 *
 * Created on April 8, 2020, 10:41 PM
 */

// PIC18F25J50 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config WDTEN = OFF      // Watchdog Timer (Disabled - Controlled by SWDTEN bit)
#pragma config PLLDIV = 5       // PLL Prescaler Selection bits (Divide by 5 (20 MHz oscillator input))
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset (Enabled)
#pragma config XINST = OFF       // Extended Instruction Set (Enabled)

// CONFIG1H
#pragma config CPUDIV = OSC1    // CPU System Clock Postscaler (No CPU system clock divide)
#pragma config CP0 = OFF        // Code Protect (Program memory is not code-protected)

// CONFIG2L
#pragma config OSC = ECPLL      // Oscillator (EC+PLL (CLKO-RA6), USB-EC+PLL)
#pragma config T1DIG = ON       // T1OSCEN Enforcement (Secondary Oscillator clock source may be selected)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator (High-power operation)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor (Enabled)
#pragma config IESO = ON        // Internal External Oscillator Switch Over Mode (Enabled)

// CONFIG2H
#pragma config WDTPS = 32768    // Watchdog Postscaler (1:32768)

// CONFIG3L
#pragma config DSWDTOSC = INTOSCREF// DSWDT Clock Select (DSWDT uses INTRC)
#pragma config RTCOSC = T1OSCREF// RTCC Clock Select (RTCC uses T1OSC/T1CKI)
#pragma config DSBOREN = ON     // Deep Sleep BOR (Enabled)
#pragma config DSWDTEN = ON     // Deep Sleep Watchdog Timer (Enabled)
#pragma config DSWDTPS = G2     // Deep Sleep Watchdog Postscaler (1:2,147,483,648 (25.7 days))

// CONFIG3H
#pragma config IOL1WAY = ON     // IOLOCK One-Way Set Enable bit (The IOLOCK bit (PPSCON<0>) can be set once)
#pragma config MSSP7B_EN = MSK7 // MSSP address masking (7 Bit address masking mode)

// CONFIG4L
#pragma config WPFP = PAGE_31   // Write/Erase Protect Page Start/End Location (Write Protect Program Flash Page 31)
#pragma config WPEND = PAGE_WPFP// Write/Erase Protect Region Select (valid when WPDIS = 0) (Page WPFP<5:0> through Configuration Words erase/write protected)
#pragma config WPCFG = OFF      // Write/Erase Protect Configuration Region (Configuration Words page not erase/write-protected)

// CONFIG4H
#pragma config WPDIS = OFF      // Write Protect Disable bit (WPFP<5:0>/WPEND region ignored)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h>
#include <pic18f25j50.h>

#define _XTAL_FREQ 48000000

#define RELE1 LATAbits.LATA5
#define RELE2 LATBbits.LATB0
#define D0 PORTAbits.RA3
#define D1 PORTAbits.RA4

float iA1;
float A1, A2;

//HABILITA PUERTO SERIE 1
void Serial_Init1()
{
    //CONFIGURACION PUERTO SERIE
    TRISCbits.TRISC7 = 1;                                                       //RX Input
    TRISCbits.TRISC6 = 0;                                                       //TX Output
    TXSTA1bits.SYNC = 0;                                                        //Transmision asincrona UART
    TXSTA1bits.TX9 = 0;                                                         //8 bits
    RCSTA1bits.SPEN = 1;                                                        //Habilita UART
    TXSTA1bits.TXEN = 1;                                                        //Habilitar transmision
    RCSTA1bits.CREN = 1;                                                        //Habilita recepcion
}
////////////////////////////////////////////////////////////////////////////////

//CONFIGURACION BAUDIOS
void Baudios1 (unsigned long baud, unsigned long fosc)                          //Especificar baudios y frecuencia de reloj
{
    int R = 0;
    if (baud == 115200) 
    {
        R = ((fosc/baud)/16)-1;
        TXSTA1bits.BRGH = 1;                                                    //Alta velocidad
    }
    else if (baud == 9600)
    {
        R = ((fosc/baud)/64)-1;
        TXSTA1bits.BRGH = 0;                                                    //Baja velocidad
    }
    //CONFIGURACION BAUD RATE
    BAUDCON1bits.BRG16 = 0;                                                     //8 bits
    SPBRG1 = R;                                                                 //Baud rate 9600
}

/*
* Rutina necesaria para que funcione correctamente el printf.
* Escribe un caracter en el puerto serial.
*/
void EUSART1_Write(uint8_t data) 
{
  while(0 == PIR1bits.TXIF)
    {
    }

    TXREG1 = data;                                                              // Write the data byte to the USART.
}

void printf1(char* trama)
{
 while(*trama)  EUSART1_Write(*trama++);    

}

char UART_read1(void)
{
    while(!PIR1bits.RCIF)
    {
    }

    
    if(1 == RCSTA1bits.OERR)
    {
        // EUSART error - restart

        RCSTA1bits.SPEN = 0; 
        RCSTA1bits.SPEN = 1; 
    }

    return RCREG1;
}

//HABILITA PUERTO SERIE 2
void Serial_Init2()
{
    //CONFIGURACION PUERTO SERIE
    TRISCbits.TRISC2 = 1;                                                       //RX Input
    TRISCbits.TRISC1 = 0;                                                       //TX Output
    TXSTA2bits.SYNC2 = 0;                                                       //Transmision asincrona UART
    TXSTA2bits.TX92 = 0;                                                        //8 bits
    RCSTA2bits.SPEN2 = 1;                                                       //Habilita UART
    TXSTA2bits.TXEN2 = 1;                                                       //Habilitar transmision
    RCSTA2bits.CREN2 = 1;                                                       //Habilita recepcion
}
////////////////////////////////////////////////////////////////////////////////

//CONFIGURACION BAUDIOS
void Baudios2 (unsigned long baud, unsigned long fosc)                          //Especificar baudios y frecuencia de reloj
{
    int R = 0;
    if (baud == 115200) 
    {
        R = ((fosc/baud)/16)-1;
        TXSTA2bits.BRGH2 = 1;                                                   //Alta velocidad
    }
    else if (baud == 9600)
    {
        R = ((fosc/baud)/64)-1;
        TXSTA2bits.BRGH2 = 0;                                                   //Baja velocidad
    }
    //CONFIGURACION BAUD RATE
    BAUDCON2bits.BRG162 = 0;                                                    //8 bits
    SPBRG2 = R;                                                                 //Baud rate 9600
}

void EUSART2_Write(uint8_t data) 
{
    while(0 == PIR3bits.TX2IF)
    {
    }

    TXREG2 = data;                                                              // Write the data byte to the USART.
}

void printf2(char* trama)
{
 while(*trama)  EUSART2_Write(*trama++);    

}

unsigned char dato_rx;

char UART_read2(void)
{
    while(!PIR3bits.RC2IF)
    {
    }

    
    if(1 == RCSTA2bits.OERR2)
    {
        // EUSART error - restart

        RCSTA2bits.SPEN2 = 0; 
        RCSTA2bits.SPEN2 = 1; 
    }

    return RCREG2;
}

////////////////////////////////////////////////////////////////////////////////
/////////////////// VARIABLES PARA TRANAJAR CON ESP8266 ////////////////////////
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
                    dato_rx = UART_read1();                                     //lee el dato
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
                    dato_rx = UART_read1();                                     //lee el dato
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
                    dato_rx = UART_read1();                                     //lee el dato
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
                    dato_rx = UART_read1();                                     //lee el dato
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
                    dato_rx = UART_read1();                                     //lee el dato
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
char trama[150];                                                                //Enviar informacion al ESP8266
char trama_largo[20];                                                           //Para calcular el largo de la trama de las variables a enviar
char captu[30];                                                                 //Para capturar informacion de la trama

int var_largo;                                                                  //Largo de la trama en entero
char d0_string, d1_string;

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
    printf1("AT+CIPSEND=");                                                     //Envia solo constantes
    printf1("4");                                                               //Manda el socket el cual se conecto
    printf1(",");
    largo = strlen_const(info);                                                 //Calcula el largo de la cadena a enviar
    sprintf(captu, "%1u", largo);                                               //Es el largo de la trama +2 por enter y fin de linea
    printf1(captu);                                                              //Envia el largo de la trama
    printf1("\r\n");
    __delay_ms(100);                                                            //retardo antes de enviar la trama
    printf1(info);                                                               //manda envia solo constantes
    
}

void manda_esp8266(char *info)
{
    unsigned int largo;
    printf1("AT+CIPSEND=");                                                     //Envia solo constantes
    printf1("4");                                                               //Manda el socket el cual se conecto
    printf1(",");
    largo = strlen(info);                                                       //Calcula el largo de la cadena a enviar
    sprintf(captu, "%1u", largo);                                               //Es el largo de la trama +2 por enter y fin de linea
    printf1(captu);                                                              //Envia el largo de la trama
    printf1("\r\n");
    __delay_ms(100);                                                            //retardo antes de enviar la trama
    printf1(info);                                                               //manda envia solo constantes
    
}
////////////////////////////////////////////////////////////////////////////////

void main(void) {
    
    
    ////////////////////////////////////////////////////////////////////////////
    /////////////////////////// REMAPEOS DE PINES //////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    PPSCON = 0;
    IOLOCK = 0;
    RPINR16 = 0b0001101;                                                        //Rx en C2
    RPOR12 = 5;                                                                 //Tx en C1
    PPSCON = 1;
    IOLOCK = 1;
    ////////////////////////////////////////////////////////////////////////////
    
    //HABILITAR COMUNICACION SERIAL
    Serial_Init1();
    Baudios1(115200,48000000);
    
    Serial_Init2();
    Baudios2(115200,48000000);
    

    //DAMOS UN TIEMPO PARA QUE INCIE EL BUCLE DE OPERACION
    __delay_ms(2000);
    ////////////////////////////////////////////////////////////////////////////
    
    
    printf2("PROBANDO");
    
    printf1("ATE0\r\n");                                                        //SIN ECO
    __delay_ms(200);

    printf1("AT+CWMODE=1\r\n");                                                 //se CONECTA A RED EXISTENTE
    __delay_ms(200);

    //Para Colocar Una Ip Al modulo
    printf1("AT+CWDHCP=1,0\r\n");                                               //Deshabilita DHCP  para Ip manual
    __delay_ms(300);
    //Configura IP IP,Gateway,Mascara   en forma Manual

    printf1("AT+CIPSTA=\"192.168.1.117\",\"192.168.1.254\",\"255.255.255.0\"\r\n");
    __delay_ms(300);


    printf1("AT+CWJAP=\"RED_APTO\",\"2NB112100448\"\r\n");                      //se conecta a una red WIFI

    __delay_ms(3000);
    __delay_ms(3000);
    printf1("AT+CIPMUX=1\r\n");                                                 //acepta mulriples conexiones
    __delay_ms(200);

    printf1("AT+CIFSR\r\n");                                                    //mira que ip tiene el modulo
    __delay_ms(1000);

    //se conecta a ubidots
    printf1("AT+CIPMUX=1\r\n");;
    __delay_ms(300);
    printf1("AT+CIPSTART=4,\"TCP\",\"things.ubidots.com\",80\r\n");
    __delay_ms(3000);
    
    while(1)
    {
        //LIMPIA LAS TRAMAS
        memset(trama_largo,20,0);
        memset(trama,150,0);
        
        //ARMAMOS TRAMA DE VARIABLES
        sprintf(trama,"{\"corriente\": %5.2f,\"inputdigital0\": %c,\"inputdigital1\": %c,\"analog1\": %5.2f,\"analog2\": %5.2f}\n",iA1,d0_string,d1_string,A1,A2);
        
        var_largo = strlen(trama)-1;                                            //Calcula el largo de la trama de variables
        
        sprintf(trama_largo,"%u\n\n",var_largo);                                //La pasa a cadena y le agrega dos fin de lineas
        
        ////////////////////////////////////////////////////////////////////////
        ////////////////////// ENVIOS DE DATOS A UBIDOTS ///////////////////////
        // El device en este caso es idem_v1-5                                //
        // y el token BBFF-cdocy3PYE8Iu2wocqEY6pMuZAiAN6G                     //
        // se debe colocar los de la inteface                                 //
        ////////////////////////////////////////////////////////////////////////
        
        //MANDA EL LARGO DE LA TRAMA
        manda_esp8266_const("POST /api/v1.6/devices/idem_v1-5/?token=BBFF-cdocy3PYE8Iu2wocqEY6pMuZAiAN6G HTTP/1.1\nHost: things.ubidots.com\nContent-Type: application/json\nContent-Length: ");
        __delay_ms(1000);       
        
        manda_esp8266(trama_largo);                                             //Manda el largo de la trama
        __delay_ms(500);
        
        manda_esp8266(trama);                                                   //Manda la info con las variables
        __delay_ms(500);
        
        //PREGUNTA POR VARIABLES DESEADAS (R1)
        manda_esp8266_const("GET /api/v1.6/devices/idem_v1-5/r1-ac/values?page_size=1&token=BBFF-cdocy3PYE8Iu2wocqEY6pMuZAiAN6G HTTP/1.1\nHost: things.ubidots.com\n\n");
        
        lee_trama();                                                            //Lee la respuesta
        
        //Captura el valor de la variables        value": 0.0}
        strcpy(captu, strtok(trama_rx, ":"));                                   //Inicia captura de tokens desde el =
        strcpy(captu, strtok(0, ","));                                          //Captura hasta el /
        
        //Pasa la cadena a  numero
        valor_rx = atof(captu);
        if (valor_rx == 1.0) RELE1 = 1; else RELE1 = 0;                         //Aplica la salida al led
        __delay_ms(200);
        
        
        //PREGUNTA POR VARIABLES DESEADAS (R2)
        manda_esp8266_const("GET /api/v1.6/devices/idem_v1-5/r2-ac/values?page_size=1&token=BBFF-cdocy3PYE8Iu2wocqEY6pMuZAiAN6G HTTP/1.1\nHost: things.ubidots.com\n\n");
        
        lee_trama();                                                            //Lee la respuesta
        
        //Captura el valor de la variables        value": 0.0}
        strcpy(captu, strtok(trama_rx, ":"));                                   //Inicia captura de tokens desde el =
        strcpy(captu, strtok(0, ","));                                          //Captura hasta el /
        
        //Pasa la cadena a  numero
        valor_rx = atof(captu);
        if (valor_rx == 1.0) RELE2 = 1; else RELE2 = 0;                         //Aplica la salida al led
        __delay_ms(200);
        
        reconect++;
        if (reconect >= 5)
        {
            reconect = 0;
            //se conecta a ubidots
            printf1("AT+CIPSTART=4,\"TCP\",\"things.ubidots.com\",80\r\n");
            __delay_ms(300); 
        }
    }
    return;
}
