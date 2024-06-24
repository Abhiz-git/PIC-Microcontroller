
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

void init(void);
void Command(unsigned char);
void Data(unsigned char);
void Keypad(void);

void main()
{
    char i, keypad[]={"Keypad Interface"};
    
    init();
    Command(0x80);
    for(i=0;i<=16;i++)
    {
        Data(keypad[i]);
    }
    Command(0xC0);
    while(1)
    {
        Keypad();
    }
}

void Keypad()
{
    PORTD = 0x01;
    if (PORTD == 0X09)
    {
        Data('1');
        while(PORTD == 0x09);
    }
    else if (PORTD == 0x11)
    {
        Data('4');
        while(PORTD == 0x11);
    }
    else if (PORTD == 0x21)
    {
        Data('7');
        while(PORTD == 0x21);
    }
    else if (PORTD == 0x41)
    {
        Data('*');
        while(PORTD == 0x41);
    }
    
    PORTD = 0x02;
    if (PORTD == 0x0A)
    {
        Data('2');
        while(PORTD == 0x0A);
    }
    else if (PORTD == 0x12)
    {
        Data('5');
        while(PORTD == 0x12);
    }
    else if (PORTD == 0x22)
    {
        Data('8');
        while(PORTD == 0x22);
    }
    else if (PORTD == 0x42)
    {
        Data('0');
        while(PORTD == 0x42);
    }
    
    PORTD = 0x04;
    if (PORTD == 0x0C)
    {
        Data('3');
        while(PORTD == 0x0C);
    }
    else if (PORTD == 0x14)
    {
        Data('6');
        while(PORTD == 0x14);
    }
    else if (PORTD == 0x24)
    {
        Data('9');
        while(PORTD == 0x24);
    }
    else if (PORTD == 0x44)
    {
        Data('#');
        while(PORTD == 0x44);
    }
}

void init()
{
    TRISB = 0X00;
    TRISC = 0X00;
    TRISD = 0XF8;
    
    Command(0x33);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
    __delay_ms(10);
    Command(0x33);
    __delay_ms(10);
    Command(0x33);
    __delay_ms(10);
    Command(0x38);
    Command(0x06);          // Cursor shift from left to right
    Command(0x0C);          // display on Cursor off
    Command(0x01);          // clear Display
}

void Data(unsigned char j)
{
    PORTB|=0X08;    // RS=1
    PORTC=j;        
    PORTB|=0X01;    
    PORTB&=~0X01;   
    __delay_ms(10);
}
void Command(unsigned char j)  //RS=RB2 AND Enable=RB0 and datapins PORT C0 to C7 
{
    PORTB&=~0x08;    // RS = 0
    PORTC= j ;      
    PORTB|=0X01;    
    PORTB&=~0X01;   
    __delay_ms(10);
}



