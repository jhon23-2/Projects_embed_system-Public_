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
#define TIEMPO 10

const unsigned char DIGITS[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
unsigned char count = 0;
int value = 0;
unsigned char state = 0; // 0 paused , 1 started

void show_numbers(int val) {
    int thousands = 0;
    int hundreds = 0;
    int tens = 0;
    int units = 0;
    
    // Extract each digit
    thousands = (val / 1000) % 10;
    hundreds = (val / 100) % 10;
    tens = (val / 10) % 10;
    units = val % 10;
    
    // Display units (rightmost display)
    PORTC = DIGITS[units];
    PORTD = 0x08;  // Enable display 4 (rightmost)
    __delay_ms(TIEMPO);
    PORTD = 0x00;
    
    // Display tens
    PORTC = DIGITS[tens];
    PORTD = 0x04;  // Enable display 3
    __delay_ms(TIEMPO);
    PORTD = 0x00;
    
    // Display hundreds
    PORTC = DIGITS[hundreds];
    PORTD = 0x02;  // Enable display 2
    __delay_ms(TIEMPO);
    PORTD = 0x00;
    
    // Display thousands (leftmost display)
    PORTC = DIGITS[thousands];
    PORTD = 0x01;  // Enable display 1 (leftmost)
    __delay_ms(TIEMPO);
    PORTD = 0x00;
}

void listener_btns() {
    // Button 1 START and RENAUDER 
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
    // set up PORTC displays 
    PORTC = 0x00;
    TRISC = 0x00;
    // set up PORTD 7404 logic
    PORTD = 0x00;
    TRISD = 0x00;
    // set up PORTA buttons
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
                if (value == 10000) {  // Changed to 10000 for 4-digit display
                    value = 0;
                }
            }
        }
    }
    return 0;
}