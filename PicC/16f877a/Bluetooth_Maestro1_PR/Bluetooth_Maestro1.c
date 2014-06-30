#include <16F877A.h>
#device adc=16

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOPUT                    //No Power Up Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOPROTECT                //Code not protected from reading

#use delay(clock=10000000)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=BLUE,errors)

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#USE FAST_IO(A) 
#USE FAST_IO(D)

char entrada[5]="\0";

char Boton1_UP[2]="\0";
int1 letra_in;

// **************************************
// Declaracion de Funciones
void Cargar_configuracion();
void Configurar_interrupciones();

// ************************************** 

// **************************************
// Declaracion de las Interrupciones
#int_RDA
void  RDA_isr(void) {
   
   fgets(entrada,BLUE); //GUARDAMOS EN ENTRADA LO QUE HAY EN LA USART
   letra_in = 1;

}//fin de metodo interrupcion rda
//***************************************

// **************************************
// FUNCION PRINCIPAL
void main() {  
   Cargar_configuracion();
   Configurar_interrupciones();
   while(true){     //Ciclo infinito en espera de interrupciones 
               Delay_ms(10);
              }                                
   }//FIN D
//***************************************

// ****************************************
// Definicion de las Funciones
void Cargar_configuracion(){
   set_tris_A(0x00); //puerto A como  1111 1110utput
   set_tris_D(0x00);
   OUTPUT_A(0x00);//limpiamos puerto, encendemos led con cero
   OUTPUT_D(0X00);
   Boton1_UP="1";
   letra_in = 0;
}

void Configurar_interrupciones(){
   setup_comparator(NC_NC_NC_NC);//DESACTIVAMOS COMPARADORES
   setup_vref(FALSE);
   enable_interrupts(INT_RDA); //POR PUERTO DE COMUNICACIONES 
   enable_interrupts(GLOBAL);  //E INTERRUPCIONES GLOBALES
}
//**********************************************************************


