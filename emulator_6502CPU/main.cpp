#include <stdio.h>
#include <stdlib.h>
#include <iostream>


struct CPU
{
    using Byte  = unsigned char ; 
    using Word = unsigned short ;
    Byte SP  ; // stack ointer 
    Word PC ; // rogra counter 
    
    Byte A , X , Y  ;  // register 

    Byte C : 1 ; // status flag 
    Byte Z : 1 ; // status flag 
    Byte I : 1 ; // status flag 
    Byte D : 1 ; // status flag 
    Byte B : 1 ; // status flag 
    Byte V : 1 ; // status flag 
    Byte N : 1 ; // status flag 
} ; 

int main() 
{
   

return 0 ; 
}