#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "fila.h"

void inicializarFila(FILA *f)
{
  f->inicio = NULL;
  f->fim = NULL;
}

int filaLength(FILA *f)
{
  NO *aux = (NO *)malloc(sizeof(NO));
  aux = f->inicio;
  int count = 0;
  while (aux)
  {
    count++;
    aux = aux->prox;
  }
  free(aux);
  return count;
}

void printFila(FILA *f)
{
  if (!f->inicio)
    return;
  NO *aux = (NO *)malloc(sizeof(NO));
  aux = f->inicio;
  int count = 0;
  while (aux)
  {
    count++;
    printf("%dº Element of Fila: %d\n", count, aux->chave);
    aux = aux->prox;
  }
  free(aux);
}

void printRecursive(NO *p)
{
  if (p)
    printf("%d\n", p->chave);
  printRecursive(p->prox);
  return;
}

bool insertFila(FILA *f, int ch)
{
  NO *new = (NO *)malloc(sizeof(NO));
  new->chave = ch;
  new->prox = NULL;
  if (!f->inicio)
    f->inicio = new;
  else
    f->fim->prox = new;
  f->fim = new;
  return true;
}

int getFromFila(FILA *f)
{
  if (!f->inicio)
    return -1;
  NO *aux = (NO *)malloc(sizeof(NO));
  aux = f->inicio;
  f->inicio = f->inicio->prox;
  int ch = aux->chave;
  free(aux);
  if (!f->inicio)
    f->fim = NULL;
  return ch;
}

// void retirarChave(FILA *f, int ch)
// {
//   NO *ant = NULL;
//   NO *p = busca(f->inicio, ch, &ant);
//   if (!p)
//     return;
//   if (ant)
//     ant->prox = p->prox;
//   else
//     f->inicio = p->prox;
//   if (p == f->fim)
//   {
//     if (ant)
//     {
//       ant->prox = NULL;
//       f->fim = ant;
//     }
//     else
//       f->fim = NULL;
//   }
//   free(p);
// }