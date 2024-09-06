#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "grafo_listaadj.h"

/*
 * Cria um grafo com n vertices.
 * Aloca espaco para o vetor de apontadores de listas de adjacencias e,
 * para cada vertice, inicializa o apontador de sua lista de adjacencia.
 * Retorna true se inicializou com sucesso e false caso contrario.
 * Vertices vao de 1 a nv.
 */
bool inicializaGrafo(Grafo * grafo, int nv)     {
    if (nv <= 0) {
        fprintf(stderr, "[inicializaGrafo] ERROR - Numero de vertices deve ser positivo.\n");
        return false;
    }
    if (nv > MAXNUMVERTICES) {
        fprintf(stderr, "[inicializaGrafo] ERROR - Numero de vertices maior que o maximo permitido de %d.\n", MAXNUMVERTICES);
        return false;
    }
    if (!(grafo->listaadj = (Aresta **) calloc(nv, sizeof(Aresta*)))) {
        fprintf(stderr, "[inicializaGrafo] ERROR - Falha ao alocar %zu bytes.\n", sizeof(Aresta*));
        return false;
    }
    grafo->numVertices = nv;
    grafo->numArestas = 0;
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
int obtemNrArestas(Grafo* grafo){
    return grafo->numArestas;
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
bool insereAresta(Grafo *grafo, int v1, int v2, Peso peso) {
    Apontador p;

    if (!(verificaValidadeVertice(grafo, v1) && verificaValidadeVertice(grafo, v2))) return false;

    if (!(p = (Apontador) calloc(1, sizeof(Aresta)))) {
        fprintf(stderr, "[insereAresta] ERROR - Falha ao alocar %zu bytes.\n", sizeof(Aresta));
        return false;
    }

    p->vdest = v2;
    p->peso = peso;
    p->prox = grafo->listaadj[v1];
    grafo->listaadj[v1] = p;
    grafo->numArestas++;
    return true;
}

/*
 * Insere a aresta (v2, v1) com peso "peso" no grafo, caso o insereAresta() retornar true.
 * Nao verifica se a aresta ja existia (isso deve ser feito pelo usuario antes, se necessario).
 */
bool insereArestaNaoDirecionado(Grafo *grafo, int v1, int v2, Peso peso) {
    if(!(insereAresta(grafo, v1, v2, peso))) return false;

    Apontador p;
    if(!(p = (Apontador) calloc(1, sizeof(Aresta)))) {
        fprintf(stderr, "[insereAresta] ERROR - Falha ao alocar %zu bytes.\n", sizeof(Aresta));
        return false;
    }

    p->vdest = v1;
    p->peso = peso;
    p->prox = grafo->listaadj[v2];
    grafo->listaadj[v2] = p;
    grafo->numArestas++;
    return true;
}

/*
 * Retorna true se existe a aresta (v1, v2) no grafo e false caso contrario.
 */
bool existeAresta(Grafo * grafo, int v1, int v2) {
    if (!(verificaValidadeVertice(grafo, v1) && verificaValidadeVertice(grafo, v2))) return false;
    Apontador p = grafo->listaadj[v1];
    while (p && p->vdest != v2) {
        p=p->prox;
        if (p) return true;
        return false;
    }
    return false;
}

/*
 * Retorna o peso da aresta (vl, v2) no grafo se ela existir e AN caso contrario.
 */
Peso obtemPesoAresta(Grafo *grafo, int v1, int v2) {
    if (!(verificaValidadeVertice(grafo, v1) && verificaValidadeVertice(grafo, v2))) return AN;
    Apontador p = grafo->listaadj[v1];
    while (p && p->vdest != v2) {
        p = p->prox;
        if (p) return p->peso;
        return AN;
    }
    return AN;
}

/*
 * Remove a aresta (v1, v2) do grafo.
 * Se a aresta existia, coloca o peso dessa aresta em "peso" e retorna true,
 * caso contrario retorna false (e "peso” e inalterado).
 */
bool removeAresta(Grafo * grafo, int v1, int v2, Peso *peso) {
    Apontador p, ant = NULL;

    if (!(verificaValidadeVertice(grafo, v1) && verificaValidadeVertice(grafo, v2))) return false;

    p = grafo->listaadj[v1];
    while(p && p->vdest != v2) {
        ant = p;
        p = p->prox;
    }

    if (!p) return false;
    if (grafo->listaadj[v1] == p) grafo->listaadj[v1] = p->prox;
    else ant->prox = p->prox;
    *peso = p->peso;
    p->prox = NULL;
    free(p);
    p = NULL;
    return true;

}

/*
 * Remove a aresta (v2, v1) do grafo, caso removeAresta() retorne true.
 * Se a aresta existia, coloca o peso dessa aresta em "peso" e retorna true,
 * caso contrario retorna false (e "peso” e inalterado).
 */
bool removeArestaNaoDirecionado(Grafo *grafo, int v1, int v2, Peso *peso) {
    if (!(removeAresta(grafo, v1, v2, peso))) return false;

    Apontador p, ant = NULL;

    p = grafo->listaadj[v2];
    while(p && p->vdest != v1) {
        ant = p;
        p = p->prox;
    }

    if (!p) return false;
    if (grafo->listaadj[v2] == p) grafo->listaadj[v2] = p->prox;
    else ant->prox = p->prox;
    p->prox = NULL;
    free(p);
    p = NULL;

    return true;
}

/*
 * Retorna true se a lista de adjacencia (de vertices adjacentes)
 * do vertice v é vazia, e false caso contrario.
 */
bool listaAdjVazia(Grafo * grafo, int v) {
    if (!verificaValidadeVertice(grafo, v))
        return false;
    return (grafo->listaadj[v] == NULL);
}

/*
 * Retorna o endereco do primeiro vertice adjacente a v.
 */
Apontador primeiroListaAdj(Grafo *grafo, int v) {
    return grafo->listaadj[v];
}

/*
 * Retorna o proximo vertice adjacente a v, partindo do vertice "atual" adjacente a v
 * ou NULL se a lista de adjacencia tiver terminado sem um novo proximo.
 */
Apontador proxListaAdj(Grafo *grafo, int v, Apontador atual) {
    if (!verificaValidadeVertice(grafo, v))
        return false;
    if (!atual) {
        fprintf(stderr, "[proxListaAdj] ERROR - Atual é NULL.\n");
        return VERTICE_INVALIDO;
    }
    return atual->prox;
}

/*
 * Retorna o vertice de destino, dado p.
 */
int obtemVerticeDestino(Grafo* grafo, Apontador p) {
    if(!p || !verificaValidadeVertice(grafo, p->vdest)) return -1;
    return p->vdest;
}

/*
 * Imprime os vertices e arestas do grafo no seguinte formato:
 * v1: (adj11, peso11); (adj12, peso12); ...
 * v2: (adj21, peso21); (adj22, peso22); ...
 * Assuma que cada vértice é um inteiro de até 2 digitos.
 */
void imprimeGrafo(Grafo *grafo) {
    for(int i = 0; i < grafo->numVertices; i++) {
        Apontador p = grafo->listaadj[i];
        printf("V%d: ", i);
        while(p) {
            printf("(%d, %d); ", p->vdest, p->peso);
            p = p->prox;
        }
        printf("\n");
    }
}

/*
 * Libera o espaco ocupado por um grafo.
 */
bool liberaGrafo(Grafo *grafo) {
//    int v;
    Apontador p;

    for (int i = 0; i < grafo->numVertices; i++) {
        while((p = grafo->listaadj[i]) != NULL) {
            grafo->listaadj[i] = p->prox;
            p->prox = NULL;
            free(p);
        }
    }

    grafo->numVertices = 0;
    grafo->numArestas = 0;
    free(grafo->listaadj);
    grafo->listaadj = NULL;
    return true;
}
