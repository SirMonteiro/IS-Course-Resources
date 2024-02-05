#include <stdio.h>

int main()
{
  int value;
  int soma;
  printf("%s", "soma dos números até: ");
  scanf("%i", &value);
  value = value % 2 ? value : value - 1;
  soma = (1 + value) * (value + 1) / 4;
  printf("%i %s", soma, "\n");
  return 0;
}