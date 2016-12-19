#include "TPO.h"

int BorrarPost (int fd, NodePost **PRoot, int id)
{
  char* buffer[BUFFER];
  POST *find;
  NodePost *Aux=*PRoot;
  int sel,i,fl,j;
  char Archivo[8];
  
  buffer[BUFFER-1]=NULL; 						//pongo el ultimo puntero a NULL para saber que termino
   
  for(i=0; Aux!=NULL; i++)					//Creo vector de Titulos
  {
    buffer[i]=(char *)malloc(sizeof(strlen(Aux->post.titulo)+1));
    strcpy(buffer[i],Aux->post.titulo);
    Aux=Aux->nxt;
  }
  buffer[i]=NULL;
  
  if((send(fd,&i,sizeof(int),0))==-1)				//Envio cantidad
  {
    perror("Send");
    exit(1);
  }
  if(i==0)
    return 0;    
  
  j=0;  
  do
  {
    for(i=0; buffer[j]!=NULL && i<9 ; i++)
    {
      if((send(fd,buffer[j],strlen(buffer[j])+1,0))==-1)		//Envio titulo post a post
      {
	perror("Send");
	exit(1);
      }
      printf("%d\n",j);
      sleep(1);
      j++;
    }
  printf("Esperando recibir\n");
  fflush(stdout);
    if((recv(fd,&sel,sizeof(int),0))==-1)			//Recivo seleccion
    {
      perror("Recv");
      exit(1);
    }
  }while(sel==0);
  sel--;
  find=BuscoPost(buffer[sel],*PRoot);				//Busco publicacion a borrar
  if(find->idU!=id && id!=1)
  {
    i=0;
    if((send(fd,&i,sizeof(int),0))==-1)				//Envio Error
    {
      perror("Send");
      exit(1);
    }
    return 1;
  }
  fl=find->id;
  if(BorrarNodoPub(find->id,PRoot))				//Borro
  {
    i=0;
    if((send(fd,&i,sizeof(int),0))==-1)				//Envio Error
    {
      perror("Send");
      exit(1);
    }
    return 1;
  }
  i=1;
  if((send(fd,&i,sizeof(int),0))==-1)				//Envio exito
  {
    perror("Send");
    exit(1);
  }
  
  sprintf(Archivo,"xcF%d",fl);
  remove(Archivo);
    
  return 0;
}