#include "../funciones_grupo/funciones_grupo.h"
#include "funciones_filtrobasico.h"
//FUNCIONES FILTROS BASICOS
int voltearVertical(HEADER *datos, PIXELBGR **mat, int codVerbose,  char* nomNewArch)
{
    /*
                                                    ¡NOTA!

            Solo es intercambiar las filas
            Hay que recorrer la matriz hasta la mitad para lograr esto.
    */
    int i, j;

    verbose("[INFO] Aplicando filtro espejar horizontal\n", codVerbose);
    PIXELBGR **matNew = crearMatriz(datos->alto, datos->ancho);
     if(matNew == NULL)
        return EMEMORIA;

    for(i=0; i<datos->alto; i++)
    {
        for(j=0; j<datos->ancho; j++)
        {
            matNew[datos->alto - 1 -i][j] = mat[ i][j];
        }

    }

    verbose("[INFO] Filtro aplicado\n[INFO] Generando imagen\n", codVerbose);
    generarImagen(datos,matNew,nomNewArch);
    verbose("[INFO] Imagen generada\n", codVerbose);

    eliminarMatriz(matNew, datos->alto);

    return EXITO;
}

int voltearHorizontal(HEADER *datos, PIXELBGR **mat, int codVerbose,  char* nomNewArch)
{
    /*
                                                    ¡NOTA!

            Solo es intercambiar las Columnas
            Hay que recorrer la matriz hasta la mitad para lograr esto.
    */
    int i, j;

    verbose("[INFO] Aplicando filtro espejar horizontal\n", codVerbose);
    PIXELBGR **matNew = crearMatriz(datos->alto, datos->ancho);
     if(matNew == NULL)
        return EMEMORIA;


    for(i=0; i<datos->alto; i++)
    {
        for(j=0; j<datos->ancho; j++)
        {
            matNew[i][datos->ancho -1 - j] = mat[i][j];
        }

    }


    verbose("[INFO] Filtro aplicado\n[INFO] Generando imagen\n", codVerbose);
    generarImagen(datos,matNew,nomNewArch);
    verbose("[INFO] Imagen generada\n", codVerbose);

    eliminarMatriz(matNew, datos->alto);

    return EXITO;
}

void intercambiar (void* a, void *b, size_t tamDato)
{
    void* aux = malloc(tamDato);

    memcpy(aux, a, tamDato);
    memcpy(a, b, tamDato);
    memcpy(b, aux, tamDato);

    free(aux);
}
float ajuste(float n)
{
    if(n>255)
        return 255;
    if(n<0)
        return 0;

    return n;
}
int negativo(PIXELBGR **mat,  HEADER *datos, int codVerbose,  char* nomNewArch)
{
    /*
                                                    ¡NOTA!

            Cada color esta en hexa y es guardado en uint8_t. Casa color va de 0x00 (0) a 0xff (255)

            Así que para obtener el valor negativo o su contraparte hay que hacer la siguiente cuenta:

                                        Color invertido = 255 - Color original
    */
    int i, j;
    verbose("[INFO] Aplicando filtro negativo\n", codVerbose);
    PIXELBGR **matNew = crearMatriz(datos->alto, datos->ancho);

    if(matNew == NULL)
        return EMEMORIA;

    for(i=0; i<datos->alto; i++)
    {
        for(j=0; j<datos->ancho; j++)
        {
            matNew[i][j].azul = 255 - mat[i][j].azul;
            matNew[i][j].rojo = 255 - mat[i][j].rojo;
            matNew[i][j].verde = 255 - mat[i][j].verde;
        }

    }

    verbose("[INFO] Filtro aplicado\n[INFO] Generando imagen\n", codVerbose);
    generarImagen(datos,matNew,nomNewArch);
    verbose("[INFO] Imagen generada\n", codVerbose);

    eliminarMatriz(matNew, datos->alto);

    return EXITO;

}

int escalaGrises(PIXELBGR **mat, HEADER *datos,int codVerbose,  char* nomNewArch)
{
    /*
                                                   ¡NOTA!
           Los humanos somos sensibles a estos colores de la siguiente forma:
               Verde - es el color al que somos mas sensibles
               Rojo - es el color al que moderadamente somos sensibles
               Azul - es el color al que menos sensible somos.

           Según la Wikipedia en la pagina de Escala de grises (https://en.wikipedia.org/wiki/Grayscale#) existen varios
           estandares para la luminosidad de sistemas de video. En este codigo usamos el estandar Rec 601 SDTV (Definición Estándar)
           por que es el mas antigüo y utilizado aun al dia de hoy:

                                       Gris = (0.299 * Rojo) + (0.587 * Verde) + (0.114 * Azul)

           Los coeficientes estan asignados a cada color segun la sensibilidad de cada color.
    */

    float gris;
    int i, j;

    verbose("[INFO] Aplicando filtro escala de grises\n", codVerbose);
    PIXELBGR **matNew = crearMatriz(datos->alto, datos->ancho);
     if(matNew == NULL)
        return EMEMORIA;

    for(i=0; i<datos->alto; i++)
    {
        for(j=0; j<datos->ancho; j++)
        {
            gris = (0.299 * mat[i][j].rojo) + (0.587 * mat[i][j].verde) + (0.114 * mat[i][j].azul);

            matNew[i][j].rojo = (uint8_t)gris;
            matNew[i][j].verde = (uint8_t)gris;
            matNew[i][j].azul = (uint8_t)gris;

        }

    }

    verbose("[INFO] Filtro aplicado\n[INFO] Generando imagen\n", codVerbose);
    generarImagen(datos,matNew,nomNewArch);
    verbose("[INFO] Imagen generada\n", codVerbose);

    eliminarMatriz(matNew, datos->alto);

    return EXITO;

}
//FUNCIONES FILTROS PARAMETROS

int psicodelia(HEADER *datos, PIXELBGR **mat, int codVerbose,  char* nomNewArch)
{

    int i, j, randomValor;
    int colores[CANTCOLORES]={AZUL, VERDE, ROJO};
    PIXELBGR **matNew = crearMatriz(datos->alto, datos->ancho);
     if(matNew == NULL)
        return EMEMORIA;

    srand(time(NULL));

    verbose("[INFO] Aplicando filtro comodin\n", codVerbose);
    for(i=0; i<CANTCOLORES; i++)
    {
        randomValor = rand()%3;
        intercambiar(&colores[i],&colores[randomValor],sizeof(int));
    }

    for(i=0; i<datos->alto; i++)
    {
        for(j=0; j<datos->ancho; j++)
        {
            matNew[i][j]=mat[i][j];

            if(colores[0]==VERDE)
                matNew[i][j].azul = matNew[i][j].verde;
            if(colores[0]==ROJO)
                matNew[i][j].azul = matNew[i][j].rojo;
            if(colores[1]==AZUL)
                matNew[i][j].verde = matNew[i][j].azul;
            if(colores[1]==ROJO)
                matNew[i][j].verde = matNew[i][j].rojo;
            if(colores[2]==VERDE)
                matNew[i][j].rojo = matNew[i][j].verde;
            if(colores[2]==AZUL)
                matNew[i][j].rojo = matNew[i][j].azul;
        }
    }

    verbose("[INFO] Filtro aplicado\n[INFO] Generando imagen\n", codVerbose);
    generarImagen(datos,matNew,nomNewArch);
    verbose("[INFO] Imagen generada\n", codVerbose);

    eliminarMatriz(matNew, datos->alto);

    return EXITO;
}


