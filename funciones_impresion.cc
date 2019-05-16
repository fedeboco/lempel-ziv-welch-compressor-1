#include <iostream>
#include <string>

#include "tipos_datos.h"
#include "funciones_impresion.h"

using namespace std;

estado_t imprimir_error(estado_t estado)
{
    string error[]={
                    MSJ_ERROR_PUNTERO_NULO,
                    MSJ_ERROR_SIZE_CONSTRUCTOR,
                    MSJ_ERROR_SIZE_1,
                    MSJ_ERROR_SIZE_2,
                    MSJ_ERROR_OBT_SEC,
                    MSJ_ERROR_SIZE_DICC,
                    MSJ_ERROR_COMP,
                    MSJ_ERROR_DESCOMP,
                    MSJ_ERROR_OPENING,
                    MSJ_ERROR_OPERATION,
                    MSJ_ERROR_FOPEN,
                    MSJ_ERROR_DESC_COMP_INDEF,
                    MSJ_ERROR_LECTURA_ARCHIVO,
                    MSJ_ERROR_ESCRITURA,
                    MSJ_ERROR_ASIGNAR_SEC
    };

    cout << error[estado] << endl;
    return OK;
}

estado_t imprimir_mensaje(mensaje_t msj)
{
    string mensaje[]={
                      MSJ_OK_COMP,
                      MSJ_OK_DESCOMP,
                      MSJ_STD_INPUT,
                      MSJ_DEFAULT_OP,
                      MSJ_DIC_LLENO,
                      MSJ_ARCHIVO_VACIO
    };

    cout << mensaje[msj] << endl;
    return OK;
}