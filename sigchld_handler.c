#include "TPO.h"

void sigchld_handler(int s)
{
	while(wait(NULL) > 0);
	printf("Waiteado!!\n");
}
