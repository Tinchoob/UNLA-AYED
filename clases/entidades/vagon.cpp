#include "vagon.h"
#include "caja.h"

struct vagonStruct
{
    int xy[2];
    int tipoRecurso;
    ListaGen cajas;
};

ptrVagon newVagon()
{
    ptrVagon vagon = new vagonStruct;
    vagon->xy[0]=0;
    vagon->xy[1]=0;
    vagon->tipoRecurso = 0;
    vagon->cajas = newListaGen();
    return vagon;
}

void delVagon(ptrVagon vagon)
{
    int i;
    for(i=0;i<getSize(vagon->cajas);i++) delete getObjeto(vagon->cajas, i);
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

int getCantidadTotalLingotes(ptrVagon vagon)
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
