/*
 * File: main.c
 * Hello World side by side with I2C module 
 * Microcontroller: PIC16F887
 * Cristal: 20MHz (HS)
 * Jhonattan:dev ;) if this project works to you please left your like to this repo.... ;)
 */
#include <xc.h>
#include <stdbool.h>
#include "i2c.h"
#include "lcd_i2c.h"

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

int main(void) 
{
    I2C_Init_Master(I2C_100KHZ);
    __delay_ms(100);
    
    Lcd_Init();
    __delay_ms(100);
    
    const char *message = "Hello World!";
    char display_buffer[17];
    char direction = 1;  // 1 = Rigth, -1 = Left
    char position = 0;
    
    while(1) 
    {
        Lcd_Clear();
        
        // fill gaps with spaces
        for(unsigned char i = 0; i < 16; i++) {
            display_buffer[i] = ' ';
        }
        
        // Put the message in current pos 
        unsigned char msg_idx = 0;
        for(unsigned char i = position; i < 16 && message[msg_idx] != '\0'; i++) {
            display_buffer[i] = message[msg_idx];
            msg_idx++;
        }
        display_buffer[16] = '\0';
        
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String(display_buffer);
        
        // Move pos
        position += direction;
        
        // Change path 
        if(position <= 0) {
            position = 0;
            direction = 1;  // Change rigth 
        }
        else if(position >= 4) {  // 16 -  message length (12) = 4
            position = 4;
            direction = -1;  // Change rigth
        }
        
        __delay_ms(300);
    }
    
    return 0;
}