
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
    TRISB=0X10;
    PORTB=0X00;

    TRISC=0X00;
    PORTC=0X00;

    TRISD=0X00;
    PORTD=0X00;

    INTCON = 0X88; // 1000 1000 {<7>-GIE SET, <3>-RBIE SET}

    while(1)        // thread method
    {
        if(PORTB == 0x10) 
        {
            PORTC = ~PORTC;   // if low turn high and vice versa
            __delay_ms(500);
        }

    }

}

void __interrupt() Bnt_ISR()    // Handler Method
{
    unsigned char val;
    if(INTCON & 0x01)          // 0000 0001 to check if <0>-RB I Flag is Set
    {
        val = PORTB;
        if(val == 0x00)
        {
            PORTD = ~PORTD;
        }
        INTCON &= 0xFE;       // 1111 1110 reverse the signal that is clear <0>- RB I Flag
        __delay_ms(5000);     // switch de-bounce
    }
}

