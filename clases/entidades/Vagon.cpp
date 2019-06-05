#include "vagon.h"
#include "caja.h"
#include <iostream>

struct vagonStruct
{
    int xy[2];
    int tipoRecurso;
    ListaGen cajas;
    int direccion;
    int capacidad;
};

ptrVagon newVagon(int x, int y, int direccion, int capacidad)
{
    ptrVagon vagon = new vagonStruct;
    vagon->xy[0]=x;
    vagon->xy[1]=y;
    vagon->tipoRecurso = 0;
    vagon->cajas = newListaGen();
    vagon->direccion = direccion;
    vagon->capacidad = capacidad;
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

    while(cantidad > 0)
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
            break;
        //Abajo
        case 1:
            vagon->xy[1]++;
            break;
        //Izquierda
        case 2:
            vagon->xy[0]--;
            break;
        //Arriba
        case 3:
            vagon->xy[1]--;
            break;
    }
    /*std::cout<<"Direccion Vagon: "<<vagon->direccion<<std::endl;
    std::cout<<"X Vagon: "<<vagon->xy[0]<<std::endl;
    std::cout<<"Y Vagon: "<<vagon->xy[1]<<std::endl;*/
}
