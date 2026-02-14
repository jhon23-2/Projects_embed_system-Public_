/*
 * File: main.c
 * Reloj Digital con LCD I2C
 * Microcontrolador: PIC16F887
 * Cristal: 20MHz (HS)
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "i2c.h"
#include "lcd_i2c.h"

// ===== CONFIGURACIÓN DEL PIC16F887 =====
#pragma config FOSC = HS        // Oscilador HS (cristal 20MHz)
#pragma config WDTE = OFF       // Watchdog Timer deshabilitado
#pragma config PWRTE = OFF      // Power-up Timer deshabilitado
#pragma config MCLRE = ON       // MCLR habilitado
#pragma config CP = OFF         // Protección de código deshabilitada
#pragma config CPD = OFF        // Protección de datos deshabilitada
#pragma config BOREN = OFF      // Brown-out Reset deshabilitado
#pragma config IESO = OFF       // Internal/External Switchover deshabilitado
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor deshabilitado
#pragma config LVP = OFF        // Low Voltage Programming deshabilitado
#pragma config DEBUG = OFF      // Debug deshabilitado

#define _XTAL_FREQ 20000000

// Global variables
unsigned char hora = 7;
unsigned char minuto = 1;
unsigned char segundos = 0;
bool is_pm = false;  // false = a.m., true = p.m.
char texto_hora[20];

int main(void) 
{
    I2C_Init_Master(I2C_100KHZ);
    __delay_ms(100);
    
    Lcd_Init();
    __delay_ms(100);
    
    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("loading...");
    __delay_ms(1000);
    
    while(1) 
    {
        Lcd_Clear();
        
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String("Everything is good ;)");
        
        segundos++;
        if(segundos >= 60) 
        {
            segundos = 0;
            minuto++;
            
            if(minuto >= 60) 
            {
                minuto = 0;
                hora++;
                
                if(hora > 12) 
                {
                    hora = 1;
                }
                
                if(hora == 12 && minuto == 0) 
                {
                    is_pm = !is_pm;
                }
            }
        }
        
        Lcd_Set_Cursor(2, 1);
        sprintf(texto_hora, "%02d:%02d:%02d %s", 
                hora, minuto, segundos, is_pm ? "PM" : "AM");
        Lcd_Write_String(texto_hora);
        
        __delay_ms(1000);
    }
    
    return 0;
}