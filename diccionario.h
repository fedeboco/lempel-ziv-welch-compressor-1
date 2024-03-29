#include <iostream>
#include "arreglo.h"
#include "secuencia.h"
#include "tipos_datos.h"
using namespace std;

#ifndef DICCIONARIO_DEF
#define DICIONARIO_DEF

class diccionario
{
private:
    arreglo * dic_;
    int size_;                               
    int ult_;

public:
    secuencia & obtener_secuencia(const int);
    diccionario(const int &);
    ~diccionario();
    const int buscar_secuencia(const int &, const char &);
    int agregar_secuencia(const int &, const char &);
    estado_t asignar_secuencia(const int, const secuencia &);
    estado_t asignar_secuencia(const int pos, const int &, const char &);
    int obtener_P(const int) const;
    int obtener_ult_();
    char obtener_S(const int) const;
    void resetear_diccionario();
    int obtener_indice(const int &);
    estado_t imprimir_indice (const int &, ostream *);
    bool cargar_ASCII();

};
#endif