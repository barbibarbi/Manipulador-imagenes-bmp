#include "../funciones_grupo/funciones_grupo.h"
#include "funciones_concatenacion.h"
int concatencacionHorizontal(HEADER *datos1, PIXELBGR **mat1, const HEADER *datos2,  PIXELBGR **mat2, int codVerbose,  char* nomNewArch)
{
    int i, j, altoOriginal = datos1->alto, anchoOriginal=datos1->ancho;

    uint32_t anchoNew = datos1->ancho + datos2->ancho;
    uint32_t altoNew = (datos1->alto > datos2->alto)? datos1->alto : datos2->alto;

    verbose("[INFO] Aplicando concatenación horizontal\n", codVerbose);

    PIXELBGR **matNew = crearMatriz(altoNew, anchoNew);

    if(matNew == NULL)
        return EMEMORIA;

    if(matNew != NULL)
    {

        for(j=0; j<datos1->ancho; j++) //columnas
        {
            for(i=0; i<datos1->alto; i++) //filas
            {
                matNew[i][j] = mat1[i][j];
            }

            if(datos1->alto < altoNew)
            {

                for(i=datos1->alto; i<altoNew; i++)
                {
                    matNew[i][j].rojo = 255;
                    matNew[i][j].verde = 255;
                    matNew[i][j].azul = 255;
                }

            }

        }

        for(j=0; j<datos2->ancho; j++) //columnas
        {
            for(i=0; i<datos2->alto; i++) //filas
            {
                matNew[i][j+datos1->ancho] = mat2[i][j];
            }

            if(datos2->alto < altoNew)
            {

                for(i=datos2->alto; i<altoNew; i++)
                {
                    matNew[i][j+datos1->ancho].rojo = 255;
                    matNew[i][j+datos1->ancho].verde = 255;
                    matNew[i][j+datos1->ancho].azul = 255;
                }

            }

        }
        datos1->alto = altoNew;
        datos1->ancho = anchoNew;

        verbose("[INFO] Filtro aplicado\n[INFO] Generando imagen\n", codVerbose);
        generarImagen(datos1,matNew,nomNewArch);
        verbose("[INFO] Imagen generada\n", codVerbose);

        eliminarMatriz(matNew, altoNew);

        datos1->alto = altoOriginal;
        datos1->ancho = anchoOriginal;


    }
    return EXITO;
}
int concatencacionVertical(HEADER *datos1, PIXELBGR **mat1, const HEADER *datos2, PIXELBGR **mat2, int codVerbose,  char* nomNewArch)
{
    int i, j, altoOriginal = datos1->alto, anchoOriginal=datos1->ancho;

    uint32_t altoNew = datos1->alto + datos2->alto;
    uint32_t anchoNew = (datos1->ancho > datos2->ancho)? datos1->ancho : datos2->ancho;

    verbose("[INFO] Aplicando concatenación vertical\n", codVerbose);

    PIXELBGR **matNew = crearMatriz(altoNew, anchoNew);

    if(matNew == NULL)
        return EMEMORIA;


    if(matNew != NULL)
    {

        for(i=0; i<datos1->alto; i++)
        {
            for(j=0; j<datos1->ancho; j++)
            {
                matNew[i][j] = mat1[i][j];
            }

            if(datos1->ancho < anchoNew)
            {

                for(j=datos1->ancho; j<anchoNew; j++)
                {
                    matNew[i][j].rojo = 255;
                    matNew[i][j].verde = 255;
                    matNew[i][j].azul = 255;
                }

            }

        }


        for(i=0; i<datos2->alto; i++)
        {
            for(j=0; j<datos2->ancho; j++)
            {
                matNew[i+datos1->alto][j] = mat2[i][j];
            }
            if(datos2->ancho < anchoNew)
            {

                for(j=datos2->ancho; j<anchoNew; j++)
                {
                    matNew[i+datos1->alto][j].rojo = 255;
                    matNew[i+datos1->alto][j].verde = 255;
                    matNew[i+datos1->alto][j].azul = 255;
                }

            }

        }

        datos1->alto = altoNew;
        datos1->ancho = anchoNew;

        verbose("[INFO] Filtro aplicado\n[INFO] Generando imagen\n", codVerbose);
        generarImagen(datos1,matNew,nomNewArch);
        verbose("[INFO] Imagen generada\n", codVerbose);

        eliminarMatriz(matNew, altoNew);

        datos1->alto = altoOriginal;
        datos1->ancho = anchoOriginal;


    }

    return EXITO;

}
