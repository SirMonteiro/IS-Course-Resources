#include <stdbool.h>
#include <stdio.h>

#include "grafoMatrizadj.h"

bool inicializaGrafo(Grafo* grafo, int nv) {
    if (nv > MAXNUMVERTICES) {
        fprintf(stderr, "[inicializaGrafo] ERROR - Numero de vertices maior que o maximo permitido de %d.\n", MAXNUMVERTICES);
        return false;
    }

    if (nv <= 0) { 
        fprintf(stderr, "[inicializaGrafo] ERROR - Numero de vertices deve ser positivo.\n");
        return false;
    }

    grafo->numVertices = nv;
    grafo->numArestas = 0;
    for (int i = 0; i < grafo->numVertices; i++) {
        for (int j = 0; j < grafo->numVertices; j++) {
            grafo->mat[i][j] = AN;
        }
    }
    return true;
}

int obtemNrVertices(Grafo* grafo) {
    return grafo->numVertices;
}

int obtemNrArestas(Grafo* grafo) {
    return grafo->numArestas;
}

void imprimeGrafo(Grafo* grafo) {
    for (int i = 0; i < grafo->numVertices; i++) {
        for (int j = 0; j < grafo->numVertices; j++) {
            if (grafo->mat[i][j] == AN) continue;
            printf("V%d -%d-> V%d\n", i, grafo->mat[i][j], j);
        }
    }
}

bool verificaValidadeVertice(Grafo * grafo, int v) {
    if (v < 0) {
        fprintf(stderr, "[verificaValidadeVertice] ERROR - Numero do vertice (%d) nao deve ser negativo.\n", v);
        return false;
    }
    if (v >= grafo->numVertices) {
        fprintf(stderr, "[verificaValidadeVertice] ERROR - Numero do vertice (%d) maior ou igual ao numero total de vertices (%d).\n", v, grafo->numVertices);
        return false;
    }
    return true;
}

bool insereAresta(Grafo * grafo, int v1, int v2, Peso peso) {
    if (!(verificaValidadeVertice(grafo, v1) && verificaValidadeVertice(grafo, v2))) return false;
    grafo->mat[v1][v2] = peso;
    grafo->numArestas++;
    return true;
}

bool insereArestaNaoDirecionado(Grafo *grafo, int v1, int v2, Peso peso) {
    if(!insereAresta(grafo, v1, v2, peso)) return false;
    grafo->mat[v2][v1] = peso;
    return true;
}

bool existeAresta(Grafo *grafo, int v1, int v2) {
    if (grafo->mat[v1][v2] != AN) return true;
    fprintf(stderr, "[existeAresta] WARN - Aresta nao existe.\n");
    return false;
}

Peso obtemPesoAresta(Grafo *grafo, int v1, int v2) {
    if (!(verificaValidadeVertice(grafo, v1) && verificaValidadeVertice(grafo, v2))) return false;
    return grafo->mat[v1][v2];
}

bool removeAresta(Grafo *grafo, int v1, int v2, Peso *peso) {
    if (!(verificaValidadeVertice(grafo, v1) && verificaValidadeVertice(grafo, v2))) return false;
    if (!existeAresta(grafo, v1, v2)) return false;

    *peso = grafo->mat[v1][v2];
    grafo->mat[v1][v2] = AN;
    grafo->numArestas--;
    return true;
}

bool removeArestaNaoDirecionado(Grafo *grafo, int v1, int v2, Peso *peso) {
    if (!removeAresta(grafo, v1, v2, peso)) return false;
    grafo->mat[v2][v1] = AN;
    return true;
}

bool listaAdjVazia(Grafo *grafo, int v) {
    if (!verificaValidadeVertice(grafo, v)) return true;

    for (int i = 0; i < grafo->numVertices; i++)
        if (grafo->mat[v][i] != AN) return false;
    return true;
}

Apontador primeiroListaAdj(Grafo *grafo, int v) {
    for (int i = 0; i < grafo->numVertices; i++) {
        Apontador p = grafo->mat[v][i];
        if (p != AN) return i;
        // return p;
    }
    return AN;
}

Apontador proxListaAdj(Grafo *grafo, int v, Apontador atual) {
    if (!(verificaValidadeVertice(grafo, v) && verificaValidadeVertice(grafo, atual))) return VERTICE_INVALIDO;

    for (int i = atual + 1; i < grafo->numVertices; i++) {
        if (grafo->mat[v][i] != AN) return i;
    }
    return VERTICE_INVALIDO;
}

int obtemVerticeDestino(Grafo* grafo, Apontador p) {
    if(!verificaValidadeVertice(grafo, p)) return VERTICE_INVALIDO;
    return p;
}

void liberaGrafo(Grafo* grafo) {}
