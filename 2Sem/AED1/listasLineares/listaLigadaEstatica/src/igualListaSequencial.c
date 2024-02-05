#include <stdio.h>
#include <stdbool.h>

#include "listaLigadaEstatica.c"

bool listasIguais(listaSeq *l1, LISTA *l2)
{
    int i1 = 0; // seq
    int i2 = l2->inicio;
    while (i2 != -1 && i1 < l1->nroElem)
    {
        if (l1->A[i1].chave != l2->A[i2].chave)
            return false;
        i1++;
        i2 = l2->A[i2].prox;
    }
    if (i1 < l1->nroElem || i2 != -1)
        return false;
    return true;
}

int main()
{
    listasIguais();
    return 0;
}