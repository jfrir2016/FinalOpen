/**********************************************************************************************************************************/
/** 
 * @details		Proyecto: TPO, Foro de Discusión Académico
 * @file		server.c
 * @brief		Main del programa Servidor
 * @date		20/12/16
 * @author		Juan Francisco Reiszer, Tomas Ordoñez, Santiago Ozan
 *
*/
/**********************************************************************************************************************************
 *** INCLUDES
***********************************************************************************************************************************/
#include "TPO.h"
/**********************************************************************************************************************************/

int Flag=0;

int main (void)
{

  int sockfd, new_fd, size;
  FILE *ffd;
  ROOT roots; 
  pthread_t thread;
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;
  
  //Creo archivo de seguimiento, guardo descriptor en la estructura roots
  ffd=fopen(FERROR,"a");
  roots.fd=ffd;
  
  //Creo el socket y guardo su descriptor
  if((sockfd= socket(AF_INET, SOCK_STREAM, 0))==-1)
  {
      fprintf(ffd,"Socket: %s\n",strerror(errno));
      exit(1);
  }
  //Ingreso y cargo con bind la info del server
  server_addr.sin_family= AF_INET;
  server_addr.sin_port= htons(PORT);
  server_addr.sin_addr.s_addr= INADDR_ANY;
  memset(&(server_addr.sin_zero),'\0',8);
  
  roots.Uroot=NULL;
  roots.Proot=NULL;
  //Configuro la señal SIGINT del Ctrl+C a la funcion sig_finish
  if(signal(SIGINT,sig_finish) == SIG_ERR)
  {
    fprintf(ffd,"Signal: %s\n",strerror(errno));
    exit(1);
  }
  
  if((bind(sockfd,(struct sockaddr *)&server_addr, sizeof(struct sockaddr)))==-1)
  {
    fprintf(ffd,"Bind: %s\n",strerror(errno));
    exit(1);
  }
  
  //Levanto todas las listas
  if(LoadUsuarios (&(roots.Uroot),FUSU))
    fprintf(ffd,"Error Cargar Lista Usuarios\n");
  if(LoadPubli (&(roots.Proot),FPUB))
    fprintf(ffd,"Error Cargar Lista Publicaciones\n");
  if(LoadComments (&(roots.Proot)))
    fprintf(ffd,"Error Cargar Lista Comentarios\n");
    
  //Configuro la cola de espera
  if(listen(sockfd,MEMSET)==-1)
  {
    fprintf(ffd,"Listen: %s\n",strerror(errno));
    exit(1);
  }
  
  while(!Flag)
  {
    size = sizeof(struct sockaddr_in);
    //Espero que se conecte un cliente
    if((new_fd=accept(sockfd,(struct sockaddr *)&client_addr,(socklen_t*)&size))==-1)
    {
	fprintf(ffd,"Accept: %s\n",strerror(errno));
	exit (1);
    }
    
    fprintf(ffd,"Se recibio conexion de: %s\n", inet_ntoa(client_addr.sin_addr));
    fflush(stdout);
    
    roots.sock=new_fd;
    //Creo un thread para atender al cliente conectado
    pthread_create(&thread, NULL, &nuevo_thread, (void*)&roots);
  }
  //Espero que finalice el thread creado
  if(pthread_join(thread, NULL)) 
  {
    fprintf(ffd, "Error joining thread\n");
    exit (1);
  }
  close(sockfd);
  //Guardo las listas
  if(GuardarUsuarios(roots.Uroot,FUSU))
    fprintf(ffd,"Error al Guardar\n");
  if(GuardarComents(roots.Proot))
    fprintf(ffd,"Error al Guardar\n");
  if(GuardarPost(roots.Proot,FPUB))
    fprintf(ffd,"Error al Guardar\n");
  fprintf(ffd,"Servidor Finalizado con exito\n");
  //Salir
  exit (0);
}


//Thread que atiende al cliente conectado
void* nuevo_thread (void *rs)
{
  int id, sel,new_fd;
  int (*Menu[])(int,NodePost**,int)={Posteo,AgregarPost,BorrarPost};
  USU *buff;
  FILE *fd;
  ROOT *rt_p;
  
  rt_p=(ROOT *)rs;
  new_fd=rt_p->sock;
  fd=rt_p->fd;

  buff=(USU*)malloc(sizeof(USU));
  do
  {
    //Recibe seleccion de Menu de Inicio
    if((recv(new_fd,buff,sizeof(USU),0))==-1)
    {
      fprintf(fd,"Recv: %s\n",strerror(errno));
      exit(1);
    }
    if(buff->id==1)
      //Logueo
      id=Check(&buff,rt_p->Uroot);
    else if(buff->id==2)
      //Registro
      id=AgregarNodoUsuario(buff,&(rt_p->Uroot));
      else
	//Salir
	id=0;
    //Envia respuesta
    if((send(new_fd,&id,sizeof(int),0))==-1)
    {
      fprintf(fd,"Send: %s\n",strerror(errno));
      exit(1);
    }
  }while(id<0);
	
  if(id!=0)
  {
    do
    {
      //Recivo seleccion
      if((recv(new_fd,&sel,sizeof(int),0))==-1)
      {
	fprintf(fd,"Recv: %s\n",strerror(errno));
	exit(1);
      }
      sel--;
      if(sel<3)
	Menu[sel](new_fd,&(rt_p->Proot),id);
	// case 1: Posteo
	// case 2: AgregarPost
	// case 3: BorrarPost
    }while(sel<3);
    if(sel==3)
      // case 4: BajaUsu
      BajaUsu (new_fd,&(rt_p->Uroot),id);
  }
  // case 5: Exit
  sleep(1);  
  fprintf(fd,"Finalizo el thread\n");
  close(rt_p->sock);
  pthread_exit(0);
}