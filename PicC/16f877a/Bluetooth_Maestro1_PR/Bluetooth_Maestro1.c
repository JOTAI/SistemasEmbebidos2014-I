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
char Boton2_UP[2]="\0";
char Boton3_UP[2]="\0";
char Boton4_UP[2]="\0";
char Boton5_UP[2]="\0";
char Boton1_DOWN[2]="\0";
char Boton2_DOWN[2]="\0";
char Boton3_DOWN[2]="\0";
char Boton4_DOWN[2]="\0";
char Boton5_DOWN[2]="\0";

char ClaveNum[3][3];
char Clave1[2]="\0";
char Clave2[2]="\0";
char Clave3[2]="\0";

// *********************************************************
// declaracion de variables
int1 letra_in;
//**********************************************************

// *********************************************************
// Declaracion de funciones
void Rutina();
void SecClav();
//**********************************************************

// *********************************************************
// Definicion de interrupciones
#int_RDA
void  RDA_isr(void) {
   
   fgets(entrada,BLUE); //GUARDAMOS EN ENTRADA LO QUE HAY EN LA USART
   letra_in = 1;

}//fin de metodo interrupcion rda
//*********************************************************


void main() {  
   setup_comparator(NC_NC_NC_NC);//DESACTIVAMOS COMPARADORES
   setup_vref(FALSE);
   enable_interrupts(INT_RDA); //POR PUERTO DE COMUNICACIONES 
   enable_interrupts(GLOBAL);  //E INTERRUPCIONES GLOBALES

   set_tris_A(0x00); //puerto A como  1111 1110utput
   set_tris_D(0x00);
   OUTPUT_A(0x00);//limpiamos puerto, encendemos led con cero
   OUTPUT_D(0X00);
   
   Boton1_UP="G";
   Boton2_UP="C";
   Boton3_UP="E";
   Boton4_UP="A";
   Boton5_UP="I";
   Boton1_DOWN="H";
   Boton2_DOWN="D";
   Boton3_DOWN="F";
   Boton4_DOWN="B";
   Boton5_DOWN="J";
   letra_in = 0;
   

   Clave1="1";
   Clave2="2";
   Clave3="3";
   
   while(true){     //Ciclo infinito en espera de interrupciones 
               Rutina();
               Delay_ms(10);
              }                                
   }//FIN D
   
   
   void Rutina(){
      if (letra_in == 1){
         if(strcmp(entrada,Boton1_UP)==0){
            output_high(PIN_D0);
            delay_ms(100);
            output_low(PIN_D0);
         }else if (strcmp(entrada,Boton1_DOWN)==0){
            output_high(PIN_D0);
            delay_ms(100);
            output_low(PIN_D0);
         }else if(strcmp(entrada,Boton2_UP)==0){
            output_high(PIN_D1);
            delay_ms(100);
            output_low(PIN_D1);
         }else if (strcmp(entrada,Boton2_DOWN)==0){
            output_high(PIN_D1);
            delay_ms(100);
            output_low(PIN_D1);
         }else if(strcmp(entrada,Boton3_UP)==0){
            output_high(PIN_D2);
            delay_ms(100);
            output_low(PIN_D2);
         }else if (strcmp(entrada,Boton3_DOWN)==0){
            output_high(PIN_D2);
            delay_ms(100);
            output_low(PIN_D2);
         }else if(strcmp(entrada,Boton4_UP)==0){      //boton para acceder a la secuencia de identificacion de clave
            output_high(PIN_D5);
            delay_ms(100);
            output_low(PIN_D5);
            letra_in = 0;
            SecClav();   
         }else if (strcmp(entrada,Boton4_DOWN)==0){
            output_high(PIN_D5);
            delay_ms(100);
            output_low(PIN_D5);
            letra_in = 0;
            SecClav();
            output_low(PIN_D5);
         }else if(strcmp(entrada,Boton5_UP)==0){
            output_high(PIN_D4);
         }else if (strcmp(entrada,Boton5_DOWN)==0){
            output_low(PIN_D4);
         }
         letra_in = 0;
      } 
   }

void SecClav(){
   int1 estado=1;
   //ContClave=0;
   while (letra_in!=1){delay_ms(5);}
      output_high(PIN_D5);
      delay_ms(100);
      output_low(PIN_D5);
      letra_in = 0;
      if (strcmp(entrada,Clave1)!=0){estado=0;}
   while (letra_in!=1){delay_ms(5);}
      output_high(PIN_D5);
      delay_ms(100);
      output_low(PIN_D5);
      letra_in = 0;
      if (strcmp(entrada,Clave2)!=0){estado=0;}
   while (letra_in!=1){delay_ms(5);}
      output_high(PIN_D5);
      delay_ms(100);
      output_low(PIN_D5);
      letra_in = 0;
      if (strcmp(entrada,Clave3)!=0){estado=0;}
   delay_ms(20);
   if(estado==1){
      output_high(PIN_D5);                      // se enciende el PIN D5 para mostrar alarma activa
      output_high(PIN_D3);
      delay_ms(100);
      output_low(PIN_D3);
   }
}
