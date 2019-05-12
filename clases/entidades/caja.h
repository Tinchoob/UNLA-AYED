#ifndef CAJA_H_INCLUDED
#define CAJA_H_INCLUDED

struct cajaStruct;
typedef struct cajaStruct* ptrCaja;

/*
    PRE: Se llama para asignar a un puntero que no puede estar inicializado
    POST: Se devuelve un ptrCaja que apunta a una cajaStruct nueva

    return: puntero a nueva cajaStruct

    Los valores internos se deben setear uno a uno con los set
*/
ptrCaja newCaja();

/*
    PRE: caja debe apuntar a una estructura existente
    POST: Se libera el espacio de memoria de la estructura a la que apuntaba caja

    caja: puntero a una estructura de tipo cajaStruct
*/
void delCaja(ptrCaja caja);

/*
    PRE: caja tiene que apuntar a una estructura cajaStruct
    POST: Se devuelve el valor de tipoRecurso

    caja: puntero a una estructura de tipo cajaStruct
*/
int getTipoRecurso(ptrCaja caja);

/*
    PRE: caja tiene que apuntar a una estructura cajaStruct
    POST: Se le asigna el valor enviado por tipoRecurso a caja->tipoRecurso

    caja: puntero a una estructura de tipo cajaStruct
    tipoRecurso: valor int
*/
void setTipoRecurso(ptrCaja caja, int tipoRecurso);

/*
    PRE: caja tiene que apuntar a una estructura cajaStruct
    POST: Se devuelve el valor de cantidad

    caja: puntero a una estructura de tipo cajaStruct
*/
int getCantidad(ptrCaja caja);

/*
    PRE: caja tiene que apuntar a una estructura cajaStruct
    POST: Se le asigna el valor enviado por cantidad a caja->cantidad

    caja: puntero a una estructura de tipo cajaStruct
    cantidad: valor int
*/
void setCantidad(ptrCaja caja, int cantidad);

#endif // CAJA_H_INCLUDED
