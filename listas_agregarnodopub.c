#include "TPO.h"

void AgregarNodoPub(POST *post, NodePost **root)
{
  int idp;
  NodePost *current=*root;
  
   if(current==NULL){
    *root = (NodePost*)malloc(sizeof(NodePost));
    (*root)->post=*post;
    (*root)->post.id=1;
    (*root)->post.root=NULL;
    (*root)->nxt=NULL;
    return;
  }
  
  while(current->nxt!=NULL)
    current=current->nxt;
  
  current->nxt=(NodePost*)malloc(sizeof(NodePost));
  idp=current->post.id;
  idp++;
  current=current->nxt;
  current->post=*post;
  current->post.id=idp;
  current->post.root=NULL;
  current->nxt=NULL;
  return;
}