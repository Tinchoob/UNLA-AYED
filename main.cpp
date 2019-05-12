#include <iostream>
#include "clases/archivos/Parametros.h"
#include "clases/archivos/Comanda.h"
#include "clases/archivos/Mina.h"
#include "clases/listas/ListaGen.h"
#include "clases/entidades/vagon.h"
#include "clases/entidades/caja.h"

#include <stdio.h>

using namespace std;

int main()
{
    int i,j;

    /*ptrParametros parametros = newParametros();
    cargarParametros(parametros);
    cout<<getS(parametros)<<"\n";
    cout<<getP(parametros)<<"\n";
    cout<<getA(parametros)<<"\n";
    cout<<getPosXE(parametros)<<"\n";
    cout<<getPosYE(parametros)<<"\n";
    cout<<getIM(parametros)<<"\n";
    cout<<getVM(parametros)<<"\n";
    cout<<getIB(parametros)<<"\n";
    cout<<getVB(parametros)<<"\n";
    cout<<getIP(parametros)<<"\n";
    delParametros(parametros);*/

    /*ptrComanda comanda = newComanda();
    cargarComanda(comanda);
    cout<<getOro(comanda)<<"\n";
    cout<<getPlata(comanda)<<"\n";
    cout<<getBronce(comanda)<<"\n";
    cout<<getPlatino(comanda)<<"\n";
    cout<<getRoca(comanda)<<"\n";
    cout<<getCarbon(comanda)<<"\n";
    delComanda(comanda);*/

    /*FILE* fMina;
    int* seq;
    ListaGen lista = newListaGen();

    j=0;
    fMina=fopen("minas.txt","r");
    while(!feof(fMina))
    {
        addObjeto(lista,newMina());
        leerLineaMina(fMina, (ptrMina)getObjeto(lista, j));
        j++;

    }
    fclose(fMina);

    cout<<getPosX((ptrMina)getObjeto(lista, 1))<<endl;
    cout<<getPosY((ptrMina)getObjeto(lista, 1))<<endl;
    cout<<getCodItem((ptrMina)getObjeto(lista, 1))<<endl;
    cout<<getIP((ptrMina)getObjeto(lista, 1))<<endl;
    seq = getSeq((ptrMina)getObjeto(lista, 1));
    for(i=0;i<5;i++) cout<<seq[i]<<endl;
    delMina((ptrMina)getObjeto(lista, 0));
    delMina((ptrMina)getObjeto(lista, 1));
    eliminarListaGen(lista);*/

    ptrVagon vagon = newVagon();
    ptrCaja caja;

    setTipoRecurso(vagon, 1);

    for(i=0;i<3;i++)
    {
        caja = newCaja();
        setTipoRecurso(caja, 1);
        setCantidad(caja, i+1);
        addObjeto(getCajas(vagon), caja);
    }
    cout<<getCantidadTotalLingotes(vagon)<<endl;
    delVagon(vagon);

    return 0;
}

