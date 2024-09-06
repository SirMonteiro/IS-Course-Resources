#include <stdbool.h>
#include <stdio.h>

#include "grafo_matrizadj.h"

/*
 * Vertices vao de 1 a nv.
 * Preenche as celulas com AN (representando ausencia de aresta)
 * Retorna true se inicializou com sucesso e false caso contrario
 */
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

/*
 * Retorna o numero de vertices dado o grafo.
 */
int obtemNrVertices(Grafo* grafo) {
    return grafo->numVertices;
}

/*
 * Retorna o numero de arestas dado o grafo.
 */
int obtemNrArestas(Grafo* grafo) {
    return grafo->numArestas;
}

/*
 * imprime na tela o grafo com seus pesos.
 */
void imprimeGrafo(Grafo* grafo) {
    for (int i = 0; i < grafo->numVertices; i++) {
        for (int j = 0; j < grafo->numVertices; j++) {
            if (grafo->mat[i][j] == AN) continue;
            printf("V%d -%d-> V%d\n", i, grafo->mat[i][j], j);
        }
    }
}

/*
 * verifica se o numero do vertice e valido no grafo, ou seja, se ele é maior
 * ou igual a zero e menor que o numeror total de vertices do grafo.
 */
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

/*
 * Insere a aresta (v1, v2) com peso "peso" no grafo.
 * Nao verifica se a aresta ja existia (isso deve ser feito pelo usuario antes, se necessario).
 */
bool insereAresta(Grafo * grafo, int v1, int v2, Peso peso) {
    if (!(verificaValidadeVertice(grafo, v1) && verificaValidadeVertice(grafo, v2))) return false;
    grafo->mat[v1][v2] = peso;
    grafo->numArestas++;
    return true;
}

/*
 * Insere a aresta (v2, v1) do grafo nao direcionado caso o insereAresta retorne true.
 * Caso ocorra, retorna true.
 */
bool insereArestaNaoDirecionado(Grafo *grafo, int v1, int v2, Peso peso) {
    if(!insereAresta(grafo, v1, v2, peso)) return false;
    grafo->mat[v2][v1] = peso;
    return true;
}

/*
 * Retorna true se existe a aresta (v1, v2) no grafo e false caso contrario.
 */
bool existeAresta(Grafo *grafo, int v1, int v2) {
    if (grafo->mat[v1][v2] != AN) return true;
    fprintf(stderr, "[existeAresta] WARN - Aresta nao existe.\n");
    return false;
}

/*
 * Retorna o peso da aresta (v1, v2) no grafo se ela existir e AN caso contrario.
 */
Peso obtemPesoAresta(Grafo *grafo, int v1, int v2) {
    if (!(verificaValidadeVertice(grafo, v1) && verificaValidadeVertice(grafo, v2))) return false;
    return grafo->mat[v1][v2];
}

/*
 * Remove a aresta (v1, v2) do grafo colocando AN em sua celula (representando ausencia de aresta).
 * Se a aresta existia, coloca o peso dessa aresta em "peso" e retorna true,
 * caso contrario retorna false (e "peso" é inalterado).
 */
bool removeAresta(Grafo *grafo, int v1, int v2, Peso *peso) {
    if (!(verificaValidadeVertice(grafo, v1) && verificaValidadeVertice(grafo, v2))) return false;
    if (!existeAresta(grafo, v1, v2)) return false;

    *peso = grafo->mat[v1][v2];
    grafo->mat[v1][v2] = AN;
    grafo->numArestas--;
    return true;
}

/*
 * Remove a aresta (v2, v1) do grafo nao direcionado caso o removeAresta() retorne true.
 * Caso ocorra, retorna true.
 */
bool removeArestaNaoDirecionado(Grafo *grafo, int v1, int v2, Peso *peso) {
    if (!removeAresta(grafo, v1, v2, peso)) return false;
    grafo->mat[v2][v1] = AN;
    return true;
}

/*
 * Retorna true se a lista de adjacencia (de vertices adjacentes)
 * do vertice v é vazia, e false caso contrario.
 */
bool listaAdjVazia(Grafo *grafo, int v) {
    if (!verificaValidadeVertice(grafo, v)) return true;

    for (int i = 0; i < grafo->numVertices; i++)
        if (grafo->mat[v][i] != AN) return false;
    return true;
}

/*
 * Trata-se de um iterador sobre a lista de adjacencia do vertice v.
 * Retorna o primeiro vertice adjacente a v ou VERTICE INVALIDO
 * se a lista de adjacencia tiver terminado sem nenhum no.
 */
Apontador primeiroListaAdj(Grafo *grafo, int v) {
    for (int i = 0; i < grafo->numVertices; i++) {
        Apontador p = grafo->mat[v][i];
        if (p != AN) return i;
        // return p;
    }
    return AN;
}

/*
 * Trata-se de um iterador sobre a lista de adjacencia do vertice v.
 * Retorna o proximo vertice adjacente a v, partindo do vertice "atual" adjacente a v
 * ou VERTICE INVALIDO se a lista de adjacencia tiver terminado sem um novo proximo.
 */
Apontador proxListaAdj(Grafo *grafo, int v, Apontador atual) {
    if (!(verificaValidadeVertice(grafo, v) && verificaValidadeVertice(grafo, atual))) return VERTICE_INVALIDO;

    for (int i = atual + 1; i < grafo->numVertices; i++) {
        if (grafo->mat[v][i] != AN) return i;
    }
    return VERTICE_INVALIDO;
}

/*
 * Retorna o vertice de destino, dado p.
 */
int obtemVerticeDestino(Grafo* grafo, Apontador p) {
    if(!verificaValidadeVertice(grafo, p)) return VERTICE_INVALIDO;
    return p;
}

/*
 * Nao faz nada para matriz de adjacencia.
 */
void liberaGrafo(Grafo* grafo) {}
