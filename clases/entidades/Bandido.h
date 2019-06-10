#ifndef BANDIDO_H_INCLUDED
#define BANDIDO_H_INCLUDED

#include "Locomotora.h"
#include "../archivos/Parametros.h"

struct bandidoStruct;
typedef struct bandidoStruct* ptrBandido;

/*
    PRE: Se llama para asignar a un puntero que no puede estar inicializado, tipoRecurso debe
         contener un valor entre 1 y 6 inclusive, cantidad no puede superar el valor de p en parametros,
         tiempoVida no puede superar el valor de vb en parametros, xy tiene que tener como mínimo 2 posiciones
         y los valores deben estar dentro de los bordes del mapa especificados en parametros, parametros
         debe apuntar a una estructura existente
    POST: Se devuelve un ptrBandido que apunta a una bandidoStruct nueva

    tipoRecurso: valor int
    cantidad: valor int
    tiempoVida: valor int
    xy: array de valores int, también acepta punteros int*
    parametros: puntero a estructura de tipo parametrosStruct
    return: puntero a nueva bandidoStruct
*/
ptrBandido newBandido(int tipoRecurso, int cantidad, int tiempoVida, int xy[], ptrParametros parametros);

/*
    PRE: bandido debe apuntar a una estructura existente
    POST: Se libera el espacio de memoria de la estructura a la que apuntaba bandido

    bandido: puntero a una estructura de tipo bandidoStruct
*/
void delBandido(ptrBandido bandido);

/*
    PRE: bandido tiene que apuntar a una estructura bandidoStruct
    POST: Se devuelve el valor de tipoRecurso

    bandido: puntero a una estructura de tipo bandidoStruct
    return: valor int
*/
int getTipoRecurso(ptrBandido bandido);

/*
    PRE: bandido tiene que apuntar a una estructura bandidoStruct, el valor de tipoRecurso debe estar en un rango de 1 a 6
    POST: Se le asigna el valor enviado por tipoRecurso a bandido->tipoRecurso

    bandido: puntero a una estructura de tipo bandidoStruct
    tipoRecurso: valor int, solo puede contener valores de 1 a 6 inclusive
*/
void setTipoRecurso(ptrBandido bandido, int tipoRecurso);

/*
    PRE: bandido tiene que apuntar a una estructura bandidoStruct
    POST: Se devuelve el valor de cantidad

    bandido: puntero a una estructura de tipo bandidoStruct
    return: valor int
*/
int getCantidad(ptrBandido bandido);

/*
    PRE: bandido tiene que apuntar a una estructura bandidoStruct, el valor de cantidad no puede superar el valor de p en parametros
    POST: Se le asigna el valor enviado por cantidad a bandido->cantidad

    bandido: puntero a una estructura de tipo bandidoStruct
    cantidad: valor int, no puede superar el valor de p en parametros
*/
void setCantidad(ptrBandido bandido, int cantidad);

/*
    PRE: bandido tiene que apuntar a una estructura bandidoStruct
    POST: Se devuelve el valor de tiempoVida

    bandido: puntero a una estructura de tipo bandidoStruct
    return: valor int
*/
int getTiempoVida(ptrBandido bandido);

/*
    PRE: bandido tiene que apuntar a una estructura bandidoStruct, el valor de tiempoVida no puede superar el valor de vb en parametros
    POST: Se le asigna el valor enviado por tiempoVida a bandido->tiempoVida

    bandido: puntero a una estructura de tipo bandidoStruct
    tiempoVida: valor int, no puede superar el valor de vb en parametros
*/
void setTiempoVida(ptrBandido bandido, int tiempoVida);

/*
    PRE: bandido tiene que apuntar a una estructura bandidoStruct
    POST: Se devuelve un puntero a xy

    bandido: puntero a una estructura de tipo bandidoStruct
    return: puntero a int
*/
int* getXY(ptrBandido bandido);

/*
    PRE: bandido tiene que apuntar a una estructura bandidoStruct
    POST: Se le asigna los valores enviados por xy a bandido->xy

    bandido: puntero a una estructura de tipo bandidoStruct
    xy: array de valores int, tiene que tener como mínimo 2 posiciones
*/
void setXY(ptrBandido bandido, int xy[]);

/*
    PRE: bandido tiene que apuntar a una estructura bandidoStruct
    POST: Se devuelve un puntero a bandido->parametros

    bandido: puntero a una estructura de tipo bandidoStruct
    return: puntero a una parametrosStruct
*/
ptrParametros getParametros(ptrBandido bandido);

/*
    PRE: bandido tiene que apuntar a una estructura bandidoStruct
    POST: Se cambia la referencia de bandido->parametros a la enviada por parametros

    bandido: puntero a una estructura de tipo bandidoStruct
    parametros: puntero a una estructura de tipo parametrosStruct
*/
void setParametros(ptrBandido bandido, ptrParametros parametros);

/*
    PRE: bandido tiene que apuntar a una estructura bandidoStruct
    POST: El valor de bandido->tiempoVida se reduce en uno, si ya está en cero, se elimina a bandido
          se devuelve un int que de acorde al valor señala si el bandido sigue siendo valido o no
          (0 para valido, 1 para eliminado)

    bandido: puntero a una estructura de tipo bandidoStruct
    locomotora: puntero a una estructura de tipo locomotoraStruct
    perder: valor bool
    return: valor int, indica con 0 que el bandido sigue vivo o con 1 que fue eliminado de la memoria
*/
int tickBandido(ptrBandido bandido, ptrLocomotora locomotora, ptrParametros parametros, bool &perder);


#endif // BANDIDO_H_INCLUDED
