#include <stdio.h>
#include <stdlib.h>

int main()
{
  int *teste = (int *)malloc(sizeof(int) * 4);
  // *teste = 1;
  *(teste + sizeof(int) * 2) = 2;
  printf("%i\n", *teste);
  printf("%i\n", *(teste + sizeof(int) * 2));
  printf("%i %i %i %i \n", teste[0], teste[1], teste[2], teste[3]);
  printf("%p\n", teste);
  printf("%p", teste + sizeof(int) * 2);
  printf("\n");
  return 0;
}