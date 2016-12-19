#include "TPO.h"

int GuardarComents (NodePost *primero)
{
  FILE* fd;
  NodeComment *aux, *first;
  NodePost* read;
  COMMT *datos;
  char Archivo[8];
  
  for(read=primero;read!=NULL;read=read->nxt)
  {
    sprintf(Archivo,"xcF%d",read->post.id);
    
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

  