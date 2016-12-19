#include "TPO.h"
//sirve para guardar en un archivo la info de usuarios y liberar memoria de lista de users
int GuardarUsuarios (NodeUser *primero, char *archivo)
{
  FILE* fd;
  NodeUser* aux;
  USU *datos;
  
  if((fd=fopen(archivo,"w"))==NULL)		//abre el archivo en modo escritura
    return 1;
  for(aux=primero;aux!=NULL;)
  {
    datos=&(aux->user);
    fwrite(datos,sizeof(USU),1,fd);
    primero=aux;
    aux=aux->nxt;
    free(primero);				//libera memoria ocupada x el  ¿nodo
  }
  fclose(fd);
  return 0;
}
