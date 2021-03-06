//------------------------------------------------------------------------------
//                                                                             *
//    Filename:      LaboratorioSPI                                            *
//    Fecha:         07/02/2020                                                *
//    Version:       v.1                                                       *
//    Author:        Nancy Alejandra Mazariegos                                *
//    Carnet:        17227                                                     *
//    Description:   Laboratorio 4                                             *
//                                                                             *
//------------------------------------------------------------------------------


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
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pic16F887.h>
#include "ADC2.h"
#include "SPIL4.h"
#define _XTAL_FREQ 4000000//Reloj interno 8Mhz

void SetUpL4S(void);

void __interrupt() isr(void){
   if(SSPIF == 1){
          spiWrite(Potenciometro1);
//        spiWrite(Potenciometro2);
        SSPIF = 0;
    }
}

void mainM(void){
    SetUpL4S();
    while(1){
        inicioADC1();
        Potenciometro1=ADRESH;
        Potenciometro1=Potenciometro1<<8;
        __delay_ms(50);
        inicioADC2();
        Potenciometro2=ADRESH;
        Potenciometro2=Potenciometro2<<8;
        __delay_ms(50);
    }
}

void SetUpL4S(void){//Solo se realizan una vez
    //----------------------------------ADC-------------------------------------
    //El esclavo realiza la lectura del Potenciometro Siempre
    ADCON0bits.ADCS1 = 0;
    ADCON0bits.ADCS0 =1;
    ADCON1bits.ADFM=0;
    ADCON1bits.VCFG0=0;
    ADCON1bits.VCFG1=0;//Justificado izquierda
    //---------------------------INTERRUP---------------------------------------
    INTCON= 0b11101100;//Habilitar Interrupciones**
    PIE1bits.ADIE=1;
    PIR1bits.ADIF=0;
    IOCB = 0b00000111;
    //-----------------------------PUERTOS--------------------------------------
    TRISB = 0b00000011;//Potenciometro
    TRISA = 0b00100000;//Indicacion de Esclavo
}