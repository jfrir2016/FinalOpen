/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "TPO.h"
/***********************************************************************************************************************************
*** FUNCIONES DEL MODULO
**********************************************************************************************************************************/

/**
	@fn  			void AgregarNodoUsuario (USU *usuario, NodeUser **root)
	@brief 			Agrega un nodo a la lista de Usuarios
 	@author 		Juan Francisco Reiszer, Tomas Ordoñez, Santiago Ozan
 	@date 			20/12/16
 	@param [in] usuario:	Direccion de la estructura de los datos
 	@param [in] root:	Direccion del puntero que contiene la direccion de comienzo de la lista de Usuarios
 	@return 		void
*/

int AgregarNodoUsuario(USU *usuario, NodeUser **root)
{
  NodeUser *current=*root;
  int id=1;
  
  if(current==NULL)
  {
    *root = (NodeUser*)malloc(sizeof(NodeUser));
    (*root)->user=*usuario;
    (*root)->user.id=id;
    (*root)->nxt=NULL;
    return id;
  }
  while(current->nxt!=NULL)
    current=current->nxt;
  
  current->nxt=(NodeUser*)malloc(sizeof(NodeUser));
  current->nxt->user=*usuario;
  id=current->user.id;
  id++;
  current=current->nxt;
  current->user.id=id;
  current->nxt=NULL;
  return id;
}

/**
	@fn  			int AgregarNodoPub (POST *post, NodePost **root)
	@brief 			Agrega un nodo a la lista de Publicaciones
 	@author 		Juan Francisco Reiszer, Tomas Ordoñez, Santiago Ozan
 	@date 			20/12/16
 	@param [in] post:	Direccion de la estructura de los datos
 	@param [in] root:	Direccion del puntero que contiene la direccion de comienzo de la lista de Publicaciones
 	@return 		void
*/

void AgregarNodoPub(POST *post, NodePost **root)
{
  int idp;
  NodePost *current=*root;
  
   if(current==NULL){
    *root = (NodePost*)malloc(sizeof(NodePost));
    (*root)->post=*post;
    //Si es la primera id=1
    (*root)->post.id=1;
    (*root)->post.root=NULL;
    (*root)->nxt=NULL;
    return;
  }
  
  while(current->nxt!=NULL)
    current=current->nxt;
  
  current->nxt=(NodePost*)malloc(sizeof(NodePost));
  //Busco id del ultimo y lo incremeto
  idp=current->post.id;
  idp++;
  current=current->nxt;
  current->post=*post;
  current->post.id=idp;
  current->post.root=NULL;
  current->nxt=NULL;
  return;
}