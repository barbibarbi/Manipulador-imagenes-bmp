#include "../funciones_grupo/funciones_grupo.h"
#include "funciones_archivo.h"
int archivo(char *nomArch, HEADER *datos, PIXELBGR ***mat, int codValidar) //Solo bajo los datos a memoria
{
    int i, padding, valRetorno=EXITO;
    FILE* pf = fopen(nomArch, "rb");
    if(pf == NULL)
        return EARCHIVO;

    fread(datos, sizeof(HEADER), 1, pf); //solo leo el encabezado

    /*
        La imagen debe cumplir con lo siguiente para poder procesar
        Especificaciones =
         • Solo archivos BMP: No se aceptan otros formatos
         • Solo BMP sin compresión
         • Solo 24 bits de profundidad
    */

    switch(valRetorno = validar(datos, nomArch, codValidar))
    {
    case FINVALIDO:

    case ECOMPRESION:

    case EPROFUNDIDAD:
        puts("ARCHIVO INVALIDO- No se puede procesar");
        return valRetorno;
        break;
    default: puts("ARCHIVO VALIDO- Listo para procesar");
        break;

    }



    //si todo se cumple se crea la matriz

    *mat = crearMatriz(datos->alto, datos->ancho);

    if(*mat == NULL)
        return EMEMORIA;

    //padding = (4 - ((datos->ancho * sizeof(PIXELBGR)) % 4)) % 4;
    padding = CALCPADDING(datos->ancho);

    //se llena la matriz con la imagen, el header ya me da la cantidad de filas así que solo uso un for

    fseek(pf, datos->datosImagen, SEEK_SET); //Donde comienza la imagen

    for(i=datos->alto - 1; i>=0; i--)//La primera ''fila'' de pixeles es la ultima de la imagen, pero la primera ''Columna'' es correcta
    {
        fread((*mat)[i],datos->ancho * sizeof(PIXELBGR), 1, pf); // Resferenciar mat y luego aplicarle el offset

        if(padding != 0)
        {
            fseek(pf, padding,SEEK_CUR); //Corrijo el padding si es necesario, linea por linea
        }
    }


    fclose(pf);
    return EXITO;
}

int generarImagen(HEADER *datos, PIXELBGR **mat, char *nomArch)
{

    int i, padding;
    char paddingBuff[3]= {0,0,0};
    FILE *pf = fopen(nomArch, "wb");
    if(pf== NULL)
        return 1;

    //padding = (4 - ((datos->ancho * sizeof(PIXELBGR)) % 4)) % 4;
    padding = CALCPADDING(datos->ancho);

    // el formato de la imagen original esta en V5 (tam header = 124) y el compilador soporta solo V1 (tam header 40) así que se modifica

    datos->tamHead = 40;

    //Como se añadio padding hay que contemplarlo en los nuevos tamaños

    datos->tamImagen = datos->alto * ((datos->ancho * sizeof(PIXELBGR)) + padding);
    datos->tamArchivo = datos->tamImagen + sizeof(HEADER);
    datos->datosImagen = sizeof(HEADER); //Aseguro el offset de los datos de la imagen


    fwrite(datos, sizeof(HEADER), 1, pf);

    for(i=datos->alto - 1; i>=0; i--)//La primera ''fila'' de pixeles es la ultima de la imagen, pero la primera ''Columna'' es correcta
    {
        fwrite(mat[i],datos->ancho * sizeof(PIXELBGR), 1, pf); // Resferenciar mat y luego aplicarle el offset

        if(padding != 0)
        {
            fwrite(paddingBuff,padding, 1, pf);
        }
    }


    fclose(pf);

    return EXITO;
}
void generarNomArch(char* nomNuevoArch, const char* nomGrupo, const char* nomFiltro, const char* nomArch)
{

    strcpy(nomNuevoArch,nomGrupo);
    strcat(nomNuevoArch,nomFiltro);
    strcat(nomNuevoArch,nomArch);

}

