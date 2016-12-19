#include "Cliente.h"

void menuInicio (IplImage* imagenFondo)
{
  int rectanguloDesdeDonde_X = ANCHO*0.2;
  int rectanguloDesdeDonde_Y = ALTO*0.5;
  int rectanguloHastaDonde_X = rectanguloDesdeDonde_X + REC_TAM_X;
  int rectanguloHastaDonde_Y = rectanguloDesdeDonde_Y + REC_TAM_Y;
  int BrectanguloDesdeDonde_X = rectanguloDesdeDonde_X + 400;
  int BrectanguloHastaDonde_X = rectanguloHastaDonde_X + 400;

  CvFont Font;

  //Incializamos las fuentes
  cvInitFont(&Font,CV_FONT_HERSHEY_SIMPLEX, 0.7, 0.8, 0, 2,8);

  cvPutText (imagenFondo,"Bienvenido al Foro",cvPoint(ANCHO/2-120, 200), &Font, cvScalar (255,255,255,0));

  cvMostrarTitulo(imagenFondo);
  
  cvRectangle (imagenFondo,
			  cvPoint (rectanguloDesdeDonde_X, rectanguloDesdeDonde_Y),
			  cvPoint (rectanguloHastaDonde_X, rectanguloHastaDonde_Y),
			  cvScalar (255,255,255,0),1,8,0);

  cvPutText (imagenFondo,"1)Ingresar",cvPoint(rectanguloDesdeDonde_X + 10, rectanguloDesdeDonde_Y + 30), &Font, cvScalar (255,255,255,0));

  cvRectangle (imagenFondo,
			  cvPoint (BrectanguloDesdeDonde_X, rectanguloDesdeDonde_Y),
			  cvPoint (BrectanguloHastaDonde_X, rectanguloHastaDonde_Y),
			  cvScalar (255,255,255,0),1,8,0);

  cvPutText (imagenFondo,"2)Registrarse",cvPoint(BrectanguloDesdeDonde_X + 10, rectanguloDesdeDonde_Y + 30), &Font, cvScalar (255,255,255,0));
  
  cvRectangle (imagenFondo,
			  cvPoint (rectanguloHastaDonde_X, rectanguloHastaDonde_Y+50),
			  cvPoint (BrectanguloDesdeDonde_X, rectanguloHastaDonde_Y+ REC_TAM_Y+50),
			  cvScalar (255,255,255,0),1,8,0);
  cvPutText (imagenFondo,"0)Salir",cvPoint(rectanguloHastaDonde_X + 60, rectanguloHastaDonde_Y +80), &Font, cvScalar (0,0,255,0));
}