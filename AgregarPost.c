#include "TPO.h"

int AgregarPost (int fd, NodePost **PRoot, int id)
{
  POST *Aux;
  
  Aux=(POST *)malloc(sizeof(POST));
  
  if((recv(fd,Aux,sizeof(POST),0))==-1)	//Recivo Publicacion
  {
    perror("Recv");
    exit(1);
  }
  Aux->idU=id;
  
  AgregarNodoPub(Aux,PRoot);
  
  return 0;
}