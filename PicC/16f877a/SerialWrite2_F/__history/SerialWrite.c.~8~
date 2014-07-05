#INCLUDE <16f877a.h>
#DEVICE ICD=TRUE
#DEVICE adc=10
#FUSES HS,NOWDT,NOPROTECT,NOLVP 
#USE delay(clock=10000000) 
#USE rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)  // Configuracion Comunicacion Serial
#USE FAST_IO(A) 
#USE FAST_IO(B)
#USE FAST_IO(C)
#INCLUDE "LCD.C"

void main (){
   float Radc;
   int Vadc;   // Voltaje ADC
   char q;
   setup_adc_ports(AN0);
   setup_adc(adc_clock_div_32);
   lcd_init();
   
   while (TRUE){
      set_adc_channel(0);
      delay_us(20);
      Radc=read_adc();
      delay_us(20);
      Radc = Radc*5.0/1024;
      Vadc = Radc;
      q = Vadc+48;
      printf("\fV: %f", Radc);
      delay_us(20);
      printf(lcd_putc,"\fV: %f", Radc);
      delay_ms(500);
   }

}


