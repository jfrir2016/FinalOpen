/**********************************************************************************************************************************/

/**
 * \file 	borrarNodo.c
 * \brief 	Este modulo contiene las funciones que borran nodos de las listas
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
	@fn  			int BorrarNodoUsuario (int id, NodeUser **root)
	@brief 			Borra un nodo de la lista de Usuarios y libera su memoria
 	@author 		Juan Francisco Reiszer, Tomas Ordoñez, Santiago Ozan
 	@date 			20/12/16
 	@param [in] id: 	Numero de id del usuario a borrar 
 	@param [in] root:	Direccion del puntero que contiene la direccion de comienzo de la lista de Usuarios 
 	@return 		0 por exito, 1 por error
*/

int BorrarNodoUsuario(int id, NodeUser **root)
{
  NodeUser *anterior=*root;
  NodeUser *current=*root;
  
  //Busca el nodo segun la id
  while(current->user.id!=id)
  {
    anterior=current;
    if(current->nxt==NULL)
      return 1;
    current=current->nxt;
  }
  if(current!=*root)
  {
    anterior->nxt=current->nxt;
    free(current);
  }
  else
  {
    *root=(*root)->nxt;
    free(current);
  }
  return 0;
}

/**
	@fn  			int BorrarNodoPub (int id, NodePost **root)
	@brief 			Borra un nodo de la lista de Publicaciones y libera su memoria
 	@author 		Juan Francisco Reiszer, Tomas Ordoñez, Santiago Ozan
 	@date 			20/12/16
 	@param [in] id: 	Numero de id de la publicacion a borrar 
 	@param [in] root:	Direccion del puntero que contiene la direccion de comienzo de la lista de Publicaciones
 	@return 		0 por exito, 1 por error
*/

int BorrarNodoPub(int id, NodePost **root)
{
  NodePost *anterior=(*root);
  NodePost *current=(*root);
  
  //Busca la publicacion segun su id
  while(current->post.id!=id)
  {
    anterior=current;
    if(current->nxt==NULL)
      return 1;
    current=current->nxt;
  }
  if(current!=(*root))
  {
    anterior->nxt=current->nxt;
    //Borra todos los comentarios asociados
    while(current->post.root!=NULL)
      BorrarComentario(current->post.root->comentario.id, &(current->post.root));
    free(current);
  }
  else
  {
    //Borra todos los comentarios asociados
    while(current->post.root!=NULL)
      BorrarComentario(current->post.root->comentario.id, &(current->post.root));
    (*root)=(*root)->nxt;
    free(current);
  }
  return 0;
}

/**
	@fn  			int BorrarComentario (int id, NodeComment **root)
	@brief 			Borra un nodo de una lista de comentarios y libera su memoria
 	@author 		Juan Francisco Reiszer, Tomas Ordoñez, Santiago Ozan
 	@date 			20/12/16
 	@param [in] id: 	Numero de id del comentario a borrar 
 	@param [in] root:	Direccion del puntero que contiene la direccion de comienzo de la lista de comentarios
 	@return 		0 por exito, 1 por error
*/

int BorrarComentario(int id, NodeComment **root)
{
  NodeComment *anterior=*root;
  NodeComment *current=*root;
  
  //Busca el cometario por su id
  while(current->comentario.id!=id)
  {
    anterior=current;
    if(current->nxt==NULL)
      return 1;
    current=current->nxt;
  }
  if(current!=*root)
  {
    anterior->nxt=current->nxt;
    free(current);
  }
  else
  {
    *root=(*root)->nxt;
    free(current);
  }
  return 0;
}