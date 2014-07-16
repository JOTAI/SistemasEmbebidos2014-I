
_INTERRUPCIONES_init:

;dimmer.c,17 :: 		void INTERRUPCIONES_init()
;dimmer.c,19 :: 		INTCON.GIE=1;
	BSF        INTCON+0, 7
;dimmer.c,20 :: 		INTCON.INTE=1;
	BSF        INTCON+0, 4
;dimmer.c,21 :: 		OPTION_REG.INTEDG=1;
	BSF        OPTION_REG+0, 6
;dimmer.c,23 :: 		PORTB.RB0=0;
	BCF        PORTB+0, 0
;dimmer.c,24 :: 		}
	RETURN
; end of _INTERRUPCIONES_init

_interrupt:
	MOVWF      R15+0
	SWAPF      STATUS+0, 0
	CLRF       STATUS+0
	MOVWF      ___saveSTATUS+0
	MOVF       PCLATH+0, 0
	MOVWF      ___savePCLATH+0
	CLRF       PCLATH+0

;dimmer.c,26 :: 		void interrupt(void) {
;dimmer.c,27 :: 		if(INTCON.INTF==1){
	BTFSS      INTCON+0, 1
	GOTO       L_interrupt0
;dimmer.c,28 :: 		if(PORTB.RB4==1&&f1==1){a=a+1;f1=0;}
	BTFSS      PORTB+0, 4
	GOTO       L_interrupt3
	MOVLW      0
	XORWF      _f1+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt63
	MOVLW      1
	XORWF      _f1+0, 0
L__interrupt63:
	BTFSS      STATUS+0, 2
	GOTO       L_interrupt3
L__interrupt61:
	INCF       _a+0, 1
	BTFSC      STATUS+0, 2
	INCF       _a+1, 1
	CLRF       _f1+0
	CLRF       _f1+1
L_interrupt3:
;dimmer.c,29 :: 		if(PORTB.RB5==0&&f2==0){a=a+1;f2=1;}
	BTFSC      PORTB+0, 5
	GOTO       L_interrupt6
	MOVLW      0
	XORWF      _f2+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt64
	MOVLW      0
	XORWF      _f2+0, 0
L__interrupt64:
	BTFSS      STATUS+0, 2
	GOTO       L_interrupt6
L__interrupt60:
	INCF       _a+0, 1
	BTFSC      STATUS+0, 2
	INCF       _a+1, 1
	MOVLW      1
	MOVWF      _f2+0
	MOVLW      0
	MOVWF      _f2+1
L_interrupt6:
;dimmer.c,30 :: 		if(PORTB.RB6==1&&f3==1){a=a+1;f3=0;}
	BTFSS      PORTB+0, 6
	GOTO       L_interrupt9
	MOVLW      0
	XORWF      _f3+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt65
	MOVLW      1
	XORWF      _f3+0, 0
L__interrupt65:
	BTFSS      STATUS+0, 2
	GOTO       L_interrupt9
L__interrupt59:
	INCF       _a+0, 1
	BTFSC      STATUS+0, 2
	INCF       _a+1, 1
	CLRF       _f3+0
	CLRF       _f3+1
L_interrupt9:
;dimmer.c,31 :: 		if(PORTB.RB7==1&&f4==1){a=a-1;f4=0;}
	BTFSS      PORTB+0, 7
	GOTO       L_interrupt12
	MOVLW      0
	XORWF      _f4+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt66
	MOVLW      1
	XORWF      _f4+0, 0
L__interrupt66:
	BTFSS      STATUS+0, 2
	GOTO       L_interrupt12
L__interrupt58:
	MOVLW      1
	SUBWF      _a+0, 1
	BTFSS      STATUS+0, 0
	DECF       _a+1, 1
	CLRF       _f4+0
	CLRF       _f4+1
L_interrupt12:
;dimmer.c,32 :: 		if(a==8){a=0;}
	MOVLW      0
	XORWF      _a+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt67
	MOVLW      8
	XORWF      _a+0, 0
L__interrupt67:
	BTFSS      STATUS+0, 2
	GOTO       L_interrupt13
	CLRF       _a+0
	CLRF       _a+1
L_interrupt13:
;dimmer.c,33 :: 		if(a<0){a=8;}
	MOVLW      128
	XORWF      _a+1, 0
	MOVWF      R0+0
	MOVLW      128
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt68
	MOVLW      0
	SUBWF      _a+0, 0
L__interrupt68:
	BTFSC      STATUS+0, 0
	GOTO       L_interrupt14
	MOVLW      8
	MOVWF      _a+0
	MOVLW      0
	MOVWF      _a+1
L_interrupt14:
;dimmer.c,34 :: 		switch(a){
	GOTO       L_interrupt15
;dimmer.c,35 :: 		case 0:   PORTD.RD0=1;delay_ms(1);break;
L_interrupt17:
	BSF        PORTD+0, 0
	MOVLW      7
	MOVWF      R12+0
	MOVLW      125
	MOVWF      R13+0
L_interrupt18:
	DECFSZ     R13+0, 1
	GOTO       L_interrupt18
	DECFSZ     R12+0, 1
	GOTO       L_interrupt18
	GOTO       L_interrupt16
;dimmer.c,36 :: 		case 1:   delay_us(750);PORTD.RD0=1;delay_us(500);break;
L_interrupt19:
	MOVLW      5
	MOVWF      R12+0
	MOVLW      221
	MOVWF      R13+0
L_interrupt20:
	DECFSZ     R13+0, 1
	GOTO       L_interrupt20
	DECFSZ     R12+0, 1
	GOTO       L_interrupt20
	NOP
	NOP
	BSF        PORTD+0, 0
	MOVLW      4
	MOVWF      R12+0
	MOVLW      61
	MOVWF      R13+0
L_interrupt21:
	DECFSZ     R13+0, 1
	GOTO       L_interrupt21
	DECFSZ     R12+0, 1
	GOTO       L_interrupt21
	NOP
	NOP
	GOTO       L_interrupt16
;dimmer.c,37 :: 		case 2:   delay_us(1520);PORTD.RD0=1;delay_us(500);break;
L_interrupt22:
	MOVLW      10
	MOVWF      R12+0
	MOVLW      221
	MOVWF      R13+0
L_interrupt23:
	DECFSZ     R13+0, 1
	GOTO       L_interrupt23
	DECFSZ     R12+0, 1
	GOTO       L_interrupt23
	NOP
	NOP
	BSF        PORTD+0, 0
	MOVLW      4
	MOVWF      R12+0
	MOVLW      61
	MOVWF      R13+0
L_interrupt24:
	DECFSZ     R13+0, 1
	GOTO       L_interrupt24
	DECFSZ     R12+0, 1
	GOTO       L_interrupt24
	NOP
	NOP
	GOTO       L_interrupt16
;dimmer.c,38 :: 		case 3:   delay_us(2250);PORTD.RD0=1;delay_us(500);break;
L_interrupt25:
	MOVLW      15
	MOVWF      R12+0
	MOVLW      155
	MOVWF      R13+0
L_interrupt26:
	DECFSZ     R13+0, 1
	GOTO       L_interrupt26
	DECFSZ     R12+0, 1
	GOTO       L_interrupt26
	BSF        PORTD+0, 0
	MOVLW      4
	MOVWF      R12+0
	MOVLW      61
	MOVWF      R13+0
L_interrupt27:
	DECFSZ     R13+0, 1
	GOTO       L_interrupt27
	DECFSZ     R12+0, 1
	GOTO       L_interrupt27
	NOP
	NOP
	GOTO       L_interrupt16
;dimmer.c,39 :: 		case 4:   delay_ms(3);PORTD.RD0=1;delay_us(500);break;
L_interrupt28:
	MOVLW      20
	MOVWF      R12+0
	MOVLW      121
	MOVWF      R13+0
L_interrupt29:
	DECFSZ     R13+0, 1
	GOTO       L_interrupt29
	DECFSZ     R12+0, 1
	GOTO       L_interrupt29
	NOP
	NOP
	BSF        PORTD+0, 0
	MOVLW      4
	MOVWF      R12+0
	MOVLW      61
	MOVWF      R13+0
L_interrupt30:
	DECFSZ     R13+0, 1
	GOTO       L_interrupt30
	DECFSZ     R12+0, 1
	GOTO       L_interrupt30
	NOP
	NOP
	GOTO       L_interrupt16
;dimmer.c,40 :: 		case 5:   delay_us(3750);PORTD.RD0=1;delay_us(500);break;
L_interrupt31:
	MOVLW      25
	MOVWF      R12+0
	MOVLW      88
	MOVWF      R13+0
L_interrupt32:
	DECFSZ     R13+0, 1
	GOTO       L_interrupt32
	DECFSZ     R12+0, 1
	GOTO       L_interrupt32
	NOP
	BSF        PORTD+0, 0
	MOVLW      4
	MOVWF      R12+0
	MOVLW      61
	MOVWF      R13+0
L_interrupt33:
	DECFSZ     R13+0, 1
	GOTO       L_interrupt33
	DECFSZ     R12+0, 1
	GOTO       L_interrupt33
	NOP
	NOP
	GOTO       L_interrupt16
;dimmer.c,41 :: 		case 6:   delay_us(4500);PORTD.RD0=1;delay_us(500);break;
L_interrupt34:
	MOVLW      30
	MOVWF      R12+0
	MOVLW      55
	MOVWF      R13+0
L_interrupt35:
	DECFSZ     R13+0, 1
	GOTO       L_interrupt35
	DECFSZ     R12+0, 1
	GOTO       L_interrupt35
	BSF        PORTD+0, 0
	MOVLW      4
	MOVWF      R12+0
	MOVLW      61
	MOVWF      R13+0
L_interrupt36:
	DECFSZ     R13+0, 1
	GOTO       L_interrupt36
	DECFSZ     R12+0, 1
	GOTO       L_interrupt36
	NOP
	NOP
	GOTO       L_interrupt16
;dimmer.c,42 :: 		case 7:   delay_us(5250);PORTD.RD0=1;delay_us(500);break;
L_interrupt37:
	MOVLW      35
	MOVWF      R12+0
	MOVLW      21
	MOVWF      R13+0
L_interrupt38:
	DECFSZ     R13+0, 1
	GOTO       L_interrupt38
	DECFSZ     R12+0, 1
	GOTO       L_interrupt38
	NOP
	NOP
	BSF        PORTD+0, 0
	MOVLW      4
	MOVWF      R12+0
	MOVLW      61
	MOVWF      R13+0
L_interrupt39:
	DECFSZ     R13+0, 1
	GOTO       L_interrupt39
	DECFSZ     R12+0, 1
	GOTO       L_interrupt39
	NOP
	NOP
	GOTO       L_interrupt16
;dimmer.c,43 :: 		}
L_interrupt15:
	MOVLW      0
	XORWF      _a+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt69
	MOVLW      0
	XORWF      _a+0, 0
L__interrupt69:
	BTFSC      STATUS+0, 2
	GOTO       L_interrupt17
	MOVLW      0
	XORWF      _a+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt70
	MOVLW      1
	XORWF      _a+0, 0
L__interrupt70:
	BTFSC      STATUS+0, 2
	GOTO       L_interrupt19
	MOVLW      0
	XORWF      _a+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt71
	MOVLW      2
	XORWF      _a+0, 0
L__interrupt71:
	BTFSC      STATUS+0, 2
	GOTO       L_interrupt22
	MOVLW      0
	XORWF      _a+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt72
	MOVLW      3
	XORWF      _a+0, 0
L__interrupt72:
	BTFSC      STATUS+0, 2
	GOTO       L_interrupt25
	MOVLW      0
	XORWF      _a+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt73
	MOVLW      4
	XORWF      _a+0, 0
L__interrupt73:
	BTFSC      STATUS+0, 2
	GOTO       L_interrupt28
	MOVLW      0
	XORWF      _a+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt74
	MOVLW      5
	XORWF      _a+0, 0
L__interrupt74:
	BTFSC      STATUS+0, 2
	GOTO       L_interrupt31
	MOVLW      0
	XORWF      _a+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt75
	MOVLW      6
	XORWF      _a+0, 0
L__interrupt75:
	BTFSC      STATUS+0, 2
	GOTO       L_interrupt34
	MOVLW      0
	XORWF      _a+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__interrupt76
	MOVLW      7
	XORWF      _a+0, 0
L__interrupt76:
	BTFSC      STATUS+0, 2
	GOTO       L_interrupt37
L_interrupt16:
;dimmer.c,44 :: 		PORTD.RD0=0;
	BCF        PORTD+0, 0
;dimmer.c,45 :: 		INTCON.INTF=0;
	BCF        INTCON+0, 1
;dimmer.c,46 :: 		}
L_interrupt0:
;dimmer.c,53 :: 		}
L__interrupt62:
	MOVF       ___savePCLATH+0, 0
	MOVWF      PCLATH+0
	SWAPF      ___saveSTATUS+0, 0
	MOVWF      STATUS+0
	SWAPF      R15+0, 1
	SWAPF      R15+0, 0
	RETFIE
; end of _interrupt

_main:

;dimmer.c,55 :: 		void main( void )
;dimmer.c,58 :: 		Lcd_Init();
	CALL       _Lcd_Init+0
;dimmer.c,59 :: 		TRISD=0X00;
	CLRF       TRISD+0
;dimmer.c,60 :: 		TRISB=0xFF;
	MOVLW      255
	MOVWF      TRISB+0
;dimmer.c,61 :: 		PORTD.RD0=0;
	BCF        PORTD+0, 0
;dimmer.c,62 :: 		INTERRUPCIONES_init();
	CALL       _INTERRUPCIONES_init+0
;dimmer.c,63 :: 		Lcd_Cmd(_LCD_CURSOR_OFF);
	MOVLW      12
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;dimmer.c,64 :: 		Delay_ms(10);
	MOVLW      65
	MOVWF      R12+0
	MOVLW      238
	MOVWF      R13+0
L_main40:
	DECFSZ     R13+0, 1
	GOTO       L_main40
	DECFSZ     R12+0, 1
	GOTO       L_main40
	NOP
;dimmer.c,65 :: 		Lcd_out(1,1,"ANGULO:");
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr1_dimmer+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;dimmer.c,66 :: 		Lcd_out(2,1,"TIEMPO:");
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr2_dimmer+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;dimmer.c,67 :: 		a=0;
	CLRF       _a+0
	CLRF       _a+1
;dimmer.c,68 :: 		while(1){
L_main41:
;dimmer.c,69 :: 		if(PORTB.RB4==0){f1=1;}
	BTFSC      PORTB+0, 4
	GOTO       L_main43
	MOVLW      1
	MOVWF      _f1+0
	MOVLW      0
	MOVWF      _f1+1
L_main43:
;dimmer.c,70 :: 		if(PORTB.RB5==1){f2=0;}
	BTFSS      PORTB+0, 5
	GOTO       L_main44
	CLRF       _f2+0
	CLRF       _f2+1
L_main44:
;dimmer.c,71 :: 		if(PORTB.RB6==0){f3=1;}
	BTFSC      PORTB+0, 6
	GOTO       L_main45
	MOVLW      1
	MOVWF      _f3+0
	MOVLW      0
	MOVWF      _f3+1
L_main45:
;dimmer.c,72 :: 		if(PORTB.RB7==0){f4=1;}
	BTFSC      PORTB+0, 7
	GOTO       L_main46
	MOVLW      1
	MOVWF      _f4+0
	MOVLW      0
	MOVWF      _f4+1
L_main46:
;dimmer.c,76 :: 		switch(a){
	GOTO       L_main47
;dimmer.c,77 :: 		case 0:  {Lcd_out(1,9,"  0.0");Lcd_out(2,11,"0 ms");}break;
L_main49:
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      9
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr3_dimmer+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      11
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr4_dimmer+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
	GOTO       L_main48
;dimmer.c,78 :: 		case 1:  {Lcd_out(1,9," 21.6");Lcd_out(2,11,"1 ms");}break;
L_main50:
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      9
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr5_dimmer+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      11
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr6_dimmer+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
	GOTO       L_main48
;dimmer.c,79 :: 		case 2:  {Lcd_out(1,9," 43.2");Lcd_out(2,11,"2 ms");}break;
L_main51:
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      9
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr7_dimmer+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      11
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr8_dimmer+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
	GOTO       L_main48
;dimmer.c,80 :: 		case 3:  {Lcd_out(1,9," 64.8");Lcd_out(2,11,"3 ms");}break;
L_main52:
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      9
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr9_dimmer+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      11
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr10_dimmer+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
	GOTO       L_main48
;dimmer.c,81 :: 		case 4:  {Lcd_out(1,9," 86.4");Lcd_out(2,11,"4 ms");}break;
L_main53:
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      9
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr11_dimmer+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      11
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr12_dimmer+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
	GOTO       L_main48
;dimmer.c,82 :: 		case 5:  {Lcd_out(1,9,"108.0");Lcd_out(2,11,"5 ms");}break;
L_main54:
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      9
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr13_dimmer+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      11
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr14_dimmer+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
	GOTO       L_main48
;dimmer.c,83 :: 		case 6:  {Lcd_out(1,9,"129.6");Lcd_out(2,11,"6 ms");}break;
L_main55:
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      9
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr15_dimmer+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      11
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr16_dimmer+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
	GOTO       L_main48
;dimmer.c,84 :: 		case 7:  {Lcd_out(1,9,"151.2");Lcd_out(2,11,"7 ms");}break;
L_main56:
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      9
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr17_dimmer+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      11
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr18_dimmer+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
	GOTO       L_main48
;dimmer.c,85 :: 		}
L_main47:
	MOVLW      0
	XORWF      _a+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main77
	MOVLW      0
	XORWF      _a+0, 0
L__main77:
	BTFSC      STATUS+0, 2
	GOTO       L_main49
	MOVLW      0
	XORWF      _a+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main78
	MOVLW      1
	XORWF      _a+0, 0
L__main78:
	BTFSC      STATUS+0, 2
	GOTO       L_main50
	MOVLW      0
	XORWF      _a+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main79
	MOVLW      2
	XORWF      _a+0, 0
L__main79:
	BTFSC      STATUS+0, 2
	GOTO       L_main51
	MOVLW      0
	XORWF      _a+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main80
	MOVLW      3
	XORWF      _a+0, 0
L__main80:
	BTFSC      STATUS+0, 2
	GOTO       L_main52
	MOVLW      0
	XORWF      _a+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main81
	MOVLW      4
	XORWF      _a+0, 0
L__main81:
	BTFSC      STATUS+0, 2
	GOTO       L_main53
	MOVLW      0
	XORWF      _a+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main82
	MOVLW      5
	XORWF      _a+0, 0
L__main82:
	BTFSC      STATUS+0, 2
	GOTO       L_main54
	MOVLW      0
	XORWF      _a+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main83
	MOVLW      6
	XORWF      _a+0, 0
L__main83:
	BTFSC      STATUS+0, 2
	GOTO       L_main55
	MOVLW      0
	XORWF      _a+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main84
	MOVLW      7
	XORWF      _a+0, 0
L__main84:
	BTFSC      STATUS+0, 2
	GOTO       L_main56
L_main48:
;dimmer.c,86 :: 		Delay_us(50);
	MOVLW      83
	MOVWF      R13+0
L_main57:
	DECFSZ     R13+0, 1
	GOTO       L_main57
;dimmer.c,87 :: 		}
	GOTO       L_main41
;dimmer.c,88 :: 		}
	GOTO       $+0
; end of _main
