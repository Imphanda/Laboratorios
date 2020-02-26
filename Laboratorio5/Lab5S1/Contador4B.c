#include <xc.h>
#include<stdint.h>
#include "Contador4B.h"

void ConfInitC(void){
   //----------------------------------4Mhz------------------------------------
   //Oscilador interno
     OSCCON=0b1100001;
   //-----------------------------PUERTOS--------------------------------------
    
    TRISA = 0;//Salida del Contador
    TRISB = 0b11000000;//Botones 
    
    //---------------------------INTERRUP---------------------------------------
    INTCON= 0b11001000;//Habilitar Interrupciones**
    //Habilitar interrupciones solo en PB6 y 7
    IOCB = 0b11000000;  
    OPTION_REG=0b00000000;//***
    
}

void BotonesS1(void){
    if(PORTBbits.RB7==1&&BanderaSuma==0)//Estado al presionar boton inicio
    {
        BanderaSuma=1;
    }
    if(PORTBbits.RB6==1&&BanderaResta==0)//Estado al presionar boton inicio
    {
        BanderaResta=1;
    }
}

void Funcion4B(void){
    if (Contador>=0b00010000){
        Contador =0;
    }
    return;
}
