
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

void init()
{
    TRISB = 0XF0; // 1111 0000
    OPTION_REG &= 0X7F;
    TRISC = 0X80; // 1000 0000 {<7>-1(Rx), <6>-0(Tx)}

    TXSTA = 0X20;
    RCSTA = 0X90;
    SPBRG = 0X09;
    
    TRISD = 0x00;
}
void main(void)
{
    unsigned char val, rec_val;
    init();
    while(1)
    {
        val = PORTB;
        switch(val)
        {
            case 0xE0:  TXREG = 'A';
                        break;
                
            case 0xD0:  TXREG = 'B';
                        break;
            
            case 0xB0:  TXREG = 'C';
                        break;
            
            case 0x70:  TXREG = 'D';
                        break;
        }
        __delay_ms(100);
    
        if(PIR1 & 0X20)
        {
            rec_val = RCREG;
            switch(rec_val)
            {
                case 'a': PORTD = 0x04; //RD7-0 RD2-1
                          break;

                case 'b': PORTD = 0x80;  //RD7-1 RD2-0
                          break;
                          
                case 'c': PORTD = 0x84;  //RD7-1 RD2-1
                          break;
                          
                case 'd': PORTD = 0x00;  //RD7-0 RD2-0
                          break;

                default: PORTD = 0x00;
            }
        }
        __delay_ms(100);
    }
}