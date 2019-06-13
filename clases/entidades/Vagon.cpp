// VAGON.CPP IGNA

#include "vagon.h"
#include "caja.h"

#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <SDL_image.h>

struct vagonStruct
{
    int xy[2];
    int tipoRecurso;
    ListaGen cajas;
    int direccion;
    int capacidad;

    int widthHeight[2];
    SDL_Texture *imagen;
    SDL_Rect *rectImg = new SDL_Rect();
};

ptrVagon newVagon(SDL_Renderer* renderer,int x, int y, int direccion, int capacidad)
{
    ptrVagon vagon = new vagonStruct;
    vagon->xy[0]=x;
    vagon->xy[1]=y;
    vagon->tipoRecurso = 0;
    vagon->cajas = newListaGen();
    vagon->direccion = direccion;
    vagon->capacidad = capacidad;
    vagon->widthHeight[0]=40;
    vagon->widthHeight[1]=40;
    vagon->imagen=IMG_LoadTexture(renderer,"img/c2/arr/1.png");
    setRectImagen(vagon);
    return vagon;
}

void delVagon(ptrVagon vagon)
{
    int i;
    for(i=0;i<getSize(vagon->cajas);i++) delCaja((ptrCaja)getObjeto(vagon->cajas, i));
    eliminarListaGen(vagon->cajas);
    delete vagon;
}

int* getXY(ptrVagon vagon)
{
    return vagon->xy;
}

void setXY(ptrVagon vagon, int xy[])
{
    vagon->xy[0] = xy[0];
    vagon->xy[1] = xy[1];
}

int getTipoRecurso(ptrVagon vagon)
{
    return vagon->tipoRecurso;
}

void setTipoRecurso(ptrVagon vagon, int tipoRecurso)
{
    vagon->tipoRecurso = tipoRecurso;
}

ListaGen getCajas(ptrVagon vagon)
{
    return vagon->cajas;
}

void setCajas(ptrVagon vagon, ListaGen cajas)
{
    vagon->cajas = cajas;
}

int getDireccionVagon(ptrVagon vagon)
{
    return vagon->direccion;
}

void setDireccionVagon(ptrVagon vagon, int direccion)
{
    vagon->direccion = direccion;

}

int getCapacidad(ptrVagon vagon)
{
    return vagon->capacidad;
}

void setCapacidad(ptrVagon vagon, int capacidad)
{
    vagon->capacidad = capacidad;
}

int cantidadTotalLingotes(ptrVagon vagon)
{
    int cantTotal = 0, i;
    ListaGen cajas = getCajas(vagon);

    for(i=0;i<getSize(cajas);i++) cantTotal = cantTotal + getCantidad((ptrCaja)getObjeto(cajas, i));
    return cantTotal;
}

void quitarLingotes(ptrVagon vagon, int cantidad)
{
    int cantUltimaCaja;
    ptrCaja ultimaCaja;
    ListaGen listaCajas = getCajas(vagon);

    while(cantidad > 0 && !listaVacia(getCajas(vagon)))
    {
        ultimaCaja = (ptrCaja)getUltimo(listaCajas);
        cantUltimaCaja = getCantidad(ultimaCaja);
        if (cantUltimaCaja > cantidad)
        {
            setCantidad(ultimaCaja, cantUltimaCaja - cantidad);
            cantidad = 0;
        }
        else
        {
            delCaja(ultimaCaja);
            delObjeto(listaCajas, getSize(listaCajas)-1);
            cantidad = cantidad - cantUltimaCaja;
        }
    }
}

void moverVagon(ptrVagon vagon)
{
     switch(vagon->direccion)
    {
        //Derecha
        case 0:
            vagon->xy[0]++;
            setRectImagen(vagon);
            break;
        //Abajo
        case 1:
            vagon->xy[1]++;
            setRectImagen(vagon);
            break;
        //Izquierda
        case 2:
            vagon->xy[0]--;
            setRectImagen(vagon);
            break;
        //Arriba
        case 3:
            vagon->xy[1]--;
            setRectImagen(vagon);
            break;
    }
}

SDL_Texture* getImagen(ptrVagon vagon){
    return vagon->imagen;
}

void setImagen(ptrVagon vagon, SDL_Texture* imagen){
    vagon->imagen = imagen;
}

SDL_Rect* getRectImagen(ptrVagon vagon){
    return vagon->rectImg;
}

void setRectImagen(ptrVagon vagon){
    vagon->rectImg->x = vagon->xy[0] * vagon->widthHeight[0];
    vagon->rectImg->y = vagon->xy[1] * vagon->widthHeight[1];
    vagon->rectImg->w =vagon->widthHeight[0];
    vagon->rectImg->h =vagon->widthHeight[1];
}
    /*std::cout<<"Direccion Vagon: "<<vagon->direccion<<std::endl;
    std::cout<<"X Vagon: "<<vagon->xy[0]<<std::endl;
    std::cout<<"Y Vagon: "<<vagon->xy[1]<<std::endl;*/

