#include "Cliente.h"

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