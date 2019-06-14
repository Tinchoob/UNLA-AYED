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
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
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

    //The sound effects that will be used
    Mix_Chunk *sonidoMoneda = NULL;
    Mix_Chunk *sonidoVillano = NULL;

    if(SDL_Init(SDL_INIT_EVERYTHING) >= 0 )
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"OK","Clash of Unla",NULL);
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );

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
    bool ganar = false;


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

    sonidoMoneda = Mix_LoadWAV( "sound/moneda.wav" );
    sonidoVillano = Mix_LoadWAV( "sound/villano.wav" );

    //----------------------------------------------Mensaje de prueba------------------------------------------------------------
    TTF_Init(); //Inicializa SDL_TTF
    TTF_Font* font = TTF_OpenFont("times.ttf", 16); //Si en esta linea se pone una fuente que no se pueda encontrar vuela todo
    SDL_Color White = {255, 255, 255}; //Color del texto
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, "Hola Mundo", White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect Message_rect; //"Cuadro" en donde va a ir el texto, con sus coordenadas y tamaño,
    Message_rect.x = 0; // si se hace muy grande para el mensaje que se quiere mostrar se ve mal
    Message_rect.y = 0;
    Message_rect.w = 500;
    Message_rect.h = 50;
    //----------------------------------------------Mensaje de prueba------------------------------------------------------------

    srand(time(NULL)); //INICIALIZA LA SEMILLA RANDOM
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
            addObjeto(lstMonedas, newMoneda(rand()%getTX(parametros) + 1, rand()%getTY(parametros) + 1, rand()%getVM(parametros) + 1, parametros,renderer,sonidoMoneda));
        }

        if(!stopLocomotora)
            moverLocomotora(renderer,locomotora);

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

           //Manejo Bandidos
        ticksUltBandido++;

        if(rand()%2==1 || ticksUltBandido>=getIB(parametros))
        {
            ticksUltBandido = 0;
            xy[0] = rand()%getTX(parametros) + 1;
            xy[1] = rand()%getTY(parametros) + 1;
            addObjeto(lstBandidos, newBandido((rand()%6)+1, (rand()%getP(parametros))+1, (rand()%getVB(parametros))+1, xy, parametros,renderer,sonidoVillano));
        }

        //Agregar bandidos a pantalla
        for(i = 0; i<getSize(lstBandidos); i++)
        {
            bandido = (ptrBandido)getObjeto(lstBandidos, i);
            SDL_RenderCopy(renderer,getImagen(bandido),NULL,getRectImagen(bandido));
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

        //----------------------------------------------Mensaje de prueba------------------------------------------------------------
        SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //Renderizar mensaje de prueba
        SDL_RenderPresent(renderer);
        //----------------------------------------------Mensaje de prueba------------------------------------------------------------

        SDL_Delay(250);
    }

  /*  string message = "";


    if(perder){
     message.assign("Perdiste!");}
     else if(ganar){
        message.assign("Ganaste!");
     }

     if(!message.empty()){
           SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"OK","Clash of Unla",NULL);
     }
*/

    Mix_FreeChunk( sonidoVillano );
    Mix_FreeChunk( sonidoMoneda );
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

    //----------------------------------------------Mensaje de prueba------------------------------------------------------------
    SDL_FreeSurface(surfaceMessage); //Hay que liberar todos los recursos que se van creando para esta cosa
    SDL_DestroyTexture(Message);
    TTF_Quit(); //También hay que decirle a SDL_TTF que se cierre
    //----------------------------------------------Mensaje de prueba------------------------------------------------------------

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
