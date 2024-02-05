#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "listaLigadaDinamica.h"

void inicializar(LISTA_LIG_DIN *l)
{
    l->inicio = NULL;
}

void exibir(LISTA_LIG_DIN *l)
{
    NO *p = l->inicio;
    while (p)
    {
        printf("%i\n", p->chave);
        p = p->prox;
    }
}

// excluir o 1º Elemento
bool excluirPrimeiro(LISTA_LIG_DIN *l)
{
    if (!l->inicio)
        return false;
    NO *aux = l->inicio;
    l->inicio = l->inicio->prox;
    free(aux);
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
        ant->prox = novo;
    }
    else
    {
        novo->prox = l->inicio;
        l->inicio = novo;
    }
}

// (1) mover ch para frente da lista
// (2) mover p para frente da lista

bool moverChaveFrente(LISTA_LIG_DIN *l, int ch, NO *ant)
{
    if (l->inicio && l->inicio->chave == ch)
        return false;
    NO *p = busca(l, ch, &ant);

    if (ant)
        ant->prox = p->prox;
    else
        l->inicio = p->prox;

    p->prox = l->inicio;
    l->inicio = p;
}

void destruir(LISTA_LIG_DIN *l)
{
    NO *p = l->inicio;
    while (p)
    {
        NO *aux = p->prox;
        free(p);
        p = aux;
    }
}

// seja uma lista que aceita chaves repetidas, sem ordem.
// Problema: eliminar todas ocorrências de uma chave ch.
void excluirOcorrencias(LISTA_LIG_DIN *l, int ch)
{
    NO *ant = NULL;
    NO *p = l->inicio;
    while (p)
    {
        NO *aux = p->prox;
        if (p->chave == ch)
        {
            if (ant)
                ant->prox = p->prox;
            else
                l->inicio = p->prox;
            free(p);
        }
        else
            ant = p; // Não percorre o ant se o proximo for excluido.
        p = aux;
    }
}

// Dada uma lista l1, efetuar uma copia, retornando o resultado.
LISTA_LIG_DIN *copia(LISTA_LIG_DIN *l1)
{
    LISTA_LIG_DIN resp;
    resp.inicio = NULL;
    NO *fim = NULL;
    NO *p = l1->inicio;
    while (p)
    {
        NO *novo = (NO *)malloc(sizeof(NO));
        novo->chave = p->chave;
        novo->prox = NULL;
        if (fim)
            fim->prox = novo;
        else
            resp.inicio = novo;
        fim = novo;
        p = p->prox;
    }
    return (&resp);
}

void inicializarSent(LISTA_SENT *l)
{
    l->sent = (NO *)malloc(sizeof(NO));
    l->inicio = l->sent;
}

void exibirSent(LISTA_SENT *l)
{
    NO *p = l->inicio;
    while (p != l->sent)
    {
        printf("%d", p->chave);
        p = p->prox;
    }
}

// void buscaComSent(LISTA_SENT *l)
// {
//     l->sent->chave = ch;
//     while (p->chave != ch)
//         p = p->prox;
//     if (p == l->sent)
//         return NULL;
// }

void catL1toL2(LISTA_LIG_DIN *l1, LISTA_LIG_DIN *l2)
{
    if (!l1->inicio)
        return;
    NO *aux = l2->inicio;
    while (aux->prox)
    {
        aux = aux->prox;
    }
    // printf("%d\n", aux->chave);
    aux->prox = l1->inicio;
    l1->inicio = NULL;
}

void catL1toL2Cloning(LISTA_LIG_DIN *l1, LISTA_LIG_DIN *l2)
{
    if (!l1->inicio)
        return;
    NO *aux = l2->inicio;
    while (aux->prox)
    {
        aux = aux->prox;
    }
    // aux->prox = l2->inicio;

    NO *aux2 = l1->inicio;
    NO *ant2;

    while (aux2)
    {
        NO *new = (NO *)malloc(sizeof(NO));
        new->chave = aux2->chave;
        if (ant2)
            ant2->prox = new;
        else
            aux->prox = new;
        ant2 = new;
        aux2 = aux2->prox;
    }
}

// int main()
// {
//     NO *novo = (NO *)malloc(sizeof(NO));

//     novo->chave = 10;
//     novo->prox = NULL;

//     NO *aux = novo;
//     novo->chave = 0;

//     novo = NULL;

//     novo = (NO *)malloc(sizeof(NO));
//     novo->chave = 1;
//     novo->prox = NULL;
//     aux->prox = novo;
//     NO *inicio = aux;

//     printf("%p\n", novo);
//     printf("%p\n", aux);

//     return 0;
// }
