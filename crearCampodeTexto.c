#include "Cliente.h"

void crearCampodeTexto(IplImage* imagenFondo)
{
  // Realizamos calculos para definir los puntos (x,y)
  int rectanguloDesdeDonde_X = ANCHO *0.6;
  int rectanguloDesdeDonde_Y = ALTO *0.25;
  int rectanguloHastaDonde_X = rectanguloDesdeDonde_X + REC_TAM_X+50;
  int rectanguloHastaDonde_Y = rectanguloDesdeDonde_Y + REC_TAM_Y;

  CvFont Font;
  
  cvMostrarTitulo(imagenFondo);
  
  cvInitFont(&Font,CV_FONT_HERSHEY_SIMPLEX, 0.7, 0.8, 0, 2,8);
  
  cvPutText (imagenFondo,"Ingresar",cvPoint(ANCHO/2-50, 100), &Font, cvScalar (255,255,255,0));	

  // Creamos un rectangulo y se lo asignamos a la imagen de fondo
  cvRectangle (imagenFondo,
			  cvPoint (rectanguloDesdeDonde_X, rectanguloDesdeDonde_Y),
			  cvPoint (rectanguloHastaDonde_X, rectanguloHastaDonde_Y),
			  cvScalar (255,255,255,0),1,8,0);
  // Ponemos un texto de referencia
  cvPutText (imagenFondo,"Nombre de usuario:",cvPoint(rectanguloDesdeDonde_X - 300, rectanguloDesdeDonde_Y+20), &Font, cvScalar (255,255,255,0));
	
  cvRectangle (imagenFondo,
			   cvPoint (rectanguloDesdeDonde_X, rectanguloDesdeDonde_Y+2*REC_TAM_Y),
			   cvPoint (rectanguloHastaDonde_X, rectanguloHastaDonde_Y+2*REC_TAM_Y),
			   cvScalar (255,255,255,0),1,8,0);
  // Ponemos un texto de referencia
  cvPutText (imagenFondo,"Password:",cvPoint(rectanguloDesdeDonde_X - 300, rectanguloDesdeDonde_Y+2*REC_TAM_Y+30), &Font, cvScalar (255,255,255,0));
  return;
}