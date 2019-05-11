#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "ListaGen.h"

struct ListaGenStruct
{
    Nodo* nodos;
    int cantNodos;
};

struct NodoStruct
{
    void* objeto;
};

ListaGen newListaGen()
{
    ListaGen lista = new ListaGenStruct;
    lista->cantNodos = 0;
    return lista;
}

void eliminarListaGen(ListaGen lista)
{
    int i;
    for(i=0;i<lista->cantNodos;i++)
    {
        delete lista->nodos[i];
    }
    delete lista->nodos;
    delete lista;
}

void addObjeto(ListaGen lista, void* objeto)
{
    int i;

    if(lista->cantNodos==0) lista->nodos = new Nodo[1];
    else
    {
        Nodo* temp = new Nodo[lista->cantNodos];

        for(i=0;i<lista->cantNodos;i++) temp[i]=lista->nodos[i];
        delete lista->nodos;
        lista->nodos = new Nodo[lista->cantNodos+1];
        for(i=0;i<lista->cantNodos;i++) lista->nodos[i]=temp[i];
        delete temp;
    }

    lista->nodos[lista->cantNodos] = new NodoStruct;
    lista->nodos[lista->cantNodos]->objeto = objeto;
    lista->cantNodos++;
}

void* getObjeto(ListaGen lista, int numNodo)
{
    void* objeto = NULL;

    if (!listaVacia(lista) && numNodo >= 0 && numNodo < lista->cantNodos)
    {
        objeto = lista->nodos[numNodo]->objeto;
    }
    else std::cout<<"Error al obtener objeto de la lista, nodo inexistente"<<std::endl;
    return objeto;
}

void delObjeto(ListaGen lista, int numNodo)
{
    int i=0, j=0;
    Nodo* temp = new Nodo[lista->cantNodos-1];

    if (!listaVacia(lista) && numNodo >= 0 && numNodo < lista->cantNodos)
    {
        while(i<lista->cantNodos)
        {
            if (i!=numNodo)
            {
                temp[j]=lista->nodos[i];
                j++;
            }
            i++;
        }

        lista->cantNodos--;
        delete lista->nodos[numNodo];
        delete lista->nodos;
        lista->nodos = new Nodo[lista->cantNodos];
        for(i=0;i<lista->cantNodos;i++) lista->nodos[i] = temp[i];
        delete temp;
    }
    else std::cout<<"Error al eliminar de la lista, nodo inexistente"<<std::endl;
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
