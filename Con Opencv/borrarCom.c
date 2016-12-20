/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "TPO.h"
/***********************************************************************************************************************************
*** FUNCIONES DEL MODULO
**********************************************************************************************************************************/

/**
	@fn  		int BorrarCom (int fd, POST *pp, int id)
	@brief 		Borra un comentario de una publicacion
 	@author 	Juan Francisco Reiszer, Tomas Ordoñez, Santiago Ozan
 	@date 		20/12/16
 	@param [in] fd: Direccion del buffer a llenar  
 	@param [in] pp:	Direccion del puntero que a punta a la direccion de la estructura dato de la publicacion donde se encuentra el comentario
 	@param [in] id:	id del usuario que quiere borrar el comentario
 	@return 	0 si no hay comentarios, 1 por exito, 2 por error, 3 si el comentario no es propio
*/

int BorrarCom (int fd, POST *pp, int id)
{
  int sel,i;
  NodeComment *aux,**first;
  char Archivo[8];
  
  //Cargo en first la direccion de comienzo de la lista
  first=&(pp->root);
  
  //Recivo seleccion
  if((recv(fd,&sel,sizeof(int),0))==-1)
  {
    perror("Recv");
    return 1;
  }
  if(*first==NULL)
  {
    sel=0;
    //Envio 0 si no hay comentarios
    if((send(fd,&sel,sizeof(int),0))==-1)
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
      //Envio 1 por exito
      {
      if((send(fd,&sel,sizeof(int),0))==-1)
	perror("Send");
	return 1;
      }
    }
    else
    {
      sel=2;
      //Envio 2 por error
      if((send(fd,&sel,sizeof(int),0))==-1)
      {
	perror("Send");
	return 1;
      }
    }
  }
  else
  {
    sel=3;
    //Envio 3 si los ids no coinciden
    if((send(fd,&sel,sizeof(int),0))==-1)
    {
      perror("Send");
      return 1;
    }
  }
  if(*first==NULL)
  {
    //Si no quedan comentarios elimino el archivo asociado
    sprintf(Archivo,"xcF%d",pp->id);
    remove(Archivo);
  }
  return 0;
}