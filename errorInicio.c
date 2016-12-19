#include "Cliente.h"

void errorInicio(IplImage* imagenFondo)
{
  CvFont Font;
  cvInitFont(&Font,CV_FONT_HERSHEY_SIMPLEX, 0.7, 0.8, 0, 2,8);
  
  cvPutText(imagenFondo,"Error, intentelo nuevamente",cvPoint(400,370), &Font, cvScalar (0,0,255,0));
  
  return;
}