#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "ListaGen.h"

/* TDA Lista Void
 * Implementación: Array dinamico de bloques secuenciales de nodos
 *  __
 * |B1|->N1 ->N2 ->N3 ->N4
 * |B2|->N5 ->N6 ->N7 ->N8
 * |B3|->N9 ->N10->N11->N12
 * |B4|->N13->N14->N15->N16
 * |__|
 */

const int INDEX_BLOCK_SIZE = 16; //Tamaño de los bloques del indice

struct ListaGenStruct
{
    Nodo* nodos; //Indice de bloques de nodos, cada bloque esta compuesto por 4 nodos secuenciales uno tras el otro
    int cantNodos;
    int cantBloques; //Se utiliza para saber cuando hay indices de mas y borrarlos
};

struct NodoStruct
{
    void* objeto;
    Nodo siguiente;
};

ListaGen newListaGen()
{
    ListaGen lista = new ListaGenStruct;
    lista->nodos = new Nodo[INDEX_BLOCK_SIZE];
    lista->cantNodos = 0;
    lista->cantBloques = INDEX_BLOCK_SIZE;
    return lista;
}

void eliminarListaGen(ListaGen lista)
{
    int i,j,k;
    Nodo actual;

    for(i=(lista->cantNodos-1)/4;i>=0;i--)
    {
        for(j=(lista->cantNodos-1)%4;j>0;j--)
        {
            actual = lista->nodos[i]; //Posicionarse sobre el ultimo bloque de la lista
            for(k=1;k<j;k++) actual = actual->siguiente; //Posicionarse sobre el ultimo nodo correspondiente a ese bloque
            delete actual->siguiente; //Eliminar nodo
            lista->cantNodos--; //Actualizar la cantidad actual de nodos
        }
        delete lista->nodos[i]; //Eliminar bloque
        lista->cantNodos--; //Actualizar la cantidad actual de nodos
    }
    delete[] lista->nodos; //Eliminar indice
    delete lista; //Eliminar lista
}

void addObjeto(ListaGen lista, void* objeto)
{
    int i;
    Nodo actual;

    //cantNodos%64=0 (multiplos de 16x4, 64, 128, 192...) indica que la lista esta actualmente
    //a maxima capacidad y hay que agregar mas bloques
    if(lista->cantNodos%64 == 0 && lista->cantNodos!=0)
    {
        Nodo* temp = new Nodo[lista->cantNodos/4];

        for(i=0;i<lista->cantNodos/4;i++) temp[i]=lista->nodos[i]; //Se transfieren los punteros de los bloques a un array temporal
        delete lista->nodos; //Se elimina el indice
        lista->nodos = new Nodo[(lista->cantNodos/4)+INDEX_BLOCK_SIZE]; //Se crea de nuevo pero con mas bloques
        for(i=0;i<lista->cantNodos/4;i++) lista->nodos[i]=temp[i]; //Se transfieren los punteros de los bloques de vuelta al indice de la lista
        delete temp; //Se elimina el array temporal
        lista->cantBloques = lista->cantBloques + INDEX_BLOCK_SIZE; //Se actualiza la cantidad de bloques maxima actual en la lista
    }

    if (lista->cantNodos%4 == 0) //Nuevo bloque
    {
        lista->nodos[lista->cantNodos/4] = new NodoStruct;
        lista->nodos[lista->cantNodos/4]->objeto = objeto;
        lista->nodos[lista->cantNodos/4]->siguiente = NULL;
    }
    else //Nuevo nodo en bloque ya existente
    {
        actual = lista->nodos[lista->cantNodos/4];
        for(i=1;i<lista->cantNodos%4;i++) actual = actual->siguiente; //Posicionarse sobre el ultimo nodo del bloque antes de crearlo
        actual->siguiente = new NodoStruct;
        actual->siguiente->objeto = objeto;
        actual->siguiente->siguiente = NULL;
    }
    lista->cantNodos++; //Actualizar la cantidad de nodos de la lista
}

void* getObjeto(ListaGen lista, int numNodo)
{
    int i;
    Nodo actual;

    actual = lista->nodos[numNodo/4]; //Posicionarse sobre el bloque correspondiente
    for(i=0;i<numNodo%4;i++) actual = actual->siguiente; //Desplazar hasta el nodo que se busca

    return actual->objeto; //Devolver el objeto pedido
}

void delObjeto(ListaGen lista, int numNodo)
{
    int i=0;
    Nodo actual, temp;

    actual = lista->nodos[numNodo/4];
    for(i=0;i<numNodo%4;i++) actual = actual->siguiente; //Nodo a eliminar
    temp = lista->nodos[numNodo/4];
    for(i=0;i<(numNodo%4)-1;i++) temp = temp->siguiente; //Anterior a actual

    if(numNodo < lista->cantNodos-1) //Si no es el ultimo nodo
    {
        if(numNodo%4==0) lista->nodos[numNodo/4] = temp->siguiente; //Si es un nodo que se referencia en el array, actuar sobre el array
        else if (numNodo%4!=3) temp->siguiente = temp->siguiente->siguiente; //Sino sobre el nodo, pero solo si no es el ultimo del bloque
        //Si es el ultimo del bloque el for no hace ciclos y directamente se setea abajo el siguiente

        //Si no es la ultima fila (y las otras dos condiciones son porque sino intenta acceder a una posicion inexistente)
        if (numNodo/4 < lista->cantNodos/4 && !(lista->cantNodos%4==0 && (lista->cantNodos/4)-(numNodo/4)==1))
        {
            for(i=0;i<(3-numNodo%4);i++) temp = temp->siguiente; //Se posiciona sobre el ultimo nodo del bloque
            temp->siguiente = lista->nodos[(numNodo/4)+1]; //Lo asigna como siguiente al primer nodo del proximo bloque
            //Y corre una posicion a la fila siguiente
            if(lista->nodos[(numNodo/4)+1]->siguiente!=NULL) lista->nodos[(numNodo/4)+1] = lista->nodos[(numNodo/4)+1]->siguiente;
            else lista->nodos[(numNodo/4)+1] = 0; //O si el bloque siguiente solo tiene un nodo (que ahora se corrio hacia arriba), lo dirije a NULL
        }

        numNodo = numNodo + 4; //Avanzar al siguiente bloque para revisar
        //Mientras no sea el ultimo bloque (y las otras dos condiciones son porque sino intenta acceder a una posicion inexistente)
        while(numNodo/4 < lista->cantNodos/4 && !(lista->cantNodos%4==0 && (lista->cantNodos/4)-(numNodo/4)==1))
        {
            temp = lista->nodos[numNodo/4]; //Pararse sobre el primero
            for(i=0;i<2;i++) temp = temp->siguiente; //Hacer 2 corrimientos (no son 3 porque un nodo se traslado al bloque de arriba)
            temp->siguiente = lista->nodos[(numNodo/4)+1]; //Asignar como siguiente al ultimo del bloque al primero de la siguiente fila

            //Correr una posicion a la fila siguiente
            if(lista->nodos[(numNodo/4)+1]->siguiente != 0) lista->nodos[(numNodo/4)+1] = lista->nodos[(numNodo/4)+1]->siguiente;
            else lista->nodos[(numNodo/4)+1] = 0; //O si el bloque siguiente solo tiene un nodo (que ahora se corrio hacia arriba), dirijirlo a NULL
            numNodo = numNodo + 4;
        }
    }
    else if(numNodo%4==0) lista->nodos[numNodo/4] = NULL; //Si es el ultimo y ademas es el unico en su bloque
    else temp->siguiente = NULL; //Si es el ultimo nodo simplemente se lo elimina y ya
    delete actual; //Eliminar nodo seleccionado
    lista->cantNodos--;

    //Finalmente, si hay demasiados indices creados, se eliminan algunos
    if(lista->cantNodos/4 < (lista->cantBloques - INDEX_BLOCK_SIZE - 2))
    {
        Nodo* temp = new Nodo[lista->cantNodos/4];

        for(i=0;i<lista->cantNodos/4;i++) temp[i]=lista->nodos[i]; //Se transfieren los punteros de los bloques a un array temporal
        delete lista->nodos; //Se elimina el indice
        lista->nodos = new Nodo[lista->cantBloques - INDEX_BLOCK_SIZE]; //Se crea de nuevo pero con menos bloques
        for(i=0;i<lista->cantNodos/4;i++) lista->nodos[i]=temp[i]; //Se transfieren los punteros de los bloques de vuelta al indice de la lista
        delete temp; //Se elimina el array temporal
        lista->cantBloques = lista->cantBloques - INDEX_BLOCK_SIZE; //Se actualiza la cantidad de bloques maxima actual en la lista
    }
}

bool listaVacia(ListaGen lista)
{
    bool ret;
    if (lista->cantNodos>0) ret = false;
    else ret = true;
    return ret;
}

int getSize(ListaGen lista)
{
    return lista->cantNodos;
}

void* getUltimo(ListaGen lista)
{
    void* ret;

    if (!listaVacia(lista)) ret = getObjeto(lista, getSize(lista)-1);
    else ret = NULL;
    return ret;
}

void* getPrimero(ListaGen lista)
{
    void* ret;

    if (!listaVacia(lista)) ret = getObjeto(lista, 0);
    else ret = NULL;
    return ret;
}
