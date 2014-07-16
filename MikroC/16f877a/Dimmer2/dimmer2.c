#include <16F877A.h>
#FUSES XT,NOWDT
#use delay (clock=10000000)
#include <lcd.c>
#include <kbd44.c>
#include <stdlib.h>
#use standard_io(a)


void main(){

char tecla;
int i;
char ingreso[9],numero[9];

kbd44_init();
lcd_init();
port_b_pullups(TRUE);

   for(;;){
   tecla=kbd44_getc();
      if(tecla=='*'){
         lcd_putc("\fNuevo Numero:\n");
         for(i=0;i<9;i++){
         tecla=kbd44_getc();
            while(tecla==0){
            tecla=kbd44_getc();
            ingreso[i]=tecla;
            }
          printf(lcd_putc,"%c",ingreso[i]);
         }
         for(i=0;i<9;i++){
         write_eeprom(i,ingreso[i]);
         numero[i]=read_eeprom(i);
         }
      }
   }
}
