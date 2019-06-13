#ifndef VAGON_H_INCLUDED
#define VAGON_H_INCLUDED

#include "../listas/ListaGen.h"
#include <ctype.h>
#include <cstdlib>
#include <SDL_image.h>

struct vagonStruct;
typedef struct vagonStruct* ptrVagon;

/*
    PRE: Se llama para asignar a un puntero que no puede estar inicializado, x e y deben contener valores mayores o iguales a cero
         y deben estar dentro de los limites del mapa (definidos por los valores correspondientes en el archivo parametros), dirección
         debe contener un valor entre 0 y 3 inclusive
    POST: Se devuelve un ptrVagon que apunta a una vagonStruct nueva

    x: valor int
    y: valor int
    direccion: valor int
    capacidad: valor int
    return: puntero a nueva vagonStruct
*/
ptrVagon newVagon(SDL_Renderer* renderer,int x, int y, int direccion, int capacidad);

/*
    PRE: vagon debe apuntar a una estructura existente
    POST: Se libera el espacio de memoria de la estructura a la que apuntaba vagon

    vagon: puntero a una estructura de tipo vagonStruct
*/
void delVagon(ptrVagon vagon);

/*
    PRE: vagon tiene que apuntar a una estructura vagonStruct
    POST: Se devuelve un puntero a xy

    vagon: puntero a una estructura de tipo vagonStruct
*/
int* getXY(ptrVagon vagon);

/*
    PRE: vagon tiene que apuntar a una estructura vagonStruct
    POST: Se le asigna los valores enviados por xy a vagon->xy

    vagon: puntero a una estructura de tipo vagonStruct
    xy: array de valores int, tiene que tener como mínimo 2 posiciones
*/
void setXY(ptrVagon vagon, int xy[]);

/*
    PRE: vagon tiene que apuntar a una estructura vagonStruct
    POST: Se devuelve el valor de tipoRecurso

    vagon: puntero a una estructura de tipo vagonStruct
*/
int getTipoRecurso(ptrVagon vagon);

/*
    PRE: vagon tiene que apuntar a una estructura vagonStruct
    POST: Se le asigna el valor enviado por tipoRecurso a vagon->tipoRecurso

    vagon: puntero a una estructura de tipo vagonStruct
    tipoRecurso: valor int
*/
void setTipoRecurso(ptrVagon vagon, int tipoRecurso);

/*
    PRE: vagon tiene que apuntar a una estructura vagonStruct
    POST: Se devuelve un puntero a cajas

    vagon: puntero a una estructura de tipo vagonStruct
*/
ListaGen getCajas(ptrVagon vagon);

/*
    PRE: vagon tiene que apuntar a una estructura vagonStruct
    POST: Se cambia la referencia de vagon->cajas a la direccion indicada por cajas

    vagon: puntero a una estructura de tipo vagonStruct
    cajas: puntero a una ListaGenStruct
*/
void setCajas(ptrVagon vagon, ListaGen cajas);

/*
    PRE: vagon tiene que apuntar a una estructura vagonStruct
    POST: Se devuelve la direccion del vagon

    vagon: puntero a una estructura de tipo vagonStruct
    return: valor int
*/
int getDireccionVagon(ptrVagon vagon);

/*
    PRE: vagon tiene que apuntar a una estructura vagonStruct
    POST: Se setea el valor de direccion, el cual indica hacia donde se mueve el vagon en la rutina moverVagon

    vagon: puntero a una estructura de tipo vagonStruct
    direccion: valor int, debe ser un valor entre 0 y 3 inclusive
*/
void setDireccionVagon(ptrVagon vagon, int direccion);

/*
    PRE: vagon tiene que apuntar a una estructura vagonStruct
    POST: Se devuelve el valor de vagon->capacidad

    vagon: puntero a una estructura de tipo vagonStruct
    return: valor int
*/
int getCapacidad(ptrVagon vagon);

/*
    PRE: vagon tiene que apuntar a una estructura vagonStruct
    POST: Se le asigna el valor enviado por capacidad a vagon->capacidad

    vagon: puntero a una estructura de tipo vagonStruct
    capacidad: valor int
*/
void setCapacidad(ptrVagon vagon, int capacidad);

/*
    PRE: vagon tiene que apuntar a una estructura vagonStruct
    POST: Se devuelve la cantidad total de lingotes en todas las cajas del vagon

    vagon: puntero a una estructura de tipo vagonStruct
*/
int cantidadTotalLingotes(ptrVagon vagon);

/*
    PRE: vagon tiene que apuntar a una estructura vagonStruct
    POST: Se quita la cantidad de lingotes indicada del vagon, no se puede pedir quitar mas
          que la suma total de todos los lingotes en las cajas del vagon

    vagon: puntero a una estructura de tipo vagonStruct
    cantidad: valor int
*/
void quitarLingotes(ptrVagon vagon, int cantidad);

/*
    PRE: vagon tiene que apuntar a una estructura vagonStruct
    POST: se modifican las coordenadas almacenadas en xy segun la dirección actual del vagon

    vagon: puntero a una estructura de tipo vagonStruct
*/
void moverVagon(ptrVagon vagon);

/*
    PRE: bandido tiene que apuntar a una estructura bandidoStruct
    POST: Se devuelve el valor la textura de imagen del bandido

    bandido: puntero a una estructura de tipo bandidoStruct
    return: valor texture
*/

SDL_Texture* getImagen(ptrVagon vagon);

/*
    PRE: bandido tiene que apuntar a una estructura bandidoStruct
    POST: Se le asigna el valor enviado por imagen

    bandido: puntero a una estructura de tipo bandidoStruct
    imagen: textura de la imagen del bandido
*/

void setImagen(ptrVagon vagon, SDL_Texture* imagen);


/*
    PRE: bandido tiene que apuntar a una estructura bandidoStruct
    POST: Se devuelve el valor del rect del bandido

    bandido: puntero a una estructura de tipo bandidoStruct
    return: valor rect
*/

SDL_Rect* getRectImagen(ptrVagon vagon);

/*
    PRE: bandido tiene que apuntar a una estructura bandidoStruct
    POST: Se le asigna el valor al rect del bandido

    bandido: puntero a una estructura de tipo bandidoStruct
*/

void setRectImagen(ptrVagon vagon);

#endif // VAGON_H_INCLUDED
