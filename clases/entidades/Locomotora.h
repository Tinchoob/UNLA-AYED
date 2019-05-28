#ifndef LOCOMOTORA_H_INCLUDED
#define LOCOMOTORA_H_INCLUDED

#include "../listas/ListaGen.h"
#include "Vagon.h"

struct locomotoraStruct;
typedef struct locomotoraStruct* ptrLocomotora;

/*
    PRE: Se llama para asignar a un puntero que no puede estar inicializado
    POST: Se devuelve un ptrLocomotora que apunta a una locomotoraStruct nueva

    return: puntero a nueva ptrLocomotora
*/
ptrLocomotora newLocomotora();

/*
    PRE: locomotora debe apuntar a una estructura existente
    POST: Se libera el espacio de memoria de la estructura a la que apuntaba locomotora, adicionalmente se
          llama a las rutinas de eliminación de los vagones para liberar la memoria que estos ocupan

    locomotora: puntero a una estructura de tipo locomotoraStruct
*/
void delLocomotora(ptrLocomotora locomotora);

/*
    PRE: locomotora tiene que apuntar a una estructura locomotoraStruct
    POST: Se devuelve un puntero a xy

    locomotora: puntero a una estructura de tipo locomotoraStruct
    return: puntero a int
*/
int* getXYLocomotora(ptrLocomotora locomotora);

/*
    PRE: locomotora tiene que apuntar a una estructura locomotoraStruct
    POST: Se le asigna los valores enviados por xy a locomotora->xy

    locomotora: puntero a una estructura de tipo locomotoraStruct
    xy: array de valores int, tambien acepta punteros int*
*/
void setXYLocomotora(ptrLocomotora locomotora, int xy[]);

/*
    PRE: locomotora tiene que apuntar a una estructura locomotoraStruct
    POST: Se devuelve el valor de direccion

    locomotora: puntero a una estructura de tipo locomotoraStruct
    return: valor int
*/
int getDireccionLocomotora(ptrLocomotora locomotora);

/*
    PRE: locomotora tiene que apuntar a una estructura locomotoraStruct, el valor de direccion debe estar en un rango de 0 a 3
    POST: Se le asigna el valor enviado por direccion a locomotora->direccion

    locomotora: puntero a una estructura de tipo locomotoraStruct
    direccion: valor int, solo puede contener valores de 0 a 3 inclusive
*/
void setDireccionLocomotora(ptrLocomotora locomotora, int direccion);

/*
    PRE: locomotora tiene que apuntar a una estructura locomotoraStruct
    POST: Se devuelve un puntero a vagones

    locomotora: puntero a una estructura de tipo locomotoraStruct
    return: puntero a una ListaGenStruct
*/
ListaGen getVagones(ptrLocomotora locomotora);

/*
    PRE: locomotora tiene que apuntar a una estructura locomotoraStruct
    POST: Se cambia la referencia de locomotora->vagones a la direccion indicada por vagones

    locomotora: puntero a una estructura de tipo locomotoraStruct
    vagones: puntero a una ListaGenStruct
*/
void setVagones(ptrLocomotora locomotora, ListaGen vagones);

/*
    PRE: locomotora tiene que apuntar a una estructura locomotoraStruct
    POST: Se devuelve el valor de hasChumbo

    locomotora: puntero a una estructura de tipo locomotoraStruct
    return: valor bool
*/
bool getHasChumbo(ptrLocomotora locomotora);

/*
    PRE: locomotora tiene que apuntar a una estructura locomotoraStruct
    POST: Se le asigna el valor enviado por hasChumbo a locomotora->hasChumbo

    locomotora: puntero a una estructura de tipo locomotoraStruct
    hasChumbo: valor bool
*/
void setHasChumbo(ptrLocomotora locomotora, bool hasChumbo);

/*
    PRE: locomotora tiene que apuntar a una estructura locomotoraStruct
    POST: Se devuelve el valor de agregarVagon

    locomotora: puntero a una estructura de tipo locomotoraStruct
    return: valor bool
*/
bool getAgregarVagon(ptrLocomotora locomotora);

/*
    PRE: locomotora tiene que apuntar a una estructura locomotoraStruct
    POST: Se le asigna el valor enviado por agregarVagon a locomotora->agregarVagon

    locomotora: puntero a una estructura de tipo locomotoraStruct
    agregarVagon: valor bool
*/
void setAgregarVagon(ptrLocomotora locomotora, bool agregarVagon);

/*
    PRE: locomotora tiene que apuntar a una estructura locomotoraStruct
    POST: La ubicación de la locomotora se modifica según su dirección y todos los vagones que tenga en su lista
          ejecutan sus respectivas rutinas de movimiento. Adicionalmente si el flag agregarVagon está seteado en true,
          se añade un vagón a la ultima posición del tren

    locomotora: puntero a una estructura de tipo locomotoraStruct
*/
void moverLocomotora(ptrLocomotora locomotora);



#endif // LOCOMOTORA_H_INCLUDED
