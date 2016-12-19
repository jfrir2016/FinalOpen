#include "TPO.h"

void sig_finish (int s)
{
  extern int Flag;
  printf("\nFlagueado!!\n");
  Flag=1;	
}
