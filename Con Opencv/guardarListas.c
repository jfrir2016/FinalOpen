/**********************************************************************************************************************************/

/**
 * \file 	guardarListas.c
 * \brief 	Este modulo contiene las funciones que guardan las listas en archivos
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
	@fn  			int GuardarUsuarios (NodeUser *primero, char *archivo)
	@brief 			Guarda en un archivo la informacion de usuarios y liberar memoria de la lista
 	@author 		Juan Francisco Reiszer, Tomas Ordoñez, Santiago Ozan
 	@date 			20/12/16
 	@param [in] primero:	Direccion de comienzo de la lista de Usuarios
 	@param [in] archivo:	nombre o path del archivo donde se va a guardar
 	@return 		0 por exito, 1 por error
*/

int GuardarUsuarios (NodeUser *primero, char *archivo)
{
  FILE* fd;
  NodeUser* aux;
  USU *datos;
  
  //Abrimos el archivo en modo escritura, si no existe lo crea
  if((fd=fopen(archivo,"w"))==NULL)
    return 1;
  for(aux=primero;aux!=NULL;)
  {
    datos=&(aux->user);
    fwrite(datos,sizeof(USU),1,fd);
    primero=aux;
    aux=aux->nxt;
    //libera la memoria del nodo
    free(primero);				
  }
  fclose(fd);
  return 0;
}

/**
	@fn  			int GuardarPost (NodePost *primero, char *archivo)
	@brief 			Guarda en un archivo la informacion de publicaciones y liberar memoria de la lista
 	@author 		Juan Francisco Reiszer, Tomas Ordoñez, Santiago Ozan
 	@date 			20/12/16
 	@param [in] primero:	Direccion de comienzo de la lista de publicaciones
 	@param [in] archivo:	nombre o path del archivo donde se va a guardar
 	@return 		0 por exito, 1 por error
*/

int GuardarPost (NodePost *primero, char *archivo)
{
  FILE* fd;
  NodePost* aux;
  POST *datos;
  
  //Abre el archivo en modo escritura, si no existe lo crea
  if((fd=fopen(archivo,"w"))==NULL)
    return 1;
  for(aux=primero;aux!=NULL;)
  {
    datos=&(aux->post);
    fwrite(datos,sizeof(POST),1,fd);
    primero=aux;
    aux=aux->nxt;
    free(primero);
  }
  fclose(fd);
  return 0;
}

/**
	@fn  			int GuardarComents (NodePost *primero)
	@brief 			Guarda en un archivo los comentarios de cada publicacion y liberar memoria de todas las lista
 	@author 		Juan Francisco Reiszer, Tomas Ordoñez, Santiago Ozan
 	@date 			20/12/16
 	@param [in] primero:	Direccion de comienzo de la lista de publicaciones
 	@return 		0 por exito, 1 por error
*/

int GuardarComents (NodePost *primero)
{
  FILE* fd;
  NodeComment *aux, *first;
  NodePost* read;
  COMMT *datos;
  char Archivo[8];
  
  for(read=primero;read!=NULL;read=read->nxt)
  {
    //Cargamos en un buffer el nombre del archivo que depende del id de la publicacion
    sprintf(Archivo,"xcF%d",read->post.id);
    //Si no hay comentarios no guardo
    first=read->post.root;
    if(first!=0)
    {
      if((fd=fopen(Archivo,"w"))==NULL)
	return 1;
    
      for(aux=first;aux!=NULL;)
      {
	datos=&(aux->comentario);
	fwrite(datos,sizeof(COMMT),1,fd);
	first=aux;
	aux=aux->nxt;
	free(first);
      }
      fclose(fd);
    }
  }
  return 0;
}