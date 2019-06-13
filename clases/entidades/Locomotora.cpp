#include "Locomotora.h"
#include <iostream>
#include <SDL.H>
#include <SDL_image.h>

struct locomotoraStruct
{
    int xy[2];
    int direccion;
    ListaGen vagones;
    bool hasChumbo; //XD
    bool agregarVagon;
    int cantRecursos[6];
    int monedas;
    int widthHeight[2];
    SDL_Texture *imagen;
    SDL_Rect *rectImg = new SDL_Rect();
};

ptrLocomotora newLocomotora(SDL_Renderer *renderer)
{
    int i;
    ptrLocomotora locomotora = new locomotoraStruct;

    locomotora->xy[0] = 0;
    locomotora->xy[1] = 0;
    locomotora->widthHeight[0] = 40;
    locomotora->widthHeight[1] = 40;
    locomotora->direccion = 0;
    locomotora->vagones = newListaGen();
    locomotora->hasChumbo = false;
    locomotora->agregarVagon = false;
    for(i=0; i<6; i++)
        locomotora->cantRecursos[i] = 0;
    locomotora->monedas = 0;
    locomotora->imagen = IMG_LoadTexture(renderer, "img/c1/aba/0.png");
    locomotora->rectImg->x = locomotora->xy[0] * locomotora->widthHeight[0];
    locomotora->rectImg->y = locomotora->xy[1] * locomotora->widthHeight[1];
    locomotora->rectImg->w =locomotora->widthHeight[0];
    locomotora->rectImg->h =locomotora->widthHeight[1];
    return locomotora;
}

void delLocomotora(ptrLocomotora locomotora)
{
    int i;
    ListaGen vagones = getVagones(locomotora);

    for(i=0; i<getSize(vagones); i++)
        delVagon((ptrVagon)getObjeto(vagones,i));
    eliminarListaGen(vagones);
    delete locomotora;
}

int* getXY(ptrLocomotora locomotora)
{
    return locomotora->xy;
}

void setXY(ptrLocomotora locomotora, int xy[])
{
    locomotora->xy[0] = xy[0];
    locomotora->xy[1] = xy[1];
}

SDL_Texture* getImagen(ptrLocomotora locomotora)
{
    return locomotora->imagen;
}

void setImagen(ptrLocomotora locomotora, SDL_Texture* imagen)
{
    locomotora->imagen = imagen;
}

SDL_Rect* getRectImagen(ptrLocomotora locomotora)
{
    return locomotora->rectImg;
}

void setRectImagen(ptrLocomotora locomotora)
{
    locomotora->rectImg->x = locomotora->xy[0] * locomotora->widthHeight[0];
    locomotora->rectImg->y = locomotora->xy[1] * locomotora->widthHeight[1];
    locomotora->rectImg->w =locomotora->widthHeight[0];
    locomotora->rectImg->h =locomotora->widthHeight[1];
}


int getDireccionLocomotora(ptrLocomotora locomotora)
{
    return locomotora->direccion;
}

void setDireccionLocomotora(ptrLocomotora locomotora, int direccion)
{
    locomotora->direccion = direccion;
}


ListaGen getVagones(ptrLocomotora locomotora)
{
    return locomotora->vagones;
}

void setVagones(ptrLocomotora locomotora, ListaGen vagones)
{
    locomotora->vagones = vagones;
}

bool getHasChumbo(ptrLocomotora locomotora)
{
    return locomotora->hasChumbo;
}

void setHasChumbo(ptrLocomotora locomotora, bool hasChumbo)
{
    locomotora->hasChumbo = hasChumbo;
}

bool getAgregarVagon(ptrLocomotora locomotora)
{
    return locomotora->agregarVagon;
}

void setAgregarVagon(ptrLocomotora locomotora, bool agregarVagon)
{
    locomotora->agregarVagon = agregarVagon;
}

int* getCantRecursos(ptrLocomotora locomotora)
{
    return locomotora->cantRecursos;
}

void setCantRecursos(ptrLocomotora locomotora, int cantRecursos[])
{
    int i;
    for (i=0; i<6; i++)
        locomotora->cantRecursos[i] = cantRecursos[i];
}

int getMonedas(ptrLocomotora locomotora)
{
    return locomotora->monedas;
}

void setMonedas(ptrLocomotora locomotora, int monedas)
{
    locomotora->monedas = monedas;
}

/*  Ok, en caso de que alguien necesite saber como anda esto:
    La locomotora ejecuta la rutina de movimiento de todos los vagones que tiene en su lista y despu�s la suya,
    cuando hay un cambio de direcci�n en la locomotora se ejecuta el movimiento en esa direcci�n, sin embargo
    los vagones solo cambian de direcci�n una vez que llegan a la posici�n en la que estaba la locomotora cuando gir�.
    El movimiento ser�a algo as�:
    L = Locomotora
    Vx = Vagon

    Giro a la derecha arrancando desde una direcci�n hacia arriba:

    L     V1 L     V2 V1 L     V3 V2 V1 L
    V1 -> V2    -> V3       ->
    V2    V3
    V3

    Para este caso, si se considera que el XY de la locomotora y sus vagones en el arranque es:
    L = 5;5
    V1 = 5;6
    V2 = 5;7
    V3 = 5;8

    El movimiento ser�a:

    Primer movimiento:
    L = 6;5
    V1 = 5;5
    V2 = 5;6
    V2 = 5;7

    Segundo movimiento:
    L = 7;5
    V1 = 6;5
    V2 = 5;5
    V2 = 5;6

    Tercer movimiento:
    L = 8;5
    V1 = 7;5
    V2 = 6;5
    V2 = 5;5
*/
void moverLocomotora(ptrLocomotora locomotora)
{
    int i, ultDireccionMov, temp;
    ptrVagon vagon, nuevoVagon;

    if (getAgregarVagon(locomotora) && !listaVacia(getVagones(locomotora)))
        nuevoVagon = newVagon(getXY((ptrVagon)getUltimo(getVagones(locomotora)))[0],
                              getXY((ptrVagon)getUltimo(getVagones(locomotora)))[1], getDireccionVagon((ptrVagon)getUltimo(getVagones(locomotora))),
                              5*getMonedas(locomotora));
    else if (getAgregarVagon(locomotora))
        nuevoVagon = newVagon(getXY(locomotora)[0], getXY(locomotora)[1], getDireccionLocomotora(locomotora), 5*getMonedas(locomotora));

    switch(getDireccionLocomotora(locomotora))
    {
    //Derecha
    case 0:
        locomotora->xy[0]++;
        setRectImagen(locomotora);
        break;
    //Abajo
    case 1:
        locomotora->xy[1]++;
        setRectImagen(locomotora);
        break;
    //Izquierda
    case 2:
        locomotora->xy[0]--;
        setRectImagen(locomotora);
        break;
    //Arriba
    case 3:
        locomotora->xy[1]--;
        setRectImagen(locomotora);
        break;
    }

    //Los vagones se mueven acuerdo a su direccion, cuando hay uno desigual se setea DESPUES de moverse, para que en el proximo ciclo se mueva bien
    ultDireccionMov = getDireccionLocomotora(locomotora);
    for (i=0; i<getSize(getVagones(locomotora)); i++)
    {
        vagon = (ptrVagon)getObjeto(getVagones(locomotora),i);
        moverVagon(vagon);

        if(getDireccionVagon(vagon) != ultDireccionMov)
        {
            temp = getDireccionVagon((ptrVagon)getObjeto(getVagones(locomotora), i));
            setDireccionVagon(vagon, ultDireccionMov);
            ultDireccionMov = temp;
        }
        else
            ultDireccionMov = getDireccionVagon((ptrVagon)getObjeto(getVagones(locomotora), i));
    }

    if(getAgregarVagon(locomotora))
    {
        setAgregarVagon(locomotora, false);
        setMonedas(locomotora, 0);
        addObjeto(getVagones(locomotora), nuevoVagon);
    }
    //Lineas de testeo de la rutina de movimiento
    /*std::cout<<"Direccion Locomotora: "<<locomotora->direccion<<std::endl;
    std::cout<<"X Locomotora: "<<locomotora->xy[0]<<std::endl;
    std::cout<<"Y Locomotora: "<<locomotora->xy[1]<<std::endl;*/
}
