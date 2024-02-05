#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct estrutura
{
  int chave;
  struct estrutura *prox;
  struct estrutura *ant;
} NO;

typedef struct
{
  NO *inicio1;
  NO *inicio2;
} DEQUE;