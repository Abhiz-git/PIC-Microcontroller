
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
void OutINC(unsigned int j);
void OutDis(unsigned int k);
void Command(unsigned char);
void init();
void Keys();

unsigned char Dis1[17]={"BATT VOLT:"};
unsigned char DisH[17]={"BATT HIGH"};
unsigned char DisL[17]={"BATT LOW"};
unsigned char DisN[17]={"BATT NORMAL"};

unsigned char n,i,x,val,dot,a[10];
unsigned int  d4,d3,d2,d1,j=0,k=0,m;

void main()
{
    dot='.';
    init();
    while(1)
    {
        Keys();
    }
}

void init()
{
    TRISC=0X00;
    TRISB=0XF0;
    TRISD=0X00;
    OPTION_REG&=0X7F;
    
    Command(0x35);
    __delay_ms(21);
    Command(0x35);
    __delay_ms(21);
    Command(0x35);
    __delay_ms(21);
    Command(0x38);
    __delay_ms(21);
    Command(0x06);         // Cursor shift from Left to Right
    __delay_ms(21);
    Command(0x0C);         // Display ON, Cursor OFF
    __delay_ms(21);
    Command(0x01);         // Clear Screen
    __delay_ms(21);
}
void Keys()
{
    val=PORTB&=0xF0;
    switch(val)
    {
        case 0xE0:  Command(0x80);
                    for(i=0;i<=9;i++)
                    {
                        Data(Dis1[i]);    // Displays " BATT VOLT: " 
                    }
                    OutINC(175);          // Displays " 17.5 " 
                    Command(0xC0);
                    for(i=0; i<17; i++)           // bASE ADDRESS OF array [DisL]
                    {
                        Data(DisL[i]);
                    }
                    j=175;
                    break;
              
        case 0xD0:  j++;
                    if(j<155 || j>225)
                    {
                        break;
                    }
                    OutINC(j);                  
                        if(j>175 && j<=205)
                        {
                            Command(0xC0);
                            for(i=0; i<12; i++)
                                Data(DisN[i]);                      
                        }
                        else if(j>205)
                        {
                            Command(0xC0);
                            for(i=0; i<12; i++)
                                Data(DisH[i]);
                        }
                        else if(j<=175 && j>=155 )
                        {
                            Command(0xC0);
                            for(i=0; i<12; i++)
                                Data(DisL[i]);                      
                        }            
                    break;
        
        case 0xB0:  j--;                    
                    if(j<155 || j>225)
                    {
                        break;
                    }
                    OutINC(j);
                        if(j<=175 && j>=155 )
                        {
                            Command(0xC0);
                            for(i=0; i<12; i++)
                                Data(DisL[i]);                      
                        }                          
                        else if(j>175 && j<=205)
                        {
                            Command(0xC0);
                            for(i=0; i<12; i++)
                                Data(DisN[i]);                      
                        }
                        else if(j>205)
                        {
                            Command(0xC0);
                            for(i=0; i<12; i++)
                                Data(DisH[i]);
                        }
                    break;
        
        case 0x70:  j=155;
                    OutINC(j);
                    Command(0xC0);
                    for(i=0; i<12; i++)
                       Data(DisL[i]);
                    break;                   
    }
}
void Data(unsigned char x)
{
    PORTC|=0X08;    // RS=1
    PORTD=x;        //Data set to PORTD
    PORTC|=0X01;    //Enable =1
    PORTC&=~0X01;   //PORTC&=0xFE Enable =0
    __delay_ms(21);
}
void Command(unsigned char x)
{ 
    PORTC&=0xF7;    // RS = 0
    PORTD= x ;      //Data set to PORTD
    PORTC|=0X01;    //Enable =1
    PORTC&=~0X01;   //Enable =0
    __delay_ms(21);
}
void OutINC(unsigned int j)
{
    d4=(unsigned char) (j/100);
    d3=(unsigned char) ((j-(d4*100))/10);
    d2=(unsigned char) (j-(d4*100)-(d3*10));
    
    Command(0x8B);  // display tens
    Data(0x30+d4);
    Command(0x8C);  // display units
    Data(0x30+d3);
    Command(0x8D);  // display dot
    Data(dot);
    Command(0x8E);  // display floating val
    Data(0x30+d2);
}