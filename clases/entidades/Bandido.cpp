#include "Bandido.h"
#include "../listas/ListaGen.h"
#include "../funciones/Funciones.h"


#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <SDL_image.h>

struct bandidoStruct
{
    int tipoRecurso;
    int cantidad;
    int tiempoVida;
    int xy[2];
    ptrParametros parametros;
    int widthHeight[2];
    SDL_Texture *imagen;
    SDL_Rect *rectImg = new SDL_Rect();
};

ptrBandido newBandido(int tipoRecurso, int cantidad, int tiempoVida, int xy[], ptrParametros parametros,SDL_Renderer* renderer)
{
    ptrBandido bandido = new bandidoStruct;
    bandido->widthHeight[0] = 40;
    bandido->widthHeight[1] = 40;
    setTipoRecurso(bandido, tipoRecurso);
    bandido->parametros = parametros;
    setCantidad(bandido, cantidad);
    setTiempoVida(bandido, tiempoVida);
    setXY(bandido, xy);
    setImagen(bandido,IMG_LoadTexture(renderer, "img/villano.png"));
    setRectImagen(bandido);

    return bandido;
}

void delBandido(ptrBandido bandido)
{
    delete bandido;
}

SDL_Texture* getImagen(ptrBandido bandido)
{
    return bandido->imagen;
}

void setImagen(ptrBandido bandido, SDL_Texture* imagen)
{
    bandido->imagen = imagen;
}

SDL_Rect* getRectImagen(ptrBandido bandido)
{
    return bandido->rectImg;
}

void setRectImagen(ptrBandido bandido)
{
    bandido->rectImg->x = bandido->xy[0] * bandido->widthHeight[0];
    bandido->rectImg->y = bandido->xy[1] * bandido->widthHeight[1];
    bandido->rectImg->w = bandido->widthHeight[0];
    bandido->rectImg->h = bandido->widthHeight[1];
}

int getTipoRecurso(ptrBandido bandido)
{
    return bandido->tipoRecurso;
}

void setTipoRecurso(ptrBandido bandido, int tipoRecurso)
{
    if(tipoRecurso>=1 && tipoRecurso<=6)
        bandido->tipoRecurso = tipoRecurso;
    else if(tipoRecurso<1)
        bandido->tipoRecurso = 1;
    else
        bandido->tipoRecurso = 6;
}

int getCantidad(ptrBandido bandido)
{
    return bandido->cantidad;
}

void setCantidad(ptrBandido bandido, int cantidad)
{
    if (cantidad>0 && cantidad<=getP(getParametros(bandido)))
        bandido->cantidad = cantidad;
    else if (cantidad<=0)
        bandido->cantidad = 0;
    else
        bandido->cantidad = getP(getParametros(bandido));
}

int getTiempoVida(ptrBandido bandido)
{
    return bandido->tiempoVida;
}

void setTiempoVida(ptrBandido bandido, int tiempoVida)
{
    if (tiempoVida>0 && tiempoVida<=getVB(getParametros(bandido)))
        bandido->tiempoVida = tiempoVida;
    else if (tiempoVida<1)
        bandido->tiempoVida = 1;
    else
        bandido->tiempoVida = getVB(getParametros(bandido));
}

int* getXY(ptrBandido bandido)
{
    return bandido->xy;
}

void setXY(ptrBandido bandido, int xy[])
{
    if (xy[0]>=0 && xy[0]<=getTX(getParametros(bandido)))
        bandido->xy[0] = xy[0];
    else if (xy[0]<0)
        bandido->xy[0] = 0;
    else
        bandido->xy[0] = getTX(getParametros(bandido));

    if (xy[1]>=0 && xy[1]<=getTY(getParametros(bandido)))
        bandido->xy[1] = xy[1];
    else if (xy[1]<0)
        bandido->xy[1] = 0;
    else
        bandido->xy[1] = getTY(getParametros(bandido));
}

ptrParametros getParametros(ptrBandido bandido)
{
    return bandido->parametros;
}

void setParametros(ptrBandido bandido, ptrParametros parametros)
{
    bandido->parametros = parametros;
}

int tickBandido(ptrBandido bandido, ptrLocomotora locomotora, ptrParametros parametros)
{
    int ret, i;
    char defender;
    bool trenEnRango=false;

    trenEnRango = enRango(bandido->xy, getA(parametros), getXY(locomotora));
    i=0;
    while (i<getSize(getVagones(locomotora)) && trenEnRango!=true)
    {
        trenEnRango = enRango(bandido->xy, getA(parametros), getXY((ptrVagon)getObjeto(getVagones(locomotora), i)));
        i++;
    }

    if (trenEnRango)
    {
        std::cout<<"Eh wachin dame todo! (Dar/Resistirse? (D/R))"<<std::endl;
        std::cin>>defender;
        if (defender>90)
            defender = defender - 32;
        if (defender=='D')
        {
            //
        }
        else if (defender=='R')
        {
            if (getHasChumbo(locomotora))
            {
                std::cout<<"Se ha usado el chumbo de la inimputabilidad, come plomo gato"<<std::endl;
                setHasChumbo(locomotora, false);
                system("pause");
            }
            else
            {
                if(!listaVacia(getVagones(locomotora)))
                {
                    delVagon((ptrVagon)getUltimo(getVagones(locomotora)));
                    delObjeto(getVagones(locomotora), getSize(getVagones(locomotora)) - 1);
                }
            }
        }
        bandido->tiempoVida = 0;
    }
    bandido->tiempoVida = bandido->tiempoVida-1;
    if (bandido->tiempoVida>0)
        ret=0;
    else
        ret=1;
    return ret; //0 si el bandido sique viviendo, 1 si tiene que borrarse de la lista
}
