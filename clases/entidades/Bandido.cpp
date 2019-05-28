#include "Bandido.h"

struct bandidoStruct
{
    int tipoRecurso;
    int cantidad;
    int tiempoVida;
    int xy[2];
};

ptrBandido newBandido(int tipoRecurso, int cantidad, int tiempoVida, int xy[])
{
    ptrBandido bandido = new bandidoStruct;

    bandido->tipoRecurso = tipoRecurso;
    bandido->cantidad = cantidad;
    bandido->tiempoVida = tiempoVida;
    bandido->xy[0] = xy[0];
    bandido->xy[1] = xy[1];

    return bandido;
}

void delBandido(ptrBandido bandido)
{
    delete bandido;
}

int getTipoRecurso(ptrBandido bandido)
{
    return bandido->tipoRecurso;
}

void setTipoRecurso(ptrBandido bandido, int tipoRecurso)
{
    bandido->tipoRecurso = tipoRecurso;
}

int getCantidad(ptrBandido bandido)
{
    return bandido->cantidad;
}

void setCantidad(ptrBandido bandido, int cantidad)
{
    bandido->cantidad = cantidad;
}

int getTiempoVida(ptrBandido bandido)
{
    return bandido->tiempoVida;
}

void setTiempoVida(ptrBandido bandido, int tiempoVida)
{
    if (tiempoVida>=0) bandido->tiempoVida = tiempoVida;
    else bandido->tiempoVida = 0;
}

int* getXY(ptrBandido bandido)
{
    return bandido->xy;
}

void setXY(ptrBandido bandido, int xy[])
{
    bandido->xy[0] = xy[0];
    bandido->xy[1] = xy[1];
}

int tickBandido(ptrBandido bandido)
{
    int ret;

    if (getTiempoVida(bandido)>0)
    {
        setTiempoVida(bandido, getTiempoVida(bandido)-1);
        ret=0;
    }
    else
    {
        delBandido(bandido);
        ret=1;
    }

    return ret; //0 si el bandido sique viviendo, 1 si tiene que borrarse de la lista
}
