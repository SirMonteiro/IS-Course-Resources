#include <stdio.h>
#include <stdbool.h>

#define MAX 100

typedef struct
{
    int chave;
    // int num; // ...
} registro;

typedef struct
{
    registro A[MAX];
    int nroElem;
} listaSeq;

void inicializar(listaSeq *l)
{
    l->nroElem = 0;
}

// Retorna indice ou -1
int buscaSeq(listaSeq *l, int ch)
{
    int i = 0;
    for (i = 0; i < l->nroElem; i++)
    {
        if (l->A[i].chave == ch)
            return i;
    }

    return -1; // não encontrou
}

bool anexar(listaSeq *l, registro *reg)
{
    if (l->nroElem == MAX)
        return false;
    l->A[l->nroElem] = *reg;
    l->nroElem++;
    return true;
}

bool excluir(listaSeq *l, registro *reg)
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

void exibir(listaSeq *l)
{
    int i;
    // printf("%i", l->nroElem);
    for (int i = 0; i < l->nroElem; i++)
    {
        printf("%d\n", l->A[i].chave);
    }
}

// implementar inserção
// implementar busca binária

bool inserir(listaSeq *l, registro *reg, int i)
{
    if (l->nroElem == MAX || i < 0)
        return false;
    if (l->nroElem == 0)
        anexar(l, reg);
    for (int j = l->nroElem; j > i; j--)
    {
        l->A[j] = l->A[j - 1];
    }
    l->A[i] = *reg;
    l->nroElem++;
    return true;
}

// int buscaBin(listaSeq *l, int ch)
// {
//     int meio;

//     meio = l->nroElem / 2;
//     if (l->A[meio].chave == ch)
//         return meio;
//     while (l->A[meio].chave != ch)
//     {
//         if (l->A[meio].chave == l->A[0].chave || l->A[meio].chave == l->A[l->nroElem - 1].chave)
//             return -1;
//         if (l->A[meio].chave > ch)
//         {
//             meio = meio / 2;
//         }
//         if (l->A[meio].chave < ch)
//         {
//             meio = meio + meio / 2;
//         }
//     }
//     return meio;
// }

int buscaBin(listaSeq *l, int ch)
{
    int meio, inf, sup;
    inf = 0;
    sup = l->nroElem - 1;
    while (inf <= sup)
    {
        meio = (inf + sup) / 2;
        if (l->A[meio].chave == ch)
            return meio;
        else
        {
            if (l->A[meio].chave < ch)
                inf = meio + 1;
            else
                sup = meio - 1;
        }
    }
    return -1;
}

int main()
{
    listaSeq l;
    registro reg, reg2, reg3, reg4, reg5, reg6;
    reg.chave = 1;
    reg2.chave = 2;
    reg3.chave = 3;
    reg4.chave = 4;
    reg5.chave = 5;
    reg6.chave = 6;
    inicializar(&l);
    // exibir(&l);

    // bool anexou = anexar(&l, &reg);
    // printf("anexou? %i\n", anexou);

    // anexou = anexar(&l, &reg2);
    // printf("anexou? %i\n", anexou);

    anexar(&l, &reg);
    anexar(&l, &reg2);
    anexar(&l, &reg3);
    anexar(&l, &reg4);
    anexar(&l, &reg5);

    exibir(&l);
    // bool excluiu = excluir(&l, &reg);
    // printf("excluiu? %i\n", excluiu);
    // exibir(&l);

    // inserir(&l, &reg6, 2);
    // printf("\n");
    // exibir(&l);
    int res = buscaBin(&l, 7);
    printf("O elemento procurado está na posição: %i\n", res);

    return 0;
}
