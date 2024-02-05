#include "arvoreBinaria.c"

int main()
{
  NO *node4 = (NO *)malloc(sizeof(NO));
  node4->chave = 4;
  node4->esq = NULL;
  node4->dir = NULL;

  NO *node3 = (NO *)malloc(sizeof(NO));
  node3->chave = 3;
  node3->esq = NULL;
  node3->dir = NULL;

  NO *node2 = (NO *)malloc(sizeof(NO));
  node2->chave = 2;
  node2->esq = NULL;
  node2->dir = NULL;

  NO *node1 = (NO *)malloc(sizeof(NO));
  node1->chave = 1;
  node1->esq = node2;
  node1->dir = node3;

  NO *raiz = (NO *)malloc(sizeof(NO));
  raiz->chave = 0;
  raiz->esq = node1;
  raiz->dir = node4;

  // NO *aux = (NO *)malloc(sizeof(NO));
  // aux->chave = 1;
  // aux->esq = NULL;
  // aux->dir = NULL;

  // raiz->dir = aux;
  // raiz->esq = (NO *)malloc(sizeof(NO));
  // raiz->esq->chave = 2;
  // raiz->esq->esq = NULL;
  // raiz->esq->dir = NULL;

  printf("Nível: %d\n", nivel(raiz, 0));

  return 0;
}