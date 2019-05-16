#include <iostream>
#include "diccionario.h"
#include "tipos_datos.h"
using namespace std;

estado_t comprimir(diccionario &, istream *, ostream *);
estado_t descomprimir(diccionario &, istream *, ostream *);