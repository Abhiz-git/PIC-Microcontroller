
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>


#define _XTAL_FREQ 6000000

void init();
void Lcd_Comand(unsigned char);
void Lcd_Data(unsigned char);

unsigned char Display[11]={"Abhishek N."};

void main()
{
    unsigned char x,j;
    init();
    Lcd_Comand(0x82);
    for(x=0; x<=10; x++)
    {
        Lcd_Data(Display[x]);
    }
    for(j=0xCD,x=0; j>=0xC0,x<=10; j--,x++)
    {   
        Lcd_Comand(j);
        Lcd_Data(Display[x]); 
    }
    while(1);
}

void init()
{
    TRISC=0x00;
    TRISD=0X00;
    Lcd_Comand(0x38);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
    __delay_ms(100);
    Lcd_Comand(0x38);
    __delay_ms(100);
    Lcd_Comand(0x38);
    __delay_ms(100);
    Lcd_Comand(0x38);
    __delay_ms(100);
    Lcd_Comand(0x0C);
    __delay_ms(100);
    Lcd_Comand(0x01);
    __delay_ms(100);
}
void Lcd_Data(unsigned char i)
{
   RC3 = 1;     // RS = 1
   PORTD = i;   // data pins
   RC0 = 1;     // En 1
   RC0 = 0;     // EN 0
   __delay_ms(100);
}
void Lcd_Comand(unsigned char i)  //RS=RC3 AND Enable=RC0 and datapins PORT D0 to D7 
{
   RC3 = 0;     // RS = 0
   PORTD = i;   // data pins
   RC0 = 1;     // En 1
   RC0 = 0;     // EN 0
    __delay_ms(100);
}