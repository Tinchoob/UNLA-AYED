#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#ifndef NULL
#define NULL      0
#endif

struct ListaGenStruct;
typedef struct ListaGenStruct* ListaGen;

struct NodoStruct;
typedef struct NodoStruct* Nodo;

ListaGen newListaGen();
void eliminarListaGen(ListaGen lista);

void addObjeto(ListaGen lista, void* objeto);
void* getObjeto(ListaGen lista, int numNodo);
void delObjeto(ListaGen lista, int numNodo);

bool listaVacia(ListaGen lista);
int getSize(ListaGen lista);
void* getUltimo(ListaGen lista);
void* getPrimero(ListaGen lista);

#endif // LISTA_H_INCLUDED
