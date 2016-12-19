#include "TPO.h"

int BorrarNodoUsuario(int id, NodeUser **root)
{
  NodeUser *anterior=*root;
  NodeUser *current=*root;
  
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