#include <iostream>
#include "ListaGen.h"

using namespace std;

int main()
{
    int n1=65, n2=51, n3=64, n4=69, n5=125;
    char a[]="Random Access Memory";
    char b[]="CPU";
    char c[]="GTX 760";
    char d[]="CD";
    char e[]="Windows";

    ListaGen lista = newListaGen();
    addObjeto(lista, a);
    addObjeto(lista, &n1);
    addObjeto(lista, b);
    addObjeto(lista, c);
    addObjeto(lista, &n2);
    addObjeto(lista, &n3);
    addObjeto(lista, &n4);
    addObjeto(lista, &n5);
    addObjeto(lista, d);
    addObjeto(lista, e);

    cout<<"lista.get(0): "<<(char*)getObjeto(lista, 0)<<endl;
    cout<<"lista.get(1): "<<*((int*)getObjeto(lista, 1))<<endl;
    cout<<"lista.get(2): "<<(char*)getObjeto(lista, 2)<<endl;
    cout<<"lista.get(3): "<<(char*)getObjeto(lista, 3)<<endl;
    cout<<"lista.get(4): "<<*((int*)getObjeto(lista, 4))<<endl;
    cout<<"lista.get(5): "<<*((int*)getObjeto(lista, 5))<<endl;
    cout<<"lista.get(6): "<<*((int*)getObjeto(lista, 6))<<endl;
    cout<<"lista.get(6): "<<*((int*)getObjeto(lista, 7))<<endl;
    cout<<"lista.get(7): "<<(char*)getObjeto(lista, 8)<<endl;
    cout<<"lista.get(8): "<<(char*)getObjeto(lista, 9)<<endl;

    delObjeto(lista,1);
    cout<<"Posicion 1 eliminada"<<endl;
    cout<<"lista.get(6): "<<(char*)getObjeto(lista, 6)<<endl;

    cout<<"lista.getSize(): "<<getSize(lista)<<endl;
    cout<<"lista.getPrimero(): "<<(char*)getPrimero(lista)<<endl;
    cout<<"lista.getUltimo(): "<<(char*)getUltimo(lista)<<endl;

    eliminarListaGen(lista);
    return 0;
}
