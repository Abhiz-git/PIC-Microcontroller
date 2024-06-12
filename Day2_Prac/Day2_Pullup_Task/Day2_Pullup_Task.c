
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
    TRISC=0X0F; // 0000 1111 RC0 to RC3 we make it as input and RC4 to RC7 as output 
    TRISD=0X00; // 0000 0000 RD0 to RD7 we make it as output
    PORTC=0X00; // 0000 0000 RC0 to RC7 we make it as Low
    
    while(1)
    {
        x = PORTC;
        switch(x)
        {
            case 0x0E:  PORTD=0X10; // RD2 OFF & RD4 ON 0001 0000
                        break;
            case 0x0D : PORTD=0x04; // RD2 ON & RD4 OFF 0000 0100
                        break;
            case 0x0B : PORTD=0X014; // Both RD2 & RD4 ON 0001 0100
                        break;
            case 0x07 : PORTD=0X00; // Both RD2 & RD4 OFF 0000 0000
                        break;
            case 0x0F : PORTD=0X00; // 0000 0000 (DEFAULT)
        }
    }    
}
