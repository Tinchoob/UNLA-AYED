#ifndef PARAMETROS_H_INCLUDED
#define PARAMETROS_H_INCLUDED

struct parametrosStruct;
typedef struct parametrosStruct* ptrParametros;

/*
    PRE: Se llama para asignar a un puntero que no puede estar inicializado
    POST: Se devuelve un ptrParametros que apunta a una parametrosStruct nueva

    return: puntero a nueva parametrosStruct

    Los valores internos se deben setear uno a uno con los set
*/
ptrParametros newParametros();

/*
    PRE: parametros debe apuntar a una estructura existente
    POST: Se libera el espacio de memoria de la estructura a la que apuntaba parametros

    parametros: puntero a una estructura de tipo parametrosStruct
*/
void delParametros(ptrParametros parametros);

/*
    PRE: parametros tiene que apuntar a una estructura parametrosStruct
    POST: Se devuelve el valor de s

    parametros: puntero a una estructura de tipo parametrosStruct
*/
long getS(ptrParametros parametros);

/*
    PRE: parametros tiene que apuntar a una estructura parametrosStruct
    POST: Se le asigna el valor enviado por s a parametros->s

    parametros: puntero a una estructura de tipo parametrosStruct
    s: valor long
*/
void setS(ptrParametros parametros, long s);

/*
    PRE: parametros tiene que apuntar a una estructura parametrosStruct
    POST: Se devuelve el valor de p

    parametros: puntero a una estructura de tipo parametrosStruct
*/
long getP(ptrParametros parametros);

/*
    PRE: parametros tiene que apuntar a una estructura parametrosStruct
    POST: Se le asigna el valor enviado por p a parametros->p

    parametros: puntero a una estructura de tipo parametrosStruct
    p: valor long
*/
void setP(ptrParametros parametros, long p);

/*
    PRE: parametros tiene que apuntar a una estructura parametrosStruct
    POST: Se devuelve el valor de a

    parametros: puntero a una estructura de tipo parametrosStruct
*/
long getA(ptrParametros parametros);

/*
    PRE: parametros tiene que apuntar a una estructura parametrosStruct
    POST: Se le asigna el valor enviado por a a parametros->a

    parametros: puntero a una estructura de tipo parametrosStruct
    a: valor long
*/
void setA(ptrParametros parametros, long a);

/*
    PRE: parametros tiene que apuntar a una estructura parametrosStruct
    POST: Se devuelve el valor de posXE

    parametros: puntero a una estructura de tipo parametrosStruct
*/
long getPosXE(ptrParametros parametros);

/*
    PRE: parametros tiene que apuntar a una estructura parametrosStruct
    POST: Se le asigna el valor enviado por a posXE parametros->posXE

    parametros: puntero a una estructura de tipo parametrosStruct
    posXE: valor long
*/
void setPosXE(ptrParametros parametros, long posXE);

/*
    PRE: parametros tiene que apuntar a una estructura parametrosStruct
    POST: Se devuelve el valor de posYE

    parametros: puntero a una estructura de tipo parametrosStruct
*/
long getPosYE(ptrParametros parametros);

/*
    PRE: parametros tiene que apuntar a una estructura parametrosStruct
    POST: Se le asigna el valor enviado por a posYE parametros->posYE

    parametros: puntero a una estructura de tipo parametrosStruct
    posYE: valor long
*/
void setPosYE(ptrParametros parametros, long posYE);

/*
    PRE: parametros tiene que apuntar a una estructura parametrosStruct
    POST: Se devuelve el valor de im

    parametros: puntero a una estructura de tipo parametrosStruct
*/
long getIM(ptrParametros parametros);

/*
    PRE: parametros tiene que apuntar a una estructura parametrosStruct
    POST: Se le asigna el valor enviado por a im parametros->im

    parametros: puntero a una estructura de tipo parametrosStruct
    im: valor long
*/
void setIM(ptrParametros parametros, long im);

/*
    PRE: parametros tiene que apuntar a una estructura parametrosStruct
    POST: Se devuelve el valor de vm

    parametros: puntero a una estructura de tipo parametrosStruct
*/
long getVM(ptrParametros parametros);

/*
    PRE: parametros tiene que apuntar a una estructura parametrosStruct
    POST: Se le asigna el valor enviado por a vm parametros->vm

    parametros: puntero a una estructura de tipo parametrosStruct
    vm: valor long
*/
void setVM(ptrParametros parametros, long vm);

/*
    PRE: parametros tiene que apuntar a una estructura parametrosStruct
    POST: Se devuelve el valor de ib

    parametros: puntero a una estructura de tipo parametrosStruct
*/
long getIB(ptrParametros parametros);

/*
    PRE: parametros tiene que apuntar a una estructura parametrosStruct
    POST: Se le asigna el valor enviado por a ib parametros->ib

    parametros: puntero a una estructura de tipo parametrosStruct
    ib: valor long
*/
void setIB(ptrParametros parametros, long ib);

/*
    PRE: parametros tiene que apuntar a una estructura parametrosStruct
    POST: Se devuelve el valor de vb

    parametros: puntero a una estructura de tipo parametrosStruct
*/
long getVB(ptrParametros parametros);

/*
    PRE: parametros tiene que apuntar a una estructura parametrosStruct
    POST: Se le asigna el valor enviado por a vb parametros->vb

    parametros: puntero a una estructura de tipo parametrosStruct
    vb: valor long
*/
void setVB(ptrParametros parametros, long vb);

/*
    PRE: parametros tiene que apuntar a una estructura parametrosStruct
    POST: Se devuelve el valor de ip

    parametros: puntero a una estructura de tipo parametrosStruct
*/
long getIP(ptrParametros parametros);

/*
    PRE: parametros tiene que apuntar a una estructura parametrosStruct
    POST: Se le asigna el valor enviado por a ip parametros->ip

    parametros: puntero a una estructura de tipo parametrosStruct
    ip: valor long
*/
void setIP(ptrParametros parametros, long ip);

/*
    PRE: parametros tiene que apuntar a una estructura parametrosStruct
    POST: Se cargan los valores del archivo parametros.txt en parametros

    parametros: puntero a una estructura de tipo parametrosStruct
*/
void cargarParametros(ptrParametros parametros);

/*
    PRE: destino y fParametros tienen que estar inicializados
    POST: Se lee una linea del archivo que se indique por fParametros

    destino: puntero a variable char, lo que se lea se almacena a donde el puntero apunte
    fParametros: puntero tipo FILE
*/
void leerLineaParametros(char* destino, FILE* fParametros);

#endif // PARAMETROS_H_INCLUDED
