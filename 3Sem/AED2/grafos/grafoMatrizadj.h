#ifndef AED2_GRAFO_H
#define AED2_GRAFO_H

#define MAXNUMVERTICES 100
#define AN -1

typedef int Peso;
typedef struct {
    Peso mat[MAXNUMVERTICES][MAXNUMVERTICES];
    int numVertices;
    int numArestas;
} Grafo;

bool inicializaGrafo(Grafo* grafo, int nv);

#endif //AED2_GRAFO_H
