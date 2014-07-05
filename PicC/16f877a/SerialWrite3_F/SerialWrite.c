#INCLUDE <16f877a.h>
#DEVICE ICD=TRUE
#DEVICE adc=10
#FUSES HS,NOWDT,NOPROTECT,NOLVP 
#USE delay(clock=10000000) 
//#USE rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)  // Configuracion Comunicacion Serial
#USE FAST_IO(A) 
#USE FAST_IO(B)
#USE FAST_IO(C)
#INCLUDE "LCD.C"

// Transmicion
#BYTE TXSTA = 0x98
#BYTE SPBRG = 0x99
#BYTE TXREG = 0x19

// Recepcion
#BYTE RCREG = 0x1A
#BYTE RCSTA = 0x18


// ********************************************************
// Declaracion de Funciones
void Ini_USART();
void USART_SendC(char send);

//*********************************************************



void main (){
   float Radc;
   int Vadc;   // Voltaje ADC
   char q;
   Ini_USART();
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
      USART_SendC(q);
      printf(lcd_putc,"\fV: %f", Radc);
      delay_ms(500);
   }

}

void Ini_USART(){
   // Son necesarios definir los bits
   /* *****
      // Transmicion
   #BYTE TXSTA = 0x98
   #BYTE SPBRG = 0x99
   #BYTE TXREG = 0x19
      // Recepcion
   #BYTE RCREG = 0x1A
   #BYTE RCSTA = 0x18
   ***** */

   TXSTA = 0x20;
   SPBRG = 15;        // V=9766 BAUD XTAL=10MHz
   RCSTA = 0x90;
   TXREG = 0x00;
   RCREG = 0x00;
   SET_TRIS_C(0x80);
}

void USART_SendC(char send){
   //while (TXSTA,1 == 1){}
   TXREG = send;
   delay_us(20);
}


