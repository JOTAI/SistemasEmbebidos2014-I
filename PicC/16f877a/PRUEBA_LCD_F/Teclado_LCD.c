#include <16f877a.h>
#FUSES HS,NOWDT,NOPROTECT,NOLVP  
#USE delay(crystal=10000000)       // Definiendo cristal de 10MHz
#USE FAST_IO(B)   //Puerto B
#INCLUDE "LCD.C"

//#BYTE OPTION_REG = 0x81             // Declaracion OPTION_REG
//#BIT   RBIF=0x0B.0                     // Bandera de la interrupcion RB
#BYTE   tecla_port=0x06
#BIT   RBPU=0x81.7                     // Bit habilitacion del PullUp del PORTB


// **************************************
// Creacion de Variables

int   tecla_temp,tecla,i,teclanew;
int   const tabla_tecla[17]={0xD7,0xEE,0xDE,0xBE,0xED,0xDD,0xBD,0xEB,0xDB,0xBB,0xE7,0xB7,0x77,0x7B,0x7D,0x7E,0x80};
int   const tabla_ascii[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

//***************************************



// **************************************
// Declaracion de Funciones
void Cargar_configuracion();
void Configurar_interrupciones();
void Iniciar_teclado();
//void DAR_COL();
void VER_TECLA();
void Escribir_KEY();

//***************************************


// **************************************
// Declaracion de las Interrupciones
#INT_RB
void  RB_isr(void) {
   VER_TECLA();
}
#int_TIMER0
void TIMER0_isr(void) {
   set_timer0 (0x1B);      // Se recarga el TMR0  
   //DAR_COL();
   }


//***************************************


// **************************************
// FUNCION PRINCIPAL
void main()
{
   Cargar_configuracion();
   //Configurar_interrupciones();
   Iniciar_teclado();
   while(TRUE)
   {
      //Escribir_KEY();
      delay_ms(50);
   }

}
//***************************************


// ****************************************
// Definicion de las Funciones

void Cargar_configuracion(){
   lcd_init();
   //SET_TRIS_B(0xFF);    //configura PORTB entrada / 0=salida / 1=entrada
   //SET_TRIS_D(0x00);    //configura PORTD salida
   }

void Configurar_interrupciones(){
   //setup_timer_0(RTCC_INTERNAL|RTCC_DIV_2);   //Configuración timer0
   //set_timer0 (0x1B);                    //Carga del timer0
   //enable_interrupts(INT_TIMER0);       //Habilita interrupción timer0

   //enable_interrupts(INT_RB);       // Habilitando interrupcion RB /RB4-RB7
   //bit_clear(OPTION_REG,7);         // Habilita el Pull-UP de RB->OPTION_REG,RBPU
   //RBPU=0;                            // Habilita el PullUP de RB 
   //enable_interrupts(GLOBAL);       // Habilita las interrupciones
}

void Iniciar_teclado(){
   printf(lcd_putc,"Espera...");
   delay_ms(500);
   SET_TRIS_B(0xF0);                //configura PORTB entrada / 0=salida / 1=entrada
   tecla_port=0xF0;                 //PORTB=0xF0
   lcd_putc('\f');
   printf(lcd_putc,"Puede escribir");
   delay_ms(1000);
   //lcd_putc('\f');
   //lcd_gotoxy(1,1);
   
}


void VER_TECLA(){
    do
      {
         do
         {
            tecla_port=0xF0;
            i=1;
            tecla_temp=0xFE;
            do
            {
               tecla_port=tecla_temp;
               tecla=tecla_temp;
               tecla_temp=(tecla_temp<<1)+1;
               i++;
            }while((i<=4) && (tecla_port==tecla));
         }while(tecla_port==tecla);
         tecla=tecla_port;
         i=0;
         while((tabla_tecla[i]!=tecla) && (i<16))
         {
            i++;
         }
      }while(i==16);      
      tecla=tabla_ascii[i];
      teclanew=1;
      delay_ms(30);
      tecla_port=0xF0;
}

void Escribir_KEY(){
   if (teclanew == 1){
      lcd_putc(tecla);
      teclanew=0;
   }
}

//*****************************************



