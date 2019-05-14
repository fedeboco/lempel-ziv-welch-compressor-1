#include <iostream>
#include "compresion.h"
#include "tipos_datos.h"
#include "funciones_impresion.h"

using namespace std;

/*
#define MSJ_ERROR_FOPEN "No se pudo abrir el archivo."
#define MSJ_ARCHIVO_VACIO "El archivo a tratar está vacío."
#define GAP_LETRAS_ASCII 48
*/

//Comprime un archivo en modo texto de iss en otro archivo oss según Lempel-ziv-Welch.
estado_t comprimir(diccionario & dic, istream * iss, ostream *oss)
{
    char S;
	int P = -1;
	int indice = -1;

	dic.resetear_diccionario();
	//Para primeros 2 carácteres. El primero lo va a encontrar. El segundo no.
	if( (S = (*iss).get())==S && (*iss).eof() == false ){
	
		//Si viene de entrada estándar y recibo \n corto.
		if( S == '\n' && iss == &cin )
			return OK;

		P = dic.buscar_secuencia(-1, S);
		if( (S = (*iss).get())==S && (*iss).eof() == false ){

			//Si viene de entrada estándar y recibo \n corto.
			if( S == '\n' && iss == &cin )
			{
				*oss << P << ',' << (int)'\n' << endl;
				return OK;
			}

			dic.agregar_secuencia(P, S);
			*oss << P << ","; 
			P = dic.buscar_secuencia(-1,S);

		}
		//Si el próximo caracter está vacío lo imprime y sale de la función.
		else
		{
			*oss << P; 
			return OK;
		}
		
	}
	//Archivo de entrada vacío.
	else
	{
		imprimir_mensaje(MSJ_ESTADO_ARCHIVO_VACIO);
		return OK;
	}

	//Desde el tercer caracter hasta el final.	
	while( (S = (*iss).get())==S  && (*iss).eof() == false )
	{	
		//Si viene de entrada estándar y recibo \n corto.
		if( S == '\n' && iss == &cin )
		{
			*oss << P << ',' << (int)'\n' << endl;
			return OK;
		}

		indice = dic.buscar_secuencia(P, S);
		if( indice == -1 )
		{
			dic.agregar_secuencia(P, S);
			*oss << P << ",";
			indice = dic.buscar_secuencia(-1,S);
		}
		P = indice;
	}
	*oss << P;
	return OK;
}

//Descomprime un archivo en modo texto de iss en otro archivo oss según Lempel-ziv-Welch.
estado_t descomprimir(diccionario & dic, istream * iss, ostream *oss)
{  
    //int ubic = 0;
	int aux_u;
	bool Pr_carac_flag = false;     
    char indice_actual_aux;
    int indice_anterior=0, indice_actual = 0;

	//Para primer caracter. Leo hasta coma. Ignoro \n.
    while( (indice_actual_aux=(*iss).get()) != ',' && !(indice_actual_aux == '\n' && iss == &cin ))
    {		
		if ( indice_actual_aux == EOF )
		{
			if( Pr_carac_flag == false )
			{
				imprimir_mensaje(MSJ_ESTADO_ARCHIVO_VACIO);
				return OK;
			}
			else
			{
				break;
			}
		}

		Pr_carac_flag = true;
		int aux;
    	aux = int(indice_actual_aux) - GAP_LETRAS_ASCII; //48 por casteo (0 = 48 en la tabla ascii).
    	indice_actual = indice_actual*10 + aux; //ejemplo: 432 = 10*( 10*(4) + 3 ) + 2; 
    }
	*oss << dic.obtener_S(indice_actual);
	//Si viene de entrada estándar y recibo \n corto.
	if(indice_actual_aux == '\n'  && iss == &cin)
		return OK;

	//Del segundo caracter hasta el final.
    while ( (*iss).eof() == false )        //Agrego el (*iss).fail() == false para salir si el flag bad o fail s eactivam a, final pregunoto si salí por eso.
    {
        indice_anterior = indice_actual;
        indice_actual=0;
		//Leo hasta coma. Ignoro \n.
        while( (indice_actual_aux=(*iss).get()) != ',' && (*iss).eof() == false && !(indice_actual_aux == '\n' && iss == &cin ))
        {   
			int aux;                
            aux = int(indice_actual_aux) - GAP_LETRAS_ASCII;
            indice_actual = indice_actual*10 + aux;
        }         
            
        //Uso la posición de indice_actual para saber si esta o no en el diccionario
        if(indice_actual <= dic.obtener_ult_())
		{
		   	//ubic = indice_actual;                                    
            dic.imprimir_indice(indice_actual, oss);
            aux_u = dic.obtener_indice(indice_actual);            
			dic.agregar_secuencia(indice_anterior,aux_u);
		}
        else
        {
            aux_u = dic.obtener_indice(indice_anterior);  
			dic.agregar_secuencia(indice_anterior,aux_u);
            dic.imprimir_indice(dic.obtener_ult_(), oss);
        }

		//Si viene de entrada estándar y recibo \n corto.
		if( indice_actual_aux == '\n' && iss == &cin )
			return OK;
    }
    return OK;
}