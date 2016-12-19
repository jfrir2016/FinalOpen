#include "Cliente.h"
void leerCampodeTexto(char* nombreVentana, IplImage* imagenFondo,usu *dir)
{
  int i = 0;
  for (i=0; i<20; i++) { dir->Usuario[i]='\0'; } //inicializo en null
  int puntero_lector = 0;
  
  // Definimos desde donde y hasta donde va a ir el texto
  int textoDesdeDonde_X = ANCHO *0.6+10;
  int textoDesdeDonde_Y = ALTO *0.25+30;
  
  //Circulo que indica que estamos en usuario
  cvCircle( imagenFondo, cvPoint(ANCHO *0.6+ REC_TAM_X+70 , textoDesdeDonde_Y), 10, cvScalar (208,194,0,0), -1, 8, 0 );
  cvShowImage(nombreVentana,imagenFondo);
  
  char aux = cvWaitKey(0); //Toma la primer letra
  
  CvFont Font;
  cvInitFont(&Font,CV_FONT_HERSHEY_SIMPLEX, 0.7, 0.8, 0, 2,8);
  
  //Leemos Usuario
  while (aux != '\n') //si no es un enter se llena el campo
  {
    //Aca vamos a entrar si escribio una letra
    if (aux > 31 && aux < 127)
    {
      if (strlen(dir->Usuario)<19)
      {
	dir->Usuario[puntero_lector]=aux;
	cvPutText(imagenFondo,dir->Usuario,cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y), &Font, cvScalar (255,255,255,0));
	cvShowImage(nombreVentana,imagenFondo);
	puntero_lector++;
      }
   }

   //Aca vamos a entrar si quiere borrar algo
   if ((aux==8 || aux==127) && puntero_lector)
   {
     cvPutText(imagenFondo,dir->Usuario,cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y), &Font, cvScalar (0,0,0,0));
     dir->Usuario[puntero_lector]=(char)0;
     puntero_lector--;
     dir->Usuario[puntero_lector]=(char)0;
     cvPutText(imagenFondo,dir->Usuario,cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y), &Font, cvScalar (255,255,255,0));
     cvShowImage(nombreVentana,imagenFondo);
   }
   
   aux = cvWaitKey(0);
   }
   
   for (i=0; i<8; i++) { dir->Contra[i]='\0'; } //inicializo en null
   
   //Circulo que indica que estamos en password
   cvCircle( imagenFondo, cvPoint(ANCHO *0.6+ REC_TAM_X+70 , textoDesdeDonde_Y), 10, cvScalar (0,0,0,0), -1, 8, 0 );
   cvCircle(imagenFondo, cvPoint (ANCHO *0.6+ REC_TAM_X+70,textoDesdeDonde_Y+2*REC_TAM_Y), 10, cvScalar (208,194,0,0), -1, 8, 0 );
   cvShowImage(nombreVentana,imagenFondo);

   aux=cvWaitKey(0);
   puntero_lector=0;
   //Leemos password
   while (aux != '\n') //si no es enter entra
   {
     //Aca vamos a entrar si escribio una letra
     if (aux > 31 && aux < 127)
     {
       if (strlen(dir->Contra)<7)
       {
	 dir->Contra[puntero_lector]=aux;
	 cvPutText(imagenFondo,dir->Contra,cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y+2*REC_TAM_Y), &Font, cvScalar (255,255,255,0));
	 cvShowImage(nombreVentana,imagenFondo);
	 puntero_lector++;
	 
       }
     }

     //Aca vamos a entrar si quiere borrar algo
     if ((aux==8 || aux==127) && puntero_lector)
     {
       cvPutText(imagenFondo,dir->Contra,cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y+2*REC_TAM_Y), &Font, cvScalar (0,0,0,0));
       dir->Contra[puntero_lector]=(char)0;
       puntero_lector--;
       dir->Contra[puntero_lector]=(char)0;
       cvPutText(imagenFondo,dir->Contra,cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y+2*REC_TAM_Y), &Font, cvScalar (255,255,255,0));
       cvShowImage(nombreVentana,imagenFondo);
     }
     aux = cvWaitKey(0);
   }
   return;
}