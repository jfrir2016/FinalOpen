#include "TPO.h"

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
