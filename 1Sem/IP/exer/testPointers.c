#include <stdio.h>
#include <stdlib.h>

int main()
{
  int valor = 101;
  int *valorPointer = &valor;

  printf("Resultado: %p\n", valorPointer);

  return 0;
}
