#include "TPO.h"

int LoadPubli (NodePost **primero,char *archivo)
{
  FILE *fd;
  NodePost *aux,*paux;
  POST *datos;
  
  if((fd=fopen(archivo,"a+"))==NULL)
    return 1;
  aux=(NodePost*)malloc(sizeof(NodePost));
  datos=&(aux->post);
  fread(datos,sizeof(POST),1,fd);
  aux->post.root=NULL;
  if(feof(fd))
  {
    free(aux);
    return 0;
  }
  *primero=aux;
  paux=aux;
  while(!feof(fd))
  {
    aux->nxt=(NodePost*)malloc(sizeof(NodePost));
    aux=aux->nxt;
    datos=&(aux->post);
    fread(datos,sizeof(POST),1,fd);
    aux->post.root=NULL;
  }
  fclose(fd);
  for(;paux->nxt!=aux;paux=paux->nxt);
  free(aux);
  paux->nxt=NULL;
  return 0; 
}

  
  