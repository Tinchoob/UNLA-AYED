#include "Moneda.h"

struct monedaStruct
{
    int xy[2];
    int tiempoVida;
    ptrParametros parametros;
    int widthHeight[2];
    SDL_Texture *imagen;
    SDL_Rect *rectImg = new SDL_Rect();
};

ptrMoneda newMoneda(int x, int y, int tiempoVida, ptrParametros parametros,SDL_Renderer* renderer)
{
    int xy[2];
    ptrMoneda moneda = new monedaStruct;
    moneda->widthHeight[0] = 40;
    moneda->widthHeight[1] = 40;
    moneda->parametros = parametros;
    xy[0] = x;
    xy[1] = y;
    setXY(moneda, xy);
    setTiempoVida(moneda, tiempoVida);
    setImagen(moneda,IMG_LoadTexture(renderer, "img/moneda.png"));
    setRectImagen(moneda);
    return moneda;
}

void delMoneda(ptrMoneda moneda)
{
    delete moneda;
}

SDL_Texture* getImagen(ptrMoneda moneda)
{
    return moneda->imagen;
}

void setImagen(ptrMoneda moneda, SDL_Texture* imagen)
{
    moneda->imagen = imagen;
}

SDL_Rect* getRectImagen(ptrMoneda moneda)
{
    return moneda->rectImg;
}

void setRectImagen(ptrMoneda moneda)
{
    moneda->rectImg->x = moneda->xy[0] * moneda->widthHeight[0];
    moneda->rectImg->y = moneda->xy[1] * moneda->widthHeight[1];
    moneda->rectImg->w = moneda->widthHeight[0];
    moneda->rectImg->h = moneda->widthHeight[1];
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

int tickMoneda(ptrMoneda moneda, ptrLocomotora locomotora)
{
    int ret;

    if(getXY(locomotora)[0]==getXY(moneda)[0] && getXY(locomotora)[1]==getXY(moneda)[1])
    {
        setMonedas(locomotora, getMonedas(locomotora) + 1);
        moneda->tiempoVida = 0;
    }
    else moneda->tiempoVida = moneda->tiempoVida-1;

    if (moneda->tiempoVida>0) ret=0;
    else ret=1;

    return ret; //0 si la moneda sique viva, 1 si tiene que borrarse de la lista
}
