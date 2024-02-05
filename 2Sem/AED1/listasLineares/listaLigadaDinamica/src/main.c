#include <stdio.h>
#include <stdlib.h>

#include "listaLigadaDinamica.c"

int main()
{
    LISTA_LIG_DIN l1;
    inicializar(&l1);
    LISTA_LIG_DIN l2;
    inicializar(&l2);

    inserir(&l1, 10);
    inserir(&l1, 20);
    inserir(&l1, 30);

    inserir(&l2, 40);
    inserir(&l2, 50);
    inserir(&l2, 60);

    catL1toL2Cloning(&l1, &l2);

    printf("l1\n");
    exibir(&l1);
    printf("l2\n");
    exibir(&l2);

    return 0;
}