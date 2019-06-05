#include <iostream>
#include "clases/archivos/Parametros.h"
#include "clases/archivos/Comanda.h"
#include "clases/archivos/Mina.h"
#include "clases/listas/ListaGen.h"
#include "clases/entidades/Vagon.h"
#include "clases/entidades/Locomotora.h"
#include "clases/entidades/Caja.h"
#include "clases/entidades/Bandido.h"
#include "clases/entidades/Moneda.h"

#include <stdio.h>
#include <time.h>
#include <cstdlib>

/*Esto solo se usa para la pantalla de prueba -------------*/
#include <windows.h>
void gotoxy(int x, int y);
/*Esto solo se usa para la pantalla de prueba -------------*/


using namespace std;

//Tests
void testParametros();
void testComanda();
void testMina();
void testVagon();
void testBandido();

/*-------------------*/
void cargarMinas(ListaGen lstMinas);

int main()
{
    //Tests

    //testParametros();
    //testComanda();
    //testMina();
    //testVagon();
    //testLocomotora();
    //testBandido();

    /*------------------------------------------------*/
    //Declaraciones
    ptrParametros parametros = newParametros();
    ptrComanda comanda = newComanda();
    ListaGen lstMinas = newListaGen();
    ptrLocomotora locomotora = newLocomotora();
    ListaGen lstBandidos = newListaGen();
    ListaGen lstMonedas = newListaGen();

    int i, j, k, ticksUltBandido=0, ticksUltMoneda=0, monedas=0;
    int xy[2];

    //Init
    cargarParametros(parametros);
    cargarComanda(comanda);
    cargarMinas(lstMinas);

    //Bucle
    char tecla = '0';
    bool vagon, mina, estacion, bandido, moneda;

    addObjeto(getVagones(locomotora), newVagon(0, 1, 3));
    srand(time(NULL));
    while (tecla != 'q')
    {
        ticksUltBandido++;
        if(rand()%2==1 || ticksUltBandido>=getIB(parametros))
        {
            ticksUltBandido = 0;
            xy[0] = rand()%getTX(parametros) + 1;
            xy[1] = rand()%getTY(parametros) + 1;
            addObjeto(lstBandidos, newBandido((rand()%6)+1, (rand()%getP(parametros))+1, (rand()%getVB(parametros))+1, xy, parametros));
        }

        ticksUltMoneda++;
        if(rand()%2==1 || ticksUltMoneda>=getIM(parametros))
        {
            ticksUltMoneda = 0;
            addObjeto(lstMonedas, newMoneda(rand()%getTX(parametros) + 1, rand()%getTY(parametros) + 1, rand()%getVM(parametros) + 1, parametros));
        }

        //Pantalla ---------------------------------------------------------------------
        system("cls");
        cout<<"M: "<<monedas<<endl;
        cout<<(char)-55;
        for(i=0;i<getTX(parametros);i++) cout<<(char)-51;
        cout<<(char)-69;
        for(i=0;i<getTY(parametros);i++)
        {
            cout<<(char)-70;
            for(j=0;j<getTX(parametros);j++)
            {
                vagon = false;
                mina = false;
                estacion = false;
                bandido = false;
                moneda = false;
                for(k=0;k<getSize(getVagones(locomotora));k++)
                {
                    if(i==getXY((ptrVagon)getObjeto(getVagones(locomotora),k))[1] &&
                       j==getXY((ptrVagon)getObjeto(getVagones(locomotora),k))[0]) vagon = true;
                }
                for(k=0;k<getSize(lstMinas);k++)
                {
                    if(i==getPosY((ptrMina)getObjeto(lstMinas,k)) && j==getPosX((ptrMina)getObjeto(lstMinas,k))) mina = true;
                }
                for(k=0;k<getSize(lstBandidos);k++)
                {
                    if(i==getXY((ptrBandido)getObjeto(lstBandidos,k))[1] && j==getXY((ptrBandido)getObjeto(lstBandidos,k))[0]) bandido = true;
                }
                for(k=0;k<getSize(lstMonedas);k++)
                {
                    if(i==getXY((ptrMoneda)getObjeto(lstMonedas,k))[1] && j==getXY((ptrMoneda)getObjeto(lstMonedas,k))[0]) moneda = true;
                }
                if (i==getPosYE(parametros) && j==getPosXE(parametros)) estacion = true;

                if (i==getXY(locomotora)[1] && j==getXY(locomotora)[0])
                {
                    gotoxy(j+1, i+2);
                    cout<<"L";
                }
                else if (vagon==true)
                {
                    gotoxy(j+1, i+2);
                    cout<<"V";
                }
                else if (mina==true)
                {
                    gotoxy(j+1, i+2);
                    cout<<"M";
                }
                else if (estacion==true)
                {
                    gotoxy(j+1, i+2);
                    cout<<"E";
                }
                else if (bandido==true)
                {
                    gotoxy(j+1, i+2);
                    cout<<"B";
                }
                else if (moneda==true)
                {
                    gotoxy(j+1, i+2);
                    cout<<"C";
                }
            }
            gotoxy(getTX(parametros)+1, i+2);
            cout<<(char)-70;
        }
        cout<<(char)-56;
        for(i=0;i<getTX(parametros);i++) cout<<(char)-51;
        cout<<(char)-68;
        //Fin Pantalla -----------------------------------------------------------------

        if (getPosXE(parametros)==getXY(locomotora)[0] && getPosYE(parametros)==getXY(locomotora)[1] && monedas>=5)
        {
            setAgregarVagon(locomotora, true);
            monedas = monedas - 5;
        }

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
        if(tecla != 'q')
        {
            moverLocomotora(locomotora);
            i=0;
            while(i<getSize(lstBandidos))
            {
                if (tickBandido((ptrBandido)getObjeto(lstBandidos,i), locomotora, parametros) == 1)
                {
                    //No usar for para esto, sino la lista se vuelve loca si hay que eliminar dos bandidos en el mismo ciclo
                    //dado que i sigue corriendo pero cantNodos se reduce por cada eliminación
                    delBandido((ptrBandido)getObjeto(lstBandidos,i));
                    delObjeto(lstBandidos, i);
                    i--;
                }
                i++;
            }
            i=0;
            while(i<getSize(lstMonedas))
            {
                if (tickMoneda((ptrMoneda)getObjeto(lstMonedas,i), locomotora, &monedas) == 1)
                {
                    //No usar for para esto, sino la lista se vuelve loca si hay que eliminar dos monedas en el mismo ciclo
                    //dado que i sigue corriendo pero cantNodos se reduce por cada eliminación
                    delMoneda((ptrMoneda)getObjeto(lstMonedas,i));
                    delObjeto(lstMonedas, i);
                    i--;
                }
                i++;
            }
        }
    }

    //Limpieza de variables
    delParametros(parametros);
    delComanda(comanda);
    for(i=0;i<getSize(lstMinas);i++) delMina((ptrMina)getObjeto(lstMinas, i));
    eliminarListaGen(lstMinas);
    delLocomotora(locomotora);
    for(i=0;i<getSize(lstBandidos);i++) delBandido((ptrBandido)getObjeto(lstBandidos, i));
    eliminarListaGen(lstBandidos);
    for(i=0;i<getSize(lstMonedas);i++) delMoneda((ptrMoneda)getObjeto(lstMonedas, i));
    eliminarListaGen(lstMonedas);
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

    setXY(locomotora, xy);
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

void testBandido()
{
    ptrParametros parametros = newParametros();
    cargarParametros(parametros);
    int xy[2];
    xy[0]=25;
    xy[1]=9;
    ptrBandido bandido = newBandido(3, 4, 2, xy, parametros);

    cout<<getTipoRecurso(bandido)<<endl<<endl;

    cout<<getP(parametros)<<endl;
    cout<<getCantidad(bandido)<<endl<<endl;

    cout<<getVB(parametros)<<endl;
    cout<<getTiempoVida(bandido)<<endl<<endl;

    cout<<getTX(parametros)<<"   "<<getXY(bandido)[0]<<endl;
    cout<<getTY(parametros)<<"   "<<getXY(bandido)[1]<<endl;

    delParametros(parametros);
    delBandido(bandido);
}

/*---------Pantalla de prueba---------*/
void gotoxy(int x, int y)
{
  static HANDLE h = NULL;
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };
  SetConsoleCursorPosition(h,c);
}
/*---------Pantalla de prueba---------*/

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
