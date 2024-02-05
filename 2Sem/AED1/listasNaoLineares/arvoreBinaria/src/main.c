#include "arvoreBinaria.c"

int main()
{
  NO *raiz = (NO *)malloc(sizeof(NO));
  raiz->chave = 0;
  raiz->esq = NULL;
  raiz->dir = NULL;

  NO *aux = (NO *)malloc(sizeof(NO));
  aux->chave = 1;
  aux->esq = NULL;
  aux->dir = NULL;

  raiz->dir = aux;
  raiz->esq = (NO *)malloc(sizeof(NO));
  raiz->esq->chave = 2;
  raiz->esq->esq = NULL;
  raiz->esq->dir = NULL;

  return 0;
}