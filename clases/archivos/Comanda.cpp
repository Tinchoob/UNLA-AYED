#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Comanda.h"

struct comandaStruct
{
    int oro;
    int plata;
    int bronce;
    int platino;
    int roca;
    int carbon;
};

ptrComanda newComanda()
{
    ptrComanda comanda = new comandaStruct;
    return comanda;
}

void delComanda(ptrComanda comanda)
{
    delete comanda;
}

int getOro(ptrComanda comanda)
{
    return comanda->oro;
}

void setOro(ptrComanda comanda, int oro)
{
    comanda->oro = oro;
}

int getPlata(ptrComanda comanda)
{
    return comanda->plata;
}

void setPlata(ptrComanda comanda, int plata)
{
    comanda->plata = plata;
}

int getBronce(ptrComanda comanda)
{
    return comanda->bronce;
}

void setBronce(ptrComanda comanda, int bronce)
{
    comanda->bronce = bronce;
}

int getPlatino(ptrComanda comanda)
{
    return comanda->platino;
}

void setPlatino(ptrComanda comanda, int platino)
{
    comanda->platino = platino;
}

int getRoca(ptrComanda comanda)
{
    return comanda->roca;
}

void setRoca(ptrComanda comanda, int roca)
{
    comanda->roca = roca;
}

int getCarbon(ptrComanda comanda)
{
    return comanda->carbon;
}

void setCarbon(ptrComanda comanda, int carbon)
{
    comanda->carbon = carbon;
}

void cargarComanda(ptrComanda comanda)
{
    FILE* fComanda;
    char lectura[20];
    int i, j;

    fComanda = fopen("comanda.txt","r");
    for(j=0;j<6;j++)
    {
        for (i=0;i<20;i++) lectura[i]=0;
        leerLineaComanda(lectura, fComanda);
        if (strstr(lectura,"oro")) setOro(comanda, atoi(strstr(lectura,";")+1));
        else if (strstr(lectura,"plata")) setPlata(comanda, atoi(strstr(lectura,";")+1));
        else if (strstr(lectura,"bronce")) setBronce(comanda, atoi(strstr(lectura,";")+1));
        else if (strstr(lectura,"platino")) setPlatino(comanda, atoi(strstr(lectura,";")+1));
        else if (strstr(lectura,"roca")) setRoca(comanda, atoi(strstr(lectura,";")+1));
        else if (strstr(lectura,"carbon")) setCarbon(comanda, atoi(strstr(lectura,";")+1));
    }
    fclose(fComanda);
}

void leerLineaComanda(char* destino, FILE* fComanda)
{
    char buffer;
    int i;

    i=0;
    buffer=0;
    while (buffer!=10 && fread(&buffer,1,1,fComanda)==1)
    {
        if(buffer!=10) destino[i] = buffer;
        i++;
    }
}
