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
unsigned int cantransmit();

//functions

unsigned int si() {
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;

}

unsigned int ci() {
    TRISBbits.RB2 = 0;
    TRISBbits.RB3 = 1;
    CANCON |= 0x80;
    while (CANSTAT != 0x00) {
        BRGCON1 = 0xC1;
        BRGCON2 = 0xAE;
        BRGCON3 = 0x45;
        CIOCON = 0x20;
        CANCON = 0x00;

    }
}

unsigned int cantransmit() {

    CANCON = 0x00; //normal mode
    //TXB0CON=0x77;//arbitration
    //0X50
    TXB0SIDH = 0x10; //8 bit high
    TXB0SIDL = 0x00; // 3 bit low
    TXB0DLC = 0x03; //data length
    //actual data

    TXB0D0 = 0x03;

    TXB0D1 = 0x04;

    TXB0D2 = 0x05;

    TXB0CON = 0x08;
}

unsigned int keyvalidation() {



    if (TXB0D0 == 0x03) {

        LATAbits.LA1 = 1;
        __delay_ms(500);
        LATAbits.LA1 = 0;
        __delay_ms(500);
        LATAbits.LA1 = 1;
        __delay_ms(500);
        LATAbits.LA1 = 0;
        __delay_ms(500);
        LATAbits.LA1 = 1;
        __delay_ms(500);
        LATAbits.LA1 = 0;


    }
    if (TXB0D1 == 0x04) {

        __delay_ms(4000);

        LATAbits.LA1 = 1;
        __delay_ms(500);
        LATAbits.LA1 = 0;
        __delay_ms(500);
        LATAbits.LA1 = 1;
        __delay_ms(500);
        LATAbits.LA1 = 0;
        __delay_ms(500);
        LATAbits.LA1 = 1;
        __delay_ms(500);
        LATAbits.LA1 = 0;
        __delay_ms(500);
        LATAbits.LA1 = 1;
        __delay_ms(500);
        LATAbits.LA1 = 0;
        __delay_ms(500);
        LATAbits.LA1 = 1;
        __delay_ms(500);
        LATAbits.LA1 = 0;
        __delay_ms(500);
        LATAbits.LA1 = 1;
        __delay_ms(500);
        LATAbits.LA1 = 0;

    }


    if (TXB0D2 == 0x05) {
        __delay_ms(8000);
        LATAbits.LA1 = 1;
    }
    while (1);
}

void main(void) {

    TRISA = 0;
    TRISBbits.RB0 = 0;
    LATA = 0;
    si();
    ci();
    cantransmit();
    keyvalidation();
    return;
}

