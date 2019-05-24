#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Mina.h"
#include "../funciones/Funciones.h"

struct minaStruct
{
    int posX; //Posicion donde se ubica la mina
    int posY; //Posicion donde se ubica la mina.
    int codItem; //Codigo del item que va a producir.
    int IP; //Intervalo de produccion.
    int seq[5]; //Especificacion de la secuencia de produccion. Siempre serán 5 en total.
};

ptrMina newMina()
{
    ptrMina mina = new minaStruct;
    return mina;
}

void delMina(ptrMina mina)
{
    delete mina;
}

int getPosX(ptrMina mina)
{
    return mina->posX;
}

void setPosX(ptrMina mina, int posX)
{
    mina->posX = posX;
}

int getPosY(ptrMina mina)
{
    return mina->posY;
}

void setPosY(ptrMina mina, int posY)
{
    mina->posY = posY;
}

int getCodItem(ptrMina mina)
{
    return mina->codItem;
}

void setCodItem(ptrMina mina, int codItem)
{
    mina->codItem = codItem;
}

int getIP(ptrMina mina)
{
    return mina->IP;
}

void setIP(ptrMina mina, int IP)
{
    mina->IP = IP;
}

int* getSeq(ptrMina mina)
{
    return mina->seq;
}

void setSeq(ptrMina mina, int seq[])
{
    int i;
    for (i=0;i<5;i++) mina->seq[i] = seq[i];
}

//posX;posY;codItem;IP;seq1;seq2;seq3;seq4;seq5
void leerLineaMina(FILE* fMina, ptrMina mina)
{
    char buffer, lectura[80];
    char* valor;
    int i;
    int iniCampo=0, finCampo=0;
    int seq[5];

    for(i=0;i<80;i++) lectura[i]=0;
    i=0;
    buffer=0;
    fseek(fMina, ftell(fMina), 0);
    while (buffer!=10 && fread(&buffer,1,1,fMina)==1)
    {
        if(buffer!=10) lectura[i] = buffer;
        i++;
    }

    finCampo = posEnArray(lectura, iniCampo,';');
    valor = subString(lectura,iniCampo,finCampo);
    setPosX(mina,atoi(valor));
    delete valor;

    iniCampo=finCampo+1;
    finCampo = posEnArray(lectura, iniCampo,';');
    valor = subString(lectura,iniCampo,finCampo);
    setPosY(mina,atoi(valor));
    delete valor;

    iniCampo=finCampo+1;
    finCampo = posEnArray(lectura, iniCampo,';');
    valor = subString(lectura,iniCampo,finCampo);
    setCodItem(mina,atoi(valor));
    delete valor;

    iniCampo=finCampo+1;
    finCampo = posEnArray(lectura, iniCampo,';');
    valor = subString(lectura,iniCampo,finCampo);
    setIP(mina,atoi(valor));
    delete valor;

    for (i=0;i<5;i++)
    {
        iniCampo=finCampo+1;
        finCampo = posEnArray(lectura, iniCampo,';');
        valor = subString(lectura,iniCampo,finCampo);
        seq[i] = atoi(valor);
        delete valor;
    }
    setSeq(mina,seq);
}
