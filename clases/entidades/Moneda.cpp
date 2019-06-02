#include "Moneda.h"

struct monedaStruct
{
    int xy[2];
    int tiempoVida;
    ptrParametros parametros;
};

ptrMoneda newMoneda(int x, int y, int tiempoVida, ptrParametros parametros)
{
    int xy[2];
    ptrMoneda moneda = new monedaStruct;

    moneda->parametros = parametros;
    xy[0] = x;
    xy[1] = y;
    setXY(moneda, xy);
    setTiempoVida(moneda, tiempoVida);
    return moneda;
}

void delMoneda(ptrMoneda moneda)
{
    delete moneda;
}

int* getXY(ptrMoneda moneda)
{
    return moneda->xy;
}

void setXY(ptrMoneda moneda, int xy[])
{
    if (xy[0]>=0 && xy[0]<=getTX(getParametros(moneda))) moneda->xy[0] = xy[0];
    else if (xy[0]<0) moneda->xy[0] = 0;
    else moneda->xy[0] = getTX(getParametros(moneda));

    if (xy[1]>=0 && xy[1]<=getTY(getParametros(moneda))) moneda->xy[1] = xy[1];
    else if (xy[1]<0) moneda->xy[1] = 0;
    else moneda->xy[1] = getTY(getParametros(moneda));
}

int getTiempoVida(ptrMoneda moneda)
{
    return moneda->tiempoVida;
}

void setTiempoVida(ptrMoneda moneda, int tiempoVida)
{
    if (tiempoVida>0 && tiempoVida<=getVM(getParametros(moneda))) moneda->tiempoVida = tiempoVida;
    else if (tiempoVida<1) moneda->tiempoVida = 1;
    else moneda->tiempoVida = getVM(getParametros(moneda));
}

ptrParametros getParametros(ptrMoneda moneda)
{
    return moneda->parametros;
}

void setParametros(ptrMoneda moneda, ptrParametros parametros)
{
    moneda->parametros = parametros;
}

int tickMoneda(ptrMoneda moneda, ptrLocomotora locomotora, int* monedas)
{
    int ret;

    if(getXY(locomotora)[0]==getXY(moneda)[0] && getXY(locomotora)[1]==getXY(moneda)[1])
    {
        (*monedas)++;
        moneda->tiempoVida = 0;
    }
    else moneda->tiempoVida = moneda->tiempoVida-1;

    if (moneda->tiempoVida>0) ret=0;
    else ret=1;

    return ret; //0 si la moneda sique viva, 1 si tiene que borrarse de la lista
}
