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

const unsigned char GRAY_CODE[5] = {
    0x00, // Decimal 0: Gray 000 -> 0000
    0x01, // Decimal 1: Gray 001 -> 0001
    0x03, // Decimal 2: Gray 011 -> 0011
    0x02, // Decimal 3: Gray 010 -> 0010
    0x06 // Decimal 4: Gray 110 -> 0110
};

unsigned char counter = 0;

void display_gray_code(unsigned char decimal_value) {
    PORTD = GRAY_CODE[decimal_value];
    __delay_ms(1000);
}

int main(void) {
    // Configure PORTD for LEDs (4 LEDs connected to RD0, RD1, RD2, RD3)
    PORTD = 0x00; // Initialize all LEDs OFF
    TRISD = 0x00; // Set PORTD as OUTPUT

    while (1) {
        // Display Binary code first, then Gray code
        display_gray_code(counter);

        // Move to next number in sequence
        counter++;

        // Reset counter after reaching maximum (decimal 4)
        if (counter > 4) {
            counter = 0;
        }
    }

    return 0;
}