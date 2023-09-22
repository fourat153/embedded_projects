#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using Byte  = unsigned char ; 
using Word = unsigned short ;
using u32 = unsigned int ; 

struct Mem {
     static constexpr u32 MAX_MEM  = 1024 * 64 ; 
     Byte Data[MAX_MEM] ; 
};

struct CPU
{
 
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
    void Reset () ; 
} ; 

int main() 
{
   CPU cpu ; 
   cpu.Reset()

return 0 ; 
}