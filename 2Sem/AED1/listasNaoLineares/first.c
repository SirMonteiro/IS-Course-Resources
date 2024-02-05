#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s {
  int chave;
  struct s *esq;
  struct s *dir;
} NO;

NO *buscaABB(NO *p, int ch, NO **pai) {
  *pai = NULL;
  while (p) {
    if (p->chave == ch)
      return p;
    *pai = p;
    if (p->chave > ch)
      p = p->esq;
    else
      p = p->dir;
  }
  return p;
}

bool insertABB(NO **raiz, int ch) {
  NO *pai;
  NO *p = buscaABB(*raiz, ch, &pai);
  if (p)
    return false;

  NO *novo = (NO *)malloc(sizeof(NO));
  novo->chave = ch;
  novo->esq = NULL;
  novo->dir = NULL;

  if (!pai) {
    *raiz = novo;
    return true;
  }

  if (novo->chave < pai->chave)
    pai->esq = novo;
  else
    pai->dir = novo;
  return true;
}

int main() {
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
