/* 
 * File:  CONFIG_CONNECT_ESP8266_SP01
 * Author: Ivan D. Echeverry M.
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef CONFIG_CONNECT_ESP8266_SP01_H
#define	CONFIG_CONNECT_ESP8266_SP01_H

#include <xc.h> // include processor files - each processor file is guarded.  

void ESP8266_CONFIG_CONNECT(char SSID[20], char password[30]);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

