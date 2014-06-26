#include <16F628A.h>

#FUSES HS,NOWDT,NOPROTECT,NOLVP
#USE delay(internal=4000000)
#USE FAST_IO(B)   //Puerto B
#USE FAST_IO(A)   //Puerto D

// Creacion de Variables
int angulo = 0;
int Portb1_ant = 0;
int Portb1_now = 0;
// Fin de Creacion de Variables

// **************************************
// Declaracion de Funciones
void Cargar_configuracion();
void Configurar_interrupciones();
void VariacionAnguloAplauso (int incremento);
void Disparar(int ang);
// **************************************

// **************************************
// Declaracion de las Interrupciones
#INT_EXT       //Sentencias de la interrupcion RB0
void ext_isr(){
   Disparar(angulo);
   }
// **************************************************

// FUNCION PRINCIPAL
void main()
{  
   Cargar_configuracion();
   Configurar_interrupciones();
      
   while(true)
   {  
      VariacionAnguloAplauso(1);
   }
}

// ****************************************
// Definicion de las Funciones

void VariacionAnguloAplauso (int incremento){
   // Portb1_ant y Portb1_now  fueron iniciados en 0
   if (input(PIN_B1) == 1){        //  verifica si el PORTB,1 es 1
         Portb1_ant = Portb1_now;
         Portb1_now = 1;
      }else {
         Portb1_ant = Portb1_now;
         Portb1_now = 0;
      }
    if (Portb1_ant == 0 && Portb1_now == 1){
         if(angulo >= 7){
            angulo = 0;
         }else {
            angulo = angulo + incremento;
         }
      }
}

void Cargar_configuracion(){
   SET_TRIS_B(0xFF);    //configura PORTB entrada / 0=salida / 1=entrada
   SET_TRIS_A(0x00);    //configura PORTA salida
   OUTPUT_A(0x00);   //inicializando PORTA en 0x00
   angulo = 2;       // inicializando el angulo de dispario en 2ms
}

void Configurar_interrupciones(){
   enable_interrupts(INT_EXT);   // habilitar interrupcion del RB0 /INTE
   ext_int_edge(L_TO_H);         // Flag INTF si flanco de bajada / H_TO_L bajada
   enable_interrupts(INT_RB);
   enable_interrupts(GLOBAL);
}

void Disparar(int ang){
   switch (ang){
      case 0 : 
               OUTPUT_A(0x01);
         break;
      case 1 : delay_ms(1000);
               OUTPUT_A(0x01);
         break;
      case 2 : delay_ms(2000);
               OUTPUT_A(0x01);
         break;
      case 3 : delay_ms(3000);
               OUTPUT_A(0x01);
         break;
      case 4 : delay_ms(4000);
               OUTPUT_A(0x01);
         break;
      case 5 : delay_ms(5000);
               OUTPUT_A(0x01);
         break;
      case 6 : delay_ms(6000);
               OUTPUT_A(0x01);
         break;
      case 7 : delay_ms(7000);
               OUTPUT_A(0x01);
         break;
   }
      delay_ms(1000);
      OUTPUT_A(0x00);
}
//*****************************************
