//------------------------------------------------------------------------------
//                                                                             *
//    Filename:      Lab5S2.c                                                  *
//    Fecha:         25/02/2020                                                *
//    Version:       v.1                                                       *
//    Author:        Nancy Alejandra Mazariegos                                *
//    Carnet:        17227                                                     *
//    Description:   Laboratorio 5                                             *
//                                                                             *
//------------------------------------------------------------------------------
// PIC16F887 Configuration Bit Settings

//Código del Esclavo 2 I2C

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
uint8_t Control;
uint8_t Registro;

void ConfInitADC(void);


void main(void){
    ConfInitADC();
    while(1){
        ADCON0bits.GO_DONE=1;
        while(ADCON0bits.GO_DONE==1);
        Registro=ADRESH;
        PORTA=Registro;
        PORTDbits.RD2=1;
        }

}


void ConfInitADC(void){// Se definen los puertos de entrada y salida
    //----------------------------------4Mhz------------------------------------
    OSCCON=0b1100001;
    
    //--------------------------------ADC --------------------------------------
    ADCON0bits.ADCS1 = 0;
    ADCON0bits.ADCS0 =1;
    ADCON0bits.CHS3 = 1;//PORTB 2
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS0 = 0;
    ADCON0bits.GO_DONE =1;
    ADCON0bits.ADON = 1; //ADC Puerto de Entrada AN8
    ADCON1bits.ADFM=0;
    ADCON1bits.VCFG0=0;
    ADCON1bits.VCFG1=0;//Justificado izquierda
    ANSEL=0;
    ANSELH = 0b00000001;
    
    
    //-----------------------------PUERTOS--------------------------------------
    
    TRISA = 0;//Verificar Funcionamiento
    TRISB = 0b00000100;//Potenciometro
    TRISD=0;
    
    //---------------------------INTERRUP---------------------------------------
//    INTCON= 0b11000000;//Habilitar Interrupciones para ADC
//    PIE1bits.ADIE=1;
//    PIR1bits.ADIF=0;
//    IOCB = 0b00000100;
    OPTION_REG=0b00000000;//***

    PORTA=0;
    PORTD=0;

}