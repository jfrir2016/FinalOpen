/**********************************************************************************************************************************/

/**
 * \file 	cvPublicaciones.c
 * \brief 	Este modulo contiene las funciones que manejan las publicaciones por medio de OpenCv
 * \author 	Tomás Ordóñez, Juan Francisco Reiszer, Santiago Ozan 
 * \date 	20/12/2016
 */

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "Cliente.h"
/***********************************************************************************************************************************
*** FUNCIONES DEL MODULO
************************************************************************************************************************************/

/**
 * \fn 		void cvCrearPublicacion (IplImage* imagenFondo, char* ventana, post* p)
 * \brief 	Esta funcion se encarga de generar la interfaz de posteo y de generar el posteo mismo
 * \author 	Tomás Ordóñez, Juan Francisco Reiszer, Santiago Ozan
 * \date 	20/12/2016
 * \param [in] 	imagenFondo: Puntero a la imagen
 * \param [in] 	ventana: String con el nombre de la ventana
 * \param [in] 	p: Puntero que apunta a la publicacion
 * \return 	void
 */

void cvCrearPublicacion (IplImage* imagenFondo, char* ventana, post *p)
{
  cvZero(imagenFondo);
  //cvMostrarTitulo se encarga de mostrar el nombre del blog y su encabezado
  cvMostrarTitulo(imagenFondo);
  cvCrearCamposPost(imagenFondo);
  cvShowImage(ventana,imagenFondo);
  cvLeerCamposPost(imagenFondo,ventana, p);
  return;
}

/**
 * \fn 		void cvCrearCamposPost (IplImage* imagenFondo)
 * \brief 	Esta funcion se encarga de generar la interfaz de posteo
 * \author 	Tomás Ordóñez, Juan Francisco Reiszer, Santiago Ozan
 * \date 	20/12/2016
 * \param [in] 	imagenFondo: Puntero a la imagen
 * \return 	void
 */
void cvCrearCamposPost(IplImage* imagenFondo)
{ 
  // Inicializamos coordenadas (x,y)
  int rectanguloDesdeDonde_X = ANCHO *0.2;
  int rectanguloDesdeDonde_Y = ALTO *0.4;
  int rectanguloHastaDonde_X = ANCHO*0.9+15;
  int rectanguloHastaDonde_Y = rectanguloDesdeDonde_Y + REC_TAM_Y;

  CvFont Font;
  cvInitFont(&Font,CV_FONT_HERSHEY_SIMPLEX, 0.7, 0.8, 0, 2,8);
  
  cvMostrarTitulo(imagenFondo);
  
  cvPutText (imagenFondo,"Crear publicacion",cvPoint(ANCHO/2-50, 100), &Font, cvScalar (255,255,255,0));	

  
  cvPutText (imagenFondo,"Titulo:",cvPoint(rectanguloDesdeDonde_X, rectanguloDesdeDonde_Y-30), &Font, cvScalar (255,255,255,0));
  cvRectangle (imagenFondo,
			  cvPoint (rectanguloDesdeDonde_X, rectanguloDesdeDonde_Y),
			  cvPoint (rectanguloHastaDonde_X, rectanguloHastaDonde_Y),
			  cvScalar (255,255,255,0),1,8,0);
  
  cvPutText (imagenFondo,"Publicacion:",cvPoint(rectanguloDesdeDonde_X, rectanguloDesdeDonde_Y+2*REC_TAM_Y), &Font, cvScalar (255,255,255,0));
  cvRectangle (imagenFondo,
			   cvPoint (rectanguloDesdeDonde_X, rectanguloDesdeDonde_Y+2*REC_TAM_Y+30),
			   cvPoint (rectanguloHastaDonde_X, ALTO*0.9),
			   cvScalar (255,255,255,0),1,8,0);
  return;
}

/**
 * \fn 		void cvLeerCamposPost (IplImage* imagenFondo, char* nombreVentana, post* p)
 * \brief 	Esta funcion se encarga de llenar los campos del posteo mismo
 * \author 	Tomás Ordóñez, Juan Francisco Reiszer, Santiago Ozan
 * \date 	20/12/2016
 * \param [in] 	imagenFondo: Puntero a la imagen
 * \param [in] 	nombreVentana: String con el nombre de la ventana
 * \param [in] 	p: Puntero que apunta a la publicacion
 * \return 	void
 */
void cvLeerCamposPost(IplImage* imagenFondo,char* nombreVentana,post* p)
{
  int j, i, baseline, ultimo=0, puntero_lector=0;
  //buffer es un vector de strings en los cual se escribira el cuerpo de la publicacion
  char buffer[7][170];
  char aux;
  
  CvSize text_size;
  
  CvFont font;
  cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX, 0.5, 0.6, 0, 2,8);
  
  //Lleno cada string con '\0'
  for(i=0;i<7;i++)
  {
    for(j=0;j<170;j++)
      buffer[i][j]='\0';
  }
  
  for (i=0; i<100; i++) { p->titulo[i]='\0'; } 
  for (i=0; i<500; i++) { p->contenido[i]='\0'; }
  
  // Definimos desde donde y hasta donde va a ir el texto
  int textoDesdeDonde_X = ANCHO *0.2+5;
  int textoDesdeDonde_Y = ALTO *0.4+30;
  int textoHastaDonde_X = ANCHO *0.9;
  
  //Circulo que indica que estamos en titulo
  cvCircle( imagenFondo, cvPoint(ANCHO *0.7+ REC_TAM_X+70 , textoDesdeDonde_Y), 10, cvScalar (208,194,0,0), -1, 8, 0 );
  cvShowImage(nombreVentana,imagenFondo);
  
  aux = cvWaitKey(0);
  
  //Este while se encarga de llenar el campo titulo
  while (aux != '\n')
  {
    //Aca vamos a entrar si escribio una letra
    if (aux > 31 && aux < 127)
    {
      if (strlen(p->titulo)<99)
      {
	p->titulo[puntero_lector]=aux;
	cvPutText(imagenFondo,p->titulo,cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y), &font, cvScalar (255,255,255,0));
	cvShowImage(nombreVentana,imagenFondo);
	puntero_lector++;
      }
   }

   //Aca vamos a entrar si quiere borrar algo
   if ((aux==8 || aux==127) && puntero_lector)
   {
     cvPutText(imagenFondo,p->titulo,cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y), &font, cvScalar (0,0,0,0));
     p->titulo[puntero_lector]=(char)0;
     puntero_lector--;
     p->titulo[puntero_lector]=(char)0;
     cvPutText(imagenFondo,p->titulo,cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y), &font, cvScalar (255,255,255,0));
     cvShowImage(nombreVentana,imagenFondo);
   }
   aux = cvWaitKey(0);
  }
   
   //Circulo que indica que estamos en contenido
   cvCircle( imagenFondo, cvPoint(ANCHO *0.7+ REC_TAM_X+70 , textoDesdeDonde_Y), 10, cvScalar (0,0,0,0), -1, 8, 0 );
   cvCircle(imagenFondo, cvPoint (ANCHO *0.7+ REC_TAM_X+70,textoDesdeDonde_Y+2.5*REC_TAM_Y), 10, cvScalar (208,194,0,0), -1, 8, 0 );
   cvShowImage(nombreVentana,imagenFondo);
   
   aux=0;
   j=0;
   
   //Este for se encarga de llenar el campo contenido
   for(i=0;i<7 && aux!='\n' && i>=0;i++)
   {
     aux=cvWaitKey(0);
     puntero_lector=0;
     
     while (aux != '\n' && i>=0)
     {
       //Aca vamos a entrar si escribio una letra
       if (aux > 31 && aux < 127)
       {
	 cvGetTextSize(buffer[i], &font, &text_size, &baseline);
	 
	 if ((textoHastaDonde_X-textoDesdeDonde_X)>text_size.width)
	 {
	   buffer[i][puntero_lector]=aux;
	   cvPutText(imagenFondo,buffer[i],cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y+2.5*REC_TAM_Y+(REC_TAM_Y/2)*i), &font, cvScalar (255,255,255,0));
	   cvShowImage(nombreVentana,imagenFondo);
	   puntero_lector++;
	 }
	 
	 //Si el texto no entra en el renglon paso al siguiente
	 else
	 {
	   buffer[i][puntero_lector]=aux;
	   cvPutText(imagenFondo,buffer[i],cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y+2.5*REC_TAM_Y+(REC_TAM_Y/2)*i), &font, cvScalar (255,255,255,0));
	   cvShowImage(nombreVentana,imagenFondo);
	   
	   //Guardo la direccion del ultimo caracter de la string por si quiero borrar
	   ultimo=puntero_lector;
	   
	   i++;
	   puntero_lector=0;
	   
	   if(i>=7)
	   {
	     //Cargo el contenido y salgo
	     for(j=0;j<7;j++)
	       strcat(p->contenido,buffer[j]);
	     return;
	   }
	 }
       }
       
       //Aca vamos a entrar si quiere borrar algo
       if (aux==8 || aux==127)
       {
	 //Si quiero borrar y estoy en el primer elemento de la primer string no hago nada
	 if(i==0 && puntero_lector==0){}
	 
	 else
	 {
	   cvPutText(imagenFondo,buffer[i],cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y+2.5*REC_TAM_Y+(REC_TAM_Y/2)*i), &font, cvScalar (0,0,0,0));
	   buffer[i][puntero_lector]=(char)0;
	   
	   //Si estoy en el primer elemento de la string subo un renglon
	   if(puntero_lector==0)
	   {
	     cvPutText(imagenFondo,buffer[i],cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y+2.5*REC_TAM_Y+(REC_TAM_Y/2)*i), &font, cvScalar (255,255,255,0));
	     
	     //puntero_lector toma el valor del ultimo elemento de la string superior
	     puntero_lector=ultimo;
	     i--;
	     
	     cvPutText(imagenFondo,buffer[i],cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y+2.5*REC_TAM_Y+(REC_TAM_Y/2)*i), &font, cvScalar (255,255,255,0));
	     cvShowImage(nombreVentana,imagenFondo);
	   }
	   
	   else
	   {
	     puntero_lector--;
	     buffer[i][puntero_lector]=(char)0;
	     cvPutText(imagenFondo,buffer[i],cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y+2.5*REC_TAM_Y+(REC_TAM_Y/2)*i), &font, cvScalar (255,255,255,0));
	     cvShowImage(nombreVentana,imagenFondo);
	   }
	 }
       }
       aux = cvWaitKey(0);
     }
   }
   if(aux=='\n')
   {
     //Cargo el contenido y salgo
     for(j=0;j<7;j++)
       strcat(p->contenido,buffer[j]);
     return;
   }
}