#include "Cliente.h"

void cvSalir (IplImage* imagenFondo,char* ventana)
{
  CvFont Font;
  cvInitFont(&Font,CV_FONT_HERSHEY_SIMPLEX, 0.7, 0.8, 0, 2,8);
  
  cvZero(imagenFondo);
  
  cvMostrarTitulo(imagenFondo);
 
  cvPutText(imagenFondo,"Gracias por usar el blog",cvPoint(ANCHO/2-120,ALTO/2-50),&Font,cvScalar(255,255,255,0));
  cvPutText(imagenFondo,"Nos vemos pronto",cvPoint(ANCHO/2-80,ALTO/2+70),&Font,cvScalar(255,255,255,0));
  cvShowImage(ventana, imagenFondo);
  cvWaitKey(0);
    return;
}