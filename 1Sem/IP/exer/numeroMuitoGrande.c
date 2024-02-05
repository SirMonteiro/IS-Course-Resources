#include <stdio.h>

int main()
{
  long long unsigned int probably_long_long;
  printf("Tamanho do long long int: %lu (bytes)\n", sizeof(long long unsigned int));
  if (1 == scanf("%llu", &probably_long_long))
    printf("Numero lido: %llu\n", probably_long_long);
  return 0;
}