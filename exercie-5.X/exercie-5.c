#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <xc.h>
#include "lcd.h"

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

// Variables
unsigned char hora = 7;
unsigned char minuto = 1;
bool is_pm = false; // 'false' for a.m., 'true' for p.m.

char texto_hora[12]; // Buffer for hour 

int main ( void )
{
    LCD lcd = { &PORTC, 2, 3, 4, 5, 6, 7 }; // PORTC, RS, EN, D4, D5, D6, D7

    LCD_Init(lcd);

    while(1)
    {
        // 1. Show the city name in the first line 
        LCD_Clear();
        LCD_Set_Cursor(0, 0);
        LCD_putrs("Santa Marta");

        // 2. increase hour
        minuto++;
        if (minuto >= 60)
        {
            minuto = 0;
            hora++;
            if (hora > 12)
            {
                hora = 1; // 13:00 become in 1:00
            }
            if (hora == 12 && minuto == 0) 
            {
                is_pm = !is_pm; // Change state(a.m. <-> p.m.)
            }
        }

        // 3. Format both text and hour and show them  
        LCD_Set_Cursor(1, 0);
        sprintf(texto_hora, "Hora: %02d:%02d %s", hora, minuto, is_pm ? "p.m." : "a.m.");
        LCD_putrs(texto_hora);

        // 4. Wait
        __delay_ms(500); 
    }

    return 0;
}