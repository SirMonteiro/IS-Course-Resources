#include <stdio.h>

#include "grafoMatrizadj.h"

int main() {
    Grafo g1;
    int numVertices;

    do {
        printf("Digite o n de vertices do grafo\n");
        scanf("%d", &numVertices);
    } while (!inicializaGrafo(&g1, numVertices));

    insereAresta(&g1, 0, 1, 10);
    insereArestaNaoDirecionado(&g1, 1, 2, 20);
    imprimeGrafo(&g1);
    return 0;
}
