#include "16f877a.h"
#include <string.h>
#fuses  NOWDT, HS, NOLVP, NOPROTECT, RESERVED
#use delay(clock=10000000)
#use rs232(baud=9600,parity=N,xmit=PIN_B2,rcv=PIN_B1,bits=8,STREAM=BLUE,errors)
#include "LCD.c"
#include "kbd2.c"

// **************************************************************
// Declaracion de las variables
char tecla[5]="\0";
char tecla_teclado;
int1 estado_clave=0;
char clave[4]={'1','3','5','7'};
int1 clave_bluetooth = 0;
int pos_clave=0;

char boton1[3]="\0"; 
char boton2[3]="\0";


//***************************************************************

// **************************************************************
// Declaracion de funciones
   void Cargar_configuracion();
   void Configurar_interrupciones();
   void Ingreso_Clave();
//***************************************************************

// **************************************************************
// Definicion de interrupciones
#INT_RDA
void  RDA_isr(void) {
   boton1="1";
   boton2="2";
  fgets(tecla,BLUE); //GUARDAMOS EN ENTRADA LO QUE HAY EN LA USART
  if(strcmp(tecla,boton1)==0){
      estado_clave = 1;
      clave_bluetooth = 1;
  }else if (strcmp(tecla,boton2)==0){
      estado_clave = 0;
      clave_bluetooth = 0;
  }
}
//***************************************************************

// ***************************************************************
// Funcion Principal
void main()
{
   Configurar_interrupciones();
   Cargar_configuracion();
   
   while(TRUE)
   {
      Ingreso_Clave();
   }

}
//****************************************************************

// **************************************************************
// Definicion de las funciones
void Cargar_configuracion(){
   lcd_init();
   printf(lcd_putc,"Programa Iniciado");
   delay_ms(500);
   printf(lcd_putc,"Ingrese Clave\n");
}
void Configurar_interrupciones(){
   setup_comparator(NC_NC_NC_NC);//DESACTIVAMOS COMPARADORES
   setup_vref(FALSE);
   enable_interrupts(INT_RDA); //POR PUERTO DE COMUNICACIONES 
   enable_interrupts(GLOBAL);  //E INTERRUPCIONES GLOBALES
}
void Ingreso_Clave(){
   pos_clave = 0;
   estado_clave = 1;
  while (pos_clave<=4){
    tecla_teclado = kbd_getc();
    if (tecla != 0 && clave_bluetooth==0){
       //printf(lcd_putc,"*");
       if (tecla != clave[pos_clave]){
          estado_clave = 0;
          //printf(lcd_putc,"*");
       }
       pos_clave++;
    }
  }
  if (estado_clave == 1){
      lcd_putc('\f');
      printf(lcd_putc,"Alarma activa");
      delay_ms(500);
      lcd_putc('\f');
  }
}
//***************************************************************
