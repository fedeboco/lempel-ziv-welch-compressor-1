#include <iostream>
#include "diccionario.h"

#define MIN_SIZE 255
#define MSJ_ERROR_SIZE_DICC "El tamaño del diccionario es muy chico, se usará el default = 255"
#define MSJ_ERROR_OBT_SEC "No existen secuencias con índice negativo o índice mayor al último elemento."
#define MSJ_DIC_LLENO "Se lleno el diccionario, se procede a resetearlo"

using namespace std;

diccionario::diccionario(const int & size)
{
    int size_aux = size; 
    if (size < MIN_SIZE)
    {
      cout << MSJ_ERROR_SIZE_DICC << endl;
      size_aux = MIN_SIZE;  
    }  
    dic_ = new arreglo(size_aux);
    size_ = new int;
    *size_ = size_aux;
}

diccionario::~diccionario()
{
    if( dic_ )
        delete dic_;
    if( size_ )
        delete size_;
}

//Obtiene una secuencia del diccionario de tipo [int Prefijo, char Sufijo] y la retorna.
secuencia & diccionario::obtener_secuencia(const int i)
{
    if( i < 0 || i > ult_ )
        cout << MSJ_ERROR_OBT_SEC << endl;
    return dic_ -> obtener_dato(i);
}

//Copia una secuencia del tipo [int Prefijo, char Sufijo] a una posición del diccionario.
void diccionario::asignar_secuencia(const int pos, const secuencia & dato)
{
    (*dic_)[pos] = dato;
}

//Asigna un int P (Prefijo) y un char S (Sufijo) a una secuencia de cierta posición del diccionario.
void diccionario::asignar_secuencia(const int pos, const int & P, const char & S)
{
    (*dic_)[pos].asignarP(P);
    (*dic_)[pos].asignarS(S);
}

//Obtiene el prefijo de cierta posición del diccionario.
int diccionario::obtener_P(const int pos) const
{
    return (*dic_)[pos].obtenerP();
}

//Obtiene el sufijo de cierta posición del diccionario.
char diccionario::obtener_S(const int pos) const 
{
    return (*dic_)[pos].obtenerS();
}

//Obtiene la ultima posición
int diccionario::obtener_ult_()
{
    return ult_;
}

//Vacía el diccionario.
void diccionario::resetear_diccionario()
{
    ult_ = 255;
}

//Asigna un int P (Prefijo) y un char S (Sufijo) a la secuencia de la primera posición vacía del diccionario.
int diccionario::agregar_secuencia(const int & P, const char & S)
{
    int size = *size_;
    if( ult_ >= size - 1){
        cout << MSJ_DIC_LLENO << endl;
        this -> resetear_diccionario();
    }
    this -> asignar_secuencia(ult_ + 1, P, S);
    ult_++;
    
    return ult_;
}

//Búsqueda secuencial de la primer secuencia que coincida con el prefijo y el sufijo suministrado. Retorna índice.
const int diccionario::buscar_secuencia(const int & P, const char & S)
{
    int size = *size_;
    for( int i = 0; i >= 0 && i <= size && i <= ult_; i++ )
    {
        if( this->obtener_P(i) == P && this->obtener_S(i) == S )
            return i;
    }
    return -1;
}

//Devuelve el primer caracter del diccionario de la ubicación buscada.
int diccionario::obtener_indice(const int & ubic)
{
    if (ubic < 256)
        return ubic;
    else
    {
        int aux_P;
        aux_P = this -> obtener_P(ubic);
        return  this -> obtener_indice(aux_P);
    }
        
}

//Imprime cadena de caracteres según indice.
void diccionario::imprimir_indice(const int & ubic, ostream * oss)
{
    int aux_P;
    //Como el S es char va del -127 al 127 por ende del 128 al 255 los toma como negativos.
    unsigned char aux_S;
    if (ubic <= 255)
    {
        *oss << this -> obtener_S(ubic);
    }
    else
    {
        aux_P = this -> obtener_P(ubic);
        aux_S = this -> obtener_S(ubic);
        this -> imprimir_indice (aux_P, oss);
        this -> imprimir_indice (aux_S, oss);
    }
        
}

//Carga tabla ASCII extendida desde 0 hasta 255.
bool diccionario::cargar_ASCII()
{
    for(int i=0; i<=255; i++)
	    this -> asignar_secuencia(i,-1,char(i));
    ult_ = 255;        
    return true;
}