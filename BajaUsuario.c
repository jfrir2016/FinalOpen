#include "TPO.h"

int BajaUsu (int fd, NodeUser **URoot,int id)
{
  int a;
  if(id==1)
  {
    a=1;
    if((send(fd,&a,sizeof(int),0))==-1)	//Envia 1 por error
    {
      perror("Send");
      return 1;
    }
    return 0;
  }
  if(!(a=BorrarNodoUsuario(id,URoot)))
  {
    if((send(fd,&a,sizeof(int),0))==-1)	//Envia 0 por correcto
    {
      perror("Send");
      return 1;
    }
  }
  else
  {
    if((send(fd,&a,sizeof(int),0))==-1)	//Envia 1 por error
    {
      perror("Send");
      return 1;
    }
  }
  return 0;
}
    
      
  