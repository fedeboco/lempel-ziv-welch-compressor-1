#include <iostream>
#include "secuencia.h"

using namespace std;

secuencia::secuencia()
{
   P_ = 0;
   S_ = 0;
}

secuencia::secuencia(const int & P, const char & S)
{
    P_ = P;
    S_ = S;
}

//Constructor copia de secuencias.
void secuencia::operator=(const secuencia & sec)
{
    P_ = sec.P_;
    S_ = sec.S_;
}

//Asigna sólo el prefijo a la secuencia.
void secuencia::asignarP(const int & P)
{
    P_ = P;
}

//Asigna sólo el sufijo a la secuencia.
void secuencia::asignarS(const char & S)
{
    S_ = S;
}

//Asigna prefijo y sufijo a la secuencia.
void secuencia::asignarPS(const int & P, const char & S)
{
    P_ = P;
    S_ = S;
}

//Extrae el prefijo de la secuencia.
int secuencia::obtenerP()
{
    return P_;
}

//Extrae el sufijo de la secuencia.
char secuencia::obtenerS()
{
    return S_;
}