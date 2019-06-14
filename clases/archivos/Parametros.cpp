#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "Parametros.h"

struct parametrosStruct
{
    long s; //Segundos que dura un intervalo
    long p; //Cantidad maxima que puede pedir un bandido
    long a; //Posiciones para definir el area de Ataque de un bandido
    long posXE; //Posici�n x de la estacion
    long posYE; //Posici�n y de la estacion
    long im; //Intervalo m�ximo para generaci�n de monedas
    long vm; //Intervalos m�ximos de vida de una moneda
    long ib; //M�xima cantidad de intervalos para la aparici�n de bandidos
    long vb; //Tiempo m�ximo de vida de un bandido
    long ip; //Intervalos entre producciones de las minas
    long tx; //Tama�o en X del mapa
    long ty; //Tama�o en Y del mapa
};

ptrParametros newParametros()
{
    ptrParametros parametros = new parametrosStruct;
    return parametros;
}

void delParametros(ptrParametros parametros)
{
    delete parametros;
}

long getS(ptrParametros parametros)
{
    return parametros->s;
}

void setS(ptrParametros parametros, long s)
{
    parametros->s = s;
}

long getP(ptrParametros parametros)
{
    return parametros->p;
}

void setP(ptrParametros parametros, long p)
{
    parametros->p = p;
}

long getA(ptrParametros parametros)
{
    return parametros->a;
}

void setA(ptrParametros parametros, long a)
{
    parametros->a = a;
}

long getPosXE(ptrParametros parametros)
{
    return parametros->posXE;
}

void setPosXE(ptrParametros parametros, long posXE)
{
    parametros->posXE = posXE;
}

long getPosYE(ptrParametros parametros)
{
    return parametros->posYE;
}

void setPosYE(ptrParametros parametros, long posYE)
{
    parametros->posYE = posYE;
}

long getIM(ptrParametros parametros)
{
    return parametros->im;
}

void setIM(ptrParametros parametros, long im)
{
    parametros->im = im;
}

long getVM(ptrParametros parametros)
{
    return parametros->vm;
}

void setVM(ptrParametros parametros, long vm)
{
    parametros->vm = vm;
}

long getIB(ptrParametros parametros)
{
    return parametros->ib;
}

void setIB(ptrParametros parametros, long ib)
{
    parametros->ib = ib;
}

long getVB(ptrParametros parametros)
{
    return parametros->vb;
}

void setVB(ptrParametros parametros, long vb)
{
    parametros->vb = vb;
}

long getIP(ptrParametros parametros)
{
    return parametros->ip;
}

void setIP(ptrParametros parametros, long ip)
{
    parametros->ip = ip;
}

long getTX(ptrParametros parametros)
{
    return parametros->tx;
}

void setTX(ptrParametros parametros, long tx)
{
    parametros->tx = tx;
}

long getTY(ptrParametros parametros)
{
    return parametros->ty;
}

void setTY(ptrParametros parametros, long ty)
{
    parametros->ty = ty;
}

void cargarParametros(ptrParametros parametros)
{
    FILE* fParametros;
    char lectura[20];
    int i,j;

    fParametros = fopen("parametros.txt","r");
    for(j=0;j<10;j++)
    {
        for (i=0;i<20;i++) lectura[i]=0;
        leerLineaParametros(lectura, fParametros);
        if (strstr(lectura, "S=")) setS(parametros, atoi(strstr(lectura,"=")+1));
        else if (strstr(lectura,"\nP=")) setP(parametros, atoi(strstr(lectura,"=")+1)); //del enter al igual, sino se puede confundir con IP
        else if (strstr(lectura,"A=")) setA(parametros, atoi(strstr(lectura,"=")+1));
        else if (strstr(lectura,"posXE=")) setPosXE(parametros, atoi(strstr(lectura,"=")+1));
        else if (strstr(lectura,"posYE=")) setPosYE(parametros, atoi(strstr(lectura,"=")+1));
        else if (strstr(lectura,"IM=")) setIM(parametros, atoi(strstr(lectura,"=")+1));
        else if (strstr(lectura,"VM=")) setVM(parametros, atoi(strstr(lectura,"=")+1));
        else if (strstr(lectura,"IB=")) setIB(parametros, atoi(strstr(lectura,"=")+1));
        else if (strstr(lectura,"VB=")) setVB(parametros, atoi(strstr(lectura,"=")+1));
        else if (strstr(lectura,"IP=")) setIP(parametros, atoi(strstr(lectura,"=")+1));
        //else if (strstr(lectura,"TX=")) setTX(parametros, atoi(strstr(lectura,"=")+1));
        //else if (strstr(lectura,"TY=")) setTY(parametros, atoi(strstr(lectura,"=")+1));
    }
    fclose(fParametros);
    parametros->tx = 20; //Tama�o X del mapa, va fijo
    parametros->ty = 15; //Tama�o Y del mapa, va fijo
}

void leerLineaParametros(char* destino, FILE* fParametros)
{
    char buffer=0;
    int i=0;

    //IP y P no pueden distinguirse si no se toma el enter tambien
    //asi que hay que hacer un poco de magia negra en esta lectura
    if (ftell(fParametros)!=0) fseek(fParametros, ftell(fParametros)-1, 0);

    while ((buffer!=10 || i==1) && fread(&buffer,1,1,fParametros)==1)
    {
        if(buffer!=10 || i==0) destino[i] = buffer;
        i++;
    }
}
