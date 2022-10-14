/*
 * File:   om.c
 * Author: lenovo
 *
 * Created on 14 October, 2022, 12:03 AM
 */


// PIC18F458 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = HS         // Oscillator Selection bits (HS oscillator)
#pragma config OSCS = OFF       // Oscillator System Clock Switch Enable bit (Oscillator system clock switch option is disabled (main oscillator is source))

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bit (Brown-out Reset disabled)
#pragma config BORV = 25        // Brown-out Reset Voltage bits (VBOR set to 2.5V)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 128      // Watchdog Timer Postscale Select bits (1:128)

// CONFIG4L
#pragma config STVR = OFF       // Stack Full/Underflow Reset Enable bit (Stack Full/Underflow will not cause Reset)
#pragma config LVP = OFF        // Low-Voltage ICSP Enable bit (Low-Voltage ICSP disabled)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000200-001FFFh) not code protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot Block (000000-0001FFh) not code protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000200-001FFFh) not write protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0001FFh) not write protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000200-001FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from Table Reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0001FFh) not protected from Table Reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ  20000000
unsigned int si();
unsigned int ci();
unsigned int keyvalidation();
unsigned int canreceive();
unsigned int msg[8];

//functions
unsigned int si()
{
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    
}
unsigned int ci()
{
    TRISBbits.RB2=0;
    TRISBbits.RB3=1;
    CANCON |= 0x80;
    while (CANSTAT!=0x00)
    {
        BRGCON1=0xC1;
        BRGCON2=0xAE;
        BRGCON3=0x45;
        CIOCON=0x20;
        CANCON=0x00;
        
    }
}
unsigned int canreceive()
{
    
    CANCON=0x00;
    RXB0SIDH=0x14;//rec
    RXB0SIDL=0x00;
    RXB0DLC=0x08;//Dl
    RXM0SIDH=0x14;//mask
    RXM0SIDL=0x00;
    RXF0SIDH=0x14;//filter
    RXF0SIDL=0x00;
    msg[0]=RXB0D0;
    msg[1]=RXB0D1;
    msg[2]=RXB0D2;
    msg[3]=RXB0D3;
    msg[4]=RXB0D4;
    msg[5]=RXB0D5;
    msg[6]=RXB0D6;
    msg[7]=RXB0D7;
    RXB0CONbits.RXM0=0x01;
    return;
}
unsigned int keyvalidation()
{
    
    unsigned int data=canreceive();
    if(data==0x03)
    {
        
            LATAbits.LA1=1;
            __delay_ms(6000);
            LATAbits.LA1=0;

    }
    if(data==0x04)

    {
        
            LATAbits.LA1=1;
            __delay_ms(6000);
            LATAbits.LA1=0;
        
    }
   if(data==0x05)

    {
       LATAbits.LA1=1; 
    }
}


void main(void)
{
 
    TRISA=0;
    EECON1bits.EEPGD=0;
    EECON1bits.CFGS=1;
    TRISBbits.RB0=0;
    LATA=0;
    si();
    ci();
    keyvalidation();
    return;
}

