#include <stdbool.h>
#include "listaSequencial.h"

void inicializar(LISTASEQ *l)
{
    l->nroElem = 0;
}

// Retorna indice ou -1
int buscaSeq(LISTASEQ *l, int ch)
{
    int i = 0;
    for (i = 0; i < l->nroElem; i++)
    {
        if (l->A[i].chave == ch)
            return i;
    }

    return -1; // não encontrou
}

bool anexar(LISTASEQ *l, REGISTROLISTASEQ *reg)
{
    if (l->nroElem == MAX)
        return false;
    l->A[l->nroElem] = *reg;
    l->nroElem++;
    return true;
}

bool excluir(LISTASEQ *l, REGISTROLISTASEQ *reg)
{
    if (l->nroElem == 0 || reg->chave <= 0)
        return false;
    int atual = buscaSeq(l, reg->chave);
    if (atual == -1)
        return false;
    for (int i = atual; i < l->nroElem - 1; i++)
    {
        l->A[i] = l->A[i + 1];
    }
    l->nroElem--;
    return true;
}

void exibir(LISTASEQ *l)
{
    int i;
    // printf("%i", l->nroElem);
    for (int i = 0; i < l->nroElem; i++)
    {
        printf("%d\n", l->A[i].chave);
    }
}
