#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "matrizesparsa.h"

void inicializar(MATRIZ *m, int i, int j, int k)
{
  m->inicio = NULL;
  m->maxcol = j;
  m->maxlin = i;
  m->defaultValue = k;
}

void exibir(MATRIZ *m)
{
  NO *aux = m->inicio;
  while (aux)
  {
    printf("%d,%d: %d\n", aux->l, aux->c, aux->chave);
    aux = aux->prox;
  }
}

void exibirLinha(MATRIZ *m, int i)
{
  NO *p = m->inicio;

  while (p->prox && p->l != i)
  {
    p = p->prox;
  }

  for (int j = 0; j < m->maxcol; j++)
  {
    if (p->l == i && p->c == j)
    {
      printf("%d\t", p->chave);
      p = p->prox;
    }
    else
    {
      printf("%d\t", 0);
    }
  }
  printf("\n");
}

int valorCelula(MATRIZ *m, int i, int j)
{
  NO *aux = m->inicio;
  while (aux)
  {
    if (aux->l == i && aux->c == j)
    {
      return aux->chave;
    }
    if (aux->l > i)
      return 0;
    if (aux->l == i && aux->c > j)
      return 0;
    aux = aux->prox;
  }
  return 0;
}

NO *busca(MATRIZ *m, int i, int j, NO **ant)
{
  *ant = NULL;
  NO *aux = m->inicio;
  while (aux)
  {
    if (aux->l == i && aux->c == j)
    {
      return aux;
    }
    if (aux->l > i)
      return NULL;
    if (aux->l == i && aux->c > j)
      return NULL;
    *ant = aux;
    aux = aux->prox;
  }
  return NULL;
}

/* valor  busca
    0      0
    0     >0
    >0     0
    >0    >0
*/
void atribuir(MATRIZ *m, int i, int j, int valor)
{
  NO *ant;
  NO *atual = busca(m, i, j, &ant);
  // caso 1
  if (!atual && valor == 0)
    return;
  // caso 4
  if (atual && valor > 0)
  {
    atual->chave = valor;
    return;
  }
  // caso 2 (exclusão)
  if (valor == 0 && atual)
  {
    if (ant)
      ant->prox = atual->prox;
    else
      m->inicio = atual->prox;
    free(atual);
    return;
  }
  // caso 3 (inserção)
  if (valor > 0 && !atual)
  {
    NO *new = (NO *)malloc(sizeof(NO));
    new->chave = valor;
    new->l = i;
    new->c = j;
    if (ant)
    {
      new->prox = ant->prox;
      ant->prox = new;
    }
    else
    {
      new->prox = m->inicio;
      m->inicio = new;
    }
  }
}

void zerarDiagPrincipal(MATRIZ *m)
{
  NO *aux = m->inicio;
  while (aux)
  {
    if (aux->c == aux->l)
    {
      aux->chave = 0;
    }
    aux = aux->prox;
  }
}

void zerarLinha(MATRIZ *m, int i)
{
  NO *aux = m->inicio;

  while (aux->prox && aux->prox->l != i)
  {
    aux = aux->prox;
  }

  if (!aux || aux->prox->l != i)
    return;

  NO *lastValidNode = aux;
  aux = aux->prox;

  while (aux && aux->l == i)
  {
    if (aux->prox->l != i)
      lastValidNode->prox = aux->prox;
    NO *nodeToFree = aux;
    aux = aux->prox;
    free(nodeToFree);
  }
}

void zerarColuna(MATRIZ *m, int j)
{
  if (!m->inicio)
    return;
  NO *aux = m->inicio;
  NO *ant = m->inicio;
  while (aux)
  {
    if (aux->c == j)
    {
      ant->prox = aux->prox;
      NO *NodeToFree = aux;
      aux = aux->prox;
      free(NodeToFree);
    }
    else
    {
      ant = aux;
      aux = aux->prox;
    }
  }
}

int countZeros(MATRIZ *m)
{
  int matrizSize = m->maxcol * m->maxlin;
  NO *aux = m->inicio;
  int counter = 0;
  while (aux)
  {
    counter += 1;
    aux = aux->prox;
  }
  return matrizSize - counter;
}
