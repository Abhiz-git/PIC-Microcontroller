
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

# define _XTAL_FREQ 6000000

void init(void);
void Command(unsigned char);
void Data(unsigned char);
void Output(unsigned int);

unsigned char n,j, k[10];
unsigned int lowVal,HiVal,m, V;
unsigned long val;


void main()
{
    init();
    while(1)
    {
        ADCON0= 0x81;  // 1001 0001 {<7:6>-10(Fosc/64), <5-3>-010(Chan.2), <2>-0(GO_DONE), <0>-1(AD-on)}
        ADCON0|= 0x04; // 0000 0100 
        while(ADCON0&0x04);
        lowVal=ADRESL;
        HiVal= ADRESH;
        val=((unsigned int)HiVal<<8)+(unsigned int)lowVal;
        V = val*338/1023;
        Command(0x80);     
        Output(V);

        CCPR1L=(V)>>2;
        CCP1CON=(CCP1CON&0x0C)+((V&0x03)<<4);
        __delay_ms(1000);
    }
}
void init(void)
{
    TRISA= 0x01;
    TRISC = 0x00;
    TRISD = 0x00;
    ADCON0 = 0x81;
    ADCON1 = 0x8E; // 1000 1110 {<7>-1(Right Justify), <6>-0(Fosc/32), <3-0>-0010(AN Con.bits)}
    
    CCP1CON = 0x1C;
    CCPR1L = 0xAD;
    T2CON = 0x06;
    PR2 = 0x5E;
    
    Command(0x33);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
    __delay_ms(10);
    Command(0x33);
    __delay_ms(10);
    Command(0x33);
    __delay_ms(10);
    Command(0x38);
    Command(0x06);          // Cursor shift from left to right
    Command(0x0C);          // display on Cursor off
    Command(0x01);          // clear Display
    }

void Output(unsigned int j)
{
    unsigned char s,l=1;
    m=j;
    while(m!=0)
    {
        s=m-((m/10)*10);
        k[l]=s;
        l++;
        m=m/10;
    }
    k[l]='\0';
    l=l-1;
    
    if (k[3]>0)
    {
        for(j=3;j!=1;j--)
        {
            n=0x30+k[j];
            Data(n);
        }
    }
    else if (k[2]>0)
    {
        Data(0x20);
        n=0x30+k[2];
        Data(n);
    }
    else
    {
        Data(0x20); // White Space
        Data(0x20);
    }
    n=0x30+k[1];
    Data(n);
    n=0x56;
    Data(n);
}
//RS=RC3 AND Enable=RC0 and datapins PORT D0 to D7 
void Data(unsigned char j)
{
    PORTC|=0X08;    // RS=1
    PORTD=j;        
    PORTC|=0X01;    
    PORTC&=~0X01;   
    __delay_ms(10);
}
void Command(unsigned char j)  
{
    PORTC&=~0x08;    // RS = 0
    PORTD= j ;      
    PORTC|=0X01;    
    PORTC&=~0X01;   
    __delay_ms(10);
}
