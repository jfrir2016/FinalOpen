/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "Cliente.h"
/***********************************************************************************************************************************
*** FUNCIONES DEL MODULO
**********************************************************************************************************************************/

/**
 * \file 	cvMenues.c
 * \brief 	Este modulo contiene las funciones que manejan los menues manejados con OpenCv
 * \author 	Tomás Ordóñez, Juan Francisco Reiszer, Santiago Ozan 
 * \date 	20/12/2016
 */

/**
 * \fn 		void cvMostrarTitulo (IplImage* imagenFondo)
 * \brief 	Esta funcion se encarga de generar el nombre del blog
 * \author 	Tomás Ordóñez, Juan Francisco Reiszer, Santiago Ozan
 * \date 	20/12/2016
 * \param [in] 	imagenFondo: Puntero a la imagen
 * \return 	void
 */
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

/**
 * \fn 		int interfaz1 (IplImage* imagenFondo,char* nombreVentana)
 * \brief 	Esta funcion se encarga de generar el menu inicial
 * \author 	Tomás Ordóñez, Juan Francisco Reiszer, Santiago Ozan
 * \date 	20/12/2016
 * \param [in] 	imagenFondo: Puntero a la imagen
 * \param [in] 	nombreVentana: String con el nombre de la ventana
 * \return 	Entero que contiene la seleccion
 */
int interfaz1 (IplImage* imagenFondo,char* nombreVentana)
{
  char a;
  int b;
  
  cvZero(imagenFondo);
  //Creamos el menu
  menuInicio(imagenFondo);
  cvShowImage (nombreVentana,imagenFondo);
  
  a = cvWaitKey(0);
  a=a-'0';
  b=a;
  return b;
}

/**
 * \fn 		void menuInicio (IplImage* imagenFondo)
 * \brief 	Esta funcion se encarga de generar la interfaz del menu inicial
 * \author 	Tomás Ordóñez, Juan Francisco Reiszer, Santiago Ozan
 * \date 	20/12/2016
 * \param [in] 	imagenFondo: Puntero a la imagen
 * \return 	void
 */

void menuInicio (IplImage* imagenFondo)
{
  //Determinamos coordenadas
  int rectanguloDesdeDonde_X = ANCHO*0.2;
  int rectanguloDesdeDonde_Y = ALTO*0.5;
  int rectanguloHastaDonde_X = rectanguloDesdeDonde_X + REC_TAM_X;
  int rectanguloHastaDonde_Y = rectanguloDesdeDonde_Y + REC_TAM_Y;
  int BrectanguloDesdeDonde_X = rectanguloDesdeDonde_X + 400;
  int BrectanguloHastaDonde_X = rectanguloHastaDonde_X + 400;

  CvFont Font;
  cvInitFont(&Font,CV_FONT_HERSHEY_SIMPLEX, 0.7, 0.8, 0, 2,8);

  cvPutText (imagenFondo,"Bienvenido al Foro",cvPoint(ANCHO/2-120, 200), &Font, cvScalar (255,255,255,0));
  cvMostrarTitulo(imagenFondo);
  
  cvPutText (imagenFondo,"1)Ingresar",cvPoint(rectanguloDesdeDonde_X + 10, rectanguloDesdeDonde_Y + 30), &Font, cvScalar (255,255,255,0));
  cvRectangle (imagenFondo,
			  cvPoint (rectanguloDesdeDonde_X, rectanguloDesdeDonde_Y),
			  cvPoint (rectanguloHastaDonde_X, rectanguloHastaDonde_Y),
			  cvScalar (255,255,255,0),1,8,0);

  
  cvPutText (imagenFondo,"2)Registrarse",cvPoint(BrectanguloDesdeDonde_X + 10, rectanguloDesdeDonde_Y + 30), &Font, cvScalar (255,255,255,0));
  cvRectangle (imagenFondo,
			  cvPoint (BrectanguloDesdeDonde_X, rectanguloDesdeDonde_Y),
			  cvPoint (BrectanguloHastaDonde_X, rectanguloHastaDonde_Y),
			  cvScalar (255,255,255,0),1,8,0);

  
  cvPutText (imagenFondo,"0)Salir",cvPoint(rectanguloHastaDonde_X + 60, rectanguloHastaDonde_Y +80), &Font, cvScalar (0,0,255,0));
  cvRectangle (imagenFondo,
			  cvPoint (rectanguloHastaDonde_X, rectanguloHastaDonde_Y+50),
			  cvPoint (BrectanguloDesdeDonde_X, rectanguloHastaDonde_Y+ REC_TAM_Y+50),
			  cvScalar (255,255,255,0),1,8,0);
  
}

/**
 * \fn 		int menuPrincipal(IplImage* imagenFondo,char* ventana, int id)
 * \brief 	Esta funcion se encarga de generar el menu principal
 * \author 	Tomás Ordóñez, Juan Francisco Reiszer, Santiago Ozan
 * \date 	20/12/2016
 * \param [in] 	imagenFondo: Puntero a la imagen
 * \param [in] 	ventana: String con el nombre de la ventana
 * \param [in] 	id: Entero que contiene el id del usuario
 * \return 	entero cuyo valor es la seleccion
 */

int menuPrincipal(IplImage* imagenFondo,char* ventana, int id)
{
  //Determinamos coordenadas
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