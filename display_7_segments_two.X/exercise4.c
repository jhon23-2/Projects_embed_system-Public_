#include <xc.h>

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = ON
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config FCMEN = OFF
#pragma config LVP = OFF
#pragma config DEBUG = OFF

#define _XTAL_FREQ 20000000
#define TIEMPO 40

// Matriz de dígitos para displays de ánodo común
const unsigned char DIGITS[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

unsigned char count = 0;
int value = 0;
unsigned char state = 1; // 0 paused , 1 started

void show_numbers(int val) {
    int dec = 0;
    int uni = 0;
    
    dec = (val/10);
    uni = (val%10);

    PORTC = DIGITS[uni];
    PORTD = 0xFD; // 1111 1101b - Pone a D1 en LOW
    __delay_ms(TIEMPO);
    
    PORTC = DIGITS[dec];
    PORTD = 0xFE; // 1111 1110b - Pone a D0 en LOW
    __delay_ms(TIEMPO);
}

void listener_btns() {
    // Button 1 START
    if (RA0 == 0) {
        __delay_ms(50);
        if (RA0 == 0) {
            state = 1;
            while (RA0 == 0);
        }
    }

    // Button 2 PAUSE
    if (RA1 == 0) {
        __delay_ms(50);
        if (RA1 == 0) {
            state = 0;
            while (RA1 == 0);
        }
    }

    // Button 3 RESET
    if (RA2 == 0) {
        __delay_ms(50);
        if (RA2 == 0) {
            value = 0;
            count = 0;
            state = 0;
            while (RA2 == 0);
        }
    }
}

int main(void) {
    // set up PORTC
    PORTC = 0x00;
    TRISC = 0x00;

    // set up PORTD
    PORTD = 0x00;
    TRISD = 0x00;

    // set up PORTA
    ANSEL = 0x00;
    PORTA = 0x00;
    TRISA = 0x07;

    while (1) {
        listener_btns();
        show_numbers(value);

        if (state) {
            count++;
            if (count == 15) {
                count = 0;
                value++;

                if (value == 100) {
                    value = 0;
                }
            }
        }
    }
    return 0;
}