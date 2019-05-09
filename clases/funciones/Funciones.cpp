#include "Funciones.h"
#include <string.h>

char* subString(char entrada[], int comienzo, int fin)
{
    int longitud = fin-comienzo;
    int i;
    char* ret = new char[longitud];

    for(i=0;i<longitud;i++)
    {
        ret[i]=entrada[i+comienzo];
    }
    return ret;
}

long posEnArray(char entrada[], int comienzo, char caracter)
{
    long i, pos=0, longitud=strlen(entrada);

    i=comienzo;
    while (i<longitud && pos==0)
    {
        if (entrada[i]==caracter) pos=i;
        i++;
    }
    if (i==longitud && pos==0) pos = longitud; //Linea para el final del array, no hay enter ni punto y coma, devolveria 0 y vuela todo
    return pos;
}
