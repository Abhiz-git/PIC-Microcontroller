
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
unsigned char pwmH20,pwmL20,pwmH60,pwmL60,pwmH90,pwmL90;

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
    TRISC = 0XFD; //1111 1101 (Enable CCP2 mode by setting RC1 bit as 0)
    CCP2CON=0X0C; // 0000 1101 c is compulsory (view Data sheet To on pwm mode) Act as a Control Registor and also stores data for dutycycle
    CCPR2L=0X00;  // (Duty cycle Data) configuration hence wrong data is written so it can be over written
    T2CON=0X06;   // (Timer2) set bit 2 as 1 to on AND set bit 1-0 for Prescaler 16 (1x)
    PR2=0X2E;     // Time period (Requires formula to convert 1ms into hexaD.) {Deci= 45.88 = 46} 
    pwmH20=0x09;  // {Deci=38}
    pwmL20=0x20;
    pwmH60=0x1C;  // {Deci = 112.5 = 113}
    pwmL60=0x10;
    pwmH90=0x2A;  // {Deci = 168.75 = 169}
    pwmL90=0x10;
}
void pwmchange()
{ 
    CCPR2L=pwmH20;
    CCP2CON=(CCP2CON & 0XCF)| pwmL20;
    __delay_ms(3000);
    CCPR2L=pwmH60;
    CCP2CON=(CCP2CON & 0XCF)| pwmL60;
    __delay_ms(3000);
    CCPR2L=pwmH90;
    CCP2CON=(CCP2CON & 0XCF)| pwmL90;
    __delay_ms(3000);
}
