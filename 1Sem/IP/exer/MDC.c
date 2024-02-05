#include <stdio.h>

int calculaMDC(int x, int y)
{
  // Adicione seu código aqui

  int temp;
  while (y > 0)
  {
    temp = y;
    y = x % y;
    x = temp;
  }
  return x;

  return 0;
}

int main()
{
  int a, b, mdc;
  printf("Entre com dois valores separados por espaço, enter ou tab:\n");
  scanf("%d %d", &a, &b);

  mdc = calculaMDC(a, b);
  printf("O MDC entre %d e %d é: %d\n", a, b, mdc);

  return 0;
}
