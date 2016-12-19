CC = gcc
CFLAGS = -c -g -Wall
LDFLAGS = -lpthread
LIBS = -lopencv_core -lopencv_highgui -lopencv_imgproc
OBJS = Server_thread.o AgregarPost.o BajaUsuario.o BorrarPub.o BorrarCom.o BuscoPub.o Check.o Guardar.o GuardarComents.o GuardarPub.o LevantarCom.o LevantarLista.o LevantarPubli.o ListarPost.o listas_agregarnodopub.o listas_agregarnodousuario.o listas_borrarpub.o listas_borrarusuario.o listas_borrarcomentario.o sig_finish.o
OBJTS = cliente.o Ingresar.o registrarse.o interfaz1.o menuInicio.o leerCampodeTexto.o crearCampodeTexto.o errorInicio.o cvMostrarTitulo.o menuppal.o cvBajaUsuario.o cvListarPost.o cvResultadoBorrarPub.o cvCrearPublicacion.o cvLeerCamposPost.o cvCrearCamposPost.c cvSalir.o

All : CliExe SerExe Del

CliExe : $(OBJTS)
	$(CC) $(OBJTS) -o $@ $(LIBS)
%.o : %.c Cliente.h TPO.h
	$(CC) $(CFLAGS) $< -o $@
SerExe : $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
%.o : %.c
	$(CC) $(CFLAGS) $< -o $@
Del :
	rm -f ./*.o