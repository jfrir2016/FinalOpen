#include "Cliente.h"

int menuPrincipal(IplImage* imagenFondo,char* ventana, int id){
  
  int rectanguloDesdeDonde_X = ANCHO/2-100;
  int rectanguloDesdeDonde_Y = 200;
  int rectanguloHastaDonde_X = rectanguloDesdeDonde_X + 300;
  int rectanguloHastaDonde_Y = rectanguloDesdeDonde_Y + 50;
  
  char a;
  int i;
  
  char buffer[5][25];
  strcpy(buffer[0],"1) Ver publicaciones");
  strcpy(buffer[1],"2) Crear publicacion");
  strcpy(buffer[2],"3) Borrar publicacion");
  strcpy(buffer[3],"4) Darse de baja");
  strcpy(buffer[4],"5) Salir");
  
  CvFont textos;
  
  //Incializamos las fuentes
  cvInitFont(&textos,CV_FONT_HERSHEY_SIMPLEX, 0.7, 0.8, 0, 2,8);
  
  cvZero(imagenFondo);
  
  if(id==1){
    cvPutText (imagenFondo,"Modo administrador", cvPoint(20,ALTO-20), &textos, cvScalar(0,255,0,0));
  }
  
  cvMostrarTitulo(imagenFondo);
  
  cvPutText (imagenFondo,"Menu principal",cvPoint(ANCHO/2-25, 135),&textos,cvScalar(255,255,255,0));
  
  for (i=0;i<5;i++){
    cvRectangle (imagenFondo,
			    cvPoint (rectanguloDesdeDonde_X, rectanguloDesdeDonde_Y+(i*75)),
			    cvPoint (rectanguloHastaDonde_X, rectanguloHastaDonde_Y+(i*75)),
			    cvScalar (255,255,255,0),1,8,0);
    
    cvPutText (imagenFondo,buffer[i], 
			   cvPoint(rectanguloDesdeDonde_X +8,rectanguloDesdeDonde_Y+(i*75)+30),
			   &textos,
			   cvScalar(255,255,255,0));
  }
  cvShowImage(ventana, imagenFondo);
  a=cvWaitKey(0)-'0';
  i=(int)a;
  printf("%d",i);
  return i;
}