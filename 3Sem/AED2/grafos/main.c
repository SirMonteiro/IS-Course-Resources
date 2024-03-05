#include <stdio.h>

#include "grafoMatrizadj.c"

int main() {
    printf("Hello, World!\n");
    Grafo g1;
    int numVertices;

//    inicializaGrafo(&g1, 10);

    do {
        printf("Digite o n de vertices do grafo\n");
        scanf("%d", &numVertices);
    } while (!inicializaGrafo(&g1, numVertices));

    // imprimeGrafo(&g1);
    return 0;
}
