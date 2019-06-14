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
    SDL_Texture *backgroundTextures[4];
    SDL_Rect *backgroundRects[4];
    ptrLocomotora locomotora = NULL;
    ptrBandido bandido = NULL;
    ptrMoneda monedaPtr = NULL;
    ptrMina mina=NULL;
    ptrVagon vagon=NULL;

    SDL_Event event;
    int eventType;
    int i, ticksUltBandido=0, ticksUltMoneda=0;
    int xy[2];
    bool perder = false,ganar = false;


    window =  SDL_CreateWindow("Test SDL",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,xSize,ySize,SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    // screenSurface = SDL_GetWindowSurface( window );


    backgroundTextures[0] = IMG_LoadTexture(renderer, "img/suelo_3.png");
    backgroundTextures[1] = IMG_LoadTexture(renderer, "img/suelo_1.png");
    backgroundTextures[2] = IMG_LoadTexture(renderer, "img/suelo_2.png");
    backgroundTextures[3] = IMG_LoadTexture(renderer, "img/suelo_3.png");
    backgroundTextures[4] = IMG_LoadTexture(renderer, "img/suelo_4.png");

    for(i=0;i<=4;i++){
        backgroundRects[i] = new SDL_Rect();
    }

     backgroundRects[0]->x = 0*40;
     backgroundRects[0]->y = 0*40;
     backgroundRects[0]->w = 320;
     backgroundRects[0]->h = 360;

     backgroundRects[1]->x = 5*40;
     backgroundRects[1]->y = 6*40;
     backgroundRects[1]->w = 320;
     backgroundRects[1]->h = 360;

     backgroundRects[2]->x = 10*40;
     backgroundRects[2]->y = 9*40;
     backgroundRects[2]->w = 320;
     backgroundRects[2]->h = 360;

     backgroundRects[3]->x = 15*40;
     backgroundRects[3]->y = 12*40;
     backgroundRects[3]->w = 320;
     backgroundRects[3]->h = 360;

     backgroundRects[4]->x = 20*40;
     backgroundRects[4]->y = 15*40;
     backgroundRects[4]->w = 320;
     backgroundRects[4]->h = 360;


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

    while(!gameOver && !perder && !ganar)
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

        if(!stopLocomotora)
            moverLocomotora(renderer,locomotora);

        SDL_RenderClear(renderer);
        for(i=2;i<3;i++){
            SDL_RenderCopy(renderer, backgroundTextures[i], NULL, backgroundRects[i]);
        }
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
                && getCantRecursos(locomotora)[4] >= getRoca(comanda) && getCantRecursos(locomotora)[5] >= getRoca(comanda))
        {
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

}


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
