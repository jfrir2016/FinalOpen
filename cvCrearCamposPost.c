#include "Cliente.h"

void cvCrearCamposPost(IplImage* imagenFondo)
{ 
  // Realizamos calculos para definir los puntos (x,y)
  int rectanguloDesdeDonde_X = ANCHO *0.2;
  int rectanguloDesdeDonde_Y = ALTO *0.4;
  int rectanguloHastaDonde_X = ANCHO*0.9+15;
  int rectanguloHastaDonde_Y = rectanguloDesdeDonde_Y + REC_TAM_Y;

  CvFont Font;
  
  cvMostrarTitulo(imagenFondo);
  
  cvInitFont(&Font,CV_FONT_HERSHEY_SIMPLEX, 0.7, 0.8, 0, 2,8);
  
  cvPutText (imagenFondo,"Crear publicacion",cvPoint(ANCHO/2-50, 100), &Font, cvScalar (255,255,255,0));	

  // Creamos un rectangulo y se lo asignamos a la imagen de fondo
  cvRectangle (imagenFondo,
			  cvPoint (rectanguloDesdeDonde_X, rectanguloDesdeDonde_Y),
			  cvPoint (rectanguloHastaDonde_X, rectanguloHastaDonde_Y),
			  cvScalar (255,255,255,0),1,8,0);
  // Ponemos un texto de referencia
  cvPutText (imagenFondo,"Titulo:",cvPoint(rectanguloDesdeDonde_X, rectanguloDesdeDonde_Y-30), &Font, cvScalar (255,255,255,0));
	
  cvRectangle (imagenFondo,
			   cvPoint (rectanguloDesdeDonde_X, rectanguloDesdeDonde_Y+2*REC_TAM_Y+30),
			   cvPoint (rectanguloHastaDonde_X, ALTO*0.9),
			   cvScalar (255,255,255,0),1,8,0);
  // Ponemos un texto de referencia
  cvPutText (imagenFondo,"Publicacion:",cvPoint(rectanguloDesdeDonde_X, rectanguloDesdeDonde_Y+2*REC_TAM_Y), &Font, cvScalar (255,255,255,0));
  return;
}