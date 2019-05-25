#include "Locomotora.h"
#include <iostream>

struct locomotoraStruct
{
    int xy[2];
    int direccion;
    ListaGen vagones;
    bool hasChumbo; //XD
};

ptrLocomotora newLocomotora()
{
    ptrLocomotora locomotora = new locomotoraStruct;

    locomotora->xy[0] = 0;
    locomotora->xy[1] = 0;
    locomotora->direccion = 0;
    locomotora->vagones = newListaGen();
    locomotora->hasChumbo = false;

    return locomotora;
}

void delLocomotora(ptrLocomotora locomotora)
{
    int i;
    ListaGen vagones = getVagones(locomotora);

    for(i=0;i<getSize(vagones);i++) delVagon((ptrVagon)getObjeto(vagones,i));
    eliminarListaGen(vagones);
    delete locomotora;
}

int* getXYLocomotora(ptrLocomotora locomotora)
{
    return locomotora->xy;
}

void setXYLocomotora(ptrLocomotora locomotora, int xy[])
{
    locomotora->xy[0] = xy[0];
    locomotora->xy[1] = xy[1];
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

void moverLocomotora(ptrLocomotora locomotora)
{
    int i, ultDireccionMov, temp;
    ptrVagon vagon;
    switch(getDireccionLocomotora(locomotora))
    {
        //Derecha
        case 0:
            locomotora->xy[0]++;
            break;
        //Abajo
        case 1:
            locomotora->xy[1]++;
            break;
        //Izquierda
        case 2:
            locomotora->xy[0]--;
            break;
        //Arriba
        case 3:
            locomotora->xy[1]--;
            break;
    }

    //Los vagones se mueven acuerdo a su direccion, cuando hay uno desigual se setea DESPUES de moverse, para que en el proximo ciclo se mueva bien
    ultDireccionMov = getDireccionLocomotora(locomotora);
    for (i=0;i<getSize(getVagones(locomotora));i++)
    {
        vagon = (ptrVagon)getObjeto(getVagones(locomotora),i);
        moverVagon(vagon);

        if(getDireccionVagon(vagon) != ultDireccionMov)
        {
            temp = getDireccionVagon((ptrVagon)getObjeto(getVagones(locomotora), i));
            setDireccionVagon(vagon, ultDireccionMov);
            ultDireccionMov = temp;
        }
        else ultDireccionMov = getDireccionVagon((ptrVagon)getObjeto(getVagones(locomotora), i));
    }
    std::cout<<"Direccion Locomotora: "<<locomotora->direccion<<std::endl;
    std::cout<<"X Locomotora: "<<locomotora->xy[0]<<std::endl;
    std::cout<<"Y Locomotora: "<<locomotora->xy[1]<<std::endl;
}
