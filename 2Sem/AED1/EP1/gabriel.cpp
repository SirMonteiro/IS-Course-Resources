#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>

// ######### ESCREVA SEU(S) NROsUSP AQUI
char *nroUSP()
{
    return ("14746450, 14653248");
}

// ######### ESCREVA SEU(S) NOME(S) AQUI
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
    NO *aux = *p;
    while (no)
    {
        printf("%d\n", no->chave);
        // sleep(1);
        if (no->prox == aux)
            break;
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

    NO *p1 = NULL; // inicio 1
    NO *p2 = NULL; // inicio 2

    NO *p1no1 = (NO *)malloc(sizeof(NO));
    NO *p1no2 = (NO *)malloc(sizeof(NO));
    NO *p1no3 = (NO *)malloc(sizeof(NO));
    NO *p1no4 = (NO *)malloc(sizeof(NO));
    NO *p1no5 = (NO *)malloc(sizeof(NO));
    NO *p1no6 = (NO *)malloc(sizeof(NO));
    NO *p1no7 = (NO *)malloc(sizeof(NO));
    NO *p1no8 = (NO *)malloc(sizeof(NO));
    NO *p1no9 = (NO *)malloc(sizeof(NO));
    NO *p1no10 = (NO *)malloc(sizeof(NO));

    NO *p2no1 = (NO *)malloc(sizeof(NO));
    NO *p2no2 = (NO *)malloc(sizeof(NO));
    NO *p2no3 = (NO *)malloc(sizeof(NO));

    p1 = p1no1;
    p1no1->prox = p1no2;
    p1no2->prox = p1no3;
    p1no3->prox = p1no4;
    p1no4->prox = p1no5;
    p1no5->prox = p1no6;
    p1no6->prox = p1no7;
    p1no7->prox = p1no8;
    p1no8->prox = p1no9;
    p1no9->prox = p1no10;
    p1no10->prox = NULL;

    p2 = p2no1;
    p2no1->prox = p2no2;
    p2no2->prox = p2no3;

    // na linha abaixo substituir NULL por p1no1, p1no2, p1no3, etc...
    p2no3->prox = p1no10;
    // p1no1 corresponde ao teste 10
    // p1no2 corresponde ao teste 9
    // p1no3 corresponde ao teste 8
    // p1no4 corresponde ao teste 7
    // p1no5 corresponde ao teste 6
    // p1no6 corresponde ao teste 5
    // p1no7 corresponde ao teste 4
    // p1no8 corresponde ao teste 3
    // p1no9 corresponde ao teste 2
    // p1no10 corresponde ao teste 1

    p1no1->chave = 111;
    p1no2->chave = 121;
    p1no3->chave = 133;
    p1no4->chave = 141;
    p1no5->chave = 155;
    p1no6->chave = 161;
    p1no7->chave = 171;
    p1no8->chave = 183;
    p1no9->chave = 199;
    p1no10->chave = 1108;

    p2no1->chave = 211;
    p2no2->chave = 221;
    p2no3->chave = 234;

    // aqui vc pode incluir codigo para inserir elementos
    // de teste nas listas p1 e p2

    // o EP sera testado com chamadas deste tipo
    removerCompartilhados(&p1, &p2);
    printf("p1:\n");
    exibir(&p1);
    printf("p2:\n");
    exibir(&p2);
}
