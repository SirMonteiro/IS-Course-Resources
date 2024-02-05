#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "arvoreBinaria.h"

void inicializarFila(FILA *f)
{
  f->inicio = NULL;
  f->fim = NULL;
}

NO *buscaABB(NO *p, int ch, NO **pai)
{
  *pai = NULL;
  while (p)
  {
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

bool insertABB(NO **raiz, int ch)
{
  NO *pai;
  NO *p = buscaABB(*raiz, ch, &pai);
  if (p)
    return false;

  NO *novo = (NO *)malloc(sizeof(NO));
  novo->chave = ch;
  novo->esq = NULL;
  novo->dir = NULL;

  if (!pai)
  {
    *raiz = novo;
    return true;
  }

  if (novo->chave < pai->chave)
    pai->esq = novo;
  else
    pai->dir = novo;
  return true;
}

// void preOrder(NO *raiz)
// {
//   PILHA p *;
//   inicializarPilha(&pi);
//   NO *p = raiz;
//   while (true)
//   {
//     while (p)
//     {
//       visitar(p);
//       if (p->dir)
//         push(&push, p->dir);
//     }
//     p = p->esq;
//     p = pop(&p);
//     if (!p)
//       break;
//   }
// }

void preOrdem(NO *p)
{
  if (p)
  {
    visitar(p);
    preOrdem(p->esq);
    preOrdem(p->dir);
  }
}

void contar(NO *p, int *resp)
{
  if (p)
  {
    *resp = *resp + 1;
    contar(p->esq, resp);
    contar(p->dir, resp);
  }
}

int contar2(NO *p)
{
  if (!p)
    return 0;
  else
  {
    return 1 + contar2(p->esq) + contar2(p->dir);
  }
}

int max(int a, int b) { return (a > b) ? a : b; }

int altura(NO *p)
{
  if (!p)
    return 0;
  if (!p->esq && !p->dir)
    return 1;
  return 1 + max(altura(p->esq), altura(p->dir));
}

void busca(NO *p, int ch, NO **resp)
{
  if (p)
  {
    if (p->chave == ch)
      *resp = p;
    if (*resp == NULL)
      busca(p->esq, ch, resp);
    if (*resp == NULL)
      busca(p->dir, ch, resp);
  }
}

NO *copia(NO *p)
{
  if (!p)
    return NULL;
  NO *novo = (NO *)malloc(sizeof(NO));
  novo->chave = p->chave;
  novo->esq = copia(p->esq);
  novo->dir = copia(p->dir);
  return novo;
}

bool iguais(NO *p1, NO *p2)
{
  if (!p1 && !p2)
    return true;
  if (!p1 || !p2)
    return false;
  if (p1->chave != p2->chave)
    return false;
  bool ok = iguais(p1->esq, p2->esq);
  if (ok)
    return iguais(p1->dir, p2->dir);
  else
    return false;
}

void destruir(NO **p)
{
  if (*p)
  {
    destruir(&(p)->esq);
    destruir(&(p)->dir);
    free(*p);
  }
  *p = NULL;
}

void emNivel(NO *p)
{
  FILA f;
  inicializarFile(&f);
  entrarFila(&f, p);
  while (f->inicio)
  {
    p = sairFila(&f);
    visitar(p);
    entrarFila(&f, p->esq);
    entrarFila(&f, p->dir);
  }
}

int maiorChaveABB(NO *p)
{
  while (p)
  {
    if (!p->esq)
      return p;
    p = p->esq;
  }
  return __INT_MAX__;
}

// ex: menor chave em árvore não ordenada
void menor(NO *p, int *resp)
{
  if (p)
  {
    if (p->chave < *resp)
      *resp->chave;
    menor(p->esq, resp);
    menor(p->dir, resp);
  }
}

// fazer lista ligada com nós que tem filho
void listarNosInteriores(NO *p, NOLISTA **inicio)
{
  if (p)
  {
    if (p->esq || p->dir)
    {
      NOLISTA *novo = (NOLISTA *)malloc(sizeof(NOLISTA));
      novo->chave = p->chave;
      novo->prox = *inicio;
      *inicio = novo;
    }
  }
  listarNosInteriores(p->esq, inicio);
  listarNosInteriores(p->dir, inicio);
}

bool ehAVL(NO_AVL *p)
{
  if (!p)
    return true;
  int hd = altura(p->dir);
  int he = altura(p->esq);
  if (hd - he < 1 || hd - he > 1)
    return false;
  bool aux = ehAVL(p->esq);
  if (!aux)
    return false;
  return ehAVL(p->dir);
}

// espelhar uma arvore
void espelhar(NO *p)
{
  if (p)
  {
    NO *aux = p->esq;
    p->esq = p->dir;
    p->dir = aux;
    espelhar(p->esq);
    espelhar(p->dir);
  }
}

// Exibir as N maiores chaves de uma ABB
void exibirNMaiores(NO *p, int *N)
{
  if (p)
  {
    exibirNMaiores(p->dir, N);
    if (*N > 0)
    {
      printf("%d", p->chave);
      *N = *N - 1;
    }
    if (*N > 0)
      exibirNMaiores(p->esq, N);
  }
}

// exc 3. exibir N chaves mais próximas da raiz
void exibirNProximas(NO *raiz, int *N)
{
  if (N == 0)
    return;
  FILA f;
  inicializarFila(&f);
  entrarFila(&f, raiz);
  while (f.inicio)
  {
    NO *p = sairFila(&f);
    printf("%d", p->chave);
    N--;
    if (N == 0)
      break;
    if (p->esq)
      entrarFila(&f, p->esq);
    if (p->dir)
      entrarFila(&f, p->dir);
  }
  while (f.inicio)
    SairFila(&f);
}

// medio: exc 4. Criar lista ligada c/ todos os elementos cada chave
// é maior do que a chave do pai em árvore não ordenada

// medio/dificil: exc 5. Verificar se uma árvore é ABB, retornando true/false

// facil: exc 6. Verificar se árvore é assimétrica retornando true/false
bool ehAssimetrico(NO *p)
{
  if (!p)
    return false;
  else
  {
    if ((p->esq && !p->dir) || (!p->esq && p->dir))
      return true;
    else
      return ehAssimetrico(p->esq) && ehAssimetrico(p->dir);
  }
}

// facil: exc 7. Verificar se árvore é cheia, retornando true, false

// avançado: exc 8. Dada uma ABB e uma chave ch,
// encontre o antecessor de ch na sequência crescente de chaves

/*
1. descer recursivamente até a folha (null)
2. chegando em null *ajustar = true
fim das recursões
3. desfaz percurso na ordem invesa, verificando se precisa fazer rotaçẽos
*/

NO *inserir(NO *p, int ch, bool *ajustar)
{
  if (!p)
  {
    NO *novo = (NO *)malloc(sizeof(NO));
    novo->chave = ch;
    novo->esq = NULL;
    novo->dir = NULL;
    *ajustar = true;
    return novo;
  }
  if (p->chave > ch)
  {
    p->esq = inserir(p->esq, ch, ajustar);
    if (*ajustar)
    {
      switch (p->bal)
      {
      case 1:
        p->bal = 0;
        *ajustar = false;
        break;
      case 0:
        p->bal = -1;
        break;
      case -1:
        p = rotacaoL(p);
        *ajustar = false;
        break;
      }
    }
    else
    {
      p->dir = inserir(p->dir, ch, ajustar);
      switch (p->bal)
      {
      case -1:
        p->bal = 0;
        *ajustar = false;
      case 0:
        p->bal = 1;
        break;
      case 1:
        p = rotacaoR(p);
        *ajustar = false;
        break;
      }
    }
  }
  return p;
}