#ifndef VAGON_H_INCLUDED
#define VAGON_H_INCLUDED

#include "../listas/ListaGen.h"

struct vagonStruct;
typedef struct vagonStruct* ptrVagon;

/*
    PRE: Se llama para asignar a un puntero que no puede estar inicializado
    POST: Se devuelve un ptrVagon que apunta a una vagonStruct nueva

    return: puntero a nueva vagonStruct

    Los valores internos se deben setear uno a uno con los set
*/
ptrVagon newVagon();

/*
    PRE: vagon debe apuntar a una estructura existente
    POST: Se libera el espacio de memoria de la estructura a la que apuntaba vagon

    vagon: puntero a una estructura de tipo vagonStruct
*/
void delVagon(ptrVagon vagon);

/*
    PRE: vagon tiene que apuntar a una estructura vagonStruct
    POST: Se devuelve un puntero a xy

    vagon: puntero a una estructura de tipo vagonStruct
*/
int* getXY(ptrVagon vagon);

/*
    PRE: vagon tiene que apuntar a una estructura vagonStruct
    POST: Se le asigna los valores enviados por xy a vagon->xy

    vagon: puntero a una estructura de tipo vagonStruct
    xy: array de valores int, tambien acepta punteros int*
*/
void setXY(ptrVagon vagon, int xy[]);

/*
    PRE: vagon tiene que apuntar a una estructura vagonStruct
    POST: Se devuelve el valor de tipoRecurso

    vagon: puntero a una estructura de tipo vagonStruct
*/
int getTipoRecurso(ptrVagon vagon);

/*
    PRE: vagon tiene que apuntar a una estructura vagonStruct
    POST: Se le asigna el valor enviado por tipoRecurso a vagon->tipoRecurso

    vagon: puntero a una estructura de tipo vagonStruct
    tipoRecurso: valor int
*/
void setTipoRecurso(ptrVagon vagon, int tipoRecurso);

/*
    PRE: vagon tiene que apuntar a una estructura vagonStruct
    POST: Se devuelve un puntero a cajas

    vagon: puntero a una estructura de tipo vagonStruct
*/
ListaGen getCajas(ptrVagon vagon);

/*
    PRE: vagon tiene que apuntar a una estructura vagonStruct
    POST: Se cambia la referencia de vagon->cajas a la direccion indicada por cajas

    vagon: puntero a una estructura de tipo vagonStruct
    cajas: puntero a una ListaGenStruct
*/
void setCajas(ptrVagon vagon, ListaGen cajas);

/*
    PRE: vagon tiene que apuntar a una estructura vagonStruct
    POST: Se devuelve la cantidad total de lingotes en todas las cajas del vagon

    vagon: puntero a una estructura de tipo vagonStruct
*/
int getCantidadTotalLingotes(ptrVagon vagon);

/*
    PRE: vagon tiene que apuntar a una estructura vagonStruct
    POST: Se quita la cantidad de lingotes indicada del vagon, no se puede pedir quitar mas
          que la suma total de todos los lingotes en las cajas del vagon

    vagon: puntero a una estructura de tipo vagonStruct
    cantidad: valor int
*/
void quitarLingotes(ptrVagon vagon, int cantidad);

#endif // VAGON_H_INCLUDED
