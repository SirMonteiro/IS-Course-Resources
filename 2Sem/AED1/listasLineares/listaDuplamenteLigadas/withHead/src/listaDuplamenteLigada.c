#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "listaDuplamenteLigada.h"

void inicializarLista(LISTA_LIG_DUP_CAB *l)
{
  l->cab = (NO *)malloc(sizeof(NO));
  l->cab->ant = l->cab;
  l->cab->prox = l->cab;
}

void destroyLista(LISTA_LIG_DUP_CAB *l)
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

void printLista(LISTA_LIG_DUP_CAB *l)
{

  NO *aux = l->cab->prox;
  while (aux && aux != l->cab)
  {
    printf("%d\n", aux->chave);
    aux = aux->prox;
  }
}

void printListaInvertida(LISTA_LIG_DUP_CAB *l)
{

  NO *aux = l->cab->ant;
  while (aux && aux != l->cab)
  {
    printf("%d\n", aux->chave);
    aux = aux->ant;
  }
}

int listaLength(LISTA_LIG_DUP_CAB *l)
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

bool anexarLista(LISTA_LIG_DUP_CAB *l, int ch)
{
  NO *new = (NO *)malloc(sizeof(NO));
  new->chave = ch;
  new->prox = l->cab;
  new->ant = l->cab->ant;
  l->cab->ant->prox = new;
  l->cab->ant = new;
  return true;
}

NO *busca(LISTA_LIG_DUP_CAB *l, int ch)
{
}

void inserirAntes(LISTA_LIG_DUP_CAB *l, int ch, NO *atual)
{
  NO *new = (NO *)malloc(sizeof(NO));
  new->chave = ch;
  new->ant = atual->ant;
  new->prox = atual;
  atual->ant->prox = new;
  atual->ant = new;
}

/* dada uma lista dupla, circular e com cabeça,
 * criar uma cópia simples, sem circularidade e
 * sem cabeça.
 */
NO2 *copiaSimples(LISTA_LIG_DUP_CAB *l)
{
  NO2 *resp = NULL;
  NO2 *ultimo = NULL;
  NO *p = l->cab->prox;
  while (p != l->cab)
  {
    NO2 *new = (NO2 *)malloc(sizeof(NO2));
    new->chave = p->chave;
    if (ultimo)
      ultimo->prox = new;
    else
      resp = new;
    new->prox = NULL;
    ultimo = new;
    p = p->prox;
  }
  return resp;
}