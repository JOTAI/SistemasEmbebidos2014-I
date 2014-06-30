#include <16f877a.h>
#FUSES HS,NOWDT,NOPROTECT,NOLVP 
#USE delay(clock=20000000)
#BYTE PORTD = 0x08   //Asignando PORTD
#USE FAST_IO(B)   //Puerto B
#USE FAST_IO(D)   //Puerto D

#INCLUDE "LCD.C"
#INCLUDE "kbd2.c"

char tecla;



void main()
{

   while(TRUE)
   {
      tecla = kbd_getc();
   }

}
