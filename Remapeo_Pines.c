#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h> // include processor files - each processor file is guarded.
#include <pic18f25j50.h>
#include "Config.h"

////////////////////////////////////////////////////////////////////////////////
///////////////////////////// REMAPEOS DE PINES ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Remap_PIN ()
{
    PPSCON = 85;
    PPSCON = 170;
    IOLOCK = 0;
    RPINR16 = 0b0001;                                                               //Rx en C2
    RPOR12 = 5;                                                                     //Tx en C1
    PPSCON = 85;
    PPSCON = 170;
    IOLOCK = 1;
}

////////////////////////////////////////////////////////////////////////////////
