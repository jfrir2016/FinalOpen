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
#include <pthread.h>
#include <errno.h>

/***********************************************************************************************************************************
*** DEFINES
**********************************************************************************************************************************/

#define FUSU "Usuarios"
#define FPUB "Posts"
#define FERROR "errorFile"

#define PORT 43210
#define CTAM 241
#define BUFFER 15
#define MEMSET 10

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
}USU;

typedef struct UserNode		//Usen esto para manejar usuarios en la lista
{
  struct User user;
  struct UserNode *nxt;
}NodeUser;

typedef struct Post
{
  int id;
  int idU;			//Id del usuario que la creo
  char titulo[100];
  char contenido[500];
  struct CommentNode *root;
}POST;

typedef struct PostNode		//Para manejar publicaciones en la lista
{
  struct Post post;
  struct PostNode *nxt;
}NodePost;

typedef struct Comentario
{
  int id;
  int idP;			//Id de la publicacion a la que pertenece
  int idU;			//Id del usuario que lo creo
  char contenido[241];
}COMMT;

typedef struct CommentNode
{
  struct Comentario comentario;
  struct CommentNode *nxt;
}NodeComment;

typedef struct Root
{
  NodeUser *Uroot;
  NodePost *Proot;
  int sock;
  FILE *fd;
}ROOT;

/***********************************************************************************************************************************
*** PROTOTIPOS DE FUNCIONES
**********************************************************************************************************************************/

int GuardarUsuarios (NodeUser *, char *);

int GuardarPost (NodePost *, char *);

int GuardarComents (NodePost *);

int LoadUsuarios (NodeUser**, char *);

int LoadPubli (NodePost **,char *);

int LoadComments (NodePost **);

void sig_finish (int);

int AgregarNodoUsuario(USU*, NodeUser**);

void AgregarNodoPub(POST*, NodePost**);

int BorrarNodoPub(int, NodePost**);

int BorrarNodoUsuario(int, NodeUser**);
 
int BorrarComentario(int, NodeComment**);

int Check (USU **,NodeUser *);

POST* BuscoPost (char*, NodePost*);

int Posteo (int, NodePost**,int);

int AgregarPost (int, NodePost**,int);

int BorrarPost (int, NodePost**,int);

int BorrarCom (int, POST *,int);

int BajaUsu (int, NodeUser**,int);

void* nuevo_thread (void *);