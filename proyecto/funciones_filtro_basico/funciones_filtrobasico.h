#ifndef FUNCIONES_FILTROBASICO_H_INCLUDED
#define FUNCIONES_FILTROBASICO_H_INCLUDED

int voltearVertical(HEADER *datos, PIXELBGR **mat, int codVerbose,  char* nomNewArch);
int voltearHorizontal(HEADER *datos, PIXELBGR **mat, int codVerbose,  char* nomNewArch);
void intercambiar (void* a, void *b, size_t tamDato);
float ajuste(float n);
int negativo(PIXELBGR **mat,  HEADER *datos,int codVerbose, char* nomNewArch);
int escalaGrises(PIXELBGR **mat, HEADER *datos,int codVerbose,  char* nomNewArch);
int psicodelia(HEADER *datos, PIXELBGR **mat, int codVerbose,  char* nomNewArch);


#endif // FUNCIONES_FILTROBASICO_H_INCLUDED
