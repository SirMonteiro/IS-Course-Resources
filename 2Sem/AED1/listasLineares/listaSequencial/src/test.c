#include <stdio.h>
#include <stdbool.h>

#include "listaSequencial.c"

int main()
{
    listaSeq l;
    registro reg;
    registro reg2;
    reg.chave = 95;
    reg2.chave = 99;
    inicializar(&l);
    exibir(&l);

    bool anexou = anexar(&l, &reg);
    printf("anexou? %i\n", anexou);

    anexou = anexar(&l, &reg2);
    printf("anexou? %i\n", anexou);

    exibir(&l);
    bool excluiu = excluir(&l, &reg);
    printf("excluiu? %i\n", excluiu);
    printf("\n");
    exibir(&l);

    return 0;
}