#include <stdbool.h>

#include "listaLigadaEstatica.h"

void inicializar(LISTALIGEST *l)
{
    l->inicio = -1;
    l->dispo = 0;
    for (int i = 0; i < MAX - 1; i++)
        l->A[i].prox = i + 1;

    l->A[MAX - 1].prox = -1;
}

void exibir(LISTALIGEST l)
{
    int i = l.inicio;
    while (i > -1)
    {
        printf("%d ", l.A[i].chave);
        i = l.A[i].prox;
    }
}

int busca(LISTALIGEST l, int ch, int *ant)
{
    int i = l.inicio;
    *ant = -1;
    while (i > -1)
    {
        if (l.A[i].chave >= ch)
            break;
        *ant = i;
        i = l.A[i].prox;
    }
    if (i == -1)
        return -1;
    if (l.A[i].chave == ch)
        return i;
    else
        return -1;
}

void devolver(LISTALIGEST *l, int atual)
{
    l->A[atual].prox = l->dispo;
    l->dispo = atual;
}

int obterEndereco(LISTALIGEST *l)
{
    if (l->dispo == -1)
        return -1;
    int res = l->dispo;
    l->dispo = l->A[l->dispo].prox;
    return res;
}

bool excluir(LISTALIGEST *l, int ch)
{
    int ant;
    int atual = busca(*l, ch, &ant);
    if (atual == -1)
        return false; // não existe
    if (ant > -1)
        l->A[ant].prox = l->A[atual].prox;
    else
        l->inicio = l->A[atual].prox;
    devolver(l, atual);
    return true;
}

bool inserir(LISTALIGEST *l, int ch)
{
    int ant;
    int atual = busca(*l, ch, &ant);
    if (atual != -1)
        return false; // já existe
    int novo = obterEndereco(l);
    if (novo == -1)
        return false; // vetor cheio
    l->A[novo].chave = ch;
    if (l->inicio == -1)
    { // lista vazia
        l->inicio = novo;
        l->A[novo].prox = -1;
        return true;
    }
    if (ant > -1)
    { // no meio
        l->A[novo].prox = l->A[ant].prox;
        l->A[ant].prox = novo;
        return true;
    }
    else
    { // no inicio
        l->A[novo].prox = l->inicio;
        l->inicio = novo;
    }
    return false;
}

// bool excluirElemListaEnc(int ch, LISTA *l)
// {
//     int ant, i;
//     i = buscaSeqOrdenada(*l, ch, &ant);
//     if (i < 0)
//         return false;
//     if (ant == -1)
//         l->inicio = l->A[i].prox;
//     else
//         l->A[ant].prox = l->A[i].prox;
//     devolverNo(l, i);
//     return true;
// }

// bool inserirElemListaEncOrd(int ch, LISTA *l)
// {
//     int ant, i;
//     i = buscaSeqOrdenada(*l, ch, &ant);
//     if ((l->dispo < 0) || (i != -1))
//         return false;

//     i = obterNo(l);
//     l->A[i].chave = ch;
//     if (l->inicio < 0)
//     {
//         l->inicio = i;
//         l->A[i].prox = -1;
//     }
//     else
//     {
//         if (ant < 0)
//         {
//             l->A[i].prox = l->inicio;
//             l->inicio = i;
//         }
//         else
//         {
//             l->A[i].prox = l->A[ant].prox;
//             l->A[ant].prox = i;
//         }
//     }
//     return true;
// }

bool anexar(LISTALIGEST *l, int ch)
{
    int novo = obterEndereco(&l);
    if (novo == -1)
        return false;
    l->A[novo].chave = ch;
    l->A[novo].prox = -1;
    int i = l->inicio;
    int fim = -1;
    while (i != -1)
    {
        fim = i;
        i = l->A[i].prox;
    }
    if (fim > -1)
    {
        l->A[fim].prox = novo;
    }
    else
    {
        l->inicio = novo;
    }
}