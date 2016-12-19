//	SERVER

#include "TPO.h"

int Flag=0;

int main (void)
{

  NodeUser *URoot=NULL;
  NodePost *PRoot=NULL;
  //NodeComment *CRoot=NULL;
	
  int sockfd, new_fd, size;
  int fd[2];
  int id, sel;
  int (*Menu[])(int,NodePost*,int)={Posteo,AgregarPost,BorrarPost};
  USU *buff;
	
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
  
  //UMaster=&URoot;
  //PMaster=&PRoot;
  
  if(signal(SIGCHLD, sigchld_handler) == SIG_ERR)
  {
    perror("Signal");
    exit(1);
  }
  
  if(signal(SIGINT,sig_finish) == SIG_ERR)
  {
    perror("Signal");
    exit(1);
  }
  
  if(pipe(fd)==-1)
  {
    perror("Error pipe: \n");
    exit (0);
  }
	
  if((bind(sockfd,(struct sockaddr *)&server_addr, sizeof(struct sockaddr)))==-1)
  {
    perror("Bind");
    exit(1);
  }
  
	if(LoadUsuarios (&URoot,FUSU))					//Levanto todas las listas
		printf("Error Cargar Lista Usuarios\n");
	if(LoadPubli (&PRoot,FPUB))
		printf("Error Cargar Lista Publicaciones\n");
	if(LoadComments (&PRoot))
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
	return 1;
    }
    
    printf("Se recibio conexion de: %s\n", inet_ntoa(client_addr.sin_addr));
    fflush(stdout);
    
    if(!fork())
    {
	//Proceso hijo
	close(sockfd);
	close (fd[0]);
	if(signal(SIGINT,SIG_IGN) == SIG_ERR)		//Ignoro Ctr+C
	{
	  perror("Signal");
	  exit(1);
	}
	buff=(USU*)malloc(sizeof(USU));
	do
	{
	  if((recv(new_fd,buff,sizeof(USU),0))==-1)	//recibe seleccion de Menu de Inicio
	  {
	    perror("Recv");
	    exit(1);
	  }
	  if(buff->id==1)
	    id=Check(&buff,URoot);			//Logueo
	  else
	    id=AgregarNodoUsuario(buff,&URoot);		//Registro
	
	  if((send(new_fd,&id,sizeof(int),0))==-1)	//Envia respuesta
	  {
	    perror("Send");
	    exit(1);
	  }
	}while(id<0); //Bucle
	
	if(id==1)
	{
	printf("%p\n",URoot);
	write(fd[1],&URoot,sizeof(NodeUser *));		//Pipe
	}
	
	do
	{
	  if((recv(new_fd,&sel,sizeof(int),0))==-1)	//Recivo seleccion
	  {
	    perror("Recv");
	    exit(1);
	  }
	
	  sel--;
	  if(sel<3)
	    Menu[sel](new_fd,PRoot,id);
	    // case 1: Posteo (Falta considerar comentar y demas)
	    // case 2: AgregarPost
	    // case 3: BorrarPost
	}while(sel<3);
	if(sel==3)
	  BajaUsu (new_fd,&URoot,id);			// case 4: BajaUsu
	printf("Murio uno\n");
	exit(0);	   				// case 5: Exit 
    }//proceso padre
    close(new_fd);
    close (fd[1]);
    while(URoot==NULL)
      read(fd[0],&URoot,sizeof(NodeUser*));
    
    printf("%p\n",URoot);    
  }
  wait(NULL);
  if(GuardarUsuarios(URoot,FUSU))
    printf("Error al Guardar\n");
  //if(GuardarComents(PRoot))
    //printf("Error al Guardar\n");
  if(GuardarPost(PRoot,FPUB))
    printf("Error al Guardar\n");
  printf("Salimoooo\n");
  exit (0);						//Salir
}