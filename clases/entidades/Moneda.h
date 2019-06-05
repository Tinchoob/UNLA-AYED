#ifndef MONEDA_H_INCLUDED
#define MONEDA_H_INCLUDED

#include "../archivos/Parametros.h"
#include "Locomotora.h"

struct monedaStruct;
typedef struct monedaStruct* ptrMoneda;

/*
    PRE: Se llama para asignar a un puntero que no puede estar inicializado, el valor de x debe ser >=0 y
    <= al valor de tx en parametros, el valor de y debe ser >=0 y <= al valor de ty en parametros,
    tiempoVida no puede superar el valor de vm en parametros
    POST: Se devuelve un ptrMoneda que apunta a una monedaStruct nueva

    x: valor int
    y: valor int
    tiempoVida: valor int
    parametros: puntero a parametrosStruct
    return: puntero a monedaStruct
*/
ptrMoneda newMoneda(int x, int y, int tiempoVida, ptrParametros parametros);

/*
    PRE: moneda debe apuntar a una estructura existente
    POST: Se libera el espacio de memoria de la estructura a la que apuntaba moneda

    moneda: puntero a una estructura de tipo monedaStruct
*/
void delMoneda(ptrMoneda moneda);

/*
    PRE: moneda tiene que apuntar a una estructura monedaStruct
    POST: Se devuelve un puntero a moneda->xy

    moneda: puntero a una estructura de tipo monedaStruct
    return: puntero a int
*/
int* getXY(ptrMoneda moneda);

/*
    PRE: moneda tiene que apuntar a una estructura monedaStruct
    POST: Se le asigna los valores enviados por xy a moneda->xy

    moneda: puntero a una estructura de tipo monedaStruct
    xy: array de valores int, tiene que tener como mínimo 2 posiciones
*/
void setXY(ptrMoneda moneda, int xy[]);

/*
    PRE: moneda tiene que apuntar a una estructura monedaStruct, el valor de tiempoVida no puede superar el valor de vm en parametros
    POST: Se devuelve el valor de moneda->tiempoVida

    moneda: puntero a una estructura de tipo monedaStruct
    return: valor int
*/
int getTiempoVida(ptrMoneda moneda);

/*
    PRE: moneda tiene que apuntar a una estructura monedaStruct
    POST: Se le asigna el valor enviado por tiempoVida a moneda->tiempoVida

    moneda: puntero a una estructura de tipo monedaStruct
    tiempoVida: valor int
*/
void setTiempoVida(ptrMoneda moneda, int tiempoVida);

/*
    PRE: moneda tiene que apuntar a una estructura monedaStruct
    POST: Se devuelve un puntero a moneda->parametros

    moneda: puntero a una estructura de tipo monedaStruct
    return: puntero a una parametrosStruct
*/
ptrParametros getParametros(ptrMoneda moneda);

/*
    PRE: moneda tiene que apuntar a una estructura monedaStruct
    POST: Se cambia la referencia de moneda->parametros a la enviada por parametros

    moneda: puntero a una estructura de tipo monedaStruct
    parametros: puntero a una estructura de tipo parametrosStruct
*/
void setParametros(ptrMoneda moneda, ptrParametros parametros);

/*
    PRE: moneda tiene que apuntar a una estructura monedaStruct, locomotora tiene que apuntar a una estructura locomotoraStruct
    POST: Se resta 1 al valor de moneda->tiempoVida y se devuelve un valor que indica el estado de la moneda,
    0 si aún tiene tiempo de vida, 1 en caso contrario, si la moneda está en las mismas coordenadas que la locomotora,
    se incrementa en 1 el valor de locomotora->monedas

    moneda: puntero a una estructura de tipo monedaStruct
    locomotora: puntero a una estructura de tipo locomotoraStruct
    return: valor int
*/
int tickMoneda(ptrMoneda moneda, ptrLocomotora locomotora);

#endif // MONEDA_H_INCLUDED
