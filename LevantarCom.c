#include "TPO.h"

int LoadComments (NodePost **primero)
{
  FILE *fd;
  NodeComment *aux,*first,*paux;;
  NodePost *read;
  COMMT *datos;
  char Archivo[8];
  
  if(*primero==NULL)
    return 0;
  for(read=*primero;read!=NULL;read=read->nxt)
  {
    sprintf(Archivo,"xcF%d",read->post.id);
    
    if((fd=fopen(Archivo,"r"))!=NULL)
    {
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
      read->post.root=first;
      fclose(fd);
    }
  }
  return 0; 
}
