#include "../funciones_grupo/funciones_grupo.h"
#include "funciones_filtroparametro.h"
int contraste(HEADER *datos, PIXELBGR **mat, int x, int orden, int codVerbose,  char* nomNewArch)
{
    /*
                                                   ¡NOTA!
           La formula para cambiar el contraste es una transformación lineal a la que se le debe aplicar a cada pixel y
           128 como ''pivote'' o valor que no cambia. No es exacto la mitad de 255 portque redondea para arriba.

                                   Nuevo color = (color original - 128) * factor + 128

           Así mismo tambien hay que ajustar porque se puede ir del rango de 0 a 255.

                                   Si nuevo color > 255    entonces nuevo color = 255
                                   Si nuevo color < 0      entonces nuevo color = 0
    */
    float colorNuevo, factor = 1.0, valAjuste = (float)x/100;
    int i, j;



    PIXELBGR **matNew = crearMatriz(datos->alto, datos->ancho);
     if(matNew == NULL)
        return EMEMORIA;

    if(orden == AUMENTAR)
    {
        factor+=valAjuste;
    }
    else
    {
        factor-=valAjuste;

        if(factor<0)
            factor = 0;
    }


    for(i=0; i<datos->alto; i++)
    {
        for(j=0; j<datos->ancho; j++)
        {
            colorNuevo = ((mat[i][j].rojo - 128) * factor) + 128;
            matNew[i][j].rojo = (uint8_t)ajuste(colorNuevo);

            colorNuevo = ((mat[i][j].verde - 128) * factor) + 128;
            matNew[i][j].verde = (uint8_t)ajuste(colorNuevo);

            colorNuevo = ((mat[i][j].azul - 128) * factor) + 128;
            matNew[i][j].azul = (uint8_t)ajuste(colorNuevo);


        }

    }


    verbose("[INFO] Filtro aplicado\n[INFO] Generando imagen\n", codVerbose);
    generarImagen(datos,matNew,nomNewArch);
    verbose("[INFO] Imagen generada\n", codVerbose);

    eliminarMatriz(matNew, datos->alto);

    return EXITO;

}
int tonalidad(HEADER *datos, PIXELBGR **mat, int x, int color, int codVerbose,  char* nomNewArch)
{
    float colorNuevo, factor = 1.0, valAjuste = (float)x/100;
    int i, j;


    PIXELBGR **matNew = crearMatriz(datos->alto, datos->ancho);
     if(matNew == NULL)
        return EMEMORIA;

    factor+=valAjuste;

    for(i=0; i<datos->alto; i++)
    {
        for(j=0; j<datos->ancho; j++)
        {

            matNew[i][j] = mat[i][j];
            if(color == ROJO)
            {
                colorNuevo = mat[i][j].rojo * factor;
                matNew[i][j].rojo = (uint8_t)ajuste(colorNuevo);
            }

            if(color == VERDE)
            {
                colorNuevo = mat[i][j].verde * factor;
                matNew[i][j].verde = (uint8_t)ajuste(colorNuevo);

            }

            if(color == AZUL)
            {
                colorNuevo = mat[i][j].azul * factor;
                matNew[i][j].azul = (uint8_t)ajuste(colorNuevo);
            }


        }

    }
    verbose("[INFO] Filtro aplicado\n[INFO] Generando imagen\n", codVerbose);
    generarImagen(datos,matNew,nomNewArch);
    verbose("[INFO] Imagen generada\n", codVerbose);

    eliminarMatriz(matNew, datos->alto);

    return EXITO;
}
int recortar (HEADER *datos, PIXELBGR **mat, int x, int codVerbose,  char* nomNewArch)
{
    int i, j, altoOriginal = datos->alto, anchoOriginal=datos->ancho ;

    uint32_t altoNew = ((datos->alto * x) / 100);
    uint32_t anchoNew = ((datos->ancho * x) / 100);

    verbose("[INFO] Aplicando recortar\n",codVerbose);

    PIXELBGR **matNew = crearMatriz(altoNew, anchoNew);

    if(matNew == NULL)
        return EMEMORIA;

    if(matNew != NULL)
    {
        for(i=0; i<altoNew; i++)
        {
            for(j=0; j<anchoNew; j++)
            {
                matNew[i][j] = mat[i][j];
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
int achicar (HEADER *datos, PIXELBGR **mat, int x, int codVerbose,  char* nomNewArch)
{
    /*
        Se crea una nueva imagen con nuevos pixeles basados en los existentes, pero no todos, solo se elije cual conservar.

        Se calcula los nuevos altos y anchos en base al porcentaje que se quiere achicar
        Luego para calcular que pixel conservar solo se le multiplica a la posicion original su maximo valor + 1 y se lo divide
        con su version nueva. Ese es el pixel que se conserva, no cualquiera ya que sino pierde ''datos de mas'' la imagen.

    */

    int i, j, altoOriginal = datos->alto, anchoOriginal=datos->ancho;

    uint32_t altoNew = ((datos->alto * x) / 100);
    uint32_t anchoNew = ((datos->ancho * x) / 100);

    PIXELBGR **matNew = crearMatriz(altoNew, anchoNew);

    if(matNew == NULL)
        return EMEMORIA;


    verbose("[INFO] Aplicando achicar\n", codVerbose);

    if(matNew != NULL)
    {
        for(i=0; i<altoNew; i++)
        {
            for(j=0; j<anchoNew; j++)
            {
                matNew[i][j] = mat[ (i * altoOriginal) / altoNew ][ (j * anchoOriginal) / anchoNew ];
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
