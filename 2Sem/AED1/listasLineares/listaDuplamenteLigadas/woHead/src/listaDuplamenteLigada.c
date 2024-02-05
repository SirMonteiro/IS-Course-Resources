#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "listaDuplamenteLigada.h"

void inicializarLista(LISTA_LIG_DUP *l)
{
  l->cab = (NO *)malloc(sizeof(NO));
  l->cab->ant = l->cab;
  l->cab->prox = l->cab;
}

void destroyLista(LISTA_LIG_DUP *l)
{
  NO *aux = l->cab;
  NO *ant;
  l->cab->ant->prox = NULL;
  while (aux)
  {
    ant = aux;
    aux = aux->prox;
    free(ant);
  }
  free(l);
}

void printLista(LISTA_LIG_DUP *l)
{

  NO *aux = l->cab->prox;
  while (aux && aux != l->cab)
  {
    printf("%d\n", aux->chave);
    aux = aux->prox;
  }
}

void printListaInvertida(LISTA_LIG_DUP *l)
{

  NO *aux = l->cab->ant;
  while (aux && aux != l->cab)
  {
    printf("%d\n", aux->chave);
    aux = aux->ant;
  }
}

int listaLength(LISTA_LIG_DUP *l)
{
  NO *aux = l->cab->prox;
  int count = 0;
  while (aux && aux->prox != l->cab->prox)
  {
    count++;
    aux = aux->prox;
  }
  return count;
}

bool anexarLista(LISTA_LIG_DUP *l, int ch)
{
  NO *new = (NO *)malloc(sizeof(NO));
  new->chave = ch;
  new->prox = l->cab;
  new->ant = l->cab->ant;
  l->cab->ant->prox = new;
  l->cab->ant = new;
  return true;
}

NO *busca(LISTA_LIG_DUP *l, int ch)
{
}

void inserirAntes(LISTA_LIG_DUP *l, int ch, NO *atual)
{
  NO *new = (NO *)malloc(sizeof(NO));
  new->chave = ch;
  new->ant = atual->ant;
  new->prox = atual;
  atual->ant->prox = new;
  atual->ant = new;
}

/* lista dupla, sem cabeça, sem circularidade
 * Ex. 1: dado um elemento p garantidamente existente, mover p para o início da lista
 */
void moverParaFrente(LISTA_LIG_DUP *l, NO *p)
{
  if (p == l->inicio)
    return;
  p->ant->prox = p->prox;
  if (p->prox)
    p->prox->ant = p->ant;
  p->prox = l->inicio;
  p->ant = NULL;
  l->inicio->ant = p;
  l->inicio = p;
}
