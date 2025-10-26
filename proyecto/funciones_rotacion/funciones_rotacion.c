#include "../funciones_grupo/funciones_grupo.h"
#include "funciones_rotacion.h"
int rotar90derecha(HEADER *datos, PIXELBGR **mat, int codVerbose,  char* nomNewArch)
{
    /*
        Para rotar una matriz 90 grados primero se transpone respecto la diagonal principal y luego se invierten las columnas, pero
        esto es solo si es cuadrada.
        La forma mas comoda de hacerlo es hacer una nueva matriz y liberar la memoria de la otra matriz.
    */

    int i, j, altoOriginal = datos->alto, anchoOriginal=datos->ancho;

    uint32_t altoNew = datos->ancho;
    uint32_t anchoNew = datos->alto;

    verbose("[INFO] Aplicando rotación a la derecha\n", codVerbose);

    PIXELBGR **matNew = crearMatriz(altoNew, anchoNew);

    if(matNew == NULL)
        return EMEMORIA;



    if(matNew != NULL)
    {
        for(i=0; i<datos->alto; i++)
        {
            for(j=0; j<datos->ancho; j++)
            {
                matNew[j][anchoNew - 1 -i] = mat[i][j];
            }

        }


        datos->alto = altoNew;
        datos->ancho = anchoNew;

        verbose("[INFO] Filtro aplicado\n[INFO] Generando imagen\n", codVerbose);
        generarImagen(datos,matNew,nomNewArch);
        verbose("[INFO] Imagen generada\n", codVerbose);

        eliminarMatriz(matNew, datos->alto);

        datos->alto = altoOriginal;
        datos->ancho = anchoOriginal;
    }
        return EXITO;

}
int rotar90izquierda(HEADER *datos, PIXELBGR **mat, int codVerbose,  char* nomNewArch)
{
    /*
        La misma logica que uso en rotar a la derecha pero a la izquierda.
        Para hacerlo solo hay que cambiar la formula
    */

     int i, j, altoOriginal = datos->alto, anchoOriginal=datos->ancho;

    uint32_t altoNew = datos->ancho;
    uint32_t anchoNew = datos->alto;

    PIXELBGR **matNew = crearMatriz(altoNew, anchoNew);

    verbose("[INFO] Aplicando rotación a la izquierda\n", codVerbose);

    if(matNew == NULL)
        return EMEMORIA;

    if(matNew != NULL)
    {
        for(i=0; i<datos->alto; i++)
        {
            for(j=0; j<datos->ancho; j++)
            {
                matNew[altoNew - 1 - j][i] = mat[i][j];
            }

        }

         datos->alto = altoNew;
        datos->ancho = anchoNew;

        verbose("[INFO] Filtro aplicado\n[INFO] Generando imagen\n", codVerbose);
        generarImagen(datos,matNew,nomNewArch);
        verbose("[INFO] Imagen generada\n", codVerbose);

        eliminarMatriz(matNew, datos->alto);

        datos->alto = altoOriginal;
        datos->ancho = anchoOriginal;
    }
        return EXITO;

}
