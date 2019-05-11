#include <iostream>
#include "ListaGen.h"

using namespace std;

int main()
{
    int n1=1, n2=2, n3=3;
    char a[]="Random Access Memory";
    char b[]="CPU";
    char c[]="GTX 760";

    ListaGen lista = newListaGen();
    addObjeto(lista, a);
    addObjeto(lista, &n2);
    addObjeto(lista, b);
    addObjeto(lista, c);
    cout<<"a: "<<a<<endl;
    cout<<"lista.get(0): "<<(char*)getObjeto(lista, 0)<<endl;

    cout<<"n2: "<<b<<endl;
    cout<<"lista.get(1): "<<*((int*)getObjeto(lista, 1))<<endl;

    cout<<"b: "<<c<<endl;
    cout<<"lista.get(2): "<<(char*)getObjeto(lista, 2)<<endl;

    cout<<"c: "<<c<<endl;
    cout<<"lista.get(3): "<<(char*)getObjeto(lista, 3)<<endl;

    delObjeto(lista,1);
    cout<<"Posicion 1 eliminada"<<endl;
    cout<<"lista.get(1): "<<(char*)getObjeto(lista, 1)<<endl;

    cout<<"lista.getSize(): "<<getSize(lista)<<endl;
    cout<<"lista.getPrimero(): "<<(char*)getPrimero(lista)<<endl;
    cout<<"lista.getUltimo(): "<<(char*)getUltimo(lista)<<endl;

    eliminarListaGen(lista);
    return 0;
}
