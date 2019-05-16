#ifndef TIPOS_DE_DATOS__H
#define TIPOS_DE_DATOS__H

//********************************************** Diccionario.cc *********************************************
#define CANT_ASCII 255
#define MSJ_ERROR_SIZE_DICC "El tamaño del diccionario es muy chico, se usará el default = 255"
#define MSJ_ERROR_OBT_SEC "No existen secuencias con índice negativo o índice mayor al último elemento."
#define MSJ_DIC_LLENO "Se lleno el diccionario, se procede a resetearlo"

//********************************************** Arreglo.cc *********************************************
#define MSJ_ERROR_SIZE_1 "Error: acceso inválido a posición "
#define MSJ_ERROR_SIZE_2 " en arreglo de tamaño " 
#define MSJ_ERROR_SIZE_CONSTRUCTOR "Tamaño inválido. No se pudo crear el arreglo."

//********************************************** Compresion.cc *********************************************
#define MSJ_ERROR_FOPEN "No se pudo abrir el archivo."
#define MSJ_ARCHIVO_VACIO "El archivo a tratar está vacío."
#define GAP_LETRAS_ASCII 48

//********************************************** Main.cc *********************************************
#define MAX_VECTOR 65536

#define MSJ_ERROR_COMP "Compresión fallida."
#define MSJ_OK_COMP "Compresión correcta."
#define MSJ_ERROR_DESCOMP "Descompresión fallida."
#define MSJ_OK_DESCOMP "Descompresión correcta." 
#define MSJ_STD_INPUT "Entrada estándar."
#define MSJ_DEFAULT_OP "Operación no especificada. Comprimiendo por defecto."
#define MSJ_ERROR_OPENING "No se puede abrir "
#define MSJ_ERROR_OPERATION "Invocación inválida."
#define MSJ_ERROR_ESCRITURA "Error escribiendo el archivo."
#define MSJ_ERROR_PUNTERO_NULO "Se produjo un error inesperado."
#define MSJ_ERROR_DESC_COMP_INDEF "Descompresión y Compresión idefinido"
#define MSJ_ERROR_LECTURA_ARCHIVO "Se produjo un error al querer leer el archivo."
#define MSJ_ERROR_ASIGNAR_SEC "No se pudo asignar la secuencia al diccionario."
typedef enum{
                ERROR_PUNTERO_NULO = 0,
                ERROR_SIZE_CONSTRUCTOR = 1,
                ERROR_SIZE_1 = 2,
                ERROR_SIZE_2 = 3,
                ERROR_OBTENER_SEC = 4,
                ERROR_SIZE_DIC = 5,
                ERROR_COMP = 6,
                ERROR_DESCOMP = 7,
                ERROR_OPENING = 8,
                ERROR_OPERATION = 9,
                ERROR_FOPEN = 10,
                ERROR_COMP_DESCOP_INDEF =11,
                ERROR_LECTURA_ARCHIVO = 12,
                ERROR_ESCRITURA = 13,
                ERROR_ASIGNAR_SEC = 14,
                OK  = 15
}estado_t;           

typedef enum{
                MSJ_ESTADO_OK_COMP = 0,
                MSJ_ESTADO_OK_DESCOMP = 1,
                MSJ_ESTADO_STD_IMPUT = 2,
                MSJ_ESTADO_DEFAULT_OP = 3,
                MSJ_ESTADO_DIC_LLENO = 4,
                MSJ_ESTADO_ARCHIVO_VACIO = 5
}mensaje_t;

#endif