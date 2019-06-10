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
int* getXY(ptrLocomotora locomotora);

/*
    PRE: locomotora tiene que apuntar a una estructura locomotoraStruct
    POST: Se le asigna los valores enviados por xy a locomotora->xy

    locomotora: puntero a una estructura de tipo locomotoraStruct
    xy: array de valores int, tiene que tener como mínimo 2 posiciones
*/
void setXY(ptrLocomotora locomotora, int xy[]);

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
    POST: Se devuelve un puntero a locomotora->cantRecursos

    locomotora: puntero a una estructura de tipo locomotoraStruct
    return: puntero a int
*/
int* getCantRecursos(ptrLocomotora locomotora);

/*
    PRE: locomotora tiene que apuntar a una estructura locomotoraStruct
    POST: Se le asigna los valores enviados por cantRecursos a locomotora->cantRecursos

    locomotora: puntero a una estructura de tipo locomotoraStruct
    cantRecursos: array de valores int, tiene que tener como mínimo 6 posiciones
*/
void setCantRecursos(ptrLocomotora locomotora, int cantRecursos[]);

/*
    PRE: locomotora tiene que apuntar a una estructura locomotoraStruct
    POST: Se devuelve el valor de locomotora->monedas

    locomotora: puntero a una estructura de tipo locomotoraStruct
    return: valor int
*/
int getMonedas(ptrLocomotora locomotora);

/*
    PRE: locomotora tiene que apuntar a una estructura locomotoraStruct
    POST: Se le asigna el valor enviado por monedas a locomotora->monedas

    locomotora: puntero a una estructura de tipo locomotoraStruct
    monedas: valor int
*/
void setMonedas(ptrLocomotora locomotora, int monedas);

/*
    PRE: locomotora tiene que apuntar a una estructura locomotoraStruct
    POST: La ubicación de la locomotora se modifica según su dirección y todos los vagones que tenga en su lista
          ejecutan sus respectivas rutinas de movimiento. Adicionalmente si el flag agregarVagon está seteado en true,
          se añade un vagón a la ultima posición del tren

    locomotora: puntero a una estructura de tipo locomotoraStruct
*/
void moverLocomotora(ptrLocomotora locomotora);

/*
    PRE: locomotora tiene que apuntar a una estructura locomotoraStruct, tipoRecurso debe contener valores entre 1 y 6 inclusive
    POST: Se quita la cantidad de lingotes especificada de los vagones del tren y se devuelve 0, indicando una operación exitosa,
    alternativamente, si el tren no tiene suficientes lingotes para realizar la operación, se devuelve 1 y no se quitan lingotes

    locomotora: puntero a una estructura de tipo locomotoraStruct
    cantidad: valor int
    tipoRecurso: valor int
*/
int quitarLingotes(ptrLocomotora locomotora, int cantidad, int tipoRecurso);

/*
    PRE: locomotora tiene que apuntar a una estructura locomotoraStruct
    POST: Se actualizan los valores de locomotora->cantRecursos según los lingotes contenidos en los vagones del tren

    locomotora: puntero a una estructura de tipo locomotoraStruct
*/
void actualizarCantRecursos(ptrLocomotora locomotora);

#endif // LOCOMOTORA_H_INCLUDED
