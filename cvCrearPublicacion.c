#include "Cliente.h"

void cvCrearPublicacion (IplImage* imagenFondo, char* ventana, post *p)
{
  cvZero(imagenFondo);
  cvMostrarTitulo(imagenFondo);
  cvCrearCamposPost(imagenFondo);
  cvShowImage(ventana,imagenFondo);
  cvLeerCamposPost(imagenFondo,ventana, p);
  return;
}