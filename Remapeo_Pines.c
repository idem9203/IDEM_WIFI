#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h> // include processor files - each processor file is guarded.
#include <pic18f26j50.h>
#include "Config.h"

////////////////////////////////////////////////////////////////////////////////
///////////////////////////// REMAPEOS DE PINES ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Remap_PIN ()
{
    EECON2 = 0x55;
    EECON2 = 0xAA;
    PPSCON = 0;
    
    RPINR16 = 13;                                                               //Rx en C2 RP13
    RPOR12 = 0x05;                                                              //Tx en C1 RP12
    
    EECON2 = 0x55;
    EECON2 = 0xAA;
    PPSCON = 1;
}

////////////////////////////////////////////////////////////////////////////////
