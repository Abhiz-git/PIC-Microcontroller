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

#include <stdio.h>

void init(void);

void main()
{
    unsigned char rec_val;
    init();

    while(1)
    {
        if(PIR1 & 0X20)
        {
            rec_val = RCREG;
            switch(rec_val)
            {
                case 'A': PORTD = 0x40; //RD4-0 RD6-1
                          break;

                case 'B': PORTD = 0x10;  //RD4-1 RD6-1
                          break;
                          
                case 'C': PORTD = 0x00;  //RD4-0 RD6-0
                          break;
                          
                case 'D': PORTD = 0x50;  //RD4-1 RD6-1
                          break;
                     
                default: PORTD = 0x00;
            }

        }
    }
}

void init()
{
    TRISD=0X00;
    PORTD=0X00;

    TRISC = 0XC0;

    TXSTA = 0X20;
    RCSTA = 0X90;
    SPBRG=0X09;
}

