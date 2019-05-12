#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#ifndef NULL
#define NULL      0
#endif

/* TDA Lista Void
 * Interfaz: Lista indexada
 *
 * objeto = getObjeto(lista, posicion);
 * delObjeto(lista, posicion);
 *
 */

struct ListaGenStruct;
typedef struct ListaGenStruct* ListaGen;

struct NodoStruct;
typedef struct NodoStruct* Nodo;

/*
    PRE: Se llama para asignar a un puntero que no puede estar inicializado
    POST: Se devuelve una ListaGen que apunta a una ListaGenStruct nueva

    return: puntero a nueva ListaGenStruct
*/
ListaGen newListaGen();

/*
    PRE: lista debe apuntar a una ListaGenStruct existente
    POST: Se libera el espacio de memoria de la ListaGenStruct a la que apuntaba lista, asi como el de todos los nodos que la componian

    IMPORTANTE: ESTO NO ELIMINA LOS OBJETOS QUE LA LISTA REFERENCIE, SI LOS MISMOS NO SON ELIMINADOS
                ANTES DE LLAMAR A ESTA FUNCION, QUEDARAN INACCESIBLES Y EN MEMORIA

    lista: puntero a una estructura de tipo ListaGenStruct
*/
void eliminarListaGen(ListaGen lista);

/*
    PRE: lista tiene que apuntar a una estructura ListaGenStruct, objeto tiene que apuntar a una region ya inicializada de la memoria
    POST: Se agrega un nodo a la lista y se le hace apuntar hacia objeto

    lista: puntero a una estructura de tipo ListaGenStruct
    objeto: puntero void, recibe otros punteros o direcciones de memoria
*/
void addObjeto(ListaGen lista, void* objeto);

/*
    PRE: lista tiene que apuntar a una estructura ListaGenStruct, numNodo tiene que ser un numero
         de nodo existente (que no este por encima de cantNodos ni por debajo de cero)
    POST: Se devuelve un puntero al objeto en la posicion numNodo de la lista

    lista: puntero a una estructura de tipo ListaGenStruct
    numNodo: valor int
    return: puntero void al objeto seleccionado
*/
void* getObjeto(ListaGen lista, int numNodo);

/*
    PRE: lista tiene que apuntar a una estructura ListaGenStruct, numNodo tiene que ser un numero
         de nodo existente (que no este por encima de cantNodos ni por debajo de cero)
    POST: Se elimina la referencia al objeto en la lista, el objeto en si NO es eliminado

    lista: puntero a una estructura de tipo ListaGenStruct
    numNodo: valor int
*/
void delObjeto(ListaGen lista, int numNodo);

/*
    PRE: lista tiene que apuntar a una estructura ListaGenStruct
    POST: Se devuelve si la lista esta vacia o no

    lista: puntero a una estructura de tipo ListaGenStruct
    return: valor bool
*/
bool listaVacia(ListaGen lista);

/*
    PRE: lista tiene que apuntar a una estructura ListaGenStruct
    POST: Se devuelve el tamaño de la lista

    lista: puntero a una estructura de tipo ListaGenStruct
    return: valor int
*/
int getSize(ListaGen lista);

/*
    PRE: lista tiene que apuntar a una estructura ListaGenStruct, la lista referenciada no puede estar vacia
    POST: Se devuelve un puntero al ultimo objeto de la lista

    lista: puntero a una estructura de tipo ListaGenStruct
    return: puntero void al ultimo objeto de la lista
*/
void* getUltimo(ListaGen lista);

/*
    PRE: lista tiene que apuntar a una estructura ListaGenStruct, la lista referenciada no puede estar vacia
    POST: Se devuelve un puntero al primer objeto de la lista

    lista: puntero a una estructura de tipo ListaGenStruct
    return: puntero void al primer objeto de la lista
*/
void* getPrimero(ListaGen lista);

#endif // LISTA_H_INCLUDED
