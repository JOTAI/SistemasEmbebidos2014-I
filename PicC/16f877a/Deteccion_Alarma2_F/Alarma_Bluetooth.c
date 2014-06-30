#include <16f877a.h>

#FUSES HS,NOWDT,NOPROTECT,NOLVP 
#USE delay(clock=10000000)

#USE FAST_IO(B)   //Puerto B
#USE FAST_IO(D)   //Puerto D

// **************************************
// Declaracion de variables
int1 estado_alarma = 0;
unsigned int cont_tiempo = 0;
//***************************************

// **************************************
// Declaracion de Funciones
void Cargar_configuracion();
void Configurar_interrupciones();

// **************************************

// **************************************
// Declaracion de las Interrupciones
#INT_EXT       //Sentencias de la interrupcion RB0
void ext_isr(){
      if(estado_alarma == 1){
         enable_interrupts(INT_TIMER0);       //Habilita interrupción timer0
      }
   }
#INT_RB
void rb_isr(){
   if (input(PIN_B4) == 1){
      if(estado_alarma == 0){
      estado_alarma = 1;
      output_high(PIN_D1);
      }
      else {
      estado_alarma = 0;
      disable_interrupts(INT_TIMER0);       //Desabilita interrupción timer0
      output_low(PIN_D0);
      output_low(PIN_D1);
      }
   }
   
}

#int_TIMER0
void TIMER0_isr(void) {
   set_timer0 (0x1B);
   cont_tiempo++;
   if (cont_tiempo == 255){
   output_toggle(PIN_D0);
   cont_tiempo = 0;
   }
}               //Se recarga el timer0
// **************************************************
void main() {
   Cargar_configuracion();
   Configurar_interrupciones();
   while(true){     //Ciclo infinito en espera de interrupciones 

               Delay_ms(10);
              }                                
   }//FIN D

// ****************************************
// Definicion de las Funciones

void Cargar_configuracion(){
   SET_TRIS_B(0xFF);    //configura PORTB entrada / 0=salida / 1=entrada
   SET_TRIS_D(0x00);    //configura PORTD salida
   OUTPUT_D(0x00);   //inicializando PORTD en 0x00
   estado_alarma = 0;
}

void Configurar_interrupciones(){
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_2);   //Configuración timer0
   set_timer0 (0x1B);                 //Carga del timer0
   ext_int_edge(L_TO_H);         // Flag INTF si flanco de bajada / H_TO_L bajada
   enable_interrupts(INT_EXT);   // habilitar interrupcion del RB0 /INTE
   enable_interrupts(INT_RB);   // habilitar interrupcion del RB
   enable_interrupts(GLOBAL);
}
//**********************************************************************


