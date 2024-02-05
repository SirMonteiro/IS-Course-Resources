#include "pilha.c"

int main()
{
  PILHA *pilha = (PILHA *)malloc(sizeof(PILHA));
  inicializarPilha(pilha);
  printf("Pilha length: %d\n", countPilhaElem(pilha));

  for (int i = 0; i < 10; i++)
  {
    pilhaPUSH(pilha, 10 + 10 * i);
  }

  printf("Pilha length: %d\n", countPilhaElem(pilha));

  for (int i = 0; i < 10; i++)
  {
    printf("Pilha: %d\n", pilhaPOP(pilha));
  }

  printf("Pilha length: %d\n", countPilhaElem(pilha));

  free(pilha);
  return 0;
}