#include <stdbool.h>

#ifndef GRAFOLISTAADJ_H
#define GRAFOLISTAADJ_H

#define MAXNUMVERTICES 100
#define AN (-1)
#define VERTICE_INVALIDO NULL

typedef int Peso;

typedef struct str_aresta {
    int vdest;
    Peso peso;
    struct str_aresta* prox;
} Aresta;

typedef Aresta* Apontador;

typedef struct {
    Apontador* listaadj;
    int numVertices;
    int numArestas;
} Grafo;

bool inicializaGrafo(Grafo* grafo, int nv);
int obtemNrVertices(Grafo* grafo);
int obtemNrArestas(Grafo* grafo);
bool verificaValidadeVertice(Grafo *grafo, int v);
bool insereAresta(Grafo *grafo, int v1, int v2, Peso peso);
bool insereArestaNaoDirecionado(Grafo *grafo, int v1, int v2, Peso peso);
bool existeAresta(Grafo *grafo, int v1, int v2);
Peso obtemPesoAresta(Grafo *grafo, int v1, int v2);
bool removeAresta(Grafo *grafo, int v1, int v2, Peso *peso);
bool removeArestaNaoDirecionado(Grafo *grafo, int v1, int v2, Peso *peso);
bool listaAdjVazia(Grafo *grafo, int v);
Apontador primeiroListaAdj(Grafo *grafo, int v);
Apontador proxListaAdj(Grafo *grafo, int v, Apontador atual);
int obtemVerticeDestino(Grafo *grafo, Apontador p);
void imprimeGrafo(Grafo* grafo);
bool liberaGrafo(Grafo *grafo);

#endif //GRAFOLISTAADJ_H
