#include <stdio.h>

int calculaMMC(int x, int y)
{
  // Adicione seu código aqui

  int temp;
  int multiplication = x * y;
  while (y > 0)
  {
    temp = y;
    y = x % y;
    x = temp;
  }
  return multiplication / x;

  return 0;
}

int main()
{
  int a, b, mmc;
  printf("Entre com dois valores separados por espaço, enter ou tab:\n");
  scanf("%d %d", &a, &b);

  mmc = calculaMMC(a, b);
  printf("O MMC entre %d e %d é: %d\n", a, b, mmc);

  return 0;
}
