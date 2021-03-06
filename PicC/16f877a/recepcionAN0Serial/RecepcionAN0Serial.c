#include <16f877A.h>
#device adc=8//La resoluci�n del m�dulo A/D es de 8 bits.
#fuses XT,NOWDT,NOPROTECT,NOLVP,PUT,BROWNOUT
#use delay(clock=4000000)
#define antirebotes           50     // Tiempo para los delays antirebotes, en ms
#define TIEMPO_ENTRE_LECTURAS 10     //ms entre una y otra lectura.
#define lcd_data_port gentev("sfr:portd") // diciendole al pic que vamos a conectar el LCD por el Puerto D
#define lcd_enable_pin pin_d0 // Conecto el enable del LCD con el pin D0
#define lcd_rs_pin pin_d1 // Conecto el RS del LCD con el pin D1
#define lcd_rw_pin pin_d2 // Conecto el RW del LCD con el pin D2

#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)


long sen1, sen2,sen3,sen4;
long s1, s2, s3, s4;
char md[4];


//Leo el valor del sensor1 -> AN0 ------------------------------------//
 int sensor1 (void){
 
  set_adc_channel(0);
  delay_ms(1);
  sen1=read_adc();     //sen1  --> sensor1
  delay_ms(1);
  delay_ms(37);
  return sen1;
 }

//Leo el valor del sensor2  -> AN1 ------------------------------------//
 int sensor2 (void){
  set_adc_channel(0);
  delay_ms(1);
  sen2=read_adc();   //sen2  ---> sensor2
  delay_ms(1);
  delay_ms(37);
  return sen2;
 }

//Leo el valor del sensor3 -> AN2 ------------------------------------//
 int sensor3 (void){
  set_adc_channel(0);
  delay_ms(1);
  sen3=read_adc();   // sen3 -->sensor3
  delay_ms(1);
  delay_ms(37);
  return sen3;
 }

//Leo el valor del sensor4 -> AN3 ------------------------------------//
 int sensor4 (void){
  set_adc_channel(0);
  delay_ms(1);
  sen4=read_adc();   // sen4 -->sensor4
  delay_ms(1);
  delay_ms(37);
  return sen4;
 }


//Efect�a el ensayo completo, guardando datos en la EEPROM---------//
void realizar_ensayo(void){
   int i;

      s1 = sensor1 ();
      
      printf("s1:%ld \r",s1);
      delay_ms(10);
     
      s2 = sensor2 ();
     
      printf("s2:%4ld \r",s2);
      delay_ms(10);
      s3 = sensor3 ();
     
      printf("s3:%4ld \r",s3);
      delay_ms(10); 
      s4 = sensor4 ();
     
      printf("s4:%4ld \r",s4);
      delay_ms(10); 
      delay_ms(TIEMPO_ENTRE_LECTURAS);
   }




//-----------------------------------------------------------------//
// Programa Principal ---------------------------------------------//
//-----------------------------------------------------------------//
void main() {
   int i;
  set_tris_a(0xFF);      // Puerto A todo entradas
  port_b_pullups(FALSE); // Resistencias de polarizaci�n
  set_tris_b(0x38);      //
  set_tris_c(0x00);      // Puerto C todo salidas
  set_tris_d(0x00);     // Puerto D todo salidas

  //Configuro los canales del ADC
  SETUP_ADC_PORTS(AN0_AN1_AN2_AN3_AN4);
  SETUP_ADC(ADC_CLOCK_DIV_8 );
  SETUP_VREF(VREF_HIGH | 6 );


  //Habilito interrupciones
  //enable_interrupts(int_rda);
  //enable_interrupts(global);

  while(1){
  realizar_ensayo();
  //printf("%4ld \r",md);
  }
 }







