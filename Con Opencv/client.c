/**********************************************************************************************************************************/
/** 
 * @details		Proyecto: TPO, Foro de Discusión Académico
 * @file		client.c
 * @brief		Main del programa Cliente
 * @date		20/12/16
 * @author		Juan Francisco Reiszer, Tomas Ordoñez, Santiago Ozan
 *
*/
/**********************************************************************************************************************************
 *** INCLUDES
***********************************************************************************************************************************/
#include "Cliente.h"
/**********************************************************************************************************************************/

int main(void)
{
  
  char buffer[BUFFER];
  int sockfd;
  int a,id=-1, cant, i=0,b;
  
  usu buff;
  post bufp;
  com bufc;
  //Puntero a funcion del menu de Inicio
  int (*Menu1[])(usu*,IplImage*,char*,int)={Ingresar,Registro};
  
  struct sockaddr_in server_addr;
  struct sockaddr_in my_addr;
    
  server_addr.sin_family= AF_INET;
  server_addr.sin_port= htons(PORT);
  server_addr.sin_addr.s_addr=inet_addr(IP);
  memset(&(server_addr.sin_zero),'\0',8);
  
  my_addr.sin_family= AF_INET;
  my_addr.sin_port= 0;
  my_addr.sin_addr.s_addr=INADDR_ANY;
  memset(&(my_addr.sin_zero),'\0',8);
  
  if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
  {
    perror("Socket");
    exit(1);
  }
  //Conecto al socket
  if((connect(sockfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_in)))==-1)
  {
    perror("Connect");
    exit(1);
  }
    //Creamos una ventana de tamaño ALTOxANCHO
  cvNamedWindow("Ventana",  CV_WINDOW_NORMAL);
  cvResizeWindow("Ventana", ANCHO, ALTO);

  //Creamos una imagen de fondo que podamos modificar del mismo tamaño que la pantalla
  IplImage* imagenFondo = cvCreateImage(cvSize(ANCHO,ALTO), 8, 3);
  
  do
  {
    if(i!=-1)
    {
      //Se genera la interfaz y se asigna la seleccion a la variable a
      do
	a=interfaz1(imagenFondo,"Ventana");
      while(a!=1&&a!=2&&a!=0);
    }
    else 
      a=1;
    
    if(a!=0)
    {
      if(a==1)
      {
	cvResizeWindow("Ventana",1,1);
	//cvReleaseImage(&imagenFondo);
	//cvDestroyAllWindows();
	//cvWaitKey(2);
      }
      Menu1[a](&buff,imagenFondo,"Ventana",i);	//Llamo a funcion Ingresar o Registrarse
      if(a==1)
      {
	//Creamos una ventana de tamaño ALTOxANCHO
	//cvNamedWindow("Ventana",  CV_WINDOW_NORMAL);
	cvResizeWindow("Ventana", ANCHO, ALTO);
	//Creamos una imagen de fondo que podamos modificar del mismo tamaño que la pantalla
	// imagenFondo = cvCreateImage(cvSize(ANCHO,ALTO), 8, 3);
      }
    }
    else
      buff.id=0;
    
    //Envio datos de Usuario
    if((send(sockfd,&buff,sizeof(buff),0))==-1)
    {
      perror("Send");
      exit(1);
    }
    //Recivo id o -1 en caso de error
    if((recv(sockfd,&id,sizeof(int),0))==-1)
    {
      perror("Recv");
      exit(1);
    }
    i=id;
  }while(id<0);
  
  system("clear");
  if(id==0)
  {
    //Salgo si seleccionaron Salir
    close(sockfd);
    exit (0);
  }
    
  do
  {
    do
      a=menuPrincipal(imagenFondo,"Ventana",id);
    while(a!=1&&a!=2&&a!=3&&a!=4&&a!=5);
    
    //Envio seleccion
    if((send(sockfd,&a,sizeof(int),0))==-1)
    {
      perror("Send");
      exit(1);
    }
  
    switch(a)
    {
      case 1:
	fflush(stdout);
	system("clear");
	//Recivo cantidad
	if((recv(sockfd,&cant,sizeof(int),0))==-1)
	{
	  perror("Recv");
	  exit(1);
	}
	if(cant==0)
	{
	  printf("No hay Publicaciones\n");
	  break;
	}
	for(i=1;i<=cant;i++)
	{
	  //Recivo nombres de posts
	  if((recv(sockfd,buffer,BUFFER,0))==-1)
	  {
	    perror("Recv");
	    exit(1);
	  }
	  //Imprimo los nombres
	  printf("%d)%s\n",i,buffer);
	}
	scanf("%d",&a);
	//Envio seleccion
	if((send(sockfd,&a,sizeof(int),0))==-1)		
	{
	  perror("Send");
	  exit(1);
	}
	//Recivo Publicacion
	if((recv(sockfd,&bufp,sizeof(post),0))==-1)
	{
	  perror("Recv");
	  exit(1);
	}
	system("clear");
	do
	{
	  //Muestro
	  printf("\t\t\t\t%s\n\n\t%s\n\n\n",bufp.titulo,bufp.contenido);
	  //Recivo cantidad
	  if((recv(sockfd,&cant,sizeof(int),0))==-1)
	  {
	    perror("Recv");
	    exit(1);
	  }
	  if(cant!=0)
	  {
	    for(i=1;i<=cant;i++)
	    {
	      //Recivo comentarios e imprimo
	      if((recv(sockfd,bufc.contenido,CTAM,0))==-1)
	      {
		perror("Recv");
		exit(1);
	      }
	      printf("%d.%s\n\n",i,bufc.contenido);
	    }
	  }
	  printf("\n\n\n1-Comentar\n2-Borrar Comentario\n3-Menu Principal\n");
	  scanf("%d",&a);
	  while(a!=1&&a!=2&&a!=3)
	    scanf("%d",&a);
	  //Envio seleccion
	  if((send(sockfd,&a,sizeof(int),0))==-1)
	  {
	    perror("Send");
	    exit(1);
	  }
	  if(a==1)
	  {
	    printf("Comentario: ");
	    getchar();
	    scanf("%241[^\r\n]",bufc.contenido);
	    //Envio Comentario
	    if((send(sockfd,bufc.contenido,CTAM,0))==-1)
	    {
	      perror("Send");
	      exit(1);
	    }
	    system("clear");
	  }
	  if(a==2)
	  {
	    printf("Ingrese Numero de Comentario\n");
	    scanf("%d",&b);
	    //Envio seleccion
	    if((send(sockfd,&b,sizeof(int),0))==-1)
	    {
	      perror("Send");
	      exit(1);
	    }
	    //Recivo resultado
	    if((recv(sockfd,&b,sizeof(int),0))==-1)
	    {
	      perror("Recv");
	      exit(1);
	    }
	    system("clear");
	    switch(b)
	    {
	      case 0:
		printf("No Hay Comentarios\n\n");
		break;
	      case 1:
		printf("Comentario borrado con exito\n\n");
		break;
	      case 2:
		printf("Error al borrar\n\n");
		break;
	      case 3:
		printf("No es un comentario propio\n\n");
		break;
	    }
	  }
	}while(a!=3);
	system("clear");
	break;
	
      case 2:
	cvCrearPublicacion(imagenFondo,"Ventana", &bufp);
	if((send(sockfd,&bufp,sizeof(post),0))==-1)	//Envio seleccion
	{
	  perror("Send");
	  exit(1);
	}
	break;
	
      case 3:
	if((recv(sockfd,&cant,sizeof(int),0))==-1)
	{
	  perror("Recv");
	  exit(1);
	}
	if(cant==0)
	{
	  printf("No hay Publicaciones\n");
	  break;
	}
	//Recivo nombres de posts
	for(i=1;i<=cant;i++)
	{
	  if((recv(sockfd,buffer,BUFFER,0))==-1)	
	  {
	    perror("Recv");
	    exit(1);
	  }
	  printf("%d)%s\n",i,buffer);
	}
	fflush(stdin);
	scanf("%d",&a);
	//Envio seleccion
	if((send(sockfd,&a,sizeof(int),0))==-1)
	{
	  perror("Send");
	  exit(1);
	}
	//Recivo resultado
	if((recv(sockfd,&cant,sizeof(int),0))==-1)
	{
	  perror("Recv");
	  exit(1);
	}
	system("clear");
	if(cant==0)
	  printf("No es una publicacion propia\n");
	else
	  printf("Publicacion borrada con exito\n");
	break;
	
      case 4:
	cvBajaUsuario(imagenFondo,"Ventana",sockfd);
	break;
	
      case 5:
	cvSalir(imagenFondo,"Ventana");
	break;
    }
  }while(a<4);
  //Cierro socket
  close(sockfd);
  //Cierro ventana
  cvReleaseImage(&imagenFondo);
  return 0;
}