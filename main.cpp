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
#include <SDL.H>
#include <SDL_image.h>
#include <string>

#define xSize 800
#define ySize 600

/*Esto solo se usa para la pantalla de prueba -------------*/
#include <windows.h>
void gotoxy(int x, int y);
/*Esto solo se usa para la pantalla de prueba -------------*/


using namespace std;

//Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

//Tests
void testParametros();
void testComanda();
void testMina();
void testVagon();
void testBandido();

/*-------------------*/
void cargarMinas(SDL_Renderer* renderer,ListaGen lstMinas);

int main(int argv, char** args)
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

    if(SDL_Init(SDL_INIT_EVERYTHING) >= 0 )
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"OK","Clash of Unla",NULL);
    }

    bool gameOver = false;
    bool stopLocomotora = false;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    //SDL_Surface* screenSurface = NULL;
    SDL_Surface* background = NULL;
    SDL_Texture *backgroundTexture = NULL;
    ptrLocomotora locomotora = NULL;
    ptrBandido bandido = NULL;
    ptrMoneda monedaPtr = NULL;
    ptrMina mina=NULL;
    ptrVagon vagon=NULL;

    SDL_Event event;
    int eventType;
    int i, ticksUltBandido=0, ticksUltMoneda=0;
    int xy[2];
    bool perder = false;


    window =  SDL_CreateWindow("Test SDL",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,xSize,ySize,SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    // screenSurface = SDL_GetWindowSurface( window );

    backgroundTexture = IMG_LoadTexture(renderer, "img/suelo_3.png");

    locomotora = newLocomotora(renderer);
    ptrParametros parametros = newParametros();
    ptrComanda comanda = newComanda();
    ListaGen lstMinas = newListaGen();
    ListaGen lstBandidos = newListaGen();
    ListaGen lstMonedas = newListaGen();

    SDL_Texture* imagenEstacion = IMG_LoadTexture(renderer, "img/estation.png");
    SDL_Rect* rectEstacion = new SDL_Rect();

    cargarParametros(parametros);
    cargarComanda(comanda);
    cargarMinas(renderer,lstMinas);

    rectEstacion->x = getPosXE(parametros) * 40;
    rectEstacion->y = getPosYE(parametros) * 40;
    rectEstacion->w = 40;
    rectEstacion->h = 40;

    while(!gameOver && !perder)
    {
        //handle key events
        while( SDL_PollEvent( &event ) != 0 )
        {
            eventType = event.type;
            if(eventType == SDL_QUIT)
            {
                gameOver = true;
            }

            else if( event.type == SDL_KEYDOWN )
            {
                switch( event.key.keysym.sym )
                {
                case SDLK_UP:
                    if(getDireccionLocomotora(locomotora)!=1)
                    {
                        setDireccionLocomotora(locomotora, 3);
                        setImagen(locomotora,IMG_LoadTexture(renderer, "img/c1/arr/0.png"));
                        stopLocomotora = false;
                    }
                    break;

                case SDLK_DOWN:
                    if(getDireccionLocomotora(locomotora)!=3)
                    {
                        setDireccionLocomotora(locomotora, 1);
                        setImagen(locomotora,IMG_LoadTexture(renderer, "img/c1/aba/0.png"));
                        stopLocomotora = false;
                    }
                    break;

                case SDLK_LEFT:
                    if(getDireccionLocomotora(locomotora)!=0)
                    {
                        setDireccionLocomotora(locomotora, 2);
                        setImagen(locomotora,IMG_LoadTexture(renderer, "img/c1/izq/0.png"));
                        stopLocomotora = false;
                    }
                    break;

                case SDLK_RIGHT:
                    if(getDireccionLocomotora(locomotora)!=2)
                    {
                        setDireccionLocomotora(locomotora, 0);
                        setImagen(locomotora,IMG_LoadTexture(renderer, "img/c1/der/0.png"));
                        stopLocomotora = false;
                    }
                    break;

                default:

                    break;
                }
            }
        }


        //Manejo monedas
        ticksUltMoneda++;

        if(rand()%2==1 || ticksUltMoneda>=getIM(parametros))
        {
            ticksUltMoneda = 0;
            addObjeto(lstMonedas, newMoneda(rand()%getTX(parametros) + 1, rand()%getTY(parametros) + 1, rand()%getVM(parametros) + 1, parametros,renderer));
        }

        if(!stopLocomotora)moverLocomotora(renderer,locomotora);

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        SDL_RenderCopy(renderer, imagenEstacion, NULL, rectEstacion);

        if (getPosXE(parametros) == getXY(locomotora)[0] && getPosYE(parametros) == getXY(locomotora)[1] && getMonedas(locomotora)>0)
        {
            stopLocomotora = true;
            setAgregarVagon(locomotora, true);
        }

        for(i=0; i<getSize(lstMinas); i++)
        {
            mina=(ptrMina)getObjeto(lstMinas,i);
            SDL_RenderCopy(renderer,getImagen(mina),NULL,getRectImagen(mina));
        }

        for(i=0; i<getSize(getVagones(locomotora)); i++)
        {
            vagon = (ptrVagon)getObjeto(getVagones(locomotora),i);
            SDL_RenderCopy(renderer,getImagen(vagon),NULL,getRectImagen(vagon));
        }

        //Agregar bandidos a pantalla
        for(i = 0; i<getSize(lstBandidos); i++)
        {
            bandido = (ptrBandido)getObjeto(lstBandidos, i);
            SDL_RenderCopy(renderer,getImagen(bandido),NULL,getRectImagen(bandido));
        }

        //Manejo Bandidos
        ticksUltBandido++;

        if(rand()%2==1 || ticksUltBandido>=getIB(parametros))
        {
            ticksUltBandido = 0;
            xy[0] = rand()%getTX(parametros) + 1;
            xy[1] = rand()%getTY(parametros) + 1;
            addObjeto(lstBandidos, newBandido((rand()%6)+1, (rand()%getP(parametros))+1, (rand()%getVB(parametros))+1, xy, parametros,renderer));
        }


        //Imprimir monedas en pantalla

        for(i = 0; i<getSize(lstMonedas); i++)
        {
            monedaPtr = (ptrMoneda)getObjeto(lstMonedas, i);
            SDL_RenderCopy(renderer,getImagen(monedaPtr),NULL,getRectImagen(monedaPtr));
        }

        i=0;

        while(i<getSize(lstBandidos))
        {
            if (tickBandido((ptrBandido)getObjeto(lstBandidos,i), locomotora, parametros,perder) == 1)
            {
                //No usar for para esto, sino la lista se vuelve loca si hay que eliminar dos bandidos en el mismo ciclo
                //dado que i sigue corriendo pero cantNodos se reduce por cada eliminaci�n
                delBandido((ptrBandido)getObjeto(lstBandidos,i));
                delObjeto(lstBandidos, i);
                i--;
            }
            i++;
        }

        //Monedas
        i=0;
        while(i<getSize(lstMonedas))
        {
            if (tickMoneda((ptrMoneda)getObjeto(lstMonedas,i), locomotora) == 1)
            {
                //No usar for para esto, sino la lista se vuelve loca si hay que eliminar dos monedas en el mismo ciclo
                //dado que i sigue corriendo pero cantNodos se reduce por cada eliminaci�n
                delMoneda((ptrMoneda)getObjeto(lstMonedas,i));
                delObjeto(lstMonedas, i);
                i--;
            }
            i++;
        }

        actualizarCantRecursos(locomotora);


        //Producci�n de las minas
        for (i=0; i<getSize(lstMinas); i++)
            tickMina((ptrMina)getObjeto(lstMinas, i), locomotora,stopLocomotora);

        //Chequeos para ver si pierde el jugador
        if (getXY(locomotora)[0]<0 || getXY(locomotora)[1]<0 || getXY(locomotora)[0]>getTX(parametros)
                || getXY(locomotora)[1]>getTY(parametros))
            perder = true;
        else
        {
            i=0;
            while (!perder && i<getSize(getVagones(locomotora)))
            {
                if (getXY(locomotora)[0] == getXY((ptrVagon)getObjeto(getVagones(locomotora), i))[0]
                        && getXY(locomotora)[1] == getXY((ptrVagon)getObjeto(getVagones(locomotora), i))[1])
                    perder = true;
                i++;
            }
        }

        if(getCantRecursos(locomotora)[0] >= getOro(comanda) && getCantRecursos(locomotora)[1] >= getPlata(comanda)
            && getCantRecursos(locomotora)[2] >= getBronce(comanda) && getCantRecursos(locomotora)[3] >= getPlatino(comanda)
            && getCantRecursos(locomotora)[4] >= getRoca(comanda) && getCantRecursos(locomotora)[5] >= getRoca(comanda)){
                ganar=true;
        }


        SDL_RenderCopy(renderer,getImagen(locomotora),NULL,getRectImagen(locomotora));
        SDL_RenderPresent(renderer);

        SDL_Delay(250);
    }

    delParametros(parametros);
    delComanda(comanda);
    for(i=0; i<getSize(lstMinas); i++)
        delMina((ptrMina)getObjeto(lstMinas, i));
    eliminarListaGen(lstMinas);
    delLocomotora(locomotora);
    for(i=0; i<getSize(lstBandidos); i++)
        delBandido((ptrBandido)getObjeto(lstBandidos, i));
    eliminarListaGen(lstBandidos);
    for(i=0; i<getSize(lstMonedas); i++)
        delMoneda((ptrMoneda)getObjeto(lstMonedas, i));
    eliminarListaGen(lstMonedas);


    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;

    /* ptrParametros parametros = newParametros();
    ptrComanda comanda = newComanda();
    ListaGen lstMinas = newListaGen();
    ptrLocomotora locomotora = newLocomotora();
    ListaGen lstBandidos = newListaGen();
    ListaGen lstMonedas = newListaGen();

    int i, j, k, ticksUltBandido=0, ticksUltMoneda=0;
    int xy[2];
    bool perder = false;

    //Init
    cargarParametros(parametros);
    cargarComanda(comanda);
    cargarMinas(lstMinas);

    //Bucle
    char tecla = '0';
    bool vagon, mina, estacion, bandido, moneda;

    addObjeto(getVagones(locomotora), newVagon(0, 1, 3, 90));
    addObjeto(getVagones(locomotora), newVagon(0, 2, 3, 90));
    addObjeto(getVagones(locomotora), newVagon(0, 3, 3, 90));
    addObjeto(getVagones(locomotora), newVagon(0, 4, 3, 90));
    addObjeto(getVagones(locomotora), newVagon(0, 5, 3, 90));
    addObjeto(getVagones(locomotora), newVagon(0, 6, 3, 90));
    srand(time(NULL));
    while (tecla != 'q' && perder != true)
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
        cout<<"Monedas: "<<getMonedas(locomotora)<<"  ";
        cout<<"Oro: "<<getCantRecursos(locomotora)[0]<<"  ";
        cout<<"Plata: "<<getCantRecursos(locomotora)[1]<<"  ";
        cout<<"Bronce: "<<getCantRecursos(locomotora)[2]<<"  ";
        cout<<"Platino: "<<getCantRecursos(locomotora)[3]<<"  ";
        cout<<"Roca: "<<getCantRecursos(locomotora)[4]<<"  ";
        cout<<"Carbon: "<<getCantRecursos(locomotora)[5]<<endl;

        for(i=0;i<getSize(getVagones(locomotora));i++)
        {
            ptrVagon vActual = (ptrVagon)getObjeto(getVagones(locomotora), i);
            cout<<"V"<<i+1<<": "<<cantidadTotalLingotes(vActual)<<"/"<<getCapacidad(vActual)<<";"<<getTipoRecurso(vActual)<<"  ";
        }
        cout<<endl;

        gotoxy(0,3);
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
                    gotoxy(j+1, i+4);
                    cout<<"L";
                }
                else if (vagon==true)
                {
                    gotoxy(j+1, i+4);
                    cout<<"V";
                }
                else if (mina==true)
                {
                    gotoxy(j+1, i+4);
                    cout<<"M";
                }
                else if (estacion==true)
                {
                    gotoxy(j+1, i+4);
                    cout<<"E";
                }
                else if (bandido==true)
                {
                    gotoxy(j+1, i+4);
                    cout<<"B";
                }
                else if (moneda==true)
                {
                    gotoxy(j+1, i+4);
                    cout<<"C";
                }
            }
            gotoxy(getTX(parametros)+1, i+4);
            cout<<(char)-70;
        }
        cout<<(char)-56;
        for(i=0;i<getTX(parametros);i++) cout<<(char)-51;
        cout<<(char)-68;
        //Fin Pantalla -----------------------------------------------------------------

        if (getPosXE(parametros)==getXY(locomotora)[0] && getPosYE(parametros)==getXY(locomotora)[1] && getMonedas(locomotora)>0)
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
        if(tecla != 'q')
        {
            //Mover la locomotora y agregar vagones si se debe
            moverLocomotora(locomotora);

            //Bandidos
            i=0;
            while(i<getSize(lstBandidos))
            {
                if (tickBandido((ptrBandido)getObjeto(lstBandidos,i), locomotora, parametros, perder) == 1)
                {
                    //No usar for para esto, sino la lista se vuelve loca si hay que eliminar dos bandidos en el mismo ciclo
                    //dado que i sigue corriendo pero cantNodos se reduce por cada eliminaci�n
                    delBandido((ptrBandido)getObjeto(lstBandidos,i));
                    delObjeto(lstBandidos, i);
                    i--;
                }
                i++;
            }

            //Actualizar cantidad de recursos recolectados
            actualizarCantRecursos(locomotora);

            //Monedas
            i=0;
            while(i<getSize(lstMonedas))
            {
                if (tickMoneda((ptrMoneda)getObjeto(lstMonedas,i), locomotora) == 1)
                {
                    //No usar for para esto, sino la lista se vuelve loca si hay que eliminar dos monedas en el mismo ciclo
                    //dado que i sigue corriendo pero cantNodos se reduce por cada eliminaci�n
                    delMoneda((ptrMoneda)getObjeto(lstMonedas,i));
                    delObjeto(lstMonedas, i);
                    i--;
                }
                i++;
            }

            //Producci�n de las minas
            for (i=0;i<getSize(lstMinas);i++) tickMina((ptrMina)getObjeto(lstMinas, i), locomotora);

            //Chequeos para ver si pierde el jugador
            if (getXY(locomotora)[0]<0 || getXY(locomotora)[1]<0 || getXY(locomotora)[0]>getTX(parametros)
                || getXY(locomotora)[1]>getTY(parametros)) perder = true;
            else
            {
                i=0;
                while (!perder && i<getSize(getVagones(locomotora)))
                {
                    if (getXY(locomotora)[0] == getXY((ptrVagon)getObjeto(getVagones(locomotora), i))[0]
                        && getXY(locomotora)[1] == getXY((ptrVagon)getObjeto(getVagones(locomotora), i))[1]) perder = true;
                    i++;
                }
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
    */
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

/*void testMina()
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
    for(i=0; i<5; i++)
        cout<<seq[i]<<endl;
    delMina((ptrMina)getObjeto(lista, 0));
    delMina((ptrMina)getObjeto(lista, 1));
    eliminarListaGen(lista);
}*/

//void testVagon()
//{
//    int i;
//    ptrVagon vagon = newVagon(0,0,0,5);
//    ptrCaja caja;
//
//    setTipoRecurso(vagon, 1);
//
//    for(i=0; i<3; i++)
//    {
//        caja = newCaja(0,1);
//        setTipoRecurso(caja, 1);
//        setCantidad(caja, i+1);
//        addObjeto(getCajas(vagon), caja);
//    }
//    cout<<cantidadTotalLingotes(vagon)<<endl;
//    delVagon(vagon);
//}


/*void testBandido()
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
}*/

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
void cargarMinas(SDL_Renderer* renderer, ListaGen lstMinas)
{
    int i;
    FILE* fMina;

    i=0;
    fMina=fopen("minas.txt","r");
    while(!feof(fMina))
    {
        addObjeto(lstMinas,newMina(renderer));
        leerLineaMina(fMina, (ptrMina)getObjeto(lstMinas, i));
        i++;

    }
    fclose(fMina);
}
