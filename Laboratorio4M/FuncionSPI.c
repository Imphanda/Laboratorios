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
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "SPIL4.h"

void SetSPI(ModoSPI ModoS, ProgresoData ProgresoS, EstadoReloj RelojS, ActivoSPI nActivo)
{
    TRISC5 = 0;
    
    if(ModoS & 0b00000100) //Verifica modo Esclavo
    {
        SSPSTAT = nActivo;
        TRISC3 = 1;
    }
    else              //En caso contrario, verifica modo Maestro
    {
        SSPSTAT = ProgresoS | nActivo;
        TRISC3 = 0;
    }
    
        SSPCON = ModoS | RelojS;
}

static void spiCompleteData()
{
    while (!SSPSTATbits.BF); //Espera a que la data se reciba por completo
}

void spiWrite(char dato)  //Envia la Data al SSPBUF
{
    SSPBUF = dato;
}

unsigned spiDataReady() //Verifica que la data ya se puede leer
{
    if(SSPSTATbits.BF)
        return 1;
    else
        return 0;
}

char spiRead() //Lee el dato recibido
{
    spiCompleteData();        // wait until the all bits receive
    return(SSPBUF); // read the received data from the buffer
}

