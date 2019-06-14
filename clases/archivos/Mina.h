#ifndef MINA_H_INCLUDED
#define MINA_H_INCLUDED

#include "../entidades/Locomotora.h"
#include "../listas/ListaGen.h"

struct minaStruct;
typedef struct minaStruct* ptrMina;

/*
    PRE: Se llama para asignar a un puntero que no puede estar inicializado
    POST: Se devuelve un ptrMina que apunta a una minaStruct nueva

    return: puntero a nueva minaStruct

    Los valores internos se deben setear uno a uno con los set
*/
ptrMina newMina(SDL_Renderer* renderer);

/*
    PRE: mina debe apuntar a una estructura existente
    POST: Se libera el espacio de memoria de la estructura a la que apuntaba mina

    mina: puntero a una estructura de tipo minaStruct
*/
void delMina(ptrMina mina);

/*
    PRE: mina tiene que apuntar a una estructura minaStruct
    POST: Se devuelve el valor de posX

    mina: puntero a una estructura de tipo minaStruct
    return: valor int
*/
int getPosX(ptrMina mina);

/*
    PRE: mina tiene que apuntar a una estructura minaStruct
    POST: Se le asigna el valor enviado por posX a mina->posX

    mina: puntero a una estructura de tipo minaStruct
    posX: valor int
*/
void setPosX(ptrMina mina, int posX);

/*
    PRE: mina tiene que apuntar a una estructura minaStruct
    POST: Se devuelve el valor de posY

    mina: puntero a una estructura de tipo minaStruct
    return: valor int
*/
int getPosY(ptrMina mina);

/*
    PRE: mina tiene que apuntar a una estructura minaStruct
    POST: Se le asigna el valor enviado por posY a mina->posY

    mina: puntero a una estructura de tipo minaStruct
    posY: valor int
*/
void setPosY(ptrMina mina, int posY);

/*
    PRE: mina tiene que apuntar a una estructura minaStruct
    POST: Se devuelve el valor de codItem

    mina: puntero a una estructura de tipo minaStruct
    return: valor int
*/
int getCodItem(ptrMina mina);

/*
    PRE: mina tiene que apuntar a una estructura minaStruct
    POST: Se le asigna el valor enviado por codItem a mina->codItem

    mina: puntero a una estructura de tipo minaStruct
    codItem: valor int
*/
void setCodItem(ptrMina mina, int codItem);

/*
    PRE: mina tiene que apuntar a una estructura minaStruct
    POST: Se devuelve el valor de IP

    mina: puntero a una estructura de tipo minaStruct
    return: valor int
*/
int getIP(ptrMina mina);

/*
    PRE: mina tiene que apuntar a una estructura minaStruct
    POST: Se le asigna el valor enviado por IP a mina->IP

    mina: puntero a una estructura de tipo minaStruct
    IP: valor int
*/
void setIP(ptrMina mina, int IP);

/*
    PRE: mina tiene que apuntar a una estructura minaStruct
    POST: Se devuelve un puntero al array de secuencias

    mina: puntero a una estructura de tipo minaStruct
    return: puntero int*
*/
int* getSeq(ptrMina mina);

/*
    PRE: mina tiene que apuntar a una estructura minaStruct, el array que se mande a seq no puede tener mas de 5 posiciones,
         seq no debe estar inicializado
    POST: Se le asigna el puntero enviado por seq a mina->seq

    mina: puntero a una estructura de tipo minaStruct
    seq: array de valores int, no puede tener mas de 5 posiciones
*/
void setSeq(ptrMina mina, int seq[]);

/*
    PRE: mina tiene que apuntar a una estructura minaStruct
    POST: Se devuelve el valor de mina->contadorIntervalos

    mina: puntero a una estructura de tipo minaStruct
    return: valor int
*/
int getContadorIntervalos(ptrMina mina);

/*
    PRE: mina tiene que apuntar a una estructura minaStruct
    POST: Se le asigna el valor enviado por contadorIntervalos a mina->contadorIntervalos

    mina: puntero a una estructura de tipo minaStruct
    contadorIntervalos: valor int
*/
void setContadorIntervalos(ptrMina mina, int contadorIntervalos);

/*
    PRE: mina tiene que apuntar a una estructura minaStruct
    POST: Se devuelve el valor de mina->contadorProduccion

    mina: puntero a una estructura de tipo minaStruct
    return: valor int
*/
int getContadorProduccion(ptrMina mina);

/*
    PRE: mina tiene que apuntar a una estructura minaStruct
    POST: Se le asigna el valor enviado por contadorProduccion a mina->contadorProduccion

    mina: puntero a una estructura de tipo minaStruct
    contadorProduccion: valor int
*/
void setContadorProduccion(ptrMina mina, int contadorProduccion);

/*
    PRE: mina tiene que apuntar a una estructura minaStruct
    POST: Se devuelve un puntero a mina->lstCajas

    mina: puntero a una estructura de tipo minaStruct
    return: puntero a una ListaGenStruct
*/
ListaGen getLstCajas(ptrMina mina);

/*
    PRE: mina tiene que apuntar a una estructura minaStruct
    POST: Se cambia la referencia de mina->lstCajas a la direccion indicada por lstCajas

    mina: puntero a una estructura de tipo minaStruct
    lstCajas: puntero a una ListaGenStruct
*/
void setLstCajas(ptrMina mina, ListaGen lstCajas);

/*
    PRE: mina y fMina tienen que estar inicializados
    POST: Se lee una linea del archivo que se indique por fMina

    fMina: puntero tipo FILE
    mina: puntero a una minaStruct

    IMPORTANTE: Mina es una instancia simple, lease UNA SOLA LINEA, por ende el bucle de lectura del archivo entero,
    tiene que hacerse en otro lado y NO ACA
*/
void leerLineaMina(FILE* fMina, ptrMina mina);

/*
    PRE: mina tiene que apuntar a una estructura minaStruct, locomotora tiene que apuntar a una estructura locomotoraStruct
    POST: Se ejecuta una cuenta de ticks desde la ultima vez que se spawneo una caja, en caso de que se haya
    alcanzado el intervalo de producción de la mina, se genera una nueva caja acorde a la secuencia de la mina,
    siempre y cuando haya menos de 5 cajas esperando ser retiradas. Si la locomotora está posicionada sobre la mina, se carga la ultima caja
    que se produjo en el primer vagón que esté disponible, si hay un vagón disponible, se elimina toda la producción actualmente almacenada.

    mina: puntero a una minaStruct
    locomotora: puntero a una locomotoraStruct
    stopLocomotora: bool para decidir si la locomotora debe detenerse en la mina
*/
void tickMina(ptrMina mina, ptrLocomotora locomotora, bool &stopLocomotora);

/*
    PRE: mina tiene que apuntar a una estructura minaStruct
    POST: Se devuelve el valor la textura de imagen de la mina

    mina: puntero a una estructura de tipo minaStruct
    return: valor texture
*/

SDL_Texture* getImagen(ptrMina mina);


/*
    PRE: mina tiene que apuntar a una estructura minaStruct
    POST: Se devuelve el valor del rect de la mina

    mina: puntero a una estructura de tipo minaStruct
    return: valor rect
*/

SDL_Rect* getRectImagen(ptrMina mina);

/*
    PRE: mina tiene que apuntar a una estructura minaStruct
    POST: Se le asigna el valor al rect de la mina

    mina: puntero a una estructura de tipo minaStruct
*/

void setRectImagen(ptrMina mina);

#endif // MINA_H_INCLUDED
