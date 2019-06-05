#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Mina.h"
#include "../funciones/Funciones.h"
#include "../entidades/Caja.h"
#include "../entidades/Vagon.h"

struct minaStruct
{
    int posX; //Posicion donde se ubica la mina
    int posY; //Posicion donde se ubica la mina.
    int codItem; //Codigo del item que va a producir.
    int IP; //Intervalo de produccion.
    int seq[5]; //Especificacion de la secuencia de produccion. Siempre serán 5 en total.

    int contadorIntervalos; //Contador interno para tickMina, para saber cuando spawnear una caja
    int contadorProduccion; //Contador interno para tickMina, para saber en que parte de la secuencia de producción se está
    ListaGen lstCajas; //Lista de cajas producidas por la mina y que están en esperando se las retire
};

ptrMina newMina()
{
    ptrMina mina = new minaStruct;
    mina->contadorIntervalos = 0;
    mina->contadorProduccion = 0;
    mina->lstCajas = newListaGen();
    return mina;
}

void delMina(ptrMina mina)
{
    int i;

    for (i=0;i<getSize(mina->lstCajas);i++) delCaja((ptrCaja)getObjeto(mina->lstCajas, i));
    eliminarListaGen(mina->lstCajas);
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

int getContadorIntervalos(ptrMina mina)
{
    return mina->contadorIntervalos;
}

void setContadorIntervalos(ptrMina mina, int contadorIntervalos)
{
    mina->contadorIntervalos = contadorIntervalos;
}

int getContadorProduccion(ptrMina mina)
{
    return mina->contadorProduccion;
}

void setContadorProduccion(ptrMina mina, int contadorProduccion)
{
    mina->contadorProduccion = contadorProduccion;
}

ListaGen getLstCajas(ptrMina mina)
{
    return mina->lstCajas;
}

void setLstCajas(ptrMina mina, ListaGen lstCajas)
{
    mina->lstCajas = lstCajas;
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

void tickMina(ptrMina mina, ptrLocomotora locomotora)
{
    int i;
    int* cantRecursos;
    bool agregado;
    ptrVagon vActual;

    if (mina->contadorIntervalos >= mina->IP)
    {
        if (mina->contadorProduccion >= 5) mina->contadorProduccion = 0;
        if (getSize(mina->lstCajas) < 5) addObjeto(mina->lstCajas, newCaja(mina->codItem, mina->seq[mina->contadorProduccion]));
        mina->contadorIntervalos = 0;
        mina->contadorProduccion++;
    }
    mina->contadorIntervalos++;

    if(getXY(locomotora)[0] == mina->posX && getXY(locomotora)[1] == mina->posY && !listaVacia(mina->lstCajas))
    {
        i = 0;
        agregado = false;
        while(i<getSize(getVagones(locomotora)) && !agregado)
        {
            vActual = (ptrVagon)getObjeto(getVagones(locomotora), i);
            if ((getTipoRecurso(vActual) == mina->codItem || getTipoRecurso(vActual) == 0) &&
                (getCapacidad(vActual) - cantidadTotalLingotes(vActual)) >= getCantidad((ptrCaja)getUltimo(mina->lstCajas)))
            {
                agregado = true;
                addObjeto(getCajas(vActual), getUltimo(mina->lstCajas));
                if (getTipoRecurso(vActual) == 0) setTipoRecurso(vActual, mina->codItem);
                cantRecursos = getCantRecursos(locomotora);
                cantRecursos[mina->codItem-1] = cantRecursos[mina->codItem-1] + getCantidad((ptrCaja)getUltimo(mina->lstCajas));
                delObjeto(mina->lstCajas, getSize(mina->lstCajas)-1);
            }
            i++;
        }
    }
}
