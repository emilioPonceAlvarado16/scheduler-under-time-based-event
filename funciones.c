#include "funciones.h"
extern bool parpadeo;

void luz_roja()
{
  printf("\033[0;31m");
  printf("\r[\u2586]");
  printf("\033[0;33m");
  printf("[ ]");
  printf("\033[0;32m");
  printf("[ ]");
  printf("\033[0m");
  fflush(stdout);
}

void luz_verde()
{
  printf("\033[0;31m");
  printf("\r[ ]");
  printf("\033[0;33m");
  printf("[ ]");
  printf("\033[0;32m");
  printf("[\u2586]");
  printf("\033[0m");
  fflush(stdout);
}

void luz_amarilla()
{
  printf("\033[0;31m");
  printf("\r[ ]");
  printf("\033[0;33m");
  printf("[\u2586]");
  printf("\033[0;32m");
  printf("[ ]");
  printf("\033[0m");
  fflush(stdout);
}

void parpadea_roja()
{
  printf("\033[0;31m");
  if(parpadeo){
    printf("\r[\u2586]");
  }else
    printf("\r[ ]");

  printf("\033[0;33m");
  printf("[ ]");
  printf("\033[0;32m");
  printf("[ ]");
  printf("\033[0m");
  fflush(stdout);
}
