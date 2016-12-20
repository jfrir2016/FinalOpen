/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "TPO.h"
/***********************************************************************************************************************************
*** FUNCIONES DEL MODULO
**********************************************************************************************************************************/

/**
	@fn  			int LoadUsuarios (NodeUser **primero, char *archivo)
	@brief 			Carga desde archivo la informacion de usuarios y crea la respectiva lista
 	@author 		Juan Francisco Reiszer, Tomas Ordoñez, Santiago Ozan
 	@date 			20/12/16
 	@param [in] primero:	Direccion del puntero que contiene la direccion de comienzo de la lista de Usuarios
 	@param [in] archivo:	nombre o path del archivo donde se va a guardar
 	@return 		0 por exito, 1 por error
*/

int LoadUsuarios (NodeUser **primero,char *archivo)
{
  FILE *fd;
  NodeUser *aux,*paux;
  USU *datos;
  
  //Abrimos el archivo, si no existe lo crea, lee desde el principio
  if((fd=fopen(archivo,"a+"))==NULL)
    return 1;
  aux=(NodeUser*)malloc(sizeof(NodeUser));
  datos=&(aux->user);
  fread(datos,sizeof(USU),1,fd);
  if(feof(fd))
  {
    //Si esta vacio libera la memoria pedida y retorna
    free(aux);
    return 0;
  }
  *primero=aux;
  paux=aux;
  while(!feof(fd))
  {
    aux->nxt=(NodeUser*)malloc(sizeof(NodeUser));
    aux=aux->nxt;
    datos=&(aux->user);
    fread(datos,sizeof(USU),1,fd);
  }
  fclose(fd);
  for(;paux->nxt!=aux;paux=paux->nxt);
  free(aux);
  paux->nxt=NULL;
  return 0;
}

/**
	@fn  			int LoadPubli (NodeUser **primero, char *archivo)
	@brief 			Carga desde archivo la informacion de las publicaciones y crea la respectiva lista
 	@author 		Juan Francisco Reiszer, Tomas Ordoñez, Santiago Ozan
 	@date 			20/12/16
 	@param [in] primero:	Direccion del puntero que contiene la direccion de comienzo de la lista de publicaciones
 	@param [in] archivo:	nombre o path del archivo donde se va a guardar
 	@return 		0 por exito, 1 por error
*/

int LoadPubli (NodePost **primero,char *archivo)
{
  FILE *fd;
  NodePost *aux,*paux;
  POST *datos;
  
  //Abrimos el archivo, si no existe lo crea, lee desde el principio
  if((fd=fopen(archivo,"a+"))==NULL)
    return 1;
  aux=(NodePost*)malloc(sizeof(NodePost));
  datos=&(aux->post);
  fread(datos,sizeof(POST),1,fd);
  aux->post.root=NULL;
  if(feof(fd))
  {
    //Si esta vacio libera la memoria pedida y retorna
    free(aux);
    return 0;
  }
  *primero=aux;
  paux=aux;
  while(!feof(fd))
  {
    aux->nxt=(NodePost*)malloc(sizeof(NodePost));
    aux=aux->nxt;
    datos=&(aux->post);
    fread(datos,sizeof(POST),1,fd);
    aux->post.root=NULL;
  }
  fclose(fd);
  for(;paux->nxt!=aux;paux=paux->nxt);
  free(aux);
  paux->nxt=NULL;
  return 0; 
}

/**
	@fn  			int LoadComments (NodeUser **primero)
	@brief 			Carga desde los distintos archivos de comentarrios, y crea las listas de cada publicacion
 	@author 		Juan Francisco Reiszer, Tomas Ordoñez, Santiago Ozan
 	@date 			20/12/16
 	@param [in] primero:	Direccion del puntero que contiene la direccion de comienzo de la lista de publicaciones
 	@param [in] archivo:	nombre o path del archivo donde se va a guardar
 	@return 		0 por exito
*/

int LoadComments (NodePost **primero)
{
  FILE *fd;
  NodeComment *aux,*first,*paux;;
  NodePost *read;
  COMMT *datos;
  char Archivo[8];
  
  //Si no hay publicaciones retorna
  if(*primero==NULL)
    return 0;
  for(read=*primero;read!=NULL;read=read->nxt)
  {
    //Carga el buffer con el archivo de cada lista
    sprintf(Archivo,"xcF%d",read->post.id);
    //Abre el archivo en lectura
    if((fd=fopen(Archivo,"r"))!=NULL)
    {
      //Si existe crea la lista
      aux=(NodeComment*)malloc(sizeof(NodeComment));
      first=aux;
      datos=&(aux->comentario);
      fread(datos,sizeof(COMMT),1,fd);
      paux=aux;
      while(!feof(fd))
      {
	aux->nxt=(NodeComment*)malloc(sizeof(NodeComment));
	aux=aux->nxt;
	datos=&(aux->comentario);
	fread(datos,sizeof(COMMT),1,fd);
      }
      for(;paux->nxt!=aux;paux=paux->nxt);
      free(aux);
      paux->nxt=NULL;
      //Asocio la lista al nodo de la publicacion
      read->post.root=first;
      fclose(fd);
    }
  }
  return 0; 
}