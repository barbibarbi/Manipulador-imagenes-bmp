#ifndef FUNCIONES_FILTROPARAMETRO_H_INCLUDED
#define FUNCIONES_FILTROPARAMETRO_H_INCLUDED

int recortar (HEADER *datos, PIXELBGR **mat, int x, int codVerbose,  char* nomNewArch);
int achicar (HEADER *datos, PIXELBGR **mat, int x, int codVerbose,  char* nomNewArch);
int contraste(HEADER *datos, PIXELBGR **mat, int x, int orden, int codVerbose,  char* nomNewArch);
int tonalidad(HEADER *datos, PIXELBGR **mat, int x,  int color, int codVerbose,  char* nomNewArch);


#endif // FUNCIONES_FILTROPARAMETRO_H_INCLUDED
