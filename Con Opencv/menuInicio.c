/**********************************************************************************************************************************/

/**
 * \file 	menuInicio.c
 * \brief 	Este modulo contiene las funciones del menu de inicio
 * \author 	Tomás Ordóñez, Juan Francisco Reiszer, Santiago Ozan 
 * \date 	20/12/2016
 */

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "Cliente.h"
/***********************************************************************************************************************************
*** FUNCIONES DEL MODULO
**********************************************************************************************************************************/

/**
	@fn  		int Ingresar (usu *dir,IplImage* imagenFondo, char* nombreVentana,int i)
	@brief 		Carga los datos de log in del usuario que quiere ingresar
 	@author 	Juan Francisco Reiszer, Tomas Ordoñez, Santiago Ozan
 	@date 		20/12/16
 	@param [in] 	dir: Direccion del buffer a llenar
 	@param [in] 	imagenFondo: puntero a imagen de fondo
 	@param [in] 	nombreVentana: Direccion de comienzo del nombre de la ventana
 	@param [in] 	i: Variable que indica si hubo un error cuando se quiso ingresar anteriormente
 	@return 	0 por exito
*/

int Ingresar (usu *dir,IplImage* imagenFondo, char* nombreVentana,int i)
{
  cvZero(imagenFondo);
  
  cvMostrarTitulo(imagenFondo);
  crearCampodeTexto(imagenFondo);
  
  if(i==-1) errorInicio(imagenFondo);
  
  //Mostramos la imagen
  cvShowImage (nombreVentana,imagenFondo);
  
  leerCampodeTexto(nombreVentana, imagenFondo, dir);
  
  dir->id=1;

  return 0;
}

/**
	@fn  			int Registro (usu *)
	@brief 			Carga los datos de del usuario que quiere registrarse
 	@author 		Juan Francisco Reiszer, Tomas Ordoñez, Santiago Ozan
 	@date 			20/12/16
 	@param [in] Datos:	Direccion del buffer a llenar  
 	@return 		0 por exito
*/

int Registro (usu *Datos)
{
  char Aux[8];
  int a=0,i;
  
  system("clear");
  do
  {
    a=0;
    printf("Ingrese Nombre: ");
    scanf("%s",Datos->Nombre);
    if(strlen(Datos->Nombre)>20)
    {
	a=1;
	system("clear");
	printf("ERROR: Nombre demasiado Largo\n\n");
    }
    if(a!=1)
    {
      printf("Ingrese edad: ");
      scanf("%s",Datos->Edad);
    
      if(strlen(Datos->Edad)>2)
      {
	a=1;
	system("clear");
	printf("ERROR: Edad muy Grande\n\n");
      } 
      //Verificamos que sea un Numero
      for(i=0;i<2;i++)
      {
	if(((Datos->Edad)[i]<'0'||(Datos->Edad)[i]>'9')&&(Datos->Edad)[i]!='\0')
	{
	  a=1;
	  system("clear");
	  printf("ERROR: Ingrese un Numero\n\n");
	  break;
	}
      }
    }
    if(a!=1)
    {
      printf("Ingrese e-mail: ");
      scanf("%s",Datos->email);
      
      printf("Ingrese Usuario: ");
      scanf("%s",Datos->Usuario);
      
      if(strlen(Datos->Usuario)>20)
      {
	a=1;
	system("clear");
	printf("ERROR: Nombre de Usuario demasiado Largo\n\n");
      }
    }
    if(a!=1)
    {
      printf("Ingrese Contraseña: ");
      scanf("%s",Datos->Contra);
    
      if(strlen(Datos->Contra)>8)
      {
	a=1;
	system("clear");
	printf("ERROR: Contraseña debe tener Maximo 8 caracteres\n\n");
      }
    }
    if(a!=1)
    {
      printf("Repita Contraseña: ");
      scanf("%s",Aux);
      system("clear");
      //Verificamos que las contraseñas coincidan
      a=strcmp(Datos->Contra,Aux);
      if(a)
	printf("ERROR: Contraseñas diferentes\n\n");
      Datos->id=2;
    }
  }while(a);
  return 0;
}