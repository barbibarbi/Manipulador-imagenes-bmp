#include "funciones_grupo.h"
int procesar_imagen(int argc, char *argv[])
{

    PIXELBGR **matImagen1= NULL; //esta matriz se debe crear para una imagen con las dimenciones del encabezado
    PIXELBGR **matImagen2= NULL; //esta matriz se debe crear para una imagen con las dimensiones del encabezado
    HEADER datos1; //encabezado
    HEADER datos2; //encabezado
    INGRESO coms[MAXCANTIMG]; //Porque pueden ser hasta dos imagenes;
    int banderas[MAXCANTBAN]= {0}; //--help, --verbose, --verificar --horizontal --vertical

    int error = 0, cantImg = 0;

    error = verificaArgumentos(argc, argv, coms, &cantImg, banderas);

    verbose("[INFO] Iniciando bmpmanipuleitor...\n", banderas[VERBOSE]);

    if(banderas[HELP])
        help();
    else
    {
        if(error==EXITO)
        {
            if(banderas[VERBOSE])
            {
                verbose("[INFO] Argumentos detectados: ", banderas[VERBOSE]);
                mostrarArgumentos(argc, argv);
            }

            error = archivo(coms[IMAGEN1].nomArch, &datos1, &matImagen1, banderas[VALIDAR]);

            if(cantImg == MAXCANTIMG)
                error = archivo(coms[IMAGEN2].nomArch, &datos2, &matImagen2, banderas[VALIDAR]);

            if(error == EXITO)
            {
                aplicarFiltros(&datos1,&datos2, matImagen1,matImagen2,coms,banderas[VERBOSE], cantImg, banderas[HORIZONTAL], banderas[VERTICAL]);

                eliminarMatriz(matImagen1,datos1.alto);

                if(cantImg==MAXCANTIMG)//Si habia dos imagenes, mata la 2da tambien
                    eliminarMatriz(matImagen2,datos2.alto);
            }
            else
            {
                switch(error)
                {
                case EMEMORIA :
                    puts("ERROR: error de memoria");
                    break;
                case EARCHIVO:
                    puts("ERROR: error de archivo, no se puede abrir el archivo");
                    break;
                default:
                    break;
                }
            }
        }
        else
        {
            puts("ERROR: error de argumentos");

        }
    }

    return EXITO;
}

void verbose(const char* msj, const int v)
{
    if(v)
        printf(msj);
}
void mostrarArgumentos(int argc, char *argv[])
{
    int i;

    for(i=1;i<argc;i++)
    {
        printf(" %s ", *(argv+i));

    }

    puts(" ");
}
int verificaArgumentos(int argc, char *argv[], INGRESO *coms, int *cantImg, int *ban)
{
    int i=1,j, cantGlobales=0, cantCom2Img = 0, k=IMAGEN1, valorIng;
    char *dirValor=NULL;
    COMANDOS globales[CANTCOMANDOS];
    MAPEOCOMANDOS mapComs[CANTCOMANDOS]=
    {
        {"--negativo", NEGATIVO},
        {"--escala-de-grises", ESCALAGRIS},
        {"--espejar-horizontal", ESPHORIZONTAL},
        {"--espejar-vertical", ESPVERTICAL},
        {"--aumentar-contraste", AUMCONTRASTE},
        {"--reducir-contraste", REDCONTRASTE},
        {"--tonalidad-azul", TONALIDADZUL},
        {"--tonalidad-verde", TONALIDADVERDE},
        {"--tonalidad-roja", TONALIDADROJO},
        {"--recortar", RECORTAR},
        {"--achicar", ACHICAR},
        {"--rotar-derecha", ROTDERECHA},
        {"--rotar-izquierda", ROTIZQUIERDA},
        {"--psicodelia", PSICODELIA},
        {"--info", INFO}
    };

    (*(coms + IMAGEN1)).cantCom=0;
    (*(coms + IMAGEN2)).cantCom=0;

    while((i<argc) && (*(cantImg) <= 2) && *(ban + HELP)==0)
    {
        if (strncmp(argv[i], "--", strlen("--")) == 0)
        {
            // Es un comando
            if((strcmp(argv[i], "--help")==0))
            {
                *(ban + HELP)=1;
            }
            else if((strcmp(argv[i], "--verbose")==0))
            {
                *(ban + VERBOSE)=1;
            }
            else if((strcmp(argv[i], "--validar")==0))
            {
                *(ban + VALIDAR)=1;
            }
            else if((strcmp(argv[i], "--concatenar-horizontal")==0))
            {
                *(ban + HORIZONTAL)=1;
                cantCom2Img++;
            }
            else if((strcmp(argv[i], "--concatenar-vertical")==0))
            {
                *(ban + VERTICAL)=1;
                cantCom2Img++;
            }
            else
            {
                j=0;
                for (j = 0; j < CANTCOMANDOS; j++)
                {
                    if(strncmp(argv[i], mapComs[j].nomCom,strlen(mapComs[j].nomCom))==0)
                    {
                        valorIng=0;
                        if(mapComs[j].codCom>=AUMCONTRASTE &&mapComs[j].codCom<=ACHICAR)
                        {
                            dirValor = strchr(argv[i], '=');
                            if(dirValor != NULL)
                             valorIng = atoi(dirValor + 1);

                        }


                        if (*cantImg == 0)
                        {
                            globales[cantGlobales].comOrden = mapComs[j].codCom;
                            globales[cantGlobales].valor = valorIng;
                            cantGlobales++;
                        }
                        else
                        {
                            (*(coms + k)).cantCom++;
                            (*(coms + k)).comando[(*(coms + k)).cantCom -1].comOrden=mapComs[j].codCom;
                            (*(coms + k)).comando[(*(coms + k)).cantCom -1].valor = valorIng;


                        }





                    }
                }
            }
        }
        else
        {
            // Asumo que es un archivo, sea imagen o no, la validación lo determina otras funciones
            (*cantImg)++;

            if(* cantImg == 2)
            {
                k=IMAGEN2;
            }

            if(cantGlobales!=0)
                {
                    for(j=0; j<cantGlobales; j++)
                    {
                        (*(coms + k)).comando[(*(coms + k)).cantCom ].comOrden=globales[j].comOrden;

                        if(globales[j].valor != 0)
                            (*(coms + k)).comando[(*(coms + k)).cantCom ].valor=globales[j].valor;

                        (*(coms + k)).cantCom++;
                    }
                }

            strcpy((*(coms +k)).nomArch, argv[i]);

        }


        i++;
    }
    if(((*cantImg==0)|| (*cantImg>2)||(*cantImg==1 && cantCom2Img>0)))
        return EARGUMENTO;


    return EXITO;
}


void info(const char* nomArch, const HEADER *datos)
{
    //int  padding = (4 - ((datos->ancho * sizeof(PIXELBGR)) % 4)) % 4;
    int  padding = padding = CALCPADDING(datos->ancho);
    int  tamImagen = datos->alto * ((datos->ancho * sizeof(PIXELBGR)) + padding);

    puts("FUNCION INFO");
    printf("\nArchivo: %s\n", nomArch);
    printf(" Tamaño del archivo: %lu bytes\n", (unsigned long)datos->tamArchivo);
    printf(" Dimensiones: %lux%lu pixeles\n", (unsigned long)datos->ancho, (unsigned long)datos->alto);
    printf(" Profundidad de color: %u bits\n", datos->tamCadaPunto);
    printf(" Compresión: %s\n", (datos->compresion == 0) ? "No comprimido" : "Comprimido (Tipo desconocido)");
    printf(" Offset de datos: %lu bytes\n", (unsigned long)datos->datosImagen);
    printf(" Tamaño de imagen: %ul bytes\n", tamImagen);
    printf(" Padding por fila: %ul bytes\n", padding);
}
int validar(const HEADER *datos, const char* nomArch, int codValiar)
{
    if(codValiar)
        printf("Validando %s...\n", nomArch);

    if(datos->tipoFichero == BM)//comparo el tipo de archivo
    {
        if(codValiar)
            puts("   Signature BMP valido");
    }
    else
    {
        puts("  ERROR: Signature BMP invalido");
        return FINVALIDO;
    }


    if(datos->tamCadaPunto == 24)//comparo la profundidad
    {
        if(codValiar)
            puts("   Profundidad de 24 bits confirmada");
    }
    else
    {
        puts("  ERROR: Profundidad de color incorrecta (8 bits, esperado 24 bits)");
        return EPROFUNDIDAD;
    }

    if(datos->compresion == 0)//comparo la compresion
    {
        if(codValiar)
            puts("   Compresion: No comprimido");
    }
    else
    {
        puts("  ERROR: La imagen esta comprimida");
        return ECOMPRESION;
    }

    return EXITO;
}
void help()
{
    puts("BMPMANIPULEITOR - Manipulador de imágenes BMP 24 bits");
    puts(" ");
    puts(" ");
    puts("Uso: bmpmanipuleitor.exe [OPCIONES]");
    puts(" ");
    puts(" ");
    puts("EJEMPLOS:");
    printf("    bmpmanipuleitor.exe imagen.bmp -- info --validar\n");
    printf("    bmpmanipuleitor.exe imagen.bmp --verbose--escala-de-grises--aumentar-contraste=25\n");
    printf("    bmpmanipuleitor.exe --filtros-o-comandos-globales imagen1.bmp --filtros-o-comandos-para-imagen1 imagen2.bmp --filtros-o-comandos-para-imagen2\n");
    printf("    bmpmanipuleitor.exe --verbose imagen1.bmp  --aumentar-contraste=100 imagen2.bmp --negativo --concatenar-vertical \n");
    puts(" ");
    puts(" ");
    puts("FILTROS:");
    puts("  --info");
    puts("  --validar");
    puts("  --verbose");
    puts("  --psicodelia (Intercambia los colores de manera aleatoria, aun asi se puede tener el resultado original)");
    puts("  --rotar-derecha");
    puts("  --rotar-izquierda");
    puts("  --concatenar-horizontal");
    puts("  --concatenar-vertical");
    puts("  --espejar-horizontal");
    puts("  --espejar-vertical");
    puts("  --negativo");
    puts("  --escala-de-grises");
    puts("  --aumentar-contraste=X");
    puts("  --reducir-contraste=X");
    puts("  --tonalidad-azul=X");
    puts("  --tonalidad-verde=X");
    puts("  --tonalidad-roja=X");
    puts("  --recortar=X");
    puts("  --achicar=X");
}
void aplicarFiltros(HEADER *datos1, HEADER *datos2, PIXELBGR **mat1, PIXELBGR **mat2, INGRESO *coms,int codVerbose, int cantImg, int conH, int conV)
{
    int i, j;
    char nomGrupo[]="RESULTADO_";
    char nomNewArch[NOMARCHMAX]="\0";


    for(i=0; i<cantImg; i++)
            {

                for(j=0; j<coms[i].cantCom; j++)
                {

                    switch(coms[i].comando[j].comOrden)
                    {
                    case NEGATIVO :
                        generarNomArch(nomNewArch,nomGrupo,"negativo-",(coms+i)->nomArch);
                        negativo((i==IMAGEN1)?mat1:mat2,(i==IMAGEN1)?datos1:datos2, codVerbose ,nomNewArch);

                        break;

                    case ESCALAGRIS :
                        generarNomArch(nomNewArch,nomGrupo,"escala-de-grises-",(coms+i)->nomArch);
                        escalaGrises((i==IMAGEN1)?mat1:mat2,(i==IMAGEN1)?datos1:datos2, codVerbose, nomNewArch);
                        break;


                    case ESPHORIZONTAL:
                        generarNomArch(nomNewArch,nomGrupo,"espejar-horizontal-",(coms+i)->nomArch);
                        voltearHorizontal((i==IMAGEN1)?datos1:datos2,(i==IMAGEN1)?mat1:mat2, codVerbose,nomNewArch );
                        break;


                    case ESPVERTICAL:
                        generarNomArch(nomNewArch,nomGrupo,"espejar-vertical-",(coms+i)->nomArch);
                        voltearVertical((i==IMAGEN1)?datos1:datos2,(i==IMAGEN1)?mat1:mat2, codVerbose,nomNewArch );
                        break;


                    case AUMCONTRASTE:
                        verbose("[INFO] Aplicando filtro aumentar contraste\n", codVerbose);
                        generarNomArch(nomNewArch,nomGrupo,"aumentar-contraste-",(coms+i)->nomArch);
                        contraste((i==IMAGEN1)?datos1:datos2,(i==IMAGEN1)?mat1:mat2,(coms+i)->comando[j].valor, AUMENTAR, codVerbose, nomNewArch );
                        break;


                    case REDCONTRASTE:
                        verbose("[INFO] Aplicando filtro reducir contraste\n", codVerbose);
                        generarNomArch(nomNewArch,nomGrupo,"reducir-contraste-",(coms+i)->nomArch);
                        contraste((i==IMAGEN1)?datos1:datos2,(i==IMAGEN1)?mat1:mat2,(coms+i)->comando[j].valor, REDUCIR, codVerbose,nomNewArch);
                        break;


                    case TONALIDADZUL:
                        verbose("[INFO] Aplicando filtro tonalidad azul\n", codVerbose);
                        generarNomArch(nomNewArch,nomGrupo,"tonalidad-azul-",(coms+i)->nomArch);
                        tonalidad((i==IMAGEN1)?datos1:datos2,(i==IMAGEN1)?mat1:mat2,(coms+i)->comando[j].valor, AZUL, codVerbose, nomNewArch);
                        break;

                    case TONALIDADVERDE:
                        verbose("[INFO] Aplicando filtro tonalidad verde\n", codVerbose);
                        generarNomArch(nomNewArch,nomGrupo,"tonalidad-verde-",(coms+i)->nomArch);
                        tonalidad((i==IMAGEN1)?datos1:datos2,(i==IMAGEN1)?mat1:mat2,(coms+i)->comando[j].valor, VERDE, codVerbose,nomNewArch);
                        break;

                    case TONALIDADROJO:
                        verbose("[INFO] Aplicando filtro tonalidad rojo\n", codVerbose);
                        generarNomArch(nomNewArch,nomGrupo,"tonalidad-rojo-",(coms+i)->nomArch);
                        tonalidad((i==IMAGEN1)?datos1:datos2,(i==IMAGEN1)?mat1:mat2,(coms+i)->comando[j].valor, ROJO, codVerbose, nomNewArch);
                        break;

                    case RECORTAR:
                        generarNomArch(nomNewArch,nomGrupo,"recortar-",(coms+i)->nomArch);
                        recortar((i==IMAGEN1)?datos1:datos2,(i==IMAGEN1)?mat1:mat2,(coms+i)->comando[j].valor, codVerbose, nomNewArch );
                        break;

                    case ACHICAR:
                        generarNomArch(nomNewArch,nomGrupo,"achicar-",(coms+i)->nomArch);
                        achicar((i==IMAGEN1)?datos1:datos2,(i==IMAGEN1)?mat1:mat2,(coms+i)->comando[j].valor, codVerbose, nomNewArch );
                        break;

                    case ROTDERECHA:
                        generarNomArch(nomNewArch,nomGrupo,"rotar-derecha-",(coms+i)->nomArch);
                        rotar90derecha((i==IMAGEN1)?datos1:datos2,(i==IMAGEN1)?mat1:mat2, codVerbose,nomNewArch);
                        break;

                    case ROTIZQUIERDA:
                        generarNomArch(nomNewArch,nomGrupo,"rotar-izquierda-",(coms+i)->nomArch);
                        rotar90izquierda((i==IMAGEN1)?datos1:datos2,(i==IMAGEN1)?mat1:mat2, codVerbose,nomNewArch);
                        break;

                    case PSICODELIA:
                        generarNomArch(nomNewArch,nomGrupo,"psicodelia-",(coms+i)->nomArch);
                        psicodelia((i==IMAGEN1)?datos1:datos2,(i==IMAGEN1)?mat1:mat2, codVerbose,nomNewArch);
                        break;


                    default:
                        info(coms[i].nomArch,(i==IMAGEN1)?datos1:datos2);
                    }
                }

            }

                    if(cantImg == MAXCANTIMG)
                    {


                         if(conH)
                            {
                                generarNomArch(nomNewArch,nomGrupo,"concatenar-izquierda-",(coms+IMAGEN1)->nomArch);
                                concatencacionHorizontal(datos1,mat1,datos2,mat2, codVerbose, nomNewArch);
                            }
                        if(conV)
                            {
                                generarNomArch(nomNewArch,nomGrupo,"concatenar-vertical-",(coms+IMAGEN1)->nomArch);
                                concatencacionVertical(datos1,mat1,datos2,mat2, codVerbose, nomNewArch);

                            }
                    }

}
