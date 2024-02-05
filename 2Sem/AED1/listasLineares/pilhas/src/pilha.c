#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "pilha.h"

void inicializarPilha(PILHA *p)
{
  p->topo = NULL;
}

int countPilhaElem(PILHA *p)
{
  int count = 0;
  NO *aux = p->topo;
  while (aux)
  {
    count++;
    aux = aux->prox;
  }
  return count;
}

bool pilhaPUSH(PILHA *p, int ch)
{
  NO *Elem = malloc(sizeof(NO));
  Elem->chave = ch;
  Elem->prox = p->topo;
  p->topo = Elem;
  return true;
}

int pilhaPOP(PILHA *p)
{
  if (!p->topo)
    return -1;
  NO *aux = p->topo;
  int ch = aux->chave;
  p->topo = p->topo->prox;
  free(aux);
  return ch;
}