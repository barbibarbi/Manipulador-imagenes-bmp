#ifndef FUNCIONES_CONCATENACION_H_INCLUDED
#define FUNCIONES_CONCATENACION_H_INCLUDED

int concatencacionVertical(HEADER *datos1, PIXELBGR **mat1, const HEADER *datos2, PIXELBGR **mat2, int codVerbose,  char* nomNewArch);
int concatencacionHorizontal(HEADER *datos1, PIXELBGR **mat1, const HEADER *datos2,  PIXELBGR **mat2, int codVerbose,  char* nomNewArch);


#endif // FUNCIONES_CONCATENACION_H_INCLUDED
