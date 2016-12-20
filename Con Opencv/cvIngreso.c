/**********************************************************************************************************************************/

/**
 * \file 	cvIngreso.c
 * \brief 	Este modulo contiene las funciones para ingresar que manejan OpenCv
 * \author 	Tomás Ordóñez, Juan Francisco Reiszer, Santiago Ozan 
 * \date 	20/12/2016
 */

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "Cliente.h"
/***********************************************************************************************************************************
*** FUNCIONES DEL MODULO
**********************************************************************************************************************************/


/**
 * \fn 		void crearCampodeTexto(IplImage* imagenFondo)
 * \brief 	Esta funcion se encarga de generar la interfaz de ingresar
 * \author 	Tomás Ordóñez, Juan Francisco Reiszer, Santiago Ozan
 * \date 	20/12/2016
 * \param [in] 	imagenFondo: Puntero a la imagen
 * \return 	void
 */
void crearCampodeTexto(IplImage* imagenFondo)
{
  //Definimos las coordenadas (x,y)
  int rectanguloDesdeDonde_X = ANCHO *0.6;
  int rectanguloDesdeDonde_Y = ALTO *0.25;
  int rectanguloHastaDonde_X = rectanguloDesdeDonde_X + REC_TAM_X+50;
  int rectanguloHastaDonde_Y = rectanguloDesdeDonde_Y + REC_TAM_Y;

  CvFont Font;
  cvInitFont(&Font,CV_FONT_HERSHEY_SIMPLEX, 0.7, 0.8, 0, 2,8);
  
  cvMostrarTitulo(imagenFondo);
  
  cvPutText (imagenFondo,"Ingresar",cvPoint(ANCHO/2-50, 100), &Font, cvScalar (255,255,255,0));
  
  cvPutText (imagenFondo,"Nombre de usuario:",cvPoint(rectanguloDesdeDonde_X - 300, rectanguloDesdeDonde_Y+20), &Font, cvScalar (255,255,255,0));
  cvRectangle (imagenFondo,
			  cvPoint (rectanguloDesdeDonde_X, rectanguloDesdeDonde_Y),
			  cvPoint (rectanguloHastaDonde_X, rectanguloHastaDonde_Y),
			  cvScalar (255,255,255,0),1,8,0);
  
  cvPutText (imagenFondo,"Password:",cvPoint(rectanguloDesdeDonde_X - 300, rectanguloDesdeDonde_Y+2*REC_TAM_Y+30), &Font, cvScalar (255,255,255,0));
  cvRectangle (imagenFondo,
			   cvPoint (rectanguloDesdeDonde_X, rectanguloDesdeDonde_Y+2*REC_TAM_Y),
			   cvPoint (rectanguloHastaDonde_X, rectanguloHastaDonde_Y+2*REC_TAM_Y),
			   cvScalar (255,255,255,0),1,8,0);
  return;
}

/**
 * \fn 		void leerCampodeTexto(char* nombreVentana, IplImage* imagenFondo,usu *dir)
 * \brief 	Esta funcion se encarga de rellenar los campos usuario y contraseña del usuario
 * \author 	Tomás Ordóñez, Juan Francisco Reiszer, Santiago Ozan
 * \date 	20/12/2016
 * \param [in]	nombreVentana: Direccion de comienzo del nombre de la ventana
 * \param [in] 	imagenFondo: Puntero a la imagen
 * \param [in]	dir: Puntero a usu, estructura que se va a rellenar
 * \return 	void
 */
void leerCampodeTexto(char* nombreVentana, IplImage* imagenFondo,usu *dir)
{
  int i=0,puntero_lector=0;
  
  for (i=0; i<20; i++) { dir->Usuario[i]='\0'; }

  
  // Definimos coordenadas (x,y)
  int textoDesdeDonde_X = ANCHO *0.6+10;
  int textoDesdeDonde_Y = ALTO *0.25+30;
  
  //Circulo que indica que estamos en usuario
  cvCircle( imagenFondo, cvPoint(ANCHO *0.6+ REC_TAM_X+70 , textoDesdeDonde_Y), 10, cvScalar (208,194,0,0), -1, 8, 0 );
  cvShowImage(nombreVentana,imagenFondo);
  
  char aux = cvWaitKey(0);
  
  CvFont Font;
  cvInitFont(&Font,CV_FONT_HERSHEY_SIMPLEX, 0.7, 0.8, 0, 2,8);
  
  //este while se encarga de llenar el usuario
  while (aux != '\n')
  {
    //Aca vamos a entrar si escribio una letra
    if (aux > 31 && aux < 127)
    {
      if (strlen(dir->Usuario)<19)
      {
	dir->Usuario[puntero_lector]=aux;
	cvPutText(imagenFondo,dir->Usuario,cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y), &Font, cvScalar (255,255,255,0));
	cvShowImage(nombreVentana,imagenFondo);
	puntero_lector++;
      }
   }

   //Aca vamos a entrar si quiere borrar algo
   if ((aux==8 || aux==127) && puntero_lector)
   {
     cvPutText(imagenFondo,dir->Usuario,cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y), &Font, cvScalar (0,0,0,0));
     
     dir->Usuario[puntero_lector]=(char)0;
     puntero_lector--;
     
     dir->Usuario[puntero_lector]=(char)0;
     cvPutText(imagenFondo,dir->Usuario,cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y), &Font, cvScalar (255,255,255,0));
     cvShowImage(nombreVentana,imagenFondo);
   }
   aux = cvWaitKey(0);
  }
   
   for (i=0; i<8; i++) { dir->Contra[i]='\0'; }
   
   //Circulo que indica que estamos en password
   cvCircle( imagenFondo, cvPoint(ANCHO *0.6+ REC_TAM_X+70 , textoDesdeDonde_Y), 10, cvScalar (0,0,0,0), -1, 8, 0 );
   cvCircle(imagenFondo, cvPoint (ANCHO *0.6+ REC_TAM_X+70,textoDesdeDonde_Y+2*REC_TAM_Y), 10, cvScalar (208,194,0,0), -1, 8, 0 );
   cvShowImage(nombreVentana,imagenFondo);

   aux=cvWaitKey(0);
   puntero_lector=0;
   
   //Este while se encarga de llenar la password
   while (aux != '\n')
   {
     //Aca vamos a entrar si escribio una letra
     if (aux > 31 && aux < 127)
     {
       if (strlen(dir->Contra)<7)
       {
	 dir->Contra[puntero_lector]=aux;
	 cvPutText(imagenFondo,dir->Contra,cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y+2*REC_TAM_Y), &Font, cvScalar (255,255,255,0));
	 cvShowImage(nombreVentana,imagenFondo);
	 puntero_lector++;
	 
       }
     }

     //Aca vamos a entrar si quiere borrar algo
     if ((aux==8 || aux==127) && puntero_lector)
     {
       cvPutText(imagenFondo,dir->Contra,cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y+2*REC_TAM_Y), &Font, cvScalar (0,0,0,0));
       dir->Contra[puntero_lector]=(char)0;
       puntero_lector--;
       dir->Contra[puntero_lector]=(char)0;
       cvPutText(imagenFondo,dir->Contra,cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y+2*REC_TAM_Y), &Font, cvScalar (255,255,255,0));
       cvShowImage(nombreVentana,imagenFondo);
     }
     aux = cvWaitKey(0);
   }
   return;
}