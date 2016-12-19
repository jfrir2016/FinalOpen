#include "Cliente.h"

int Registro (usu *Datos,IplImage* imagenFondo, char* nombreVentana,int j)
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
      a=strcmp(Datos->Contra,Aux);
      if(a)
	printf("ERROR: Contraseñas diferentes\n\n");
      //sleep(3);
      Datos->id=2;
    }
  }while(a);
  
  
  return 0;
}
  