#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "arvoreBinaria.h"

void inicializarFila(FILA *f)
{
  f->inicio = NULL;
  f->fim = NULL;
}

// inserir item ao final da fila dinamica
void entrarFila(int ch, FILA *f)
{
  NO_FILA *novo;
  novo = (NO_FILA *)malloc(sizeof(NO_FILA));
  novo->chave = ch;
  novo->prox = NULL;
  if (f->fim)
    f->fim->prox = novo;
  // fila não é vazia
  else
    f->inicio = novo;
  // 1a. inserção em fila vazia
  f->fim = novo;
}

// retirar a chave da frente ou -1
int sairFila(FILA *f)
{
  NO_FILA *aux;
  int ch;
  if (!f->inicio)
    return (-1);
  ch = f->inicio->chave;
  aux = f->inicio;
  f->inicio = f->inicio->prox;
  free(aux);
  if (!f->inicio)
    f->fim = NULL;
  return (ch);
}

// Inicialização da árvore vazia
void inicializarArvore(NO **raiz)
{
  *raiz = NULL;
}

// Verificar se árvore é vazia
bool arvoreVazia(NO *raiz)
{
  if (!raiz)
    return (true);
  else
    return (false);
}

// Inserção de um nó em árvore comum (sem ordem) esq:pos=1 dir:pos=2
bool inserirNo(NO **raiz, NO *pai, int ch, int pos)
{
  NO *novo;
  if (pai)
  {
    if (
        ((pos == 1) && (pai->esq != NULL)) ||
        ((pos == 2) && (pai->dir != NULL)))
    {
      return (false);
    }
  }
  novo = (NO *)malloc(sizeof(NO));
  novo->chave = ch;
  novo->esq = NULL;
  novo->dir = NULL;
  if (!pai)
    *raiz = novo;
  else
  {
    if (pos == 1) // esquerda
      pai->esq = novo;
    else
      pai->dir = novo;
  }
}

void visita(NO *p)
{
  printf("\n%d\n", p->chave);
}

void preOrdem(NO *p)
{
  if (p)
  {
    visita(p);
    preOrdem(p->esq);
    preOrdem(p->dir);
  }
}
void emOrdem(NO *p)
{
  if (p)
  {
    emOrdem(p->esq);
    visita(p);
    emOrdem(p->dir);
  }
}
void posOrdem(NO *p)
{
  if (p)
  {
    posOrdem(p->esq);
    posOrdem(p->dir);
    visita(p);
  }
}

// void exibirArvoreEmNivel(NO *raiz)
// {
//   NO *p = raiz;
//   FILA f;
//   inicializarFila(&f);

//   while (p)
//   {
//     if (p->esq)
//       entrarFila(p->esq, &f);
//     if (p->dir)
//       entrarFila(p->dir, &f);
//     printf("%d", p->chave);
//     if (f.inicio)
//       p = sairFila(&f);
//     else
//       p = NULL;
//   }
// }

NO *buscaLocal(NO *p, int ch, bool *achou)
{
  NO *aux;
  *achou = false;
  if (!p)
    return NULL;
  if (p->chave == ch)
  {
    return p;
    *achou = true;
  }
  aux = buscaLocal(p->esq, ch, achou);
  if (*achou)
    return aux;
  else
    return buscaLocal(p->dir, ch, achou);
}

NO *busca(NO *raiz, int ch)
{
  bool achou;
  return buscaLocal(raiz, ch, &achou);
}

void destruirArvore(NO **p)
{
  if (*p)
  {
    destruirArvore(&(*p)->esq);
    destruirArvore(&(*p)->dir);
    free(*p);
  }
  *p = NULL;
}

void testeNivel(NO *p, int ch, bool *achou, int *nivel)
{
  if (p)
  {
    *nivel += 1;
    if (p->chave == ch)
    {
      *achou = true;
    }
    else
    {
      testeNivel(p->esq, ch, achou, nivel);
      if (!*achou)
        testeNivel(p->dir, ch, achou, nivel);
      if (!*achou)
        *nivel -= 1;
    }
  }
}

int nivel(NO *raiz, int ch)
{
  int n = 0;
  bool achou = false;
  testeNivel(raiz, ch, &achou, &n);
  return n;
}

// medio: exc 4. Criar lista ligada c/ todos os elementos cada chave
// é maior do que a chave do pai em árvore não ordenada

// medio/dificil: exc 5. Verificar se uma árvore é ABB, retornando true/false
void verificaABB(NO *p, bool *abb)
{
  if (!p)
  {
    *abb = true;
    return;
  }
  if (p->esq && p->esq->chave > p->chave)
  {
    *abb = false;
    return;
  }
  if (p->dir && p->dir->chave < p->chave)
  {
    *abb = false;
    return;
  }
  verificaABB(p->esq, abb);
  if (!*abb)
    return;

  verificaABB(p->dir, abb);
}

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
bool ehCheia(NO *p)
{
  if (!p)
    return true;

  if (p->esq && p->dir)
    return ehCheia(p->esq) && ehCheia(p->dir);

  if (!p->esq && !p->dir)
    return true;

  return false;
}

// avançado: exc 8. Dada uma ABB e uma chave ch,
// encontre o antecessor de ch na sequência crescente de chaves
void encontrarPai(NO *p, int ch, int *antec)
{
  if (!p)
  {
    *antec = NULL;
    return;
  }
  else
  {
    if (p->esq)
    {
      if (p->esq->chave == ch)
      {
        *antec = p;
        return;
      }
      else
      {
        antecessor(p->esq, ch, antec);
      }
    }
    if (p->chave == ch)
      return;
    if (p->dir)
    {
      if (p->dir->chave == ch)
      {
        *antec = p;
        return;
      }
      else
      {
        antecessor(p->dir, ch, antec);
      }
    }
  }
}

/*
1. descer recursivamente até a folha (null)
2. chegando em null *ajustar = true
fim das recursões
3. desfaz percurso na ordem invesa, verificando se precisa fazer rotaçẽos
*/