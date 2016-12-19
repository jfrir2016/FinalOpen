#include "Cliente.h"

void cvMostrarTitulo (IplImage* imagenFondo)
{
  CvFont infonianos;
  CvFont encabezado;
  
  cvInitFont(&infonianos,CV_FONT_HERSHEY_COMPLEX,1.3,1.3, 0, 3,9);
  cvInitFont(&encabezado,CV_FONT_HERSHEY_SIMPLEX, 0.8, 0.7, 0, 2,8);
  
  cvPutText (imagenFondo,"SEGMENTATION BLOG",cvPoint(20,50),&infonianos,cvScalar(208,201,0,0));
  cvPutText (imagenFondo,"Yo si C",cvPoint(20,90),&encabezado,cvScalar(208,201,0,0));
  return;
}