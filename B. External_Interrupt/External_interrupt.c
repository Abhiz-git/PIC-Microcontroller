
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
    INTCON = 0X90; // 1001 0000 {<7>-GIE SET, <4>-INTE SET}
    TRISB=0X01; // 0000 0001 <0>-external interrupt RB0/INT is SET 
    PORTB=0X00;

    TRISC=0X00;
    PORTC=0X00;

    TRISD=0X00;
    PORTD=0X00;

    while(1)        // Thread method
    {
            PORTC = ~PORTC;   // if low turn high and vice versa
            __delay_ms(500);
    }

}

void __interrupt() ESR()    // Handler Method
{
    unsigned char val;
    if(INTCON & 0x02)    // 0000 0010 to check if <1>-External interrupt flag(INTF) is Set
    {
        val = PORTB;
        if(val == 0x01)
        {
            PORTD = ~PORTD;
        }
        INTCON &= 0xFC;       // 1111 1100  Flag is clear <0>-INTF
        __delay_ms(3000);     // switch de-bounce
    }
}