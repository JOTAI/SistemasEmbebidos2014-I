#include <16F628.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(internal=4000000)
#USE FAST_IO(A)   //Puerto A
#USE FAST_IO(B)   //Puerto B



// **********************************************
// Declaracion de las funciones
void Cargar_configuracion();
void Configurar_interrupciones();
void invertir_PORTA();
//***********************************************


// **********************************************
// Interrupciones
#INT_EXT             // Interrupcion RB0
void  EXT_isr(void) 
{
   invertir_PORTA();
}
#INT_RB
void  RB_isr(void) {
   if (input(PIN_B4) == 1 ){
      invertir_PORTA();
   } else if (input(PIN_B5) == 1){

   }else if (input(PIN_B6) == 1){

   }else if (input(PIN_B7) == 1){

   }
}

//***********************************************

// **********************************************
// Funcion Principal
void main()
{
   Cargar_configuracion();
   Configurar_interrupciones();
   while(TRUE)
   {
      //TODO: User Code
   }

}
//**********************************************


// *********************************************
// Definicion de las funciones

void Cargar_configuracion() {
   SET_TRIS_B(0xFF);    //configura PORTB entrada / 0=salida / 1=entrada
   SET_TRIS_A(0x00);    //configura PORTA salida
   OUTPUT_A(0xFF);   //inicializando PORTD en 0x00
}
void Configurar_interrupciones(){
   enable_interrupts(INT_EXT);   // habilitar interrupcion del RB0 /INTE
   ext_int_edge(L_TO_H);         // Flag INTF si flanco de bajada / H_TO_L bajada
   enable_interrupts(INT_RB);    // habilita interrupcion del RB 
   enable_interrupts(GLOBAL);
}

void invertir_PORTA(){
   if (input(PIN_A0) == 1 ){ 
      output_low(PIN_A0);
   }else {
      output_high(PIN_A0);
   }
}
//**********************************************
