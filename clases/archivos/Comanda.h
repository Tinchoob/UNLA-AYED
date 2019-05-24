#ifndef COMANDA_H_INCLUDED
#define COMANDA_H_INCLUDED

struct comandaStruct;
typedef struct comandaStruct* ptrComanda;

/*
    PRE: Se llama para asignar a un puntero que no puede estar inicializado
    POST: Se devuelve un ptrComanda que apunta a una comandaStruct nueva

    return: puntero a nueva comandaStruct

    Los valores internos se deben setear uno a uno con los set
*/
ptrComanda newComanda();

/*
    PRE: comanda debe apuntar a una estructura existente
    POST: Se libera el espacio de memoria de la estructura a la que apuntaba comanda

    comanda: puntero a una estructura de tipo comandaStruct
*/
void delComanda(ptrComanda comanda);

/*
    PRE: comanda tiene que apuntar a una estructura comandaStruct
    POST: Se devuelve el valor de oro

    comanda: puntero a una estructura de tipo comandaStruct
*/
int getOro(ptrComanda comanda);

/*
    PRE: comanda tiene que apuntar a una estructura comandaStruct
    POST: Se le asigna el valor enviado por oro a comanda->oro

    comanda: puntero a una estructura de tipo comandaStruct
    oro: valor int
*/
void setOro(ptrComanda comanda, int oro);

/*
    PRE: comanda tiene que apuntar a una estructura comandaStruct
    POST: Se devuelve el valor de plata

    comanda: puntero a una estructura de tipo comandaStruct
*/
int getPlata(ptrComanda comanda);

/*
    PRE: comanda tiene que apuntar a una estructura comandaStruct
    POST: Se le asigna el valor enviado por plata a comanda->plata

    comanda: puntero a una estructura de tipo comandaStruct
    plata: valor int
*/
void setPlata(ptrComanda comanda, int plata);

/*
    PRE: comanda tiene que apuntar a una estructura comandaStruct
    POST: Se devuelve el valor de bronce

    comanda: puntero a una estructura de tipo comandaStruct
*/
int getBronce(ptrComanda comanda);

/*
    PRE: comanda tiene que apuntar a una estructura comandaStruct
    POST: Se le asigna el valor enviado por bronce a comanda->bronce

    comanda: puntero a una estructura de tipo comandaStruct
    bronce: valor int
*/
void setBronce(ptrComanda comanda, int bronce);

/*
    PRE: comanda tiene que apuntar a una estructura comandaStruct
    POST: Se devuelve el valor de platino

    comanda: puntero a una estructura de tipo comandaStruct
*/
int getPlatino(ptrComanda comanda);

/*
    PRE: comanda tiene que apuntar a una estructura comandaStruct
    POST: Se le asigna el valor enviado por platino a comanda->platino

    comanda: puntero a una estructura de tipo comandaStruct
    platino: valor int
*/
void setPlatino(ptrComanda comanda, int platino);

/*
    PRE: comanda tiene que apuntar a una estructura comandaStruct
    POST: Se devuelve el valor de roca

    comanda: puntero a una estructura de tipo comandaStruct
*/
int getRoca(ptrComanda comanda);

/*
    PRE: comanda tiene que apuntar a una estructura comandaStruct
    POST: Se le asigna el valor enviado por roca a comanda->roca

    comanda: puntero a una estructura de tipo comandaStruct
    roca: valor int
*/
void setRoca(ptrComanda comanda, int roca);

/*
    PRE: comanda tiene que apuntar a una estructura comandaStruct
    POST: Se devuelve el valor de carbon

    comanda: puntero a una estructura de tipo comandaStruct
*/
int getCarbon(ptrComanda comanda);

/*
    PRE: comanda tiene que apuntar a una estructura comandaStruct
    POST: Se le asigna el valor enviado por carbon a comanda->carbon

    comanda: puntero a una estructura de tipo comandaStruct
    carbon: valor int
*/
void setCarbon(ptrComanda comanda, int carbon);

/*
    PRE: comanda tiene que apuntar a una estructura comandaStruct
    POST: Se cargan los valores del archivo comanda.txt en comanda

    comanda: puntero a una estructura de tipo comandaStruct
*/
void cargarComanda(ptrComanda comanda);

/*
    PRE: destino y fComanda tienen que estar inicializados
    POST: Se lee una linea del archivo que se indique por fComanda

    destino: puntero a variable char, lo que se lea se almacena a donde el puntero apunte
    fComanda: puntero tipo FILE
*/
void leerLineaComanda(char* destino, FILE* fComanda);

#endif // COMANDA_H_INCLUDED
