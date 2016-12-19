#include "TPO.h"

int BorrarCom (int fd, POST *pp, int id)
{
  int sel,i;
  NodeComment *aux,**first;
  char Archivo[8];
  
  first=&(pp->root);
  
  if((recv(fd,&sel,sizeof(int),0))==-1)					//Recivo seleccion
  {
    perror("Recv");
    return 1;
  }
  if(*first==NULL)
  {
    sel=0;
    if((send(fd,&sel,sizeof(int),0))==-1)				//Envio 0 si no hay comentarios
    {
      perror("Send");
      return 1;
    }
    return 0;
  }
  aux=*first;
  for(i=1;i<sel;i++)
    aux=aux->nxt;
  
  if(aux->comentario.idU==id||id==1)
  {
    if(!BorrarComentario(aux->comentario.id,first))
    {
      sel=1;
      if((send(fd,&sel,sizeof(int),0))==-1)				//Envio 1 por exito
      {
	perror("Send");
	return 1;
      }
    }
    else
    {
      sel=2;
      if((send(fd,&sel,sizeof(int),0))==-1)				//Envio 2 por error
      {
	perror("Send");
	return 1;
      }
    }
  }
  else
  {
    sel=3;
    if((send(fd,&sel,sizeof(int),0))==-1)				//Envio 3 si no es propia
    {
      perror("Send");
      return 1;
    }
  }
  if(*first==NULL)
  {
    sprintf(Archivo,"xcF%d",pp->id);
    remove(Archivo);
  }
  return 0;
}