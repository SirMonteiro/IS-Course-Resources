#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "grafoListaadj.h"

bool inicializaGrafo(Grafo * grafo, int nv) {
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

int obtemNrVertices(Grafo* grafo) {
    return grafo->numVertices;
}

int obtemNrArestas(Grafo* grafo){
    return grafo->numArestas;
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

bool existeAresta(Grafo * grafo, int v1, int v2) {
    if (!(verificaValidadeVertice(grafo, v1) && verificaValidadeVertice(grafo, v2))) return false;
    Apontador p = grafo->listaadj[v1];
    while (p && p->vdest != v2) {
        p=p->prox;
        if (p) return true;
        return false;
    }
}

Peso obtemPesoAresta(Grafo *grafo, int v1, int v2) {
    if (!(verificaValidadeVertice(grafo, v1) && verificaValidadeVertice(grafo, v2))) return AN;
    Apontador p = grafo->listaadj[v1];
    while (p && p->vdest != v2) {
        p = p->prox;
        if (p) return p->peso;
        return AN;
    }
}

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

bool listaAdjVazia(Grafo * grafo, int v) {
    if (!verificaValidadeVertice(grafo, v))
        return false;
    return (grafo->listaadj[v] == NULL);
}

Apontador primeiroListaAdj(Grafo *grafo, int v) {
    return grafo->listaadj[v];
}

Apontador proxListaAdj(Grafo *grafo, int v, Apontador atual) {
    if (!verificaValidadeVertice(grafo, v))
        return false;
    if (!atual) {
        fprintf(stderr, "[proxListaAdj] ERROR - Atual é NULL.\n");
        return VERTICE_INVALIDO;
    }
    return atual->prox;
}

int obtemVerticeDestino(Grafo* grafo, Apontador p) {
    if(!p || !verificaValidadeVertice(grafo, p->vdest)) return -1;
    return p->vdest;
}

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

bool liberaGrafo(Grafo *grafo) {
    int v;
    Apontador p;

    for (int i = 0; i < grafo->numVertices; i++) {
        while((p = grafo->listaadj[v]) != NULL) {
            grafo->listaadj[v] = p->prox;
            p->prox = NULL;
            free(p);
        }
    }

    grafo->numVertices = 0;
    grafo->numArestas = 0;
    free(grafo->listaadj);
    grafo->listaadj = NULL;
}
