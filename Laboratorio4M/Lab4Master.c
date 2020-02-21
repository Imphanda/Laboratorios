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
#include "SPIL4.h"
#include "USARTL4.h"
#define _XTAL_FREQ 4000000//Reloj interno 8Mhz
#define Baud_rate 9600
uint8_t Pot1;
uint8_t Pot2;
uint8_t ContadorS;
uint8_t Fallo;
uint8_t ContadorR;
uint8_t Contador;

void SetUpL4M(void);

void main(void){
    SetUpL4M();
    unsigned char Controluart;
    while(1){
        PORTA=Contador;
        Controluart=recibe_caracter_usart();
        switch (Controluart){
            case '1':
                ++Contador;
                break;
            case '2':
                --Contador;
                break;
            case '3':
                PORTD=0;
                break;
            case '4':
                PORTD=0;
                break;
            case '5':
                Contador=20;
                break;
        }
        return;
        
    }
    
}

void SetUpL4M(void){//Solo se realizan una vez
    //-----------------------------PUERTOS--------------------------------------
    TRISA = 0;//Contador
    TRISC =0;
    TRISCbits.TRISC7=1;//RX como una entrada digital
    TRISCbits.TRISC6=0;//TX como una salida digital
    PORTA =0;
    PORTCbits.RC2=1;
    
    //---------------------------INTERRUP---------------------------------------
    INTCON= 0b11101100;//Habilitar Interrupciones**
    PIE1bits.RCIE=1;
    PIE1bits.TXIE=1;
    IOCB = 0b00000111;
    
    //Configuracion maestro tomada del ejemplo de clase-------------------------
    //Set del Maestro, Activa la recepcion de datos, recibe la data completa al verificar
    
//    SetSPI(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    
    
    //-----------------------------UART-----------------------------------------
    TXSTA=0b00100110;// 8bits, transmisión habilitada, asíncrono, alta velocidad
    RCSTA=0b10010000;//habilitado el USART PIC, recepción 8 bits,habilitada, asíncrono
    SPBRG=25;//9600 Baud Rate a 4Mhz
    Contador= 125;
}