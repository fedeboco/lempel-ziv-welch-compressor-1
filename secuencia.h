#include <iostream>
using namespace std;

#ifndef SECUENCIA_DEF
#define SECUENCIA_DEF

//-------------------- Declaración de la clase secuencia -------------------//
class secuencia
{
private:
    int * P_; //prefijo
    char * S_; //sufijo

public:
    secuencia();
    secuencia(const int &, const char &);
    ~secuencia();

    void operator=(const secuencia &);
    void asignarP(const int &);
    void asignarS(const char &);
    void asignarPS(const int &, const char &);
    int obtenerP();
    char obtenerS();
};
#endif