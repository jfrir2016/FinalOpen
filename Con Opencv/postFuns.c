/**********************************************************************************************************************************/

/**
 * \file 	postFuns.c
 * \brief 	Este modulo contiene las funciones de manejo de publicaciones
 * \author 	Tomás Ordóñez, Juan Francisco Reiszer, Santiago Ozan 
 * \date 	20/12/2016
 */

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "TPO.h"
/***********************************************************************************************************************************
*** FUNCIONES DEL MODULO
**********************************************************************************************************************************/
/**
	@fn  			int AgregarPost (int fd, NodePost **PRoot, int id)
	@brief 			Agrega una publicacion
 	@author 		Juan Francisco Reiszer, Tomas Ordoñez, Santiago Ozan
 	@date 			20/12/16
 	@param [in] fd: 	Descriptor del socket 
 	@param [in] PRoot:	Direccion del puntero que contiene la direccion de comienzo de la lista de Publicaciones
 	@param [in] id: 	Id del usuario
 	@return 		0 por exito, 1 por error
*/

int AgregarPost (int fd, NodePost **PRoot, int id)
{
  POST *Aux;
  
  Aux=(POST *)malloc(sizeof(POST));
  //Recivo Publicacion
  if((recv(fd,Aux,sizeof(POST),0))==-1)	
  {
    perror("Recv");
    return 1;
  }
  Aux->idU=id;
  //Agrego Nodo
  AgregarNodoPub(Aux,PRoot);
  return 0;
}

/**
	@fn  			int Posteo (int fd, NodePost **PRoot, int id)
	@brief 			Muestra las publicaciones y sus comentarios, permite comentar
 	@author 		Juan Francisco Reiszer, Tomas Ordoñez, Santiago Ozan
 	@date 			20/12/16
 	@param [in] fd: 	Descriptor del socket 
 	@param [in] PRoot:	Direccion del puntero que contiene la direccion de comienzo de la lista de Publicaciones
 	@param [in] id: 	Id del usuario
 	@return 		0 por exito, 1 por error
*/
int Posteo (int fd, NodePost **PRoot, int id)
{
  int i,sel,idC;
  char* buffer[BUFFER];
  NodePost *Aux=*PRoot;
  POST *find;
  NodeComment *aux,*fcom;
  //Ponemos el ultimo puntero a NULL para saber que termino
  buffer[BUFFER]=NULL; 				
  //Creo vector de Titulos
  for(i=0; Aux!=NULL; i++)			
  {
    buffer[i]=(char *)malloc(sizeof(strlen(Aux->post.titulo)+1));
    strcpy(buffer[i],Aux->post.titulo);
    Aux=Aux->nxt;
  }
  buffer[i]=NULL;
  //Envio cantidad
  if((send(fd,&i,sizeof(int),0))==-1)			
  {
    perror("Send");
    return 1;
  }
  //Si no hay Publicaciones retorno
  if(i==0)						
    return 0;
    
  for(i=0; buffer[i]!=NULL; i++)
  {
    //Envio titulo post a post
    if((send(fd,buffer[i],strlen(buffer[i])+1,0))==-1)	
    {
      perror("Send");
      return 1;
    }
    sleep(1);
  }
  //Recivo seleccion
  if((recv(fd,&sel,sizeof(int),0))==-1)			
  {
    perror("Recv");
    return 1;
  }
  sel--;
  //Busco la publicacion
  find=BuscoPost(buffer[sel],*PRoot);
  //Envio publicacion Entera
  if((send(fd,find,sizeof(POST),0))==-1)		
  {
    perror("Send");
    return 1;
  }
  
  //Envio de Comentarios
  do
  {
    for(aux=find->root,i=0;aux!=NULL;aux=aux->nxt)
      i++;
    //Envio cantidad
    if((send(fd,&i,sizeof(int),0))==-1)			
    {
      perror("Send");
      return 1;
    }
    for(aux=find->root;aux!=NULL;aux=aux->nxt)
    {
      //Envio comentario
      if((send(fd,aux->comentario.contenido,strlen(aux->comentario.contenido)+1,0))==-1)
      {
	perror("Send");
	return 1;
      }
      sleep(1);
    }
    //Recivo seleccion
    if((recv(fd,&sel,sizeof(int),0))==-1)
    {
      perror("Recv");
      return 1;
    }
    if(sel==1)
    {
      aux=(NodeComment *)malloc(sizeof(NodeComment));
      //Recivo comentario
      if((recv(fd,aux->comentario.contenido,CTAM,0))==-1)
      {
	perror("Recv");
	return 1;
      }
      //Agrego cometario a la lista
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

/**
	@fn  			POST* BuscoPost (char *name, NodePost *PRoot)
	@brief 			Busca una publicacion por su titulo
 	@author 		Juan Francisco Reiszer, Tomas Ordoñez, Santiago Ozan
 	@date 			20/12/16
 	@param [in] name: 	titulo 
 	@param [in] PRoot:	Direccion de comienzo de la lista de Publicaciones
 	@return 		Direccion de comienzo de la estructura POST
*/

POST* BuscoPost (char *name, NodePost *PRoot)
{
  POST* find;
  NodePost *Aux;
  find=NULL;
  
  for(Aux=PRoot; Aux!=NULL;Aux=Aux->nxt)
  {
    if(!strcmp(Aux->post.titulo,name))
      find=&(Aux->post);
  }
  return find;
}

/**
	@fn  			int BorrarPost (int fd, NodePost **PRoot, int id)
	@brief 			Borra una publicacion
 	@author 		Juan Francisco Reiszer, Tomas Ordoñez, Santiago Ozan
 	@date 			20/12/16
 	@param [in] fd: 	Descriptor del socket 
 	@param [in] PRoot:	Direccion del puntero que contiene la direccion de comienzo de la lista de Publicaciones
 	@param [in] id: 	Id del usuario
 	@return 		0 por exito, 1 por error
*/

int BorrarPost (int fd, NodePost **PRoot, int id)
{
  char* buffer[BUFFER];
  POST *find;
  NodePost *Aux=*PRoot;
  int sel,i,fl;
  char Archivo[8];
  
  //Pongo el ultimo puntero a NULL para saber que termino
  buffer[BUFFER]=NULL;
  
  //Creo vector de Titulos
  for(i=0; Aux!=NULL; i++)					
  {
    buffer[i]=(char *)malloc(sizeof(strlen(Aux->post.titulo)+1));
    strcpy(buffer[i],Aux->post.titulo);
    Aux=Aux->nxt;
  }
  buffer[i]=NULL;
  //Envio cantidad
  if((send(fd,&i,sizeof(int),0))==-1)	
  {
    perror("Send");
    return 1;
  }
  if(i==0)
    return 0;    
    
  for(i=0; buffer[i]!=NULL; i++)
  {
    //Envio titulo post a post
    if((send(fd,buffer[i],strlen(buffer[i])+1,0))==-1)
    {
      perror("Send");
      return 1;
    }
    sleep(1);
  }
  //Recivo seleccion
  if((recv(fd,&sel,sizeof(int),0))==-1)	
  {
    perror("Recv");
    return 1;
  }
  sel--;
  //Busco publicacion a borrar
  find=BuscoPost(buffer[sel],*PRoot);
  if(find->idU!=id && id!=1)
  {
    i=0;
    //Envio Error
    if((send(fd,&i,sizeof(int),0))==-1)	
    {
      perror("Send");
      return 1;
    }
    return 1;
  }
  fl=find->id;
  //Borro
  if(BorrarNodoPub(find->id,PRoot))
  {
    i=0;
    //Envio Error
    if((send(fd,&i,sizeof(int),0))==-1)	
    {
      perror("Send");
      return 1;
    }
    return 1;
  }
  i=1;
  //Envio exito
  if((send(fd,&i,sizeof(int),0))==-1)
  {
    perror("Send");
    return 1;
  }
  //Elimina el archivo de sus cometarios
  sprintf(Archivo,"xcF%d",fl);
  remove(Archivo); 
  return 0;
}