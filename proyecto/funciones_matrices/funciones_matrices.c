#include "../funciones_grupo/funciones_grupo.h"
#include "funciones_matrices.h"
void eliminarMatriz(PIXELBGR **mat, int filas)
{
    int i;

    for(i=0; i<filas; i++)
    {
        free(mat[i]);
    }

    free(mat);
}
PIXELBGR** crearMatriz(int filas, int columnas)
{
    int i=0;
    PIXELBGR **iniMat = NULL;
    PIXELBGR** mat = (PIXELBGR**)malloc(filas * sizeof(PIXELBGR*));

    if(mat == NULL)
        return NULL;

    iniMat = mat;

    while(i<filas)
    {
        *mat = (PIXELBGR*) malloc(columnas * sizeof(PIXELBGR));
        if(*mat == NULL)
        {
            eliminarMatriz(iniMat, i);
            i= filas + 1;
        }

        mat++;
        i++;

    }

    return (i==filas)? iniMat: NULL;
}
