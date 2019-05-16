#include <iostream>
#include "arreglo.h"
#include "secuencia.h"
#include "tipos_datos.h"
#include "funciones_impresion.h"

using namespace std;

arreglo::arreglo(const int & size)
{
    if( size > 0 )
    {
        dato_ = new secuencia[size];
        size_ = size;
    }
    else
        imprimir_error(ERROR_SIZE_CONSTRUCTOR);
}

arreglo::~arreglo()
{
    if( dato_ )
        delete[] dato_;
}

secuencia & arreglo::operator[](const int pos)
{
    if( pos >= size_ || pos < 0 )
    {
        cout    << MSJ_ERROR_SIZE_1 
                << pos 
                << MSJ_ERROR_SIZE_2 
                << size_ 
                << '.' 
                << endl;
    }
    return dato_[pos];
}

secuencia & arreglo::obtener_dato(const int pos)
{
    if( pos >= size_ || pos < 0 )
    {
        cout    << MSJ_ERROR_SIZE_1 
                << pos 
                << MSJ_ERROR_SIZE_2 
                << size_ 
                << '.' 
                << endl;
    }
    return dato_[pos];
}

int arreglo::obtener_size() const
{
    return size_;
}

