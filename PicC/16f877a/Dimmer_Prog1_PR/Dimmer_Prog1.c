#include <16f877a.h>
#FUSES HS,NOWDT,NOPROTECT,NOLVP 
#USE delay(clock=10000000)
#BYTE PORTD = 0x08   //Asignando PORTD
#USE FAST_IO(B)   //Puerto B
#USE FAST_IO(D)   //Puerto D

// Creacion de Variables
int angulo = 0;
int Portb1_ant = 0;
int Portb1_now = 0;
int Cristal = 10;             // es la frecuencia del cristal en MHz
int Tiempo_espera = 15;       // es el tiempo que se esperara x100ms para poder entrar a la programacion del dimmer
int Cont_Tiempo_espera = 0;   //Contador del tiempo que se ha estado esperando
int Cont_TMR0 = 0;            // contador para el TMR0
int Num_aplausos = 2;         // es el numero de aplausos que se necesitan para entrar a la programacion
int Cont_Num_aplausos = 0;    // Contador del nuemro de aplausos realizados
int Estado_foco = 0;          // 1 = foco encendido --- 0 = foco apagado --- 2 = en programacion
int Estado_foco_ant = 0;      // una variable temporal que almacenara el Estado_foco cuando este cambie
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
   
#INT_TIMER0      //Sentencias de la interrupcion TMR0
void TIMER0_isr(void) {
   Cont_TMR0++;
   if (Cont_TMR0 >= 1000){         //las sentencias del if se daran cada 100ms
      Cont_Tiempo_espera++;
      if (Cont_Tiempo_espera >= Tiempo_espera){    // se verifica que se paso solo el tiempo permitido
         if (Cont_Num_aplausos == Num_aplausos){   // se verifica que se tenga la cantidad de aplausos necesarios
            Estado_foco_ant = Estado_foco;         //se guarda el estado anterior del foco
            Estado_foco = 2;                       // se establece el foco en modo programacion
         }
         Cont_Tiempo_espera = 0;
      }
      Cont_TMR0 = 0;
   }
   //output_toggle(PIN_D1);
   set_timer0 (0x97);            //para que la interrupcion se de cada 100us
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
   SET_TRIS_D(0x00);    //configura PORTD salida
   OUTPUT_D(0x00);   //inicializando PORTD en 0x00
   angulo = 2;       // inicializando el angulo de dispario en 2ms
}

void Configurar_interrupciones(){
   enable_interrupts(INT_EXT);   // habilitar interrupcion del RB0 /INTE
   ext_int_edge(L_TO_H);         // Flag INTF si flanco de bajada / H_TO_L bajada
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_2);   //Configuración timer0
   set_timer0 (0x97);                    //Carga del timer0
   enable_interrupts(INT_TIMER0);       //Habilita interrupción timer0
   enable_interrupts(GLOBAL);
}

void Disparar(int ang){
   switch (ang){
      case 0 : 
               bit_set(PORTD,0);
         break;
      case 1 : delay_ms(1);
               bit_set(PORTD,0);
         break;
      case 2 : delay_ms(2);
               bit_set(PORTD,0);
         break;
      case 3 : delay_ms(3);
               bit_set(PORTD,0);
         break;
      case 4 : delay_ms(4);
               bit_set(PORTD,0);
         break;
      case 5 : delay_ms(5);
               bit_set(PORTD,0);
         break;
      case 6 : delay_ms(6);
               bit_set(PORTD,0);
         break;
      case 7 : delay_ms(7);
               bit_set(PORTD,0);
         break;
   }
      delay_ms(1);
      bit_clear(PORTD,0);
}
//*****************************************
