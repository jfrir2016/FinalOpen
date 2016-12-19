#include "TPO.h"

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