#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Parametros.h"

struct parametrosStruct
{
    long s; //Segundos que dura un intervalo
    long p; //Cantidad maxima que puede pedir un bandido
    long a; //Posiciones para definir el area de Ataque de un bandido
    long posXE; //Posición x de la estacion
    long posYE; //Posición y de la estacion
    long im; //Intervalo máximo para generación de monedas
    long vm; //Intervalos máximos de vida de una moneda
    long ib; //Máxima cantidad de intervalos para la aparición de bandidos
    long vb; //Tiempo máximo de vida de un bandido
    long ip; //Intervalos entre producciones de las minas
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
    }
    fclose(fParametros);
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
