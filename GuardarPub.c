#include "TPO.h"
//guarda los post en un archivo
int GuardarPost (NodePost *primero, char *archivo)
{
  FILE* fd;
  NodePost* aux;
  POST *datos;
  
  if((fd=fopen(archivo,"w"))==NULL)//abre el archivo en modo escritura ¡Creo que habria q abrirlo con "a", ya q escribe al final!
    return 1;				//		No escribe al final, plancha y escribe de vuelta!
  for(aux=primero;aux!=NULL;)
  {
    datos=&(aux->post);
    fwrite(datos,sizeof(POST),1,fd);
    primero=aux;
    aux=aux->nxt;
    free(primero);
  }
  fclose(fd);
  return 0;
}
