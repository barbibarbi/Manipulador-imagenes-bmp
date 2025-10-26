#ifndef FUNCIONES_ARCHIVO_H_INCLUDED
#define FUNCIONES_ARCHIVO_H_INCLUDED

int archivo(char *nomArch, HEADER *datos, PIXELBGR ***mat, int codValidar);
int generarImagen(HEADER *datos, PIXELBGR **mat, char *nomArch);
void generarNomArch(char* nomNuevoArch, const char* nomGrupo, const char* nomFiltro, const char* nomArch);


#endif // FUNCIONES_ARCHIVO_H_INCLUDED
