#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#ifdef MATRIZ
#include "grafoMatrizadj.h"
#else
#include "grafoListaadj.h"
#endif

#define MAX_FILENAME 256

typedef struct NODESTRUCT{
    int key;
    struct NODESTRUCT *nxt;
} NODE;

typedef struct {
    NODE *front;
    NODE *back;
} QUEUE;

bool legrafo(Grafo *grafo, char* nomearq) {
    FILE* f = fopen(nomearq, "r");
    if(!f) {
        fprintf(stderr, "[legrafo] ERROR - Falha ao abrir arquivo em \"%s\".\n", nomearq);
        return false;
    }

    int numVertices, numArestas;
    fscanf(f, "%d %d\n", &numVertices, &numArestas);

    inicializaGrafo(grafo, numVertices);

    for (int i = 0; i < numArestas; i++) {
        int v1,v2;
        float peso;
        fscanf(f, "%d %d %f\n", &v1, &v2, &peso);
        insereAresta(grafo, v1, v2, peso);
    }

    fclose(f);
}

void visitaBP(Grafo *grafo, int v, int *tempo, int *cor, int *tdesc, int *tterm, int *antecessor) {
    cor[v] = 1; // 0=branco, 1=cinza, 2=preto
    tdesc[v] = ++(*tempo);

    printf("%d,", v);

    for (Apontador p = primeiroListaAdj(grafo, v); p != VERTICE_INVALIDO; p = proxListaAdj(grafo, v, p)) {
        int adjVertex = obtemVerticeDestino(grafo, p);
        if (cor[adjVertex] == 0) {
            antecessor[adjVertex] = v;
            visitaBP(grafo, adjVertex, tempo, cor, tdesc, tterm, antecessor);
        }
    }

    tterm[v] = ++(*tempo);
    cor[v] = 2;
}

void DFS(Grafo *grafo) {
    // perguntar para o cordeiro se é mais otimizado usar calloc
    int *cor = (int *) malloc(sizeof(int) * grafo->numVertices);
    int *tdesc = (int *) malloc(sizeof(int) * grafo->numVertices);
    int *tterm = (int *) malloc(sizeof(int) * grafo->numVertices);
    int *antecessor = (int *) malloc(sizeof(int) * grafo->numVertices);
    int tempo = 0;
    for(int i = 0; i < grafo->numVertices; i++) {
        cor[i] = 0;
        tdesc[i] = -1;
        tterm[i] = -1;
        antecessor[i] = -1;
    }

    for(int i = 0; i < grafo->numVertices; i++)
        if (cor[i] == 0)
            visitaBP(grafo, i, &tempo, cor, tdesc, tterm, antecessor);

    printf("\x8\nNo\tAnterior\tDescoberta\tTermino\tCor:\n");
    for(int i = 0; i< grafo->numVertices; i++)
        printf("%2i\t%8i\t%10i\t%7i\t%3i\n", i, antecessor[i], tdesc[i], tterm[i], cor[i]);
    printf("\n");

    free(cor);
    free(tdesc);
    free(tterm);
    free(antecessor);
}

void initializeQueue(QUEUE *q) {
    q->front = NULL;
    q->back = NULL;
}

bool enqueue(QUEUE *q, int k) {
    NODE *new = (NODE*) malloc(sizeof(NODE));
    if (!new) {
        fprintf(stderr, "");
        return false;
    }
    new->key = k;
    new->nxt = NULL;
    if (!q->front) q->front = new;
    else q->back->nxt = new;
    q->back = new;
    return true;
}

int dequeue(QUEUE *q) {
    if (!q->front) return -1;
    NODE *aux = (NODE*) malloc(sizeof(NODE));
    aux = q->front;
    q->front = q->front->nxt;
    int k = aux->key;
    free(aux);
    if (!q->front) q->back = NULL;
    return k;
}

void visitaLargura(Grafo *grafo, int s, int *cor, int *antecessor, int *distancia) {
    cor[s] = 1;
    distancia[s] = 0;
    QUEUE queue;
    initializeQueue(&queue);
    enqueue(&queue, s);
    printf("%d,", s); // Print the first node
    while (queue.front) {
        int w = dequeue(&queue);
        for (Apontador p = primeiroListaAdj(grafo, w); p != VERTICE_INVALIDO; p = proxListaAdj(grafo, w, p)) {
            int q = obtemVerticeDestino(grafo, p);
            if (cor[q] == 0) {
                printf("%d,", q);
                cor[q] = 1;
                antecessor[q] = w;
                distancia[q] = distancia[w] + 1;
                enqueue(&queue, q);
            }
            cor[w] = 2;
        }
    }
}

void BFS(Grafo *grafo) {
    int *cor = (int *) malloc(sizeof(int) * grafo->numVertices);
    int *antecessor = (int *) malloc(sizeof(int) * grafo->numVertices);
    int *distancia = (int *) malloc(sizeof(int) * grafo->numVertices);

    for(int i = 0; i < grafo->numVertices; i++) {
        cor[i] = 0;
        antecessor[i] = -1;
        distancia[i] = INT_MIN;
    }
    for (int i = 0; i < grafo->numVertices; i++) {
        if (cor[i] == 0)
            visitaLargura(grafo, i, cor, antecessor, distancia);
    }
    puts("\x8");
}

int main() {
    Grafo g1;
//    int numVertices;

//    do {
//        printf("Digite o n de vertices do grafo\n");
//        scanf("%d", &numVertices);
//    } while (!inicializaGrafo(&g1, numVertices));

    inicializaGrafo(&g1, 8);

    // https://www.geeksforgeeks.org/difference-between-bfs-and-dfs/
    insereAresta(&g1, 0, 3, 40);
    insereAresta(&g1, 0, 2, 30);
    insereAresta(&g1, 0, 1, 10);
    insereAresta(&g1, 3, 7, 90);
    insereAresta(&g1, 2, 6, 80);
    insereAresta(&g1, 1, 5, 70);
    insereAresta(&g1, 1, 4, 60);


//    insereArestaNaoDirecionado(&g1, 0, 1, 10);
//    insereArestaNaoDirecionado(&g1, 0, 2, 20);
//    insereArestaNaoDirecionado(&g1, 1, 2, 30);
//    insereArestaNaoDirecionado(&g1, 1, 3, 40);
////    insereAresta(&g1, 2, 0, 50);
//    insereArestaNaoDirecionado(&g1, 3, 2, 60);
//    insereArestaNaoDirecionado(&g1, 4, 1, 70);
//    insereArestaNaoDirecionado(&g1, 4, 3, 80);


//    insereArestaNaoDirecionado(&g1, 0, 4, 40);
//    insereAresta(&g1, 0, 4, 40);
//    insereArestaNaoDirecionado(&g1, 1, 2, 20);
//    Peso p;
//    bool foi = removeArestaNaoDirecionadoObtendoPeso(&g1, 0, 2, &p);
//    printf("[%d %d]\n", foi, p);

//    imprimeGrafo(&g1);

//    Grafo g2;
//    legrafo(&g2, "grafo.in");
    imprimeGrafo(&g1);
    DFS(&g1);
    BFS(&g1);

    return 0;
}
