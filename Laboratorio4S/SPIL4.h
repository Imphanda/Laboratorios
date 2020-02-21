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

//Seccion adquirida del Ejemplo de Clase, con modificicaciones en estructura----

#ifndef SPIL4_H
#define	SPIL4_H

#include <xc.h> 
#include <stdio.h>
#include <stdint.h>
#include <pic16f887.h>

//Arreglo para escoger Modo Esclavo o Maestro
typedef enum 
{
    SPI_MASTER_OSC_DIV4  = 0b00100000,
    SPI_MASTER_OSC_DIV16 = 0b00100001,
    SPI_MASTER_OSC_DIV64 = 0b00100010,
    SPI_MASTER_TMR2      = 0b00100011,
    SPI_SLAVE_SS_EN      = 0b00100100,
    SPI_SLAVE_SS_DIS     = 0b00100101
}ModoSPI;

//Arreglo para indicar el estado del envio de Datos
typedef enum
{
    SPI_DATA_SAMPLE_MIDDLE   = 0b00000000,
    SPI_DATA_SAMPLE_END      = 0b10000000
}ProgresoData;

//Set del SCK
typedef enum
{
    SPI_CLOCK_IDLE_HIGH  = 0b00010000,
    SPI_CLOCK_IDLE_LOW   = 0b00000000        
}EstadoReloj;

//Indica si la data esta siendo recibida o si el receptor esta en descanso
//Para modo asincrono
typedef enum
{
    SPI_IDLE_2_ACTIVE    = 0b00000000,
    SPI_ACTIVE_2_IDLE    = 0b01000000
}ActivoSPI;


void SetSPI(ModoSPI, ProgresoData, EstadoReloj, ActivoSPI);
void spiWrite(char);
unsigned spiDataReady();
char spiRead();

#endif	/* SPIL4_H */

