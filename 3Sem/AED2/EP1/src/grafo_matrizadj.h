#include <stdbool.h>

#ifndef GRAFOMATRIZADJ_H
#define GRAFOMATRIZADJ_H

#define MAXNUMVERTICES 100
#define AN (-1)
#define VERTICE_INVALIDO (-1)

typedef int Peso;
typedef int Apontador;

typedef struct {
    Peso mat[MAXNUMVERTICES][MAXNUMVERTICES];
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
void liberaGrafo(Grafo* grafo);

#endif //GRAFOMATRIZADJ_H