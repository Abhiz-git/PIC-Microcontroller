
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

void main() 
{
    unsigned char x;
    
    TRISC = 0xFF;
    TRISD = 0xEB;
    PORTC = 0x00;
    
    while(1)
    {
        x = PORTC;
        switch(x)
        {
            case 0x01: PORTD = 0x10;
                       break;
            case 0x02: PORTD = 0x04;
                       break;
            case 0x04: PORTD = 0x14;
                       break;
            case 0x08: PORTD = 0x00;
                       break;
            default: PORTD = 0x00;
        }
    }
}
