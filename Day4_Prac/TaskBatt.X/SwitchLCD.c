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

void Data(unsigned char);
void Output(unsigned int j);
void Command(unsigned char);
void init();
void Keys();
unsigned char Dis[30]={"SET SPD:     rpm"};
unsigned char i,x,val;
unsigned int  d4,d3,d2,d1,j=0;

void main()
{
    TRISC=0X00;
    TRISB=0XF0;
    TRISD=0X00;
    init();
    while(1)
    {
        Keys();
    }
}

void init()
{
    OPTION_REG&=0X7F;
    Command(0x38);
    __delay_ms(100);
    Command(0x38);
    __delay_ms(100);
    Command(0x38);
    __delay_ms(100);
    Command(0x38);
    __delay_ms(100);
    Command(0x0C);
    __delay_ms(100);
    Command(0x01);
    __delay_ms(100);
    j=0;
}
void Keys()
{
    val=PORTB&=0xF0;
    switch(val)
    {
        case 0xE0:  Command(0x80);
                    for(i=0;i<8;i++)
                    {
                        Data(Dis[i]);
                    }
                    Command(0x8D);
                    for(i=13;i<=15;i++)
                    {
                        Data(Dis[i]);
                    }
                    Command(0x89);
                    Output(j);
                    break;
              
        case 0xD0:  j++;
                    Command(0x89);
                    if(j>5000)
                    {
                        j=5000;
                    }
                    Output(j);
                    break;
        
        case 0xB0:  j--;
                    Command (0x89);
                    if(j<1)
                        j=1;
                    Output(j);
                    break;
        
        case 0x70:  j=0;
                    Command(0x89);
                    Output(j);
                    break;                   
    }
}
void Data(unsigned char j)
{
    PORTC|=0X08;    // RS=1
    PORTD=j;        //Data set to PORTD
    PORTC|=0X01;    //Enable =1
    PORTC&=~0X01;   //PORTC&=0xFE Enable =0
    __delay_ms(100);
}
void Command(unsigned char j)  //RS=RC2 AND Enable=RC0 and datapins PORT D0 to D7 
{
    PORTC&=0xF7;    // RS = 0
    PORTD= j ;      //Data set to PORTD
    PORTC|=0X01;    //Enable =1
    PORTC&=~0X01;   //Enable =0
    __delay_ms(100);
}
void Output(unsigned int i)
{
    d4=(unsigned char) (i/1000);
    d3=(unsigned char) ((i-(d4*1000))/100);
    d2=(unsigned char) ((i-(d4*1000)-(d3*100))/10);
    d1=(unsigned char) (i-(d4*1000)-(d3*100)-(d2*10));
    
    Command(0x89);
    //for(i=0; i<4; i++)
    //{
        Data(0x30+d4);
        Command(0x8A);
        Data(0x30+d3);
        Command(0x8B);
        Data(0x30+d2);
        Command(0x8C);
        Data(0x30+d1);
   // }
}