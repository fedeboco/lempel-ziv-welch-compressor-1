#include <iostream>
#include "secuencia.h"
using namespace std;

#ifndef ARREGLO_DEF
#define ARREGLO_DEF

class arreglo
{
private:
    secuencia * dato_;
    int size_;
    int ult_;

public:
    arreglo(const int &);
    ~arreglo();
    
    secuencia & operator[](const int);
    secuencia & obtener_dato(const int);
    int obtener_size() const;


};
#endif