
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
void Command(unsigned char);
void Data(unsigned char);
void OutputR(unsigned long);
void OutputV(unsigned int);

unsigned char n, k[10], V,r[]={"Raw Data: "}, c[]={"Cal Data: "};
unsigned int lowVal,HiVal,m;
unsigned long val,j;


void main()
{
    init();
    while(1)
    {
        ADCON0= 0x91;  // 1001 0001 {<7:6>-10(Fosc/64), <5-3>-010(Chan.2), <2>-0(GO_DONE), <0>-1(AD-on)}
        ADCON0|= 0x04; // 0000 0100 
        while(ADCON0&0x04);
        lowVal=ADRESL;
        HiVal= ADRESH;
        val=((unsigned int)HiVal<<2)+((unsigned int)lowVal>>6);
        V = val*100/1023;
        
        Command(0x80);     // Raw Data on First row of LCD
        j=0;
        while(r[j]!='\0')
        {
            Data(r[j]);
            j++;
        }
        OutputR(val);
        
        j=0;
        Command(0xC0);
        while(c[j]!='\0')
        {
           Data(c[j]);
           j++;
        }
        OutputV(V);
    
        //__delay_ms(10);
    }
}
void init(void)
{
    TRISA = 0x04;
    TRISC = 0x00;
    TRISD = 0x00;
    ADCON0 = 0x91;
    ADCON1 = 0x42; // 0100 0010 {<7>-0(Left Justify), <6>-1(Fosc/64), <3-0>-0010(AN Con.bits)}
    
    Command(0x33);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
    __delay_ms(10);
    Command(0x33);
    __delay_ms(5);
    Command(0x33);
    __delay_ms(5);
    Command(0x38);
    Command(0x06);          // Cursor shift from left to right
    Command(0x0C);          // display on Cursor off
    Command(0x01);          // clear Display
    }
void OutputR(unsigned long j)
{
    unsigned char s,c=1;
    m=j;
    while(m!=0)
    {
        s=m-((m/10)*10);
        k[c]=s;
        c++;
        m=m/10;
    }
    k[c]='\0';
    c -= 1;

    if(k[4]>0)
    {
        j = 4;
       while(j!=0)
       {
            n=0x30+k[j];
            Data(n);
            j--;
       }
    }
    else if(k[3]>0)
    {
        Data(0x20);
        j = 3;
        while(j!=0)
       {
            n=0x30+k[j];
            Data(n);
            j--;
       }
    }
    else if(k[2]>0)
    {
        j = 2;
        Data(0x20);
        Data(0x20);
        while(j!=0)
       {
            n=0x30+k[j];
            Data(n);
            j--;
       }
        
    }
    else
    {
        Data(0x20);
        Data(0x20);
        Data(0x20);
        n=0x30+k[c];
        Data(n);
    }
        
}
void OutputV(unsigned int j)
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
void Data(unsigned char j)
{
    PORTC|=0X08;    // RS=1
    PORTD=j;        
    PORTC|=0X01;    
    PORTC&=~0X01;   
    __delay_ms(10);
}
void Command(unsigned char j)  //RS=RC2 AND Enable=RC0 and datapins PORT D0 to D7 
{
    PORTC&=~0x08;    // RS = 0
    PORTD= j ;      
    PORTC|=0X01;    
    PORTC&=~0X01;   
    __delay_ms(10);
}
