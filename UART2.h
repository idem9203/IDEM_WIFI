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

#include <xc.h> // include processor files - each processor file is guarded.  

void UART2_Init(unsigned long BAUD);
int B2 = 0;
void UART2_Write(char data);
void UART2_printf(char* trama);
char UART2_Read();

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

