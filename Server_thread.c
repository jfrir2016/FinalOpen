//	SERVER

#include "TPO.h"

int Flag=0;

int main (void)
{

  int sockfd, new_fd, size;
  ROOT roots; 
  pthread_t thread;
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;
  
  // Creo el socket y guardo su descriptor; exit si hubo error
  if((sockfd= socket(AF_INET, SOCK_STREAM, 0))==-1)
  {
      perror("Socket");
      exit(1);
  }
  //ingreso y cargo con bind la info del server
  server_addr.sin_family= AF_INET;
  server_addr.sin_port= htons(PORT);
  server_addr.sin_addr.s_addr= INADDR_ANY;
  memset(&(server_addr.sin_zero),'\0',8);
  
  roots.Uroot=NULL;
  roots.Proot=NULL;
    
  if(signal(SIGINT,sig_finish) == SIG_ERR)
  {
    perror("Signal");
    exit(1);
  }
  
	
  if((bind(sockfd,(struct sockaddr *)&server_addr, sizeof(struct sockaddr)))==-1)
  {
    perror("Bind");
    exit(1);
  }
  
	if(LoadUsuarios (&(roots.Uroot),FUSU))					//Levanto todas las listas
		printf("Error Cargar Lista Usuarios\n");
	if(LoadPubli (&(roots.Proot),FPUB))
		printf("Error Cargar Lista Publicaciones\n");
	if(LoadComments (&(roots.Proot)))
		printf("Error Cargar Lista Comentarios\n");
    
  if(listen(sockfd,MEMSET)==-1)
  {
    perror("Listen");
    exit(1);
  }
  
  while(!Flag)
  {
    size = sizeof(struct sockaddr_in);
      
    if((new_fd=accept(sockfd,(struct sockaddr *)&client_addr,(socklen_t*)&size))==-1)
    {
	perror("Accept");
	exit (1);
    }
    
    printf("Se recibio conexion de: %s\n", inet_ntoa(client_addr.sin_addr));
    fflush(stdout);
    
    roots.sock=new_fd;
    
    pthread_create(&thread, NULL, &nuevo_thread, (void*)&roots);
    	
    //thread padre
    //close(new_fd);
  }
  
  if(pthread_join(thread, NULL)) 
  {
    fprintf(stdout, "Error joining thread\n");
    exit (1);
  }
  close(sockfd);
  if(GuardarUsuarios(roots.Uroot,FUSU))
    printf("Error al Guardar\n");
  if(GuardarComents(roots.Proot))
    printf("Error al Guardar\n");
  if(GuardarPost(roots.Proot,FPUB))
    printf("Error al Guardar\n");
  printf("Salimoooo\n");
  exit (0);						//Salir
}



void* nuevo_thread (void *rs)
{
  //Thread hijo
  int id, sel,new_fd;
  int (*Menu[])(int,NodePost**,int)={Posteo,AgregarPost,BorrarPost};
  USU *buff;
  ROOT *rt_p;
  
  rt_p=(ROOT *)rs;
  new_fd=rt_p->sock;

  buff=(USU*)malloc(sizeof(USU));
  do
  {
    if((recv(new_fd,buff,sizeof(USU),0))==-1)	//recibe seleccion de Menu de Inicio
    {
      perror("Recv");
      exit(1);
    }
    if(buff->id==1)
      id=Check(&buff,rt_p->Uroot);			//Logueo
    else if(buff->id==2)
      id=AgregarNodoUsuario(buff,&(rt_p->Uroot));	//Registro
      else
	id=0;						//Salir

    if((send(new_fd,&id,sizeof(int),0))==-1)		//Envia respuesta
    {
      perror("Send");
      exit(1);
    }
  }while(id<0); //Bucle
	
  if(id!=0)
  {
    do
    {
      if((recv(new_fd,&sel,sizeof(int),0))==-1)	//Recivo seleccion
      {
	perror("Recv");
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
      BajaUsu (new_fd,&(rt_p->Uroot),id);		// case 4: BajaUsu
  }
  sleep(1);
  printf("Murio uno\n");
  close(rt_p->sock);					// case 5: Exit
  pthread_exit(0);
  //return(NULL);
}