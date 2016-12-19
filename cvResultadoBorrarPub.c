#include "Cliente.h"

void cvResultadoBorrarPub(IplImage* imagenFondo, int cant)
{
  CvFont Font;
  cvInitFont(&Font, CV_FONT_HERSHEY_SIMPLEX, 0.7, 0.8, 0, 2, 8);
  
  if(cant==0)
  {
    cvPutText(imagenFondo,"No es una publicacion propia",cvPoint(ANCHO/2-300,ALTO/2),&Font,cvScalar(0,0,255,0));
    cvPutText(imagenFondo,"ENTER para continuar",cvPoint(ANCHO/2-300,ALTO/2+30),&Font,cvScalar(0,0,255,0));
  }
  else
  {
    cvPutText(imagenFondo,"Publicacion borrada",cvPoint(ANCHO/2-300,ALTO/2),&Font,cvScalar(0,0,255,0));
    cvPutText(imagenFondo,"ENTER para continuar",cvPoint(ANCHO/2-300,ALTO/2+30),&Font,cvScalar(0,0,255,0));
  }
  return;
}