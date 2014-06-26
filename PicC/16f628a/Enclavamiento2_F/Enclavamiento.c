#include <16F628A.h>

#FUSES HS,NOWDT,NOPROTECT,NOLVP
#use delay(internal=4000000)

#USE FAST_IO(B)   //Puerto B
#USE FAST_IO(A)   //Puerto D
//#BIT RBIF = 0x0B.0
#BYTE CMCON = 0x1F


// *****************************************************************
// Declaracion de Funciones
void Configuracion();
void Configurar_interrupciones();
void Variar_led();

//******************************************************************

// *****************************************************************
// Declaracion de las Interrupciones
#INT_EXT       //Sentencias de la interrupcion RB0
void ext_isr(){
   Variar_led();
}

//******************************************************************

// *****************************************************************
// Funcion Prinipal
void main()
{
   Configuracion();
   Configurar_interrupciones();
   while(TRUE)
   {

   }

}
//*****************************************************************

// ****************************************************************
// Definicion de Funciones
void Configuracion(){
   SET_TRIS_B(0xFF);    //configura PORTB entrada / 0=salida / 1=entrada
   SET_TRIS_A(0x00);    //configura PORTD salida  
   OUTPUT_A(0x00);   //inicializando PORTD en 0x00
   CMCON = 0x07;
}

void Configurar_interrupciones(){

   enable_interrupts(INT_EXT);    // Habilita la interrupcion RB0
   ext_int_edge(L_TO_H);         // Flag INTF si flanco de bajada / H_TO_L bajada
   enable_interrupts(GLOBAL);

}

void Variar_led(){
   if (input(PIN_A0) == 1 ){
         output_low(PIN_A0);   //establece la salida del PORTD
      }else {
         output_high(PIN_A0);
      }
}

//****************************************************************
