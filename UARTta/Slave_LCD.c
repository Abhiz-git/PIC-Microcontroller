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
void cmd(unsigned char);
void data(unsigned char);

void main()
{
    unsigned char i=0, rec_val, t[]={'Tx: '}, r[]={'Rx: '};
    init();

    cmd(0x80);
    while(i != '\0')
    {
        data(r[i]);
        i++;
    }

    i=0;
    cmd(0xC0);
    while(i != '\0')
    {
        data(t[i]);
        i++;
    }

    while(1)
    {
        if(PIR1&0X20)
        {
            rec_val = RCREG;
            switch(rec_val)
            {
                case 'A': cmd(0x80);
                          data('A');
                          TXREG = 'a';
                          cmd(0xC0);
                          data('a');
                          break;

                case 'B': cmd(0x80);
                          data('B');
                          TXREG = 'b';
                          cmd(0xC0);
                          data('b');
                          break;
                          
                case 'C': cmd(0x80);
                          data('C');
                          TXREG = 'c';
                          cmd(0xC0);
                          data('c');
                          break;
                          
                case 'D': cmd(0x80);
                          data('D');
                          TXREG = 'd';
                          cmd(0xC0);
                          data('d');
                          break;
            }

        }
        __delay_ms(100);
    }
}

void init()
{
    TXSTA = 0X20;
    RCSTA = 0X90;
    SPBRG = 0X09;
    TRISC = 0X80; // 1000 0000 {<7>-1(Rx), <6>-0(Tx)}
    
    TRISB = 0X00;
    TRISD = 0X00;

    cmd(0x34);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
    __delay_ms(10);
    cmd(0x34);
    __delay_ms(10);
    cmd(0x34);
    __delay_ms(10);
    cmd(0x38);
    cmd(0x06);          // Cursor shift from left to right
    cmd(0x0C);          // display on Cursor off
    cmd(0x01);          // clear Display
}
void cmd(unsigned char j)  //RS=RC3 AND Enable=RC0
{
    PORTC&=~0x08;    // RS = 0
    PORTD= j ;      
    PORTC|=0X01;    
    PORTC&=~0X01;   
    __delay_ms(10);
}
void data(unsigned char j) //RS=RC3 AND Enable=RC0 and datapins PORT D0 to D7 
{
    PORTC|=0X08;    // RS=1
    PORTD=j;        
    PORTC|=0X01;    
    PORTC&=~0X01;   
    __delay_ms(10);
}