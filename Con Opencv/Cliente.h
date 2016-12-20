/**********************************************************************************************************************************/
/** 
 * @details		Proyecto: TPO, Foro de Discusión Académico
 * @file		Cliente.c
 * @brief		Archivo de cabecera del programa cliente
 * @date		20/12/16
 * @author		Juan Francisco Reiszer, Tomas Ordoñez, Santiago Ozan
 *
*/
/***********************************************************************************************************************************/
/***********************************************************************************************************************************
*** INCLUDES
**********************************************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <netdb.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

/***********************************************************************************************************************************
*** DEFINES
**********************************************************************************************************************************/

#define ANCHO 1000
#define ALTO 700
#define REC_TAM_Y 25*2
#define REC_TAM_X 100*2

#define BUFFER 100
#define CTAM 241
#define PORT 43311
#define IP "192.168.0.7"

/***********************************************************************************************************************************
*** TIPO DE DATOS
**********************************************************************************************************************************/

typedef struct User
{
  int id;
  char Nombre[20];
  char Edad[2];
  char Usuario[20];
  char Contra[8];
  char email[35];
}usu;

typedef struct Post
{
  int id;
  int idU;			//Id del usuario que la creo
  char titulo[100];
  char contenido[500];
  struct CommentNode *root;
}post;

typedef struct Comentario
{
  int id;
  int idP;			//Id de la publicacion a la que pertenece
  int idU;			//Id del usuario que lo creo
  char contenido[CTAM];
}com;

/***********************************************************************************************************************************
*** PROTOTIPOS DE FUNCIONES
**********************************************************************************************************************************/

int Registro (usu*,IplImage*, char*, int);

int Ingresar (usu*,IplImage*, char*, int);

int interfaz1 (IplImage*, char*);

void menuInicio (IplImage*);

void leerCampodeTexto (char*, IplImage*,usu*);

void crearCampodeTexto (IplImage*);

void errorInicio(IplImage*);

void cvMostrarTitulo (IplImage*);

int menuPrincipal(IplImage*,char*, int);

int cvListarPost(IplImage*, char*,int);

void cvResultadoBorrarPub(IplImage*, int);

int cvBajaUsuario(IplImage*, char*, int);

void cvLeerCamposPost(IplImage*,char*,post*);

void cvCrearCamposPost(IplImage*);

void cvCrearPublicacion (IplImage* , char* , post *);

void cvSalir(IplImage* , char*);
