/* 
 * File: UART2
 * Author: Ivan D. Echeverry M.
 * Comments: Libreria para trabajar con la comunicacion serial Tx2 y Rx2
 * Revision history: 12/04/2020
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef UART2_H
#define	UART2_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h> // include processor files - each processor file is guarded.
#include <pic18f25j50.h>
#include "Config.h"  

void UART2_Init(unsigned long BAUD);
int B2 = 0;
void UART2_Write(char data);
void UART2_printf(char* trama);
char UART2_Read();
bool UART2_Rx_Ready(void);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

