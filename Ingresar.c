#include "Cliente.h"

int Ingresar (usu *dir,IplImage* imagenFondo, char* nombreVentana,int i)
{
  cvZero(imagenFondo);
  
  cvMostrarTitulo(imagenFondo);
  crearCampodeTexto(imagenFondo);
  
  if(i==-1) errorInicio(imagenFondo);
  
  //Mostramos la imagen
  cvShowImage (nombreVentana,imagenFondo);
  
  leerCampodeTexto(nombreVentana, imagenFondo, dir);
  
  dir->id=1;

  return 0;
}