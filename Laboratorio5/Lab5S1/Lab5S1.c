//------------------------------------------------------------------------------
//                                                                             *
//    Filename:      Lab5S1.c                                                  *
//    Fecha:         25/02/2020                                                *
//    Version:       v.1                                                       *
//    Author:        Nancy Alejandra Mazariegos                                *
//    Carnet:        17227                                                     *
//    Description:   Laboratorio 5                                             *
//                                                                             *
//------------------------------------------------------------------------------
// PIC16F887 Configuration Bit Settings

//C�digo del Esclavo 1 I2C

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 4000000//Reloj interno 4Mhz
#include<stdint.h>
#include "Contador4B.h"
uint8_t Contador;
uint8_t BanderaSuma;
uint8_t BanderaResta;

void __interrupt() isr(void){//direccion 0x04 siempre en la interrupcion
    if(RBIF == 1){
        
    //--------------------------SUMA-------------------------------------------
        //Condiciones para la interrupcion
    if (PORTBbits.RB7==0&&BanderaSuma==1){
        Contador++;//realiza la suma
        BanderaSuma=0;//apaga la bandera
        Funcion4B();
        RBIF = 0;
    }
    
    
    //-----------------------RESTA---------------------------------------------
    else if (PORTBbits.RB6==0&&BanderaResta==1){
        Contador--;//realiza la resta
        BanderaResta=0;//apaga la bandera
        Funcion4B();
        RBIF = 0;
    }
    else{
        RBIF =0;
    }
    }
}

void main(void){
    //--------------------------------VAL INI-----------------------------------
    //Set de variables en 0 al inicio
    ConfInitC();
    Contador =0;
    BanderaSuma =0;
    BanderaResta =0;
    
    while(1){
        
        BotonesS1();
        //El valor del contador se despliega al Puerto A
        PORTA=Contador;
        
    }    
        
}



