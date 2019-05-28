#include <iostream>
#include "clases/archivos/Parametros.h"
#include "clases/archivos/Comanda.h"
#include "clases/archivos/Mina.h"
#include "clases/listas/ListaGen.h"
#include "clases/entidades/Vagon.h"
#include "clases/entidades/Locomotora.h"
#include "clases/entidades/Caja.h"

#include <stdio.h>
#include <cstdlib>

using namespace std;

//Tests
void testParametros();
void testComanda();
void testMina();
void testVagon();
void cargarMinas(ListaGen lstMinas);

/*-------------------*/
void cargarMinas();

int main()
{
    //Tests

    //testParametros();
    //testComanda();
    //testMina();
    //testVagon();
    //testLocomotora();

    /*------------------------------------------------*/
    //Declaraciones
    ptrParametros parametros = newParametros();
    ptrComanda comanda = newComanda();
    ListaGen lstMinas = newListaGen();
    ptrLocomotora locomotora = newLocomotora();

    int i, j, k;

    //Init
    cargarParametros(parametros);
    cargarComanda(comanda);
    cargarMinas(lstMinas);

    //Bucle
    char tecla = '0';
    bool vagon, mina, estacion;
    int xy[2];

    //xy[0]=5;
    //xy[1]=5;
    //setXYLocomotora(locomotora, xy);

    addObjeto(getVagones(locomotora), newVagon(0, 1, 3));
    //addObjeto(getVagones(locomotora), newVagon(0, 2, 3));
    //addObjeto(getVagones(locomotora), newVagon(0, 3, 3));
    //setDireccionLocomotora(locomotora, 0);

    while (tecla != 'q')
    {
        system("cls");
        for(i=0;i<getTY(parametros);i++)
        {
            for(j=0;j<getTX(parametros);j++)
            {
                vagon = false;
                mina = false;
                estacion = false;
                for(k=0;k<getSize(getVagones(locomotora));k++)
                {
                    if(i==getXYVagon((ptrVagon)getObjeto(getVagones(locomotora),k))[1] &&
                       j==getXYVagon((ptrVagon)getObjeto(getVagones(locomotora),k))[0]) vagon = true;
                }
                for(k=0;k<getSize(lstMinas);k++)
                {
                    if(i==getPosY((ptrMina)getObjeto(lstMinas,k)) && j==getPosX((ptrMina)getObjeto(lstMinas,k))) mina = true;
                }
                if (i==getPosYE(parametros) && j==getPosXE(parametros)) estacion = true;

                if (i==getXYLocomotora(locomotora)[1] && j==getXYLocomotora(locomotora)[0]) cout<<"L";
                else if (vagon==true) cout<<"V";
                else if (mina==true) cout<<"M";
                else if (estacion==true) cout<<"E";
                else cout<<" ";
            }
        }
        if (getPosXE(parametros)==getXYLocomotora(locomotora)[0] && getPosYE(parametros)==getXYLocomotora(locomotora)[1])
            setAgregarVagon(locomotora, true);

        fflush(stdin);
        scanf("%c",&tecla);

        switch(tecla)
        {
            case 'd':
                if(getDireccionLocomotora(locomotora)!=2) setDireccionLocomotora(locomotora, 0);
                break;
            case 's':
                if(getDireccionLocomotora(locomotora)!=3) setDireccionLocomotora(locomotora, 1);
                break;
            case 'a':
                if(getDireccionLocomotora(locomotora)!=0) setDireccionLocomotora(locomotora, 2);
                break;
            case 'w':
                if(getDireccionLocomotora(locomotora)!=1) setDireccionLocomotora(locomotora, 3);
                break;
        }
        if(tecla != 'q') moverLocomotora(locomotora);
    }

    //Limpieza de variables
    delParametros(parametros);
    delComanda(comanda);
    for(i=0;i<getSize(lstMinas);i++) delMina((ptrMina)getObjeto(lstMinas, i));
    eliminarListaGen(lstMinas);
    delLocomotora(locomotora);
    return 0;
}

void testParametros()
{
    ptrParametros parametros = newParametros();
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
    cout<<getTX(parametros)<<"\n";
    cout<<getTY(parametros)<<"\n";
    delParametros(parametros);
}

void testComanda()
{
    ptrComanda comanda = newComanda();
    cargarComanda(comanda);
    cout<<getOro(comanda)<<"\n";
    cout<<getPlata(comanda)<<"\n";
    cout<<getBronce(comanda)<<"\n";
    cout<<getPlatino(comanda)<<"\n";
    cout<<getRoca(comanda)<<"\n";
    cout<<getCarbon(comanda)<<"\n";
    delComanda(comanda);
}

void testMina()
{
    int i,j;
    FILE* fMina;
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
    eliminarListaGen(lista);
}

void testVagon()
{
    int i;
    ptrVagon vagon = newVagon(0,0,0);
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
}

void testLocomotora()
{
    ptrLocomotora locomotora = newLocomotora();
    int xy[2];
    xy[0]=5;
    xy[1]=5;

    setXYLocomotora(locomotora, xy);
    setDireccionLocomotora(locomotora, 3);

    addObjeto(getVagones(locomotora), newVagon(5,6,3));
    addObjeto(getVagones(locomotora), newVagon(5,7,3));

    setDireccionLocomotora(locomotora, 0);
    moverLocomotora(locomotora);
    moverLocomotora(locomotora);

    setDireccionLocomotora(locomotora, 1);
    moverLocomotora(locomotora);
    moverLocomotora(locomotora);

    delLocomotora(locomotora);
}


/*--------------------------------------------------------*/
void cargarMinas(ListaGen lstMinas)
{
    int i;
    FILE* fMina;

    i=0;
    fMina=fopen("minas.txt","r");
    while(!feof(fMina))
    {
        addObjeto(lstMinas,newMina());
        leerLineaMina(fMina, (ptrMina)getObjeto(lstMinas, i));
        i++;

    }
    fclose(fMina);
}
