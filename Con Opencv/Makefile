CC = gcc
CFLAGS = -c -g -Wall
LDFLAGS = -lpthread
OBJS = server.o postFuns.o usuFuns.o borrarCom.o guardarListas.o levantarListas.o agregarNodo.o borrarNodo.o sig_finish.o
OBJTS = client.o menuInicio.o

All : CliExe SerExe Del

CliExe : $(OBJTS)
	$(CC) $(OBJTS) -o $@
%.o : %.c Cliente.h TPO.h
	$(CC) $(CFLAGS) $< -o $@
SerExe : $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
%.o : %.c
	$(CC) $(CFLAGS) $< -o $@
Del :
	rm -f ./*.o