sbit LCD_RS at RD2_bit;
sbit LCD_EN at RD3_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

sbit LCD_RS_Direction at TRISD2_bit;
sbit LCD_EN_Direction at TRISD3_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;

int a,ang,f1,f2,f3,f4;

void INTERRUPCIONES_init()
{
        INTCON.GIE=1;
        INTCON.INTE=1;
        OPTION_REG.INTEDG=1;
        //INTCON.RBIE=1;
        PORTB.RB0=0;
}

void interrupt(void) {
if(INTCON.INTF==1){
if(PORTB.RB4==1&&f1==1){a=a+1;f1=0;}
if(PORTB.RB5==0&&f2==0){a=a+1;f2=1;}
if(PORTB.RB6==1&&f3==1){a=a+1;f3=0;}
if(PORTB.RB7==1&&f4==1){a=a-1;f4=0;}
if(a==8){a=0;}
if(a<0){a=8;}
switch(a){
case 0:   PORTD.RD0=1;delay_ms(1);break;
case 1:   delay_us(750);PORTD.RD0=1;delay_us(500);break;
case 2:   delay_us(1520);PORTD.RD0=1;delay_us(500);break;
case 3:   delay_us(2250);PORTD.RD0=1;delay_us(500);break;
case 4:   delay_ms(3);PORTD.RD0=1;delay_us(500);break;
case 5:   delay_us(3750);PORTD.RD0=1;delay_us(500);break;
case 6:   delay_us(4500);PORTD.RD0=1;delay_us(500);break;
case 7:   delay_us(5250);PORTD.RD0=1;delay_us(500);break;
}
PORTD.RD0=0;
INTCON.INTF=0;
}
/*else if (INTCON.RBIF==1) {
a++;
if(a==8){a=0;}
    INTCON.RBIF = 0;
  }  */

}

void main( void )
{
//ADC_Init();
Lcd_Init();
TRISD=0X00;
TRISB=0xFF;
PORTD.RD0=0;
INTERRUPCIONES_init();
Lcd_Cmd(_LCD_CURSOR_OFF);
Delay_ms(10);
Lcd_out(1,1,"ANGULO:");
Lcd_out(2,1,"TIEMPO:");
a=0;
while(1){
if(PORTB.RB4==0){f1=1;}
if(PORTB.RB5==1){f2=0;}
if(PORTB.RB6==0){f3=1;}
if(PORTB.RB7==0){f4=1;}
/*ang=8*ADC_Read(1)/1023;
if(ang>3) {a=a+1;}
if(a==8) {a=0;}     */
switch(a){
case 0:  {Lcd_out(1,9,"  0.0");Lcd_out(2,11,"0 ms");}break;
case 1:  {Lcd_out(1,9," 21.6");Lcd_out(2,11,"1 ms");}break;
case 2:  {Lcd_out(1,9," 43.2");Lcd_out(2,11,"2 ms");}break;
case 3:  {Lcd_out(1,9," 64.8");Lcd_out(2,11,"3 ms");}break;
case 4:  {Lcd_out(1,9," 86.4");Lcd_out(2,11,"4 ms");}break;
case 5:  {Lcd_out(1,9,"108.0");Lcd_out(2,11,"5 ms");}break;
case 6:  {Lcd_out(1,9,"129.6");Lcd_out(2,11,"6 ms");}break;
case 7:  {Lcd_out(1,9,"151.2");Lcd_out(2,11,"7 ms");}break;
}
Delay_us(50);
}
}