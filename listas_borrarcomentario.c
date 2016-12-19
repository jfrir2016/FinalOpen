#include "TPO.h"

int BorrarComentario(int id, NodeComment **root)
{
  NodeComment *anterior=*root;
  NodeComment *current=*root;
  
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