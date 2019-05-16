#include <iostream>
#include "compresion.h"
#include "tipos_datos.h"
#include "funciones_impresion.h"

using namespace std;

//Comprime un archivo en modo texto de iss en otro archivo oss según Lempel-ziv-Welch.
estado_t comprimir(diccionario & dic, istream * iss, ostream *oss)
{
    char S;
	int P = -1;
	int indice = -1;
	// estado_f es una variable para corroborar la candición de error al leer un caracter.
	bool estado_f; 
	dic.resetear_diccionario();
	//Para primeros 2 carácteres. El primero lo va a encontrar. El segundo no.
	S =(*iss).get();
	if( (*iss).eof() == false && (estado_f = (*iss).fail()) == false){
	
		//Si viene de entrada estándar y recibo \n corto.
		if( S == '\n' && iss == &cin )
			return OK;

		P = dic.buscar_secuencia(-1, S);
		S = (*iss).get();
		if((*iss).eof() == false && (estado_f = (*iss).fail()) == false ){

			//Si viene de entrada estándar y recibo \n corto.
			if( S == '\n' && iss == &cin )
			{
				*oss << P << ',' << (int)'\n' << endl;
				if((*oss).fail())
					return ERROR_ESCRITURA;
				return OK;
			}
			dic.agregar_secuencia(P, S);
			*oss << P << ",";
			if((*oss).fail())
				return ERROR_ESCRITURA;
			P = dic.buscar_secuencia(-1,S);

		}
		else if(estado_f == true)
			return ERROR_LECTURA_ARCHIVO;
		//Si el próximo caracter está vacío lo imprime y sale de la función.
		else
		{
			*oss << P;
			if((*oss).fail())
				return ERROR_ESCRITURA;
			return OK;
		}
		
	}
	else if (estado_f == true)
		return ERROR_LECTURA_ARCHIVO;
	//Archivo de entrada vacío.
	else
	{
		imprimir_mensaje(MSJ_ESTADO_ARCHIVO_VACIO);
		return OK;
	}
	S = (*iss).get();
	//Desde el tercer caracter hasta el final.	
	while((*iss).eof() == false && (estado_f = (*iss).fail()) == false )
	{	
		//Si viene de entrada estándar y recibo \n corto.
		if( S == '\n' && iss == &cin )
		{
			*oss << P << ',' << (int)'\n' << endl;
			if((*oss).fail())
				return ERROR_ESCRITURA;
			return OK;
		}

		indice = dic.buscar_secuencia(P, S);
		if( indice == -1 )
		{
			dic.agregar_secuencia(P, S);
			*oss << P << ",";
			if((*oss).fail())
				return ERROR_ESCRITURA;
			indice = dic.buscar_secuencia(-1,S);
		}
		P = indice;
		S = (*iss).get();
	}
	if(estado_f == true)
		return ERROR_LECTURA_ARCHIVO;
	*oss << P;
	if((*oss).fail())
		return ERROR_ESCRITURA;
	return OK;
}

//Descomprime un archivo en modo texto de iss en otro archivo oss según Lempel-ziv-Welch.
estado_t descomprimir(diccionario & dic, istream * iss, ostream *oss)
{  
	int aux_u;
	bool Pr_carac_flag = false;     
    char indice_actual_aux;
    int indice_anterior=0, indice_actual = 0;
	// estado_f es una variable para corroborar la candición de error al leer un caracter.
	bool estado_f;			
	//Para primer caracter. Leo hasta coma. Ignoro \n.
    while( (indice_actual_aux=(*iss).get()) != ',' && !(indice_actual_aux == '\n' && iss == &cin))
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
		else if((estado_f=(*iss).fail()) == true)
			return ERROR_LECTURA_ARCHIVO;

		Pr_carac_flag = true;
		int aux;
    	aux = int(indice_actual_aux) - GAP_LETRAS_ASCII; //48 por casteo (0 = 48 en la tabla ascii).
    	indice_actual = indice_actual*10 + aux; //ejemplo: 432 = 10*( 10*(4) + 3 ) + 2; 
    }
	//Compruebo si el while salió por un fallo de lectura.
	
	*oss << dic.obtener_S(indice_actual);
	if((*oss).fail())
		return ERROR_ESCRITURA;
	//Si viene de entrada estándar y recibo \n corto.
	if(indice_actual_aux == '\n'  && iss == &cin)
		return OK;

	//Del segundo caracter hasta el final.
    while ( (*iss).eof() == false)        
    {
        indice_anterior = indice_actual;
        indice_actual=0;
		
		//Leo hasta coma. Ignoro \n.
        while( ((indice_actual_aux=(*iss).get()) != ',' && (*iss).eof() == false && !(indice_actual_aux == '\n' && iss == &cin )) && (estado_f=(*iss).fail()) == false)  //Agrego el (*iss).fail() == false para salir si el flag bad o fail s eactivam a, final pregunoto si salí por eso.
        {   
			int aux;                
            aux = int(indice_actual_aux) - GAP_LETRAS_ASCII;
            indice_actual = indice_actual*10 + aux;
        }         
        if  (estado_f == true)
			return ERROR_LECTURA_ARCHIVO;  
        //Uso la posición de indice_actual para saber si esta o no en el diccionario
        if(indice_actual <= dic.obtener_ult_())
		{
		   	//ubic = indice_actual;                                    
            if(dic.imprimir_indice(indice_actual, oss) != OK)
				return ERROR_ESCRITURA;
            aux_u = dic.obtener_indice(indice_actual);            
			dic.agregar_secuencia(indice_anterior,aux_u);
		}
        else
        {
            aux_u = dic.obtener_indice(indice_anterior);  
			dic.agregar_secuencia(indice_anterior,aux_u);
            if(dic.imprimir_indice(dic.obtener_ult_(), oss) != OK)
				return ERROR_ESCRITURA;
        }

		//Si viene de entrada estándar y recibo \n corto.
		if( indice_actual_aux == '\n' && iss == &cin )
			return OK;
    }
    return OK;
}