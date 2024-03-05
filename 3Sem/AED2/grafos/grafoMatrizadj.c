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
