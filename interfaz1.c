#include "Cliente.h"

int interfaz1 (IplImage* imagenFondo,char* nombreVentana)
{
  char a;
  int b;
  
  //Limpiamos la imagen
  cvZero(imagenFondo);
  
  //Creamos el menu
  menuInicio(imagenFondo);
  
  //Mostramos la imagen
  cvShowImage (nombreVentana,imagenFondo);
  
  a = cvWaitKey(0);
  a=a-'0';
  b=a;
  return b;
}