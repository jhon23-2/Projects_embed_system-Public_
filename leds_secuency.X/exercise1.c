/*
 * File:   exercise-1.c
 * Author: jhonatanalmanza
 *
 * Created on September 9, 2025, 11:28 AM
 */
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

// LED patterns
const unsigned char RIGHT_TO_LEFT_PATTERN[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
const unsigned char CENTER_TO_ENDS_PATTERN[4] = {0x18, 0x24, 0x42, 0x81};

// Global state
unsigned char current_animation = 0; // 0=none, 1=RB0, 2=RB1, 3=RB2, 4=RB3
unsigned char anim_index = 0;

// -------------------------
// Run one step of animation
// -------------------------
void handler_animation() {
    switch (current_animation) {
        case 1: // RB0: Left to right
            PORTC = RIGHT_TO_LEFT_PATTERN[anim_index];
            anim_index++;
            if (anim_index >= 8) anim_index = 0;
            __delay_ms(200);
            break;
        case 2: // RB1: Right to left
            PORTC = RIGHT_TO_LEFT_PATTERN[7 - anim_index];
            anim_index++;
            if (anim_index >= 8) anim_index = 0;
            __delay_ms(200);
            break;
        case 3: // RB2: Center to ends
            PORTC = CENTER_TO_ENDS_PATTERN[anim_index];
            anim_index++;
            if (anim_index >= 4) anim_index = 0;
            __delay_ms(200);
            break;
        case 4: // RB3: Ends to center
            PORTC = CENTER_TO_ENDS_PATTERN[3 - anim_index];
            anim_index++;
            if (anim_index >= 4) anim_index = 0;
            __delay_ms(200);
            break;
        default:
            PORTC = 0x00; // LEDs off
            break;
    }
}

// -------------------------
// Listen for button presses
// -------------------------
void listener_buttons() {
    if (RB0 == 0) {
        __delay_ms(50);
        if(RB0 == 0){
            current_animation++;
            anim_index = 0;
            if(current_animation > 4) current_animation = 0;
            while(RB0 == 0); // Wait for button release
        }
    }
}

// -------------------------
// Main program
// -------------------------
void main(void) {
    // Setup for PORTB (buttons)
    ANSELH = 0x00;
    PORTB = 0x00;
    TRISB = 0x01;
    WPUB = 0x00;
    OPTION_REG = 0xFF;
    IOCB = 0x00;
    
    // Setup for PORTC (LEDs)
    PORTC = 0x00;
    TRISC = 0x00;
    
    while (1) {
        listener_buttons();   // check if a button is pressed
        handler_animation();  // run one step of the active animation
    }
}
