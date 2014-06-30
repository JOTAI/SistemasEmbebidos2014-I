#include "16f877a.h"
#fuses  NOWDT, HS, NOLVP, NOPROTECT
#use delay(clock=10000000)
#include "LCD.c"
#include "kbd2.c"

// **************************************************************
// Declaracion de las variables
char tecla;
int1 estado_clave=0;
char clave[4]={'1','3','5','7'};
char clave_blth = 'M';
int1 clave_bluetooth = 0;
int pos_clave=0;
int i=0;
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
void  RD_isr(void) {
  tecla = getc(0);
  if (tecla == clave_blth){
      estado_clave = 1;
      tecla = 0;
  }
}
//***************************************************************

// ***************************************************************
// Funcion Principal
void main()
{

   while(TRUE)
   {
      
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
   enable_interrupts(INT_RDA); //POR PUERTO DE COMUNICACIONES 
   enable_interrupts(GLOBAL);  //E INTERRUPCIONES GLOBALES
}
void Ingreso_Clave(){
   pos_clave = 0;
   estado_clave = 1;
  while (pos_clave<=4){
    tecla = kbd_getc();
    if (tecla != 0 && clave_bluetooth==0){
       printf(lcd_putc,"*");
       if (tecla != clave[pos_clave]){
          estado_clave = 0;
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
