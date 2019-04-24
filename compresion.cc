#include <iostream>
#include "compresion.h"

using namespace std;

#define MSJ_ERROR_FOPEN "No se pudo abrir el archivo."
#define MSJ_ARCHIVO_VACIO "El archivo a tratar está vacío."

//Comprime un archivo en modo texto de iss en otro archivo oss según Lempel-ziv-Welch.
bool comprimir(diccionario & dic, istream * iss, ostream *oss)
{
    char S;
	int P = -1;
	int indice = -1;

	dic.resetear_diccionario();
	//Para primeros 2 carácteres. El primero lo va a encontrar. El segundo no.
	if( (S = (*iss).get()) != EOF ){
	
		//Si viene de entrada estándar y recibo \n corto.
		if( S == '\n' && iss == &cin )
			return false;

		P = dic.buscar_secuencia(-1, S);
		if( (S = (*iss).get()) != EOF ){

			//Si viene de entrada estándar y recibo \n corto.
			if( S == '\n' && iss == &cin )
			{
				*oss << P << ',' << (int)'\n' << endl;
				return false;
			}

			dic.agregar_secuencia(P, S);
			*oss << P << ","; 
			P = dic.buscar_secuencia(-1,S);

		}
		//Si el próximo caracter está vacío lo imprime y sale de la función.
		else
		{
			*oss << P; 
			return false;
		}
		
	}
	//Archivo de entrada vacío.
	else
	{
		cout << MSJ_ARCHIVO_VACIO << endl;
		return false;
	}

	//Desde el tercer caracter hasta el final.	
	while( (S = (*iss).get()) != EOF )
	{	
		//Si viene de entrada estándar y recibo \n corto.
		if( S == '\n' && iss == &cin )
		{
			*oss << P << ',' << (int)'\n' << endl;
			return false;
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
	return false;
}

//Descomprime un archivo en modo texto de iss en otro archivo oss según Lempel-ziv-Welch.
bool descomprimir(diccionario & dic, istream * iss, ostream *oss)
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
				cout << MSJ_ARCHIVO_VACIO << endl;
				return false;
			}
			else
			{
				break;
			}
		}

		Pr_carac_flag = true;
		int aux;
    	aux = int(indice_actual_aux) - 48; //48 por casteo (0 = 48 en la tabla ascii).
    	indice_actual = indice_actual*10 + aux; //ejemplo: 432 = 10*( 10*(4) + 3 ) + 2; 
    }
	*oss << dic.obtener_S(indice_actual);
	//Si viene de entrada estándar y recibo \n corto.
	if(indice_actual_aux == '\n'  && iss == &cin)
		return false;

	//Del segundo caracter hasta el final.
    while ( (*iss).eof() == false )        
    {
        indice_anterior = indice_actual;
        indice_actual=0;
		//Leo hasta coma. Ignoro \n.
        while( (indice_actual_aux=(*iss).get()) != ',' && (*iss).eof() == false && !(indice_actual_aux == '\n' && iss == &cin ))
        {   
			int aux;                
            aux = int(indice_actual_aux) - 48;
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
			return false;
    }


    return false;
}