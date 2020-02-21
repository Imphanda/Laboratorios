//------------------------------------------------------------------------------
//                                                                             *
//    Filename:      LaboratorioSPI                                            *
//    Fecha:         07/02/2020                                                *
//    Version:       v.1                                                       *
//    Author:        Nancy Alejandra Mazariegos                                *
//    Carnet:        17227                                                     *
//    Description:   FuncionADC para Laboratorio 4                             *
//                                                                             *
//------------------------------------------------------------------------------
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pic16F887.h>
#include "ADC2.h"


void inicioADC1(void){// Se definen los puertos de entrada y salida
    //--------------------------------ADC1--------------------------------------

    ADCON0bits.CHS3 = 1;//PORTB Canal AN10
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS1 = 1;
    ADCON0bits.CHS0 = 0;
    ADCON0bits.GO_DONE =1;
    ADCON0bits.ADON = 1; 
    ANSEL=0;
    ANSELH = 0b00000100;
    
    PIR1bits.ADIF=0;

    //--------------------------------------------------------------------------
}
void inicioADC2(void){// Se definen los puertos de entrada y salida  
    //--------------------------------ADC2--------------------------------------
    ADCON0bits.CHS3 = 1;//PORTB Canal AN12
    ADCON0bits.CHS2 = 1;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS0 = 0;
    ADCON0bits.GO_DONE =1;
    ADCON0bits.ADON = 1; 
    ANSEL=0;
    ANSELH = 0b00010000;
    
    PIR1bits.ADIF=0;
    
    //--------------------------------------------------------------------------
}