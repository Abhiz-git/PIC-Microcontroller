
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
void pwmchange(void);
void delay();
unsigned char pwmH10,pwmL10,pwmH50,pwmL50,pwmH80,pwmL80;

void main(void)
{
    init();
    while(1)
    {
        pwmchange();
    }
}
void init(void)
{
    TRISC = 0XFB; //1111 1011
    CCP1CON=0X3C; // 0011 1101 3 is unessecery c is compulsory (view Data sheet Ti: 1:25:00)
    CCPR1L=0X2E;  // (Duty cycle) configuration hence wrong data is written so it can be over written
    T2CON=0X06;   
    PR2=0X5D;
    pwmH10=0x09;
    pwmL10=0x20;
    pwmH50=0x02F;
    pwmL50=0x00;
    pwmH80=0x4B;
    pwmL80=0x00;
}
void pwmchange()
{ 
    CCPR1L=pwmH10;
    CCP1CON=(CCP1CON & 0XCF)| pwmL10;
    __delay_ms(3000);
    CCPR1L=pwmH50;
    CCP1CON=(CCP1CON & 0XCF)| pwmL50;
    __delay_ms(3000);
    CCPR1L=pwmH80;
    CCP1CON=(CCP1CON & 0XCF)| pwmL80;
    __delay_ms(3000);
}
