#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h> // include processor files - each processor file is guarded.
#include <pic18f25j50.h>
#include "Config.h"
#include "UART1.h"


//HABILITA PUERTO SERIE 1
void UART1_Init(unsigned long BAUD)
{
    //CONFIGURACION PUERTO SERIE
    TRISCbits.TRISC7 = 1;                                                       //RX Input
    TRISCbits.TRISC6 = 0;                                                       //TX Output
    
    //Configuracion
    TXSTA1bits.SYNC1 = 0;                                                       //Transmision asincrona UART
    RCSTA1bits.SPEN1 = 1;                                                        //Habilita UART
    
    //Transmision
    TXSTA1bits.TX91 = 0;                                                        //8 bits
    TXSTA1bits.TXEN1 = 1;                                                       //Habilitar transmision
    
    //Recepcion
    RCSTA1bits.RC9 = 0;                                                         //8 bits
    RCSTA1bits.CREN1 = 1;                                                       //Habilita recepcion

    //CONFIGURACION BAUDIOS
    if (BAUD == 115200) 
    {
        B1 = ((_XTAL_FREQ/BAUD)/16)-1;
        TXSTA1bits.BRGH = 1;                                                    //Alta velocidad
    }
    else if (BAUD == 9600)
    {
        B1 = ((_XTAL_FREQ/BAUD)/64)-1;
        TXSTA1bits.BRGH = 0;                                                    //Baja velocidad
    }
    //CONFIGURACION BAUD RATE
    BAUDCON1bits.BRG16 = 0;                                                     //8 bits
    SPBRG1 = B1;                                                                //Baud rate 9600
}
////////////////////////////////////////////////////////////////////////////////

/*
* Rutina necesaria para que funcione correctamente el printf.
* Escribe un caracter en el puerto serial.
*/
void UART1_Write(char data) 
{ 
    while(0 == PIR1bits.TX1IF);

    TXREG1 = data;                                                              // Write the data byte to the USART.
}

void UART1_printf(char* trama)
{
    while(*trama) UART1_Write(*trama++);    
}

char UART1_Read(void)
{                                                        
    if (PIR1bits.RC1IF == 1) return RCREG1;
    else return 0;
}
