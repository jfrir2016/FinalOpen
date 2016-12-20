/**********************************************************************************************************************************/

/**
 * \file 	usuFuns.c
 * \brief 	Este modulo contiene las funciones de manejo de usuarios
 * \author 	Tomás Ordóñez, Juan Francisco Reiszer, Santiago Ozan 
 * \date 	20/12/2016
 */

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "TPO.h"
/***********************************************************************************************************************************
*** FUNCIONES DEL MODULO
**********************************************************************************************************************************/

/**
	@fn  			int BajaUsu (int fd, Node **PRoot, int id)
	@brief 			Da de baja un usuario, eliminandolo de la lista
 	@author 		Juan Francisco Reiszer, Tomas Ordoñez, Santiago Ozan
 	@date 			20/12/16
 	@param [in] fd: 	Descriptor del socket 
 	@param [in] PRoot:	Direccion del puntero que contiene la direccion de comienzo de la lista de Usuarios
 	@param [in] id: 	Id del usuario
 	@return 		0 por exito, 1 por error
*/

int BajaUsu (int fd, NodeUser **URoot,int id)
{
  int a;
  if(id==1)
  {
    a=1;
    //Envia 1 por error
    if((send(fd,&a,sizeof(int),0))==-1)
    {
      perror("Send");
      return 1;
    }
    return 0;
  }
  if(!(a=BorrarNodoUsuario(id,URoot)))
  {
    //Envia 0 por correcto
    if((send(fd,&a,sizeof(int),0))==-1)
    {
      perror("Send");
      return 1;
    }
  }
  else
  {
    //Envia 1 por error 
    if((send(fd,&a,sizeof(int),0))==-1)
    {
      perror("Send");
      return 1;
    }
  }
  return 0;
}

/**
	@fn  			int Check (USU **cli, NodeUser *primo,)
	@brief 			Revisa si el usuario ingresado esta registrado y si es correcto
 	@author 		Juan Francisco Reiszer, Tomas Ordoñez, Santiago Ozan
 	@date 			20/12/16
 	@param [in] cli: 	Direccion de la estructura USU con los datos del usuario que quiere ingresar 
 	@param [in] primo:	Direccion de comienzo de la lista de Usuarios
 	@return 		-1 por error, id del usuario registrado en caso de exito
*/


int Check (USU **cli,NodeUser *primo)
{
  int e;
  NodeUser *a;
  
  a=primo;
  //Si la lista de usuarios esta vacia sale por error	
  if(a==NULL)	
    return -1;
  
  //Compara los campos de usuario hasta hallar coincidencia o llegar al NULL de la lista
  e=strcmp((*cli)->Usuario,a->user.Usuario);
  while(e!=0&&a->nxt!=NULL)
  {
    a=a->nxt;
    e=strcmp((*cli)->Usuario,a->user.Usuario);
  }
  //Si llego al NULL y no encontro coincidencia sale por error
  if(e)		 
    return -1;
  //Compara contraseñas y retorna el idUser
  if(!strcmp((*cli)->Contra,a->user.Contra))
    return a->user.id;
  //Si contraseñas no coinciden sale por error
  return -1;
}

    