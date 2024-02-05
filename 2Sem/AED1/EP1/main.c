#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
// #include <unistd.h>

// ######### ESCREVA O NROUSP AQUI
char *nroUSP()
{
    return ("14746450, 14653248");
}

// ######### ESCREVA SEU NOME AQUI
char *nome()
{
    return ("Gabriel Monteiro de Souza, Gabriel Dimant");
}

// elemento da lista
typedef struct estr
{
    int chave;
    struct estr *prox;
} NO;

int tamanhoLista(NO **p)
{
    NO *pno = *p;
    int tam = 0;
    while (pno)
    {
        tam++;
        pno = pno->prox;
    }
    return (tam);
}

void exibir(NO **p)
{
    NO *no = *p;
    while (no)
    {
        printf("%d\n", no->chave);
        // sleep(1);
        no = no->prox;
    }
}

// funcao principal
void removerCompartilhados(NO **p1, NO **p2);

//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------
void removerCompartilhados(NO **p1, NO **p2)
{
    // seu codigo AQUI
    if (!*p1 || !*p2)
        return;
    NO *pno1 = *p1;
    NO *pno2 = *p2;
    NO *ant1 = NULL;
    NO *ant2 = NULL;
    NO *intersec = NULL;
    NO *aux = NULL;

    while (pno1 != pno2->prox && pno1->prox != pno2 && pno1 != pno2)
    {
        ant1 = pno1;
        ant2 = pno2;
        pno1 = pno1->prox;
        pno2 = pno2->prox;
        if (!pno1 || !pno2)
        {
            ant1->prox = *p1;
            ant2->prox = *p2;
            return; // Verify if never merges
        }
        intersec = pno1;

        if (pno1 == pno2->prox)
        {
            ant2 = ant2->prox;
            intersec = pno1;
        }
        else if (pno1->prox == pno2)
        {
            ant1 = ant1->prox;
            intersec = pno2;
        }
    }

    if (!pno1->prox && pno2->prox)
    {
        pno2->prox = *p2;
        free(*p1);
        *p1 = NULL;
    }
    else if (!pno2->prox && pno1->prox)
    {
        pno1->prox = *p1;
        free(*p2);
        *p2 = NULL;
    }
    else if (!pno2->prox && !pno1->prox)
    {
        free(*p1);
        *p1 = NULL;
        *p2 = NULL;
    }

    // Circularização
    if (ant1)
        ant1->prox = *p1;
    if (ant2)
        ant2->prox = *p2;

    // Exclusão
    while (intersec)
    {
        aux = intersec->prox;
        free(intersec);
        intersec = aux;
    }

    return;
}

// por favor nao inclua nenhum codigo a ser entregue abaixo deste ponto

//----------------------------------------------------------------
// use main() apenas para fazer chamadas de teste ao seu programa
//----------------------------------------------------------------
int main()
{
    // aqui vc pode incluir codigo para inserir elementos
    // de teste nas listas p1 e p2

    NO *p1 = NULL; // inicio 1
    NO *p2 = NULL; // inicio 2

    NO *p1no1 = (NO *)malloc(sizeof(NO));
    NO *p1no2 = (NO *)malloc(sizeof(NO));
    NO *p1no3 = (NO *)malloc(sizeof(NO));
    NO *p1no4 = (NO *)malloc(sizeof(NO));

    NO *p2no1 = (NO *)malloc(sizeof(NO));
    NO *p2no2 = (NO *)malloc(sizeof(NO));
    NO *p2no3 = (NO *)malloc(sizeof(NO));
    // NO *p2no4 = (NO *)malloc(sizeof(NO));

    /* caso do pdf
     */
    p1 = p1no1;
    p1no1->prox = p1no2;
    p1no2->prox = p1no3;
    p1no3->prox = p1no4;
    p1no4->prox = NULL;

    p2 = p2no1;
    p2no1->prox = p2no2;
    p2no2->prox = p2no3;
    p2no3->prox = p1no3;

    p1no1->chave = 20;
    p1no2->chave = 30;
    p1no3->chave = 40;
    p1no4->chave = 90;

    p2no1->chave = 200;
    p2no2->chave = 900;
    p2no3->chave = 300;

    /* caso do pdf 2

 p1 = p1no1;
 p1no1->prox = p1no2;
 p1no2->prox = p1no3;
 p1no3->prox = p2no3;

 p2 = p2no1;
 p2no1->prox = p2no2;
 p2no2->prox = p2no3;
 p2no3->prox = p2no4;
 p2no4->prox = NULL;

 p1no1->chave = 20;
 p1no2->chave = 30;
 p1no3->chave = 40;

 p2no1->chave = 200;
 p2no2->chave = 900;
 p2no3->chave = 300;
 p2no4->chave = 800;

 */

    /* lista que se intercepta (1-2)

    p1 = p1no1;
    p1no1->prox = p2no1;

    p2 = p2no1;
    p2no1->prox = NULL;

    p1no1->chave = 10;
    p2no1->chave = 200;
    */

    /* lista que se intercepta (1-1)

    p1 = p1no1;
    p1no1->prox = NULL;

    p2 = p2no1;
    p2no1->prox = p1no1;

    p1no1->chave = 10;
    p2no1->chave = 200;
    */

    /* lista que se intercepta (0)

    p1 = p1no1;
    p1no1->prox = NULL;

    p2 = p1no1;

    p1no1->chave = 10;
    */

    /* listas que nunca se interceptam

    p1 = p1no1;
    p1no1->prox = p1no2;
    p1no2->prox = p1no3;
    p1no3->prox = NULL;

    p2 = p2no1;
    p2no1->prox = p2no2;
    p2no2->prox = p2no3;
    p2no3->prox = NULL;

    p1no1->chave = 20;
    p1no2->chave = 30;
    p1no3->chave = 40;

    p2no1->chave = 200;
    p2no2->chave = 900;
    p2no3->chave = 300;
    */

    // printf("Lista 1:\n");
    // exibir(&p1);
    // printf("Lista 2: \n");
    // exibir(&p2);
    // printf("%d\n", tamanhoLista(&p1));

    // o EP sera testado com chamadas deste tipo
    removerCompartilhados(&p1, &p2);

    exibir(&p1);
    // exibir(&p2);
    // free(p1no1);
    // free(p1no2);
    // free(p1no3);
    // free(p1no4);
    // free(p2no1);
    // free(p2no2);
    // free(p2no3);
}
