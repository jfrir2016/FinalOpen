#include "TPO.h"

int LoadUsuarios (NodeUser **primero,char *archivo)
{
  FILE *fd;
  NodeUser *aux,*paux;
  USU *datos;
  
  if((fd=fopen(archivo,"a+"))==NULL)
    return 1;
  aux=(NodeUser*)malloc(sizeof(NodeUser));
  datos=&(aux->user);
  fread(datos,sizeof(USU),1,fd);
  if(feof(fd))
  {
    free(aux);
    return 0;
  }
  *primero=aux;
  paux=aux;
  while(!feof(fd))
  {
    aux->nxt=(NodeUser*)malloc(sizeof(NodeUser));
    aux=aux->nxt;
    datos=&(aux->user);
    fread(datos,sizeof(USU),1,fd);
  }
  fclose(fd);
  for(;paux->nxt!=aux;paux=paux->nxt);
  free(aux);
  paux->nxt=NULL;
  return 0;
}
