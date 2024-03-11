#include <stdbool.h>

#ifndef AED2_GRAFOMATRIZADJ_H
#define AED2_GRAFOMATRIZADJ_H

#define MAXNUMVERTICES 100
#define AN (-1)
#define VERTICE_INVALIDO (-1)

typedef int Peso;
typedef struct {
    Peso mat[MAXNUMVERTICES][MAXNUMVERTICES];
    int numVertices;
    int numArestas;
} Grafo;

bool inicializaGrafo(Grafo* grafo, int nv);
void imprimeGrafo(Grafo* grafo);
bool insereAresta(Grafo * grafo, int v1, int v2, Peso peso);
bool insereArestaNaoDirecionado(Grafo *grafo, int v1, int v2, Peso peso);
bool existeAresta(Grafo *grafo, int v1, int v2);
bool removeAresta(Grafo *grafo, int v1, int v2, Peso *peso);
bool removeArestaNaoDirecionado(Grafo *grafo, int v1, int v2, Peso *peso);
bool listaAdjVazia(Grafo *grafo, int v);
int proxListaAdj(Grafo *grafo, int v, int atual);

#endif //AED2_GRAFOMATRIZADJ_H
