#include <stdio.h>
#include <stdbool.h>

#include "listaLigadaEstatica.c"

bool VerificaIguais(LISTA *l1, LISTA *l2)
{
    int i1 = l1->inicio;
    int i2 = l2->inicio;
    while (i1 != -1 && i2 != -1)
    {
        if (l1->A[i1].chave != l2->A[i2].chave)
            return false;
        i1 = l1->A[i1].prox;
        i2 = l2->A[i2].prox;
    }
    if (i1 == -1 && i2 == -1)
        return true;
    return false;
}

/*
Dado um elemento i garantidamente existente (i é um indice) mova esse elemento para a frente da lista;
# variação: manda para o final.
*/

bool moverParaFrente(LISTA *l, int i)
{
    if (l->inicio == i)
        return false; // já é o primeiro nó
    int ant;
    int i2 = busca(*l, i, &ant);
    if (i2 == -1)
        return false; // não existe
    l->A[ant].prox = l->A[i].prox;
    l->A[i].prox = l->inicio;
    l->inicio = i;
}

/*
#variação:
(i)     Achar o ultimo elemento da lista
(ii)    Achar atual e seu anterior
(iii)   Ajustar atual->prox = -1;
                ult->prox = atual;
                ant a l->inicio;
*/

bool moverParaFrenteAUX(LISTA *l, int ch, int *ant, int *ult)
{
    /*
    (i)     Achar o ultimo elemento da lista
    (ii)    Achar atual e seu anterior
    */
}

bool moverParaFinal(LISTA *l, int i)
{
    if (l->A[i].prox == -1)
        return false; // já está no final
}

int main()
{
    LISTA l;
    inicializar(&l);
    exibir(l);
    printf("\n");
    inserir(&l, 23);
    exibir(l);
    printf("\n");
    inserir(&l, 32);
    exibir(l);
    printf("\n");
    excluir(&l, 23);
    exibir(l);
    printf("\n");
    return 0;
}