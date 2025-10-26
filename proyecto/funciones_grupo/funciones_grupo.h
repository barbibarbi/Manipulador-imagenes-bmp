#ifndef FUNCIONES_GRUPO_H_INCLUDED
#define FUNCIONES_GRUPO_H_INCLUDED

#include <stdio.h>
#include <stdint.h> //Para usar unit8_t, unit16_t y uint32_t
#include <stdlib.h>
#include <string.h>
#include <time.h>



/*
                Librería stdint.h

    Esta libreria proporciona tipos de enteros con ancho fijo

        uint8_t entero con signo de 8 bits
        uint16_t entero con signo de 16 bits
        uint32_t entero con signo de 32 bits

    Lo usamos para guardar los datos del head de la imagen
*/



//ESTRUCTURAS
/*
    Aclaración de tipo de datos
    Se incluye la libreria stdint.h que contiene este ''tipo de dato''
    uint16_t lee exactamente 2 bytes
    uint32_t lee exactamente 4 bytes
    Esta estrucura es para guardar correctamente los metadatos de la imagen
*/
typedef struct
{
    uint16_t  tipoFichero;                   //bytes 0 1
    uint32_t  tamArchivo;                    //bytes 2 3 4 5
    uint16_t  reservado1;                    //bytes 6 7
    uint16_t  reservado2;                    //bytes 8 9
    uint32_t  datosImagen;                   //bytes 10 11 12 13
    uint32_t  tamHead;                       //bytes 14 15 16 17
    uint32_t  ancho;                         //bytes 18 19 20 21
    uint32_t  alto;                          //bytes 22 23 24 25
    uint16_t  numPlanos;                     //bytes 26 27
    uint16_t  tamCadaPunto;                  //bytes 28 29
    uint32_t  compresion;                    //bytes 30 31 32 33
    uint32_t  tamImagen;                     //bytes 34 35 36 37
    uint32_t  resHorizontal;                 //bytes 38 39 40 41
    uint32_t  resVertical;                   //bytes 42 43 44 45
    uint32_t  tamTablaColor;                 //bytes 46 47 48 49
    uint32_t  contColoresImportantes;        //bytes 50 51 52 53

} __attribute__((packed)) HEADER;
/*__attribute__((packed)) nota: el compilador hacer que los elementos uint32_t comiencen en direcciones multiplo de 4
                                así que el compilador añade un PADDING (relleno) y esto hace que lea mal el HEADER del archivo
                                esto se arregla empaquetano la estructura
*/

/*
    Esta estructura es para cada pixel de la imagen
    Cada pixel se compone de 3 colores: Rojo, Verde, Azul y tienen 1 byte cada color.
    Cada pixel ocupa 3 bytes.
    Usar uint8_t para cada color.
    Cada pixel esta en formato BGR -> Blue(azul), Green(verde), Red(rojo)
*/
typedef struct
{
    uint8_t  azul;
    uint8_t  verde;
    uint8_t  rojo;

} PIXELBGR;

typedef struct
{
    int   comOrden;
    int     valor;

} COMANDOS;

typedef struct
{
    char nomArch[50];
    COMANDOS comando[15];
    int cantCom;

} INGRESO;

typedef struct
{
    char nomCom[50];
    int codCom;

} MAPEOCOMANDOS;

//MACROS
#define BM  0x4D42
/*
                             El programa debe retornar los siguientes códigos
                             • 0: Éxito
                             • 1: Error de argumentos
                             • 2: Error de archivo (no encontrado, sin permisos)
                             • 3: Error de memoria (por ejemplo, malloc falló)
                             • 4: Formato BMP inválido
*/
#define EXITO           0
#define EARGUMENTO      1
#define EARCHIVO        2
#define EMEMORIA        3
#define FINVALIDO       4
#define ECOMPRESION     5
#define EPROFUNDIDAD    6


//        CADA COMANDO SE LE ASIGNA UN NUMERO
#define CANTCOMANDOS    15


#define NEGATIVO        1
#define ESCALAGRIS      2
#define ESPHORIZONTAL   3
#define ESPVERTICAL     4
#define INFO            5
#define PSICODELIA      6
#define ROTIZQUIERDA    7
#define ROTDERECHA      8
#define AUMCONTRASTE    9
#define REDCONTRASTE    10
#define TONALIDADZUL    11
#define TONALIDADVERDE  12
#define TONALIDADROJO   13
#define RECORTAR        14
#define ACHICAR         15



#define HELP                0
#define VERBOSE             1
#define VALIDAR             2
#define HORIZONTAL          3
#define VERTICAL            4
#define MAXCANTBAN          5

#define AZUL            0
#define VERDE           1
#define ROJO            2
#define CANTCOLORES     3

#define AUMENTAR        1
#define REDUCIR         0

#define IMAGEN1         0
#define IMAGEN2         1
#define MAXCANTIMG      2


#define NOMARCHMAX      100


#include "../funciones_matrices/funciones_matrices.h"
#include "../funciones_rotacion/funciones_rotacion.h"
#include "../funciones_concatenacion/funciones_concatenacion.h"
#include "../funciones_archivo/funciones_archivo.h"
#include "../funciones_filtro_parametro/funciones_filtroparametro.h"
#include "../funciones_filtro_basico/funciones_filtrobasico.h"

#define CALCPADDING(X) ((4 - ((X * sizeof(PIXELBGR)) % 4)) % 4)

void verbose(const char* msj, const int v);
void mostrarArgumentos(int argc, char *argv[]);
int verificaArgumentos(int argc, char *argv[], INGRESO *coms, int *cantImg, int *ban);
void info(const char* nomArch, const HEADER *datos);
int validar(const HEADER *datos, const char* nomArch, int codVerbose);
void help();
void aplicarFiltros(HEADER *datos1, HEADER *datos2, PIXELBGR **mat1, PIXELBGR **mat2, INGRESO *coms,int codVerbose, int cantImg, int conH, int conV);

int procesar_imagen(int argc, char *argv[]);




#endif // FUNCIONES_GRUPO_H_INCLUDED
