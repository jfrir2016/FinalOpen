#include "Cliente.h"
void cvLeerCamposPost(IplImage* imagenFondo,char* nombreVentana,post* p)
{
  int i=0, ultimo=0,j;
  int puntero_lector = 0;
  char buffer[7][170];
  
  CvSize text_size;
  int baseline;
  
  for(i=0;i<5;i++)
  {
    for(j=0;j<100;j++)
      buffer[i][j]='\0';
  }
  
  for (i=0; i<100; i++) { p->titulo[i]='\0'; } //inicializo en null
  
  // Definimos desde donde y hasta donde va a ir el texto
  int textoDesdeDonde_X = ANCHO *0.2+5;
  int textoDesdeDonde_Y = ALTO *0.4+30;
  int textoHastaDonde_X = ANCHO *0.9;
  //Circulo que indica donde estamos
  cvCircle( imagenFondo, cvPoint(ANCHO *0.7+ REC_TAM_X+70 , textoDesdeDonde_Y), 10, cvScalar (208,194,0,0), -1, 8, 0 );
  cvShowImage(nombreVentana,imagenFondo);
  
  char aux = cvWaitKey(0); //Toma la primer letra
  
  CvFont font;
  cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX, 0.5, 0.6, 0, 2,8);
  
  //Titulo
  while (aux != '\n') //si no es un enter se llena el campo
  {
    //Aca vamos a entrar si escribio una letra
    if (aux > 31 && aux < 127)
    {
      if (strlen(p->titulo)<99)
      {
	p->titulo[puntero_lector]=aux;
	cvPutText(imagenFondo,p->titulo,cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y), &font, cvScalar (255,255,255,0));
	cvShowImage(nombreVentana,imagenFondo);
	puntero_lector++;
      }
   }

   //Aca vamos a entrar si quiere borrar algo
   if ((aux==8 || aux==127) && puntero_lector)
   {
     cvPutText(imagenFondo,p->titulo,cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y), &font, cvScalar (0,0,0,0));
     p->titulo[puntero_lector]=(char)0;
     puntero_lector--;
     p->titulo[puntero_lector]=(char)0;
     cvPutText(imagenFondo,p->titulo,cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y), &font, cvScalar (255,255,255,0));
     cvShowImage(nombreVentana,imagenFondo);
   }
   
   aux = cvWaitKey(0);
   }
  
  //************************ 
   
   for (i=0; i<500; i++) { p->contenido[i]='\0'; } //inicializo en null

   //Circulo que indica que estamos en contenido
   cvCircle( imagenFondo, cvPoint(ANCHO *0.7+ REC_TAM_X+70 , textoDesdeDonde_Y), 10, cvScalar (0,0,0,0), -1, 8, 0 );
   cvCircle(imagenFondo, cvPoint (ANCHO *0.7+ REC_TAM_X+70,textoDesdeDonde_Y+2.5*REC_TAM_Y), 10, cvScalar (208,194,0,0), -1, 8, 0 );
   cvShowImage(nombreVentana,imagenFondo);
   
   aux=0;
   j=0;
   
   for(i=0;i<7 && aux!='\n' && i>=0;i++)
   {
     aux=cvWaitKey(0);
     puntero_lector=0;
     
     while (aux != '\n' && i>=0) //si no es enter entra
     {
       //Aca vamos a entrar si escribio una letra
       if (aux > 31 && aux < 127)
       {
	 cvGetTextSize(buffer[i], &font, &text_size, &baseline);
	 
	 if ((textoHastaDonde_X-textoDesdeDonde_X)>text_size.width)
	 {
	   buffer[i][puntero_lector]=aux;
	   cvPutText(imagenFondo,buffer[i],cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y+2.5*REC_TAM_Y+(REC_TAM_Y/2)*i), &font, cvScalar (255,255,255,0));
	   cvShowImage(nombreVentana,imagenFondo);
	   puntero_lector++;
	 }
	 
	 else
	 {
	   buffer[i][puntero_lector]=aux;
	   cvPutText(imagenFondo,buffer[i],cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y+2.5*REC_TAM_Y+(REC_TAM_Y/2)*i), &font, cvScalar (255,255,255,0));
	   cvShowImage(nombreVentana,imagenFondo);

	   ultimo=puntero_lector;
	//   j+=puntero_lector;
	   i++;
	   
	   puntero_lector=0;
	   if(i>=7)
	   {
	     for(j=0;j<7;j++)
	       strcat(p->contenido,buffer[j]);
	     return;
	   }
	 }
       }
     //  strcpy(p->contenido+j,buffer[i]);
       //Aca vamos a entrar si quiere borrar algo
       if (aux==8 || aux==127)
       {
	 if(i==0 && puntero_lector==0){}
	 
	 else
	 {
	   cvPutText(imagenFondo,buffer[i],cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y+2.5*REC_TAM_Y+(REC_TAM_Y/2)*i), &font, cvScalar (0,0,0,0));
	   
	   buffer[i][puntero_lector]=(char)0;
	   
	   if(puntero_lector==0)
	   {
	     cvPutText(imagenFondo,buffer[i],cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y+2.5*REC_TAM_Y+(REC_TAM_Y/2)*i), &font, cvScalar (255,255,255,0));
	     puntero_lector=ultimo;
	     
	     i--;
	     cvPutText(imagenFondo,buffer[i],cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y+2.5*REC_TAM_Y+(REC_TAM_Y/2)*i), &font, cvScalar (255,255,255,0));
	     cvShowImage(nombreVentana,imagenFondo);
	   }
	   
	   else
	   {
	     puntero_lector--;
	     buffer[i][puntero_lector]=(char)0;
	     cvPutText(imagenFondo,buffer[i],cvPoint(textoDesdeDonde_X,textoDesdeDonde_Y+2.5*REC_TAM_Y+(REC_TAM_Y/2)*i), &font, cvScalar (255,255,255,0));
	     cvShowImage(nombreVentana,imagenFondo);
	   }
	 }
       }
       aux = cvWaitKey(0);
       
     }
     
   }
   if(aux=='\n')
   {
     for(j=0;j<7;j++)
       strcat(p->contenido,buffer[j]);
     return;
   }
}