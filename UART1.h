/* 
 * File: USART1
 * Author: Ivan D. Echeverry M.
 * Comments: Libreria para el uso de comunicacion serie Tx y Rx
 * Revision history: 12/04/2020
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef UART1_H
#define	UART1_H

#include <xc.h> // include processor files - each processor file is guarded.  

void UART1_Init(unsigned long BAUD);
int B1 = 0;
void UART1_Write(char data);
void UART1_printf(char* trama);
char UART1_Read();

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

