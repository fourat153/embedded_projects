/* 
 * File:   std_types.h
 * Author: mm77
 *
 * Created on June 1, 2023, 8:50 AM
 */

#ifndef STD_TYPES_H
#define	STD_TYPES_H
/*section : includes*/
#include "std_libararies.h"
#include "complier.h"
/*section : macros definition */
#define STD_HIGH  0x01
#define STD_LOW   0x00

#define STD_ON    0x01
#define STD_OFF   0x00


#define STD_ACTIVE 0X01    /*STATE ACTIVE FOR UART FOR EXAMPLE*/
#define STD_IDL    0X00

#define  E_OK (std_ReturnType)0x01 ;        /* return form function status recomanded from autosar  */
#define  E_NOT_ok (std_ReturnType)0x00;


/*section : macros function definition */

/*section : user define data types */
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;
typedef  char  sint8;
typedef  short sint16;
typedef  int   sint32;
typedef   uint8  std_ReturnType; 
/*section : function declaration*/


#endif	/* STD_TYPES_H */

