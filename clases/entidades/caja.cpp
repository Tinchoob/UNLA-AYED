#include "caja.h"

struct cajaStruct
{
    int tipoRecurso;
    int cantidad;
};

ptrCaja newCaja()
{
    ptrCaja caja = new cajaStruct();
    caja->tipoRecurso = 0;
    caja->cantidad = 0;
    return caja;
}

void delCaja(ptrCaja caja)
{
    delete caja;
}

int getTipoRecurso(ptrCaja caja)
{
    return caja->tipoRecurso;
}

void setTipoRecurso(ptrCaja caja, int tipoRecurso)
{
    caja->tipoRecurso = tipoRecurso;
}

int getCantidad(ptrCaja caja)
{
    return caja->cantidad;
}

void setCantidad(ptrCaja caja, int cantidad)
{
    caja->cantidad = cantidad;
}
