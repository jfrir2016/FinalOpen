#include "TPO.h"
//revisa si el usuario ingresado esta registrado y si es correcto
int Check (USU **cli,NodeUser *primo)
{
  int e;
  NodeUser *a;
  
  a=primo;
		
  if(a==NULL)	//si la lista de usuarios esta vacia sale por error
    return -1;
  
		//compara los campos de usuario hasta hallar coincidencia o llegar al NULL de la lista
  e=strcmp((*cli)->Usuario,a->user.Usuario);
  while(e!=0&&a->nxt!=NULL)
  {
    a=a->nxt;
    e=strcmp((*cli)->Usuario,a->user.Usuario);
  }
  if(e)		 //si llego al NULL y no encontro coincidencia sale por error
    return -1;
  
  if(!strcmp((*cli)->Contra,a->user.Contra))//compara contraseñas y retorna el idUser
    return a->user.id;
  
  return -1; 	//si contraseñas no coinciden sale por error
}

    