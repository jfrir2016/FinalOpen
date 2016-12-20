#include "Cliente.h"
#define REC_X 50
#define REC_Y 50
//#define REC_TAM_Y 25
//#define REC_TAM_X 100
#define TAM_STRING 100
#define TITULO_X 140 
#define TITULO_Y 30 

void crearBoton(IplImage*);
void callbackBoton(int, int, int, int, void*);

int interfaz1 (IplImage* imagenFondo,char* nombreVentana)
{
  int a=0;
  //int b;
  
  //Limpiamos la imagen
  cvZero(imagenFondo);
  
  //Creamos el menu
  menuInicio(imagenFondo);
  
  //Creamos nuestro boton
  crearBoton(imagenFondo);
  
  //Mostramos la imagen
  cvShowImage (nombreVentana,imagenFondo);
 
    cvSetMouseCallback("CampoDeTexto", callbackBoton, &a);
  
  cvWaitKey(0);
  cvReleaseImage(&imagenFondo);
  /*
  a = cvWaitKey(0);
  a=a-'0';
  b=a;*/
  return a;
}

void crearBoton(IplImage* imagenFondo)
{
	CvFont Font;

	int rectanguloDesdeDonde_X = REC_X;
	int rectanguloDesdeDonde_Y = REC_Y;
	int rectanguloHastaDonde_X = rectanguloDesdeDonde_X + REC_TAM_X;
	int rectanguloHastaDonde_Y = rectanguloDesdeDonde_Y + REC_TAM_Y;
	int tituloDesde_X = TITULO_X;
	int tituloDesde_Y = TITULO_Y;

	//Incializamos las fuentes
	cvInitFont(&Font,CV_FONT_HERSHEY_SIMPLEX, 0.4, 0.5, 0, 1,8);

	cvPutText (imagenFondo,"Bienvenido al Foro",cvPoint(tituloDesde_X, tituloDesde_Y), &Font, cvScalar (255,255,255,0));
	
	cvRectangle (imagenFondo,
				 cvPoint (rectanguloDesdeDonde_X, rectanguloDesdeDonde_Y),
				 cvPoint (rectanguloHastaDonde_X, rectanguloHastaDonde_Y),
				 cvScalar (255,255,255,0),1,8,0);

	cvPutText (imagenFondo,"Ingresar",cvPoint(rectanguloDesdeDonde_X + 20, rectanguloDesdeDonde_Y + 16), &Font, cvScalar (255,255,255,0));
	
	cvRectangle (imagenFondo,
				 cvPoint (rectanguloDesdeDonde_X + 200, rectanguloDesdeDonde_Y),
				 cvPoint (rectanguloHastaDonde_X + 200, rectanguloHastaDonde_Y),
				 cvScalar (255,255,255,0),1,8,0);

	cvPutText (imagenFondo,"Registrarse",cvPoint(rectanguloDesdeDonde_X + 210, rectanguloDesdeDonde_Y + 16), &Font, cvScalar (255,255,255,0));
}

void callbackBoton(int evento, int x, int y,int flags, void* sth)
{
	int rectanguloDesdeDonde_X = REC_X;
	int rectanguloDesdeDonde_Y = REC_Y;
	int rectanguloHastaDonde_X = rectanguloDesdeDonde_X + REC_TAM_X;
	int rectanguloHastaDonde_Y = rectanguloDesdeDonde_Y + REC_TAM_Y;
	int *p;
	p=(int *)sth;
	
	if(evento == CV_EVENT_LBUTTONDOWN && x > rectanguloDesdeDonde_X && y > rectanguloDesdeDonde_Y && x < rectanguloHastaDonde_X && y < rectanguloHastaDonde_Y)
	  *p=1;
	if(evento == CV_EVENT_LBUTTONDOWN && x > (rectanguloDesdeDonde_X+200) && y > rectanguloDesdeDonde_Y && x < (rectanguloHastaDonde_X+200) && y < rectanguloHastaDonde_Y)
	  *p=2;
}