
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
    TRISB=0XF0; // 1111 0000 RB4 to RB7 we make it as input and RB0 to RB3 as output 
    TRISC=0X00; // 0000 0000 RC0 to RC7 we make it as output
    PORTB=0X00; // 0000 0000 RB0 to RB7 we make it as Low (RB4 to RB7 state ignored)
    
    while(1)
    {
        x = PORTB;
        switch(x)
        {
            case 0xE0 : PORTC=0X02; // RC1 ON & RC2 OFF 0000 0010
                        break;
            case 0xD0 : PORTC=0x06; // RC2 & RC1 both ON 0000 0110
                        break;
            case 0xB0 : PORTC=0X04; // RC2 ON 0000 0100
                        break;
            case 0x70 : PORTC=0X00; // Both RC1 & RC2 OFF 0000 0000
                        break;
            case 0xF0 : PORTC=0X00; // 0000 0000 (DEFAULT)
        }
    }    
}
