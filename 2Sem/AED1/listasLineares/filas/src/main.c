#include "fila.c"

int main()
{
  FILA *fila = malloc(sizeof(NO));
  inicializarFila(fila);
  printf("Fila length: %d\n", filaLength(fila));

  for (int i = 0; i < 10; i++)
  {
    insertFila(fila, 10 + 10 * i);
  }

  // printFila(fila);
  printRecursive(fila->inicio);
  printf("Fila length: %d\n", filaLength(fila));

  for (int i = 0; i < 10; i++)
  {
    printf("Element from Fila: %d\n", getFromFila(fila));
  }
  printf("Fila length: %d\n", filaLength(fila));

  return 0;
}