#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "linearLists.h"

void inicializarDIN(LISTA_LIG_DIN *l)
{
  l->inicio = NULL;
}

void inicializarDINCAB(LISTA_LIG_DIN_CAB *l)
{
  l->cab = (NO *)malloc(sizeof(NO));
  l->cab->prox = l->cab;
}

void inicializarDINDUPCAB(LISTA_LIG_DUP_CAB *l)
{
  l->cab = (NO_DUP *)malloc(sizeof(NO_DUP));
  l->cab->prox = l->cab;
  l->cab->ant = l->cab;
}

void inicializarFila(FILA *f)
{
  f->inicio = NULL;
  f->fim = NULL;
}

void inicializarPilha(PILHA *p)
{
  p->topo = NULL;
  typedef struct
  {
    NO *inicio;
    int maxlin;
    int maxcol;
    int defaultValue;
  } MATRIZ;
}

void inicializarMATRIZ(MATRIZ *m, int i, int j, int k)
{
  m->inicio = NULL;
  m->maxlin = i;
  m->maxcol = j;
  m->defaultValue = k;
}

void exibirCAB(LISTA_LIG_DIN_CAB *l)
{

  NO *aux = l->cab->prox;
  while (aux && aux != l->cab)
  {
    printf("%d\n", aux->chave);
    aux = aux->prox;
  }
}

void exibir(LISTA_LIG_DIN *l)
{
  NO *p = l->inicio;
  while (p)
  {
    printf("%i\n", p->chave);
    p = p->prox;
    if (p == l->inicio)
    {
      printf("Lista circular!, parando loop.\n");
      return;
    }
  }
}

NO *busca(LISTA_LIG_DIN *l, int ch, NO **ant)
{
  *ant = NULL;
  NO *p = l->inicio;
  while (p)
  {
    if (p->chave == ch)
      return p;
    if (p->chave > ch)
      return NULL;
    *ant = p;
    p = p->prox;
    if (p == l->inicio)
    {
      return NULL;
    }
  }
  return NULL;
}

bool excluir(LISTA_LIG_DIN *l, int ch)
{
  NO *ant;
  NO *atual = busca(l, ch, &ant);
  if (!atual)
    return false;
  if (ant)
    ant->prox = atual->prox;
  else
    l->inicio = atual->prox;
  free(atual);
  return true;
}

bool inserir(LISTA_LIG_DIN *l, int ch)
{
  NO *ant;
  NO *atual = busca(l, ch, &ant);
  if (atual)
    return false;
  NO *novo = (NO *)malloc(sizeof(NO));
  novo->chave = ch;
  // novo->prox = NULL;
  if (ant)
  {
    novo->prox = ant->prox;
    // novo->prox = l->inicio;
    ant->prox = novo;
  }
  else
  {
    l->inicio = novo;
    novo->prox = l->inicio;
  }
}

LISTA_LIG_DIN_CAB *transformarCircularSCabecaEmCabeca(LISTA_LIG_DIN *l1)
{
  LISTA_LIG_DIN_CAB *l2 = (LISTA_LIG_DIN_CAB *)malloc(sizeof(LISTA_LIG_DIN_CAB));
  if (!l1->inicio)
    return NULL;
  NO *l1AUX = l1->inicio;

  inicializarDINCAB(l2);
  l2->cab->prox = l1->inicio;
  // l1AUX = l1AUX->prox;

  while (l1AUX)
  {
    l1AUX = l1AUX->prox;
    if (l1AUX->prox == l1->inicio)
      break;
  }

  l1AUX->prox = NULL;
  return l2;
}

NO *copiaSimplesInvertida(NO_DUP *p)
{
  if (!p)
    return NULL;

  NO_DUP *auxDUP = p->ant;
  NO *aux = NULL;

  NO *inicioListaSimples = (NO *)malloc(sizeof(NO));
  inicioListaSimples->chave = auxDUP->chave;
  inicioListaSimples->prox = NULL;
  aux = inicioListaSimples;
  if (auxDUP->ant)
    auxDUP = auxDUP->ant;
  while (auxDUP && auxDUP != p->ant)
  {
    NO *novo = (NO *)malloc(sizeof(NO));
    novo->chave = auxDUP->chave;
    novo->prox = NULL;
    aux->prox = novo;
    aux = novo;
    auxDUP = auxDUP->ant;
  }
  return inicioListaSimples;
}

void filaExibir(FILA *f)
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

bool filaInserir(FILA *f, int ch)
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

int filaRetirar(FILA *f)
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

void pilhaExibir(PILHA *p)
{
  NO *aux = p->topo;
  while (aux)
  {
    printf("pilha: %d\n", aux->chave);
    aux = aux->prox;
  }
}

int pilhaElems(PILHA *p)
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

bool compararFilaEPilha(FILA *f, PILHA *p)
{
  NO *filaAUX = f->inicio;
  NO *pilhaAUX = p->topo;

  while (filaAUX && pilhaAUX)
  {
    // printf("Fila: |%d|, Pilha: |%d|\n", filaAUX->chave, pilhaAUX->chave);
    if (filaAUX->chave != pilhaAUX->chave)
      return false;
    filaAUX = filaAUX->prox;
    pilhaAUX = pilhaAUX->prox;
  }

  if (!filaAUX && !pilhaAUX)
    return true;
  return false;
}

void catFilaToPilha(FILA *f, PILHA *p)
{
  if (!f->inicio)
    return;

  NO *pilhaAUX = p->topo;

  while (pilhaAUX->prox)
  {
    pilhaAUX = pilhaAUX->prox;
  }

  NO *filaAUX = f->inicio;

  if (!pilhaAUX)
    pilhaAUX = filaAUX;

  while (filaAUX)
  {
    pilhaAUX->prox = filaAUX;
    pilhaAUX = pilhaAUX->prox;
    filaAUX = filaAUX->prox;
  }
}

void catPilhaToFila(PILHA *p, FILA *f)
{
  if (!p->topo)
    return;
  NO *filaAUX = f->fim;
  NO *pilhaAUX = p->topo;

  while (pilhaAUX)
  {
    filaAUX->prox = pilhaAUX;
    filaAUX = filaAUX->prox;
    pilhaAUX = pilhaAUX->prox;
  }
}