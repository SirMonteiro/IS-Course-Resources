#include <stdio.h>

void conjecturaDeCollatz(int n)
{
  printf("Imprimindo sequencia iniciando em %i\n", n);
  while (n > 1)
  {
    if (n % 2 == 0)
      n = n / 2;
    else
      n = 3 * n + 1;
    printf("%i\n", n);
  }
}

int main()
{

  // NAO ESQUECA DE TROCAR O PARAMETRO PELOS DOIS ULTIMOS DIGITOS DO SEU NUMERO USP MAIS 1
  conjecturaDeCollatz(51);

  return 0;
}