#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct estrutura
{
    int chave;

    struct estrutura *prox;
} NO;

typedef struct
{
    NO *inicio;
} LISTA_LIG_CIRC;

void exibir(LISTA_LIG_CIRC *l)
{
    NO *p = l->inicio;
    while (p)
    {
        printf("%d", p->chave);
        p = p->prox;
        if (p == l->inicio)
            break;
    }
}

NO *utimo(NO *inicio)
{
    NO *ult = NULL;
    NO *p = inicio;
    while (p)
    {
        ult = p;
        p = p->prox;
        if (p == inicio)
            break;
    }
    return ult;
}

void excluirPrimeiro(LISTA_LIG_CIRC *l)
{
    if (!l->inicio)
        return;
    NO *ult = ultimo(l->inicio);
    ult->prox = l->inicio->prox;
    NO *aux = l->inicio;
    l->inicio = l->inicio->prox;
    if (l->inicio == aux)
        l->inicio = NULL;
    free(aux);
}