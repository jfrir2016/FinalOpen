/***********************************************************************************************************************************/

/**
 * \file 	cvResultados.c
 * \brief 	Este modulo contiene las funciones que indican resultados de procedimientos por medio de OpenCv
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
 * \fn 		int cvBajaUsuario (IplImage* imagenFondo,char* ventana, int sockfd)
 * \brief 	Esta funcion informa si se pudo o no dar de baja al usuario
 * \author 	Tomás Ordóñez, Juan Francisco Reiszer, Santiago Ozan
 * \date 	20/12/2016
 * \param [in] 	imagenFondo: Puntero a la imagen
 * \param [in] 	ventana: Direccion de comienzo de la string con el nombre de la ventana
 * \param [in] 	sockfd: Descriptor del socket
 * \return 	0 por exito, 1 por error
 */

int cvBajaUsuario(IplImage* imagenFondo, char* ventana, int sockfd)
{
  int a;
  
  CvFont Font;
  cvInitFont(&Font,CV_FONT_HERSHEY_SIMPLEX, 0.7, 0.8, 0, 2,8);
  
  if((recv(sockfd,&a,sizeof(int),0))==-1)
  {
    perror("Recv");
    exit(1);
  }
  cvZero(imagenFondo);
  
  cvMostrarTitulo(imagenFondo);
  
  if(a!=1)
  {
    cvPutText(imagenFondo,"Se ha dado de baja",cvPoint(ANCHO/2-100,ALTO/2),&Font,cvScalar(255,255,255,0));
    cvPutText(imagenFondo,"Hasta luego",cvPoint(ANCHO/2-80,ALTO/2+70),&Font,cvScalar(255,255,255,0));
    cvShowImage(ventana, imagenFondo);
    cvWaitKey(0);
    return 0;
  }
  cvPutText(imagenFondo,"No se pudo dar de baja",cvPoint(ANCHO/2-100,ALTO/2),&Font,cvScalar(0,0,255,0));
  cvShowImage(ventana, imagenFondo);
  cvWaitKey(0);
  return 1;
}

/**
 * \fn 		int cvSalir (IplImage* imagenFondo,char* ventana)
 * \brief 	Esta funcion se encarga de salir
 * \author 	Tomás Ordóñez, Juan Francisco Reiszer, Santiago Ozan
 * \date 	20/12/2016
 * \param [in] 	imagenFondo: Puntero a la imagen
 * \param [in] 	ventana: Direccion de comienzo de la string con el nombre de la ventana
 * \return 	void
 */
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


/**
 * \fn 		void errorInicio (IplImage* imagenFondo)
 * \brief 	Esta funcion se encarga de informar que hubo un error al ingresar
 * \author 	Tomás Ordóñez, Juan Francisco Reiszer, Santiago Ozan
 * \date 	20/12/2016
 * \param [in] 	imagenFondo: Puntero a la imagen
 * \return 	void
 */
void errorInicio(IplImage* imagenFondo)
{
  CvFont Font;
  cvInitFont(&Font,CV_FONT_HERSHEY_SIMPLEX, 0.7, 0.8, 0, 2,8);
  
  cvPutText(imagenFondo,"Error, intentelo nuevamente",cvPoint(400,370), &Font, cvScalar (0,0,255,0));
  
  return;
}