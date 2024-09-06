/*********************************************************************/
/**   ACH2024 - Algoritmo e Estrutura de dados II                   **/
/**   EACH-USP - Primeiro Semestre de 2024                          **/
/**   Turma 01 - Prof.Dra. Ariane Machado Lima                      **/
/**                                                                 **/
/**   Segundo Exercicio-Programa                                    **/
/**                                                                 **/
/**   Gabriel Monteiro de Souza                   14746450          **/
/**                                                                 **/
/**   11/05/2023                                                    **/
/*********************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#ifdef MATRIZ
#include "grafo_matrizadj.h"
#else
#include "grafo_listaadj.h"
#endif

/*
 * Retorna o minimo entre dois numeros com verificacao de tipagem
 */
#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

#define MAX_FILENAME 256 // tamanho máximo do nome do arquivo

typedef struct NODESTRUCT{
    int key;
    struct NODESTRUCT *nxt;
} NODE;

typedef struct {
    NODE *front;
    NODE *back;
} QUEUE;

enum COR {BRANCO, CINZA, PRETO};

bool legrafo(Grafo *grafo, char* nomearq);

void initializeQueue(QUEUE *q);
bool enqueue(QUEUE *q, int k);
int dequeue(QUEUE *q);
bool isEmptyQueue(QUEUE *q);

void BFS(Grafo *grafo);
void visitaLargura(Grafo *grafo, int s, int *cor, int *antecessor, int *distancia);
void printBFSPath(int origem, int destino, int *antecessor, int *distancia);

void DFS(Grafo *grafo);
int compare_function(const void *a,const void *b);
void visitaBP(Grafo *grafo, int v, int *tempo, int *cor, int *tdesc, int *tterm,
              int *antecessor, int *inf, bool *vArticulacao, int *conexos, int *conexosLength, int *visitedLength);
void printDFSPath(int v, int *antecessor);

int main(int argc, char* argv[]) {

    // verifica a quantidade de argumentos, se for diferente de 3, encerra o programa
    if (argc != 3)
    {
        printf("Uso: %s <arquivo_de_entrada> <arquivo_de_saida>\n",
               argv[0]);
        exit(1);
    }

    // copia o nome do arquivo
    char inputFilename[MAX_FILENAME];
    strcpy(inputFilename, argv[1]);

    char outputFilename[MAX_FILENAME];
    strcpy(outputFilename, argv[2]);

    // Abre o arquivo de saida, caso nao abra, fecha o programa reportando o erro
    FILE* outputFile = fopen(outputFilename, "w+");
    if (!outputFile) {
        fprintf(stderr, "[main] ERROR - Falha ao criar arquivo em \"%s\".\n", outputFilename);
        exit(1);
    }
    // Sobrescreve o padrao de saida para o arquivo
    stdout = outputFile;

//    stderr = fopen("./error.txt", "w+");

    // inicializa o grafo, populando ele com o arquivo de entrada
    Grafo grafo;
    if(!legrafo(&grafo, inputFilename)) exit(1);

//    imprimeGrafo(&grafo);

    puts("BL:");
    BFS(&grafo);
    printf("\n");

    puts("BP:");
    DFS(&grafo);
    printf("\n");

    // limpeza de memoria
    liberaGrafo(&grafo);
    fclose(outputFile);

    return 0;
}

/*
 * Popula o grafo "grafo" com os dados lidos no arquivo com o nome "nomearq".
 * Retorna true caso tenha sucesso, e false caso contrario.
 */
bool legrafo(Grafo *grafo, char* nomearq) {
    FILE* f = fopen(nomearq, "r");
    if(!f) {
        fprintf(stderr, "[legrafo] ERROR - Falha ao abrir arquivo em \"%s\".\n", nomearq);
        return false;
    }

    int numVertices, numArestas;
    if(!fscanf(f, "%d %d\n", &numVertices, &numArestas)){
        fprintf(stderr, "[legrafo] ERROR - Falha ao ler o numero de vertices e arestas.\n");
        return false;
    }

    if(!inicializaGrafo(grafo, numVertices)) {
        fprintf(stderr, "[legrafo] ERROR - Falha ao inicializar o grafo.\n");
        return false;
    }

    int v1,v2;
    float peso;
    while(fscanf(f, "%d %d %f\n", &v1, &v2, &peso) != EOF)
        if(!insereArestaNaoDirecionado(grafo, v1, v2, peso)) {
            fprintf(stderr, "[legrafo] ERROR - Falha ao inserir a aresta.\n");
            return false;
        }

    fclose(f);
    return true;
}

/*
 * Inicializa a fila "q".
 */
void initializeQueue(QUEUE *q) {
    q->front = NULL;
    q->back = NULL;
}

/*
 * Insere a chave "k" no final da fila "q",
 * retorna true se der sucesso e false caso contrario.
 */
bool enqueue(QUEUE *q, int k) {
    NODE *new = (NODE*) malloc(sizeof(NODE));
    if (!new) {
        fprintf(stderr, "[enqueue] ERROR - Falha ao alocar %zu bytes.\n", sizeof(NODE));
        return false;
    }
    new->key = k;
    new->nxt = NULL;
    if (!q->front) q->front = new;
    else q->back->nxt = new;
    q->back = new;
    return true;
}
/*
 * Retorna a chave do incio da fila, removendo ele.
 * Retorna -1 caso a fila esteja vazia
 */
int dequeue(QUEUE *q) {
    if (!q->front) return -1;
    NODE *aux = q->front;
    q->front = q->front->nxt;
    int k = aux->key;
    free(aux);
    if (!q->front) q->back = NULL;
    return k;
}
/*
 * Retorna true caso a fila esteja vazia e false caso contrario.
 */
bool isEmptyQueue(QUEUE *q) {
    if (q->front) return false;
    return true;
}
/*
 * Executa recursivamente a busca em largura no grafo dado.
 */
void BFS(Grafo *grafo) {
    int numVertices = obtemNrVertices(grafo);
    int cor[numVertices], antecessor[numVertices], distancia[numVertices];
    bool primeiraVisita = true;

    for(int i = 0; i < numVertices; i++) {
        cor[i] = BRANCO;
        antecessor[i] = -1;
        distancia[i] = INT_MIN;
    }
    for (int i = 0; i < numVertices; i++)
        if (cor[i] == BRANCO) {
            if (!primeiraVisita) printf(" ");
            else primeiraVisita = false;
            visitaLargura(grafo, i, cor, antecessor, distancia);
        }

    printf("\n\nCaminhos BL: \n");
    for (int i = 0, sourceNode = 0; i < numVertices; i++) {
        if (distancia[i] == 0) sourceNode = i;
        printBFSPath(sourceNode, i, antecessor, distancia);
        printf("\n");
    }
}
void visitaLargura(Grafo *grafo, int s, int *cor, int *antecessor, int *distancia) {
    cor[s] = CINZA;
    distancia[s] = 0;
    QUEUE queue;
    initializeQueue(&queue);
    enqueue(&queue, s);
    printf("%d", s);
    while (!isEmptyQueue(&queue)) {
        int w = dequeue(&queue);
        if (w != s) printf(" %d", w);
        for (Apontador p = primeiroListaAdj(grafo, w); p != VERTICE_INVALIDO; p = proxListaAdj(grafo, w, p)) {
            int q = obtemVerticeDestino(grafo, p);
            if (cor[q] == BRANCO) {
                cor[q] = CINZA;
                antecessor[q] = w;
                distancia[q] = distancia[w] + 1;
                enqueue(&queue, q);
            }
            cor[w] = PRETO;
        }
    }
}
void printBFSPath(int origem, int destino, int *antecessor, int *distancia) {
    if (distancia[destino] != 0) {
        printBFSPath(origem, antecessor[destino], antecessor, distancia);
        printf(" %d", destino);
        return;
    }

    printf("%d", origem);
}

/*
 * Executa recursivamente a busca em profundidade no grafo dado.
 */
void DFS(Grafo *grafo) {
    int numVertices = obtemNrVertices(grafo);
    int cor[numVertices], tdesc[numVertices], tterm[numVertices], antecessor[numVertices];
    int inf[numVertices];
    bool vArticulacao[numVertices];
    int conexosLength[numVertices], conexos[numVertices];
    int tempo = 0, visitedLength = 0;
    for(int i = 0; i < numVertices; i++) {
        cor[i] = BRANCO;
        tdesc[i] = 0;
        tterm[i] = 0;
        antecessor[i] = -1;
        vArticulacao[i] = false;
        conexosLength[i] = 0;
        conexos[i] = AN;
    }

    for(int i = 0, counter = 0; i < numVertices; i++)
        if (cor[i] == BRANCO) {
            if (counter) printf(" ");
            visitaBP(grafo, i, &tempo, cor, tdesc, tterm, antecessor, inf, vArticulacao, conexos, &(conexosLength[counter]), &visitedLength);
            counter++;
        }

    printf("\n\nCaminhos BP:\n");
    for(int i = 0; i < numVertices; i++) {
        printDFSPath(i, antecessor);
        printf("\n");
    }

    printf("\nComponentes Conectados:\n");
    for (int i = 0, k = 0; conexosLength[i] != 0; i++) {
        printf("C%d:", i + 1);
//        quickSort(conexos, k, k + conexosLength[i] - 1);
        qsort(conexos + k, conexosLength[i], sizeof(int), compare_function);
        for (int j = 0; j < conexosLength[i]; j++) {
            printf(" %d", conexos[j + k]);
        }
        k+=conexosLength[i];
        printf("\n");
    }

    printf("\nVertices de articulacao:\n");
    bool firstVerticeDeArticulacao = true;
    for (int i = 0; i < numVertices; i++) {
        if (vArticulacao[i]) {
            if (!firstVerticeDeArticulacao)
                printf(" %d", i);
            else {
                printf("%d", i);
                firstVerticeDeArticulacao = false;
            }
        }
    }
}
/*
 * Funcao de comparacao entre dois valores usado
 * para o qsort comparar em ordem crescente.
 */
int compare_function(const void *a,const void *b) {
    int *x = (int *) a;
    int *y = (int *) b;
    return *x - *y;
}
void visitaBP(Grafo *grafo, int v, int *tempo, int *cor, int *tdesc, int *tterm,
              int *antecessor, int *inf, bool *vArticulacao, int *conexos, int *conexosLength, int *visitedLength) {
    int filhos = 0;
    cor[v] = CINZA;
    tdesc[v] = inf[v] = ++(*tempo);

    printf("%d", v);

    conexos[*visitedLength] = v;
    (*visitedLength)++;
    (*conexosLength)++;

    if(!listaAdjVazia(grafo, v)) {
        for (Apontador p = primeiroListaAdj(grafo, v); p != VERTICE_INVALIDO; p = proxListaAdj(grafo, v, p)) {
            int adjVertex = obtemVerticeDestino(grafo, p);
            if (cor[adjVertex] == BRANCO) {
                filhos++;
                antecessor[adjVertex] = v;
                printf(" ");
                visitaBP(grafo, adjVertex, tempo, cor, tdesc, tterm, antecessor, inf, vArticulacao, conexos, conexosLength, visitedLength);

                inf[v] = min(inf[v], inf[adjVertex]);

                if (antecessor[v] != -1 && inf[adjVertex] >= tdesc[v]) {
                    vArticulacao[v] = true;
                }

                if (antecessor[v] == -1 && filhos >= 2) {
                    vArticulacao[v] = true;
                }

            } else if (adjVertex != antecessor[v])
                inf[v] = min(inf[v], tdesc[adjVertex]);
        }
    }

    tterm[v] = ++(*tempo);
    cor[v] = PRETO;
}
void printDFSPath(int v, int *antecessor) {
    if (antecessor[v] == -1) {
        printf("%d", v);
        return;
    }
    printDFSPath(antecessor[v], antecessor);
    printf(" %d", v);
}
