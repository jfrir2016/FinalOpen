#include "TPO.h"

int Posteo (int fd, NodePost **PRoot, int id)
{
  int i,sel,idC;
  char* buffer[BUFFER];
  NodePost *Aux=*PRoot;
  POST *find;
  NodeComment *aux,*fcom;
  
  buffer[BUFFER-1]=NULL; 				//pongo el ultimo puntero a NULL para saber que termino
   
  for(i=0; Aux!=NULL; i++)			//Creo vector de Titulos
  {
    buffer[i]=(char *)malloc(sizeof(strlen(Aux->post.titulo)+1));
    strcpy(buffer[i],Aux->post.titulo);
    Aux=Aux->nxt;
  }
  buffer[i]=NULL;
  
  if((send(fd,&i,sizeof(int),0))==-1)			//Envio cantidad
  {
    perror("Send");
    return 1;
  }
  if(i==0)						//Si no hay Publicaciones retorno
    return 0;
    
  for(i=0; buffer[i]!=NULL; i++)
  {
    if((send(fd,buffer[i],strlen(buffer[i])+1,0))==-1)	//Envio titulo post a post
    {
      perror("Send");
      return 1;
    }
    sleep(1);
  }
  
  if((recv(fd,&sel,sizeof(int),0))==-1)			//Recivo seleccion
  {
    perror("Recv");
    return 1;
  }
  
  sel--;
  find=BuscoPost(buffer[sel],*PRoot);
  if((send(fd,find,sizeof(POST),0))==-1)		//Envio publicacion Entera
  {
    perror("Send");
    return 1;
  }
  
  //Envio de Comentarios
  
  do
  {
    for(aux=find->root,i=0;aux!=NULL;aux=aux->nxt)
      i++;
    if((send(fd,&i,sizeof(int),0))==-1)			//Envio cantidad
    {
      perror("Send");
      return 1;
    }
    for(aux=find->root;aux!=NULL;aux=aux->nxt)
    {
      if((send(fd,aux->comentario.contenido,strlen(aux->comentario.contenido)+1,0))==-1)	//Envio comentario
      {
	perror("Send");
	exit(1);
      }
      sleep(1);
    }
    if((recv(fd,&sel,sizeof(int),0))==-1)					//Recivo seleccion
    {
      perror("Recv");
      return 1;
    }
    if(sel==1)
    {
      aux=(NodeComment *)malloc(sizeof(NodeComment));
      if((recv(fd,aux->comentario.contenido,CTAM,0))==-1)			//Recivo comentario
      {
	perror("Recv");
	return 1;
      }
      if(find->root==NULL)
      {
	find->root=aux;
	aux->comentario.idU=id;
	aux->comentario.id=1;
	find->root->nxt=NULL;
      }
      else
      {
	for(fcom=find->root;fcom->nxt!=NULL;fcom=fcom->nxt);
	fcom->nxt=aux;
	idC=fcom->comentario.id;
	idC++;
	aux->comentario.idU=id;
	aux->comentario.id=idC;
	aux->nxt=NULL;
      }
    }
    if(sel==2)
      BorrarCom(fd,find,id);
  }while(sel!=3);
  return 0;
}