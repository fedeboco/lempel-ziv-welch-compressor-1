#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main ()
{
    size_t cant=0;
    ofstream salida;
    unsigned char caracter;
    int limite_inf = 0,limite_sup = 255,semilla;
    salida.open("./tests/entrada9.txt");

    cout << "Ingrese cantidad de caracteres que quiere generar:";
    cin >> cant;
    cout << "Ingrese una semilla :";
    cin >> semilla;
    srand(semilla);
    for (unsigned int i=0;i < cant;i++){
        caracter = limite_inf+rand()%(limite_sup-limite_inf);
        salida << caracter<<endl;
    }
    salida.close();
}